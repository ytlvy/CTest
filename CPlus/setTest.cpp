#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct StringPtrLess: public binary_function<const string *, const string *, bool> {
    bool operator()(const string *ps1, const string *ps2) const {
        return *ps1 < *ps2;
    }
};

struct DereferenceLess {
    template<typename PtrType>
    bool operator()(PtrType pT1, PtrType pT2) const {
        return *pT1 < *pT2;
    }
};

void testString() {
    set<string *, DereferenceLess>ssp;

    ssp.insert(new string("Anteater"));
    ssp.insert(new string("Wombat"));
    ssp.insert(new string("Lemur"));
    ssp.insert(new string("Penguin"));

    // for (auto iter = ssp.begin(); iter != ssp.end(); iter++) {
    //     cout<< **iter<<endl;
    // }

    for_each(ssp.begin(), ssp.end(), [](const string *ps){std::cout << *ps << '\n';});
}
void testErase() {

    int x[] = {1, 2, 3, 4, 5};
    vector<int> v(x, x+5);

    for_each(v.begin(), v.end(), [](int i){printf("%d\t", i);});
    cout<<endl;

    remove(v.begin(), v.end(), 3);
    for_each(v.begin(), v.end(), [](int i){printf("%d\t", i);});
    cout<<endl;

    v.erase(v.begin() + 2);
    for_each(v.begin(), v.end(), [](int i){printf("%d\t", i);});
    cout<<endl;
}

void testInsert() {
    set<int, less_equal<int>> s;
    s.insert(10);

}


int main(int argc, char const *argv[]) {

    testErase();
    return 0;
}
