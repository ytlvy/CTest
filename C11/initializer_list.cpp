/*
 * @Author: Y.t
 * @Date: 2021-07-26 09:52:41
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-26 10:00:36
 * @Description: 

聚合类型可以进行直接列表初始化，这里需要了解什么是聚合类型：

#### 类型是一个普通数组，如int[5]，char[]，double[]等
#### 类型是一个类，且满足以下条件：
- 没有用户声明的构造函数
- 没有用户提供的构造函数(允许显示预置或弃置的构造函数)
- 没有私有或保护的非静态数据成员
- 没有基类
- 没有虚函数
- 没有{}和=直接初始化的非静态数据成员
- 没有默认成员初始化器
*/
struct A {
public:
   A(int) {}
private:
    A(const A&) {}
};

struct B {
   int a;
   int b;
   int c;
   B(int, int){}
};


struct AA {
int a;
   int b;
   virtual void func() {} // 含有虚函数，不是聚合类
};

struct Base {};
struct BB : public Base { // 有基类，不是聚合类
int a;
   int b;
};

struct CC {
   int a;
   int b = 10; // 有等号初始化，不是聚合类
};

struct DD {
   int a;
   int b;
private:
   int c; // 含有私有的非静态数据成员，不是聚合类
};

struct EE {
int a;
   int b;
   EE() : a(0), b(0) {} // 含有默认成员初始化器，不是聚合类
};

int main() {
   A a(123);
   A b = 123; // error
   A c = { 123 };
   A d{123}; // c++11
   
   int e = {123};
   int f{123}; // c++11
   
   B bb{1, 2, 3};// error，A有自定义的构造函数，不能列表初始化
   return 0;
}