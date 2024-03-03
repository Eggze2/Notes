#include <iostream>
#include <thread>
#include <memory>

void thread_work1(std::string str) {
    std::cout << "str is: " << str << std::endl;
}

// 仿函数作为参数
class background_task {
public:
    void operator()(std::string str) {
        std::cout << "str is: " << str << std::endl;
    }
};

// struct func {
//     int& _i;
//     func(int & i): _i(i) {}
//     void operator()() {
//         for (int i = 0; i < 3; i++) {
//             _i = i;
//             std::cout << "_i is: " << _i << std::endl;
//             std::this_thread::sleep_for(std::chrono::seconds());
//         }
//     }
// };

// void oops() {
//     int some_local_state = 0;
//     func myfunc(some_local_state);
//     std::thread functhread(myfunc);
//     // 存在隐患，访问局部变量，局部变量可能随着}结束而随着主线程退出而回收
//     functhread.detach();
// }

// 使用智能指针的版本
struct func {
    std::shared_ptr<int> _i;
    func(std::shared_ptr<int> i): _i(i) {}
    void operator()() {
        for (int i = 0; i < 3; i++) {
            *_i = i;    // Dereference shared_ptr to access the value
            std::cout << "_i is: " << *_i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

void oops() {
    auto some_local_state = std::make_shared<int>(0);   // Use shared_ptr to manage the memory
    func myfunc(some_local_state);
    std::thread functhread(myfunc);
    functhread.detach();
}

void catch_exception() {
    int some_local_state = 0;
    func myfunc(std::make_shared<int>(some_local_state));
    std::thread functhread { myfunc };
    try {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } catch (std::exception& e) {
        functhread.join();
        throw;
    }
    functhread.join();
}

// 采用RAII技术，保证线程对象析构的时候等待线程运行结束，回收资源
class thread_guard {
private:
    std::thread& _t;
public: 
    explicit thread_guard(std::thread& t): _t(t) {}
    ~thread_guard() {
        if (_t.joinable()) {
            _t.join();
        }
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void auto_guard() {
    int some_local_state = 0;
    func myfunc(std::make_shared<int>(some_local_state));
    std::thread t(myfunc);
    thread_guard g(t);
    std::cout << "auto guard finished\r\n" << std::endl;
}

void print_str(int n, const std::string& str) {
    for (int i = 0; i < n; ++i) {
        std::cout << str << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Be cautious when using implicit conversions
/*
定义一个线程变量thread t时，传递给这个线程的参数buffer会被保存到thread的成员变量中。
而在线程对象t内部启动并运行线程时，参数才会被传递给调用函数print_str。
而此时buffer可能随着}运行结束而释放了。
*/
void danger_oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    // 在线程内部将char const* 转化为std::string
    // 指针常量  char * const  指针本身不能变
    // 常量指针  const char * 指向的内容不能变
    std::thread t(print_str, 3, buffer);
    t.detach();
    std::cout << "danger oops finished" << std::endl;
}

void safe_oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    std::thread t(print_str, 3, std::string(buffer));
    t.detach();
}

void change_param(int& param) {
    param++;
}

void ref_oops(int some_param) {
    std::cout << "before change, param is: " << some_param << std::endl;
    std::thread t(change_param, std::ref(some_param));
    t.join();
    std::cout << "after change, param is: " << some_param << std::endl;
}

class X
{
public:
    void do_lengthy_work() {
        std::cout << "do_lengthy_work " << std::endl;
    }
};

void bind_class_oops() {
    X my_x;
    std::thread t(&X::do_lengthy_work, &my_x);
    t.join();
}

void deal_unique(std::unique_ptr<int> p) {
    std::cout << "unique ptr data is " << *p << std::endl;
    (*p)++;
    std::cout << "after unique ptr data is " << *p << std::endl;
}

void move_oops() {
    auto p = std::make_unique<int>(100);
    std::thread  t(deal_unique, std::move(p));
    t.join();
    //不能再使用p了，p已经被move废弃
    // std::cout << "after unique ptr data is " << *p << std::endl;
}

// 对于std::thread C++ 不允许其执行拷贝构造和拷贝赋值, 
// 所以只能通过移动和局部变量返回的方式将线程变量管理的线程转移给其他变量管理
// 下面是线程归属权转移的例子
void some_function() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void some_other_function() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



int main() {
    // std::thread t(hello);
    // t.join();

    std::string hellostr = "hello world";

    // std::thread t1(thread_work1, hellostr);
    // t1.join();

    // std::thread t2{background_task()};
    // t2.join();
    // std::thread t2(background_task(), hellostr);
    // t3.join();

    // std::thread t4([](std::string str) {
    //     std::cout << "str is: " << str << std::endl;
    // }, hellostr);
    // t4.join();

    // oops();
    // std::this_thread::sleep_for(std::chrono::seconds(4));   // 防止主线程退出过快，需要停顿一下，让子线程跑起来detach

    // catch_exception();

    // auto_guard();
    // std::this_thread::sleep_for(std::chrono::seconds(6));   // 防止主线程退出过快，需要停顿一下，让子线程跑起来detach

    // int some_param = 10;
    // safe_oops(some_param);
    // std::this_thread::sleep_for(std::chrono::seconds(4));

    // ref_oops(some_param);

    // 1 t1绑定some_function
    std::thread t1(some_function);
    // 2 转移t1的线程所有权给t2，转移后t1不再管理线程
    std::thread t2 = std::move(t1);
    // 3 t1可以继续绑定其他线程，执行some_other_function
    t1 = std::thread(some_other_function);
    // 4 创建一个线程变量t3
    std::thread t3;
    // 5 转移t2的线程所有权给t3，转移后t2不再管理线程
    t3 = std::move(t2);
    // 6 转移t3的线程所有权给t1，转移后t3不再管理线程
    t1 = std::move(t3);
    std::this_thread::sleep_for(std::chrono::seconds(2000));   // 规避主函数退出引发崩溃的问题
    // 但程序仍然会崩溃，此时说明是步骤6导致的崩溃
    // 由于t1已经管理了一个线程，再次将t3的线程所有权转移给t1时，t1会调用std::terminate()终止程序
    
    return 0;
}



