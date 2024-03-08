#include <iostream>
#include <thread>

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