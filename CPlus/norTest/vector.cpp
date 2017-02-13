#include <iostream>
#include <vector>


void eraseTest() {
    std::vector<int> myvector;
    for (int i=1; i<=10; i++) myvector.push_back(i);

    // // erase the 6th element
    // myvector.erase (myvector.begin()+5);
    //
    // // erase the first 3 elements:
    // myvector.erase (myvector.begin(),myvector.begin()+3);


    for (auto iter=myvector.begin(); iter != myvector.end();) {
        if(*iter > 3 && *iter < 6) {
            iter = myvector.erase(iter);
        }
        else {
            iter ++;
        }
    }

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
    std::cout << '\n';

}

int main(int argc, char *argv[]) {
    eraseTest();

    return 0;
}
