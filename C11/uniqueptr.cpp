/*
 * @Author: Y.t
 * @Date: 2023-01-22 19:43:21
 * @LastEditors: Y.t
 * @LastEditTime: 2023-01-22 20:01:28
 * @Description: 
 */

#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Foo {
    public:
    string name;
    string title;
    string desc;

    public:
    explicit Foo(string name, string title): name(name), title(title){

    }

    ~Foo (){
        cout<<"delete Foo"<<endl;
    }
};

unique_ptr<Foo> makeFoo() {
    return make_unique<Foo>("aaaa", "bbbb");
} 

int main() {

    unique_ptr<Foo> ptr;
    for (size_t i = 0; i < 10; i++)
    {
        ptr = makeFoo();
        cout << ptr->name << ptr->desc << " " << endl;
    }
}