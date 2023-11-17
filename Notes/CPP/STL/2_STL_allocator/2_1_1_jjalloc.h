// file: 2jjalloc.h

#ifndef __JJALLOC__
#define __JJALLOC_

#include <new>      // for placement new
#include <cstddef>  // for ptrdiff_t, size_t
#include <cstdlib>  // for exit()
#include <climits>  // for UINT_MAX
#include <iostream> // for cerr
using namespace std;

// 在全局命名空间中有一个自带的、隐藏的 operator new 专门用来分配内存。
// 默认情况下编译器会将 new 这个关键字翻译成这个 operator new 和相应的构造函数。
// 但在有的情况下，用户自己会在类中重载 operator new ，这种情况下，编译器默认会使用类中重载的 operator new
// （本质上因为编译器会从命名空间由内而外查找自己想要的函数，选用第一个）。
// 如果我们想要继续使用默认的 operator new ，就应该写成 ::new 字面意思就是调用最外层命名空间中的 operator new
// 值得一提的是最外层的（也是默认的）operator new 也是可以被重载的。通过这种方式我们可以改变所有 new 的部分行为。

namespace JJ {
    // 配置空间，足以储存n个T对象。第二自变量是个提示。
    // 可能会利用它来增进区域性（locality），或完全忽略之。
    template <class T>
    inline T* _allocate(ptrdiff_t size, T*) {
        /**
         * set_new_handler 是一个 C++ 标准库函数，
         * 用于设置 new 操作符在无法分配足够内存时所调用的函数。
         * 这个函数接受一个函数指针作为参数，这个函数指针指向的函数没有返回值并接受无参数。
         * 在代码 set_new_handler(0); 中，
         * 将 new 操作符的处理函数设置为 0，也就是 NULL。
         * 这意味着当 new 操作符无法分配足够的内存时，程序将不会调用任何函数，
         * 而是直接抛出 std::bad_alloc 异常。
        */
        set_new_handler(0);
        // 计算需要分配的字节数，然后调用全局的 new 操作符分配内存，
        // 将返回的 void* 指针转换为 T* 指针，然后将这个指针存储在 tmp 中
        T *tmp = (T *)(::operator new((size_t)(size * sizeof(T))));
        if (tmp == 0) {
            cerr << "out of memory" << endl;
            exit(1);
        }
        return tmp;
    }

    // 归还先前配置的空间
    template <class T>
    inline void _deallocate(T* buffer) {
        ::operator delete(buffer);
    }

    // 等同于 new(const void*) p) T(x)
    template <class T1, class T2>
    inline void _construct(T1* p, const T2& value) {
        /**
         * 在已经分配好的内存 p 上构造一个新的 T1 类型的对象。
         * 这是通过 "placement new" 来实现的。
         * "placement new" 是一种特殊的 new 表达式，
         * 它接受一个额外的参数，
         * 这个参数是一个已经分配好的内存地址。
         * "placement new" 不会分配新的内存，
         * 而是在这个已经分配好的内存上构造对象。
         * 在这个函数中，new (p) T1(value); 这行代码就是在 p 指向的内存上构造一个 T1 类型的对象，
         * 并且使用 value 作为构造函数的参数
        */
        new (p) T1(value);   // placement new. invoke ctor of T1
    }

    // 等同于 p->~T()。
    template <class T>
    inline void _destroy(T* ptr) {
        ptr->~T();
    }

    template <class T>
    class allocator {
    public:
        typedef T          value_type;
        typedef T *        pointer;
        typedef const T *  const_pointer;
        typedef T &        reference;
        typedef const T &  const_reference;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;

        // rebind allocator of type U
        /**
         * 在 C++ 的内存分配器模型中，rebind 是一个常见的模式。
         * 它的主要作用是将一个分配器的类型参数转换为另一个。
         * 例如，如果你有一个 allocator<int>，
         * 你可以使用 allocator<int>::rebind<double>::other 来得到一个 allocator<double>。
         * 这个功能在泛型编程中非常有用，
         * 因为它允许我们在不知道具体类型的情况下创建分配器。
         * 例如，如果我们正在编写一个模板类，我们可能不知道用户会使用什么类型的分配器，
         * 但是我们可以使用 rebind 来确保我们总是得到正确类型的分配器。
        */
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        // hint used for locality. ref. [Austern], p189
        pointer allocate(size_type n, const void* hint=0) {
            return _allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p, size_type n) {
            _deallocate(p);
        }

        void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        void destroy(pointer p) {
            _destroy(p);
        }

        // 传回某个对象的地址。a.address(x) 等同于 &x
        pointer address(reference x) {
            return (pointer)&x;
        }

        // 传回某个const对象的地址。a.address(x) 等同于 &x
        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }

        // 传回可成功配置的最大量
        size_type max_size() const {
            return size_type(UINT_MAX / sizeof(T));
        }
    };
}
#endif
