/*
 * @Author: Y.t
 * @Date: 2021-07-26 10:06:26
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-26 10:08:50
 * @Description: 
 * 
 * 
 * 折叠表达式
 * 在C++中通过折叠表达式可以更容易的在可变参数模板中处理可变参数
 * 函数体中的三个点触发折叠。它会针对可变参数中的每个参数调用print()，对print()的每个调用用逗号分隔
 * 例如对于func(1, 2, 3)，函数内的折叠表达式会展开成这样
 * (print(1), (print(2), print(3)));
 */
#include <iostream>

void print(int i) {
    std::cout << i << " ";
}

template<typename... T>
void func(const T&... args) {
    (print(args), ...);
    std::cout << "\n";
}

template<typename... T>
void func1(const T&... args) {
    ((std::cout << args << " "), ...);
    std::cout << "\n";
}


template<typename T, typename... Tn>
int sum(const T& v, const Tn&... values) {
    return (v + ... + values);
}

template<typename... Tn>
int sum2(const Tn&... values) {
    return (... + values);
}

template <typename... Values>
double allTrue(const Values&... values) { 
    return (... && values); 
}

template <typename... Values>
double anyTrue(const Values&... values) { 
    return (... || values); 
}

int main() {
    func(1, 2, 3);
    std::cout << "Hello World \n";

    func1(1, 2, 3);
    std::cout << "Hello World \n";

    std::cout << sum(1, 2, 3, 4) << "\n";
    std::cout << sum2(1, 2, 3, 4) << "\n";
    std::cout << "Hello World \n";

    std::cout << allTrue(1, 1, 0) << allTrue(1, 1) << allTrue() << "\n"; // 011
    std::cout << anyTrue(1, 1, 0) << anyTrue(0, 0) << anyTrue() << "\n"; // 100
}