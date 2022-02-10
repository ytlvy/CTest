/*
 * @Author: Y.t
 * @Date: 2021-07-28 17:21:29
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-28 19:39:43
 * @Description: 
 * clang -Xclang -fdump-record-layouts -stdlib=libc++ -c model.cc // 查看对象布局
 * clang -Xclang -fdump-vtable-layouts -stdlib=libc++ -c model.cc // 查看虚函数表布局
 */
#include<iostream>

struct Base {
   Base() = default;
   ~Base() = default;
   
   void Func() const {std::cout<<"Func"<<std::endl;}

   int a;
   int b;
};

int main() {
   Base a;
   a.Func();
   return 0;
}