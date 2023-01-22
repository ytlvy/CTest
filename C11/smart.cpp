/*
 * @Author: Y.t
 * @Date: 2023-01-22 11:41:04
 * @LastEditors: Y.t
 * @LastEditTime: 2023-01-22 12:26:35
 * @Description: 
 */
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {

    auto pNico = make_shared<string>("nico");
    auto pJutta = make_shared<string>("jutta");

    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    vector <shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);


    for(auto ptr: whoMadeCoffee) {
        cout << *ptr << " ";
    }
    cout << endl;

    *pNico = "Nicolai";

    for(auto ptr: whoMadeCoffee) {
        cout << *ptr << " ";
    }
    cout << endl;

    cout << "use count" << whoMadeCoffee[0].use_count() << endl;
}
