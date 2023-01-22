/*
 * @Author: Y.t
 * @Date: 2023-01-22 20:10:33
 * @LastEditors: Y.t
 * @LastEditTime: 2023-01-22 21:32:31
 * @Description: 
 */
#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
using namespace std;

class Bar {
    public:
    string name;
    string title;
    
    Bar(string name): name(name){
        cout << "create bar:" << name << endl;
    }

    ~ Bar() {
        cout<<"delete Bar"<<endl;
    }

};

class Foo {
    public:
    unique_ptr<Bar> ptr1;
    unique_ptr<Bar> ptr2;

    public:
    Foo(string name1, string name2): ptr1(new Bar(name1)), ptr2(new Bar(name2)) {
        
    }

    Foo(const Foo& x): ptr1(new Bar(*x.ptr1)), ptr2(new Bar(*x.ptr2)) {

    }

    const Foo& operator= (const Foo& x) {
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;

        return *this;
    }
};

int main() {
    Foo x{"John", "Lei"};
    Foo y{"Jay", "Shore"};

    // cout<<x.ptr1->name<<endl;
    // cout<<y.ptr1->name<<endl;
    
    y = x;
    cout<<x.ptr1->name<< &(x.ptr1->name) << endl;
    cout<<y.ptr1->name<< &(y.ptr1->name) << endl;

    printf("%p %p \r\n", &(x.ptr1->name), &(y.ptr1->name));

    x.ptr1.reset();
    x.ptr2.reset();
    cout<<y.ptr1->name<<endl;
}