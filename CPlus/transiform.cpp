#include <iostream>
#include <deque>
#include <vector>

void test() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    std::deque<int> dq;

    std::transform(arr, arr+6, inserter(dq, dq.begin()), bind2nd(std::plus<int>(), 41));

    std::for_each(dq.begin(), dq.end(), [](int x){printf("%d\n", x);});
}

int main(int argc, char const *argv[]) {

    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    auto iter = std::find_if(v.begin(), v.end(), [](int x){ return x>3;});
    std::cout << *iter << '\n';
    return 0;
}
