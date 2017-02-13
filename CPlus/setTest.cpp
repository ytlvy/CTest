#include <iostream>
#include <set>

using namespace std;

struct StringPtrLess: public binary_function<const string *, const string *, bool> {
    bool operator()(const string *ps1, const string *ps2) const {
        return *ps1 < *ps2;
    }
};

void testString() {
    set<string *, StringPtrLess>ssp;

    ssp.insert(new string("Anteater"));
    ssp.insert(new string("Wombat"));
    ssp.insert(new string("Lemur"));
    ssp.insert(new string("Penguin"));

    // for (auto iter = ssp.begin(); iter != ssp.end(); iter++) {
    //     cout<< **iter<<endl;
    // }

    for_each(ssp.begin(), ssp.end(), [](const string *ps){std::cout << *ps << '\n';});
}


int main(int argc, char const *argv[]) {

    testString();
    return 0;
}
