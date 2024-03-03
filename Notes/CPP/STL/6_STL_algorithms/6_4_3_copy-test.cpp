// file: 6copy-test.cpp

#include <iostream> // for cout
#include <algorithm> // for copy()
#include <vector>
#include <deque>
#include <list>
// #include "string.h"

using namespace std;

class C {
public:
    C() : _data(3) { } 
    // 显式定义了构造函数，所以是 non-trivial ctor
    // 没有显式定义dtor/copy/assignemt所以都是trivial

private:
    int _data;
};

class String {
public:
    // 需要定义无参构造函数
    String() : _data("") {} 

    // 显式定义了构造函数，所以是non-trivial ctor
    String(string s) : _data(s) { } 
    
    // 显式定义了构造函数，所以是non-trivial ctor
    String(const char* c) : _data(c) { }
    
    // 有显式定义assignemt所以是non-trivial
    String& operator=(const String& S) {
        _data = S._data;
        return *this;
    }

    // 有显式定义assignemt所以是non-trivial
    String& operator=(const char* c) {
        _data = c;
        return *this;
    }

private:
    string _data;
};

int main() {
    const char ccs[5] = {'a', 'b', 'c', 'd', 'e'};
    char ccd[5];
    // 调用copy(const char*)
    copy(ccs, ccs + 5, ccd);

    const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'};
    wchar_t cwcd[5];
    copy(cwcs, cwcs + 5, cwcd);
    // 调用copy(const wchar_t*)

    int ia[5] = {0, 1, 2, 3, 4};
    copy(ia, ia + 5, ia);
    // 调用
    // copy()
    //   __copy_dispatch(T*, T*)
    //     __copy_t(__true_type)

    // list 迭代器为 InputIterator
    list<int> ilists(ia, ia + 5);
    list<int> ilistd(5);
    copy(ilists.begin(), ilists.end(), ilistd.begin());
    // 调用
    // copy()
    //   __copy_dispatch()
    //     __copy(input_iterator)

    // vector迭代器为原生指针
    vector<int> ivecs(ia, ia + 5);  // vector的ctor会调用copy
    vector<int> ivecd(5);
    copy(ivecs.begin(), ivecs.end(), ivecd.begin());
    // copy()
    //   __copy_dispatch(T*, T*)
    //     __copy_t(__true_type)    为什么不是__copy(random_access_iterator)
    //                              因为是原生指针

    // class C具备trivial operator=
    C c[5];
    vector<C> Cvs(c, c + 5);
    vector<C> Cvd(5);
    copy(Cvs.begin(), Cvs.end(), Cvd.begin());
    // copy()
    //   __copy_dispatch(T*, T*)
    //     __copy_t(_false_type)    
    //       __copy_d()             
    
    // 为什么不是__true_type
    // 因为编译器不一定能验证自定义类的类型特性，所以
    // 被视为拥有non-trivial ctor/dtor/operator=
    // 需要自己手动为class C做特化版本。
    // 如果自定义的类 C 没有默认的拷贝构造函数和赋值操作符，
    // 或者这些函数的实现不支持直接内存复制（即不是trivial的），
    // std::copy() 就无法通过简单的内存复制来执行元素的复制操作。

    // deque迭代器为random access iterator
    deque<C> Cds(c, c + 5);
    deque<C> Cdd(5);
    copy(Cds.begin(), Cds.end(), Cdd.begin());
    // copy()
    //   __copy_dispatch()
    //     __copy(random_access_iterator)
    //       __copy_d()

    // string拥有non-trivial opeartor=
    vector<String> strvs(5);
    vector<String> strvd(5);
    // 需要重载operator(const char*)
    strvs[0] = "jjhou";  
    strvs[1] = "grace";
    strvs[2] = "david";
    strvs[3] = "jason";
    strvs[4] = "jerry";
    copy(strvs.begin(), strvs.end(), strvd.begin());
    // copy()
    //   __copy_dispatch(T*, T*)
    //     __copy_t(_false_type)    
    //       __copy_d()
    /**
     * 之所以不是__copy(random_access_iterator)
     * strvd 是一个空的 vector<String>，容器大小为 5，
     * 但是里面的元素都是默认构造的空字符串。
     * 在调用 copy 函数时，strvd 的迭代器指向的区间并没有足够的空间
     * 用来存储从 strvs 复制过来的元素。这就导致了未定义行为。
    */

    // deque迭代器为random access iterator
    deque<String> strds(5);
    deque<String> strdd(5);
    // 需要定义String(const char*)
    strds.push_back("jjhou"); 
    strds.push_back("grace");
    strds.push_back("david");
    strds.push_back("jason");
    strds.push_back("jerry");
    copy(strds.begin(), strds.end(), strdd.begin());
    // copy()
    //   __copy_dispatch()
    //     __copy(random_access_iterator)
    //       __copy_d()
}