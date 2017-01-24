#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> plusOneNew(std::vector<int> &digits);

    std::vector<int> plusOne(std::vector<int> &digits) {
        std::vector<int> res(digits.size(), 0);
        int sum = 0;
        int one = 1;
        for(int i =  digits.size() - 1; i >= 0; i--) {
            sum = one + digits[i];
            one = sum / 10;
            res[i] = sum % 10;
        }

        if(one > 0) {
            res.insert(res.begin(), one);
        }
        return res;
    }
};

std::vector<int> Solution::plusOneNew(std::vector<int> &digits) {
    std::vector<int> res(digits.size(), 0);
    int sum = 0;
    int carry = 1;

    auto iter = digits.rbegin();
    auto r_iter = res.rbegin();
    for (; iter != digits.rend(); iter++, r_iter++) {
        sum = *iter + carry;
        if (sum > 9) {
            *r_iter = sum - 10;
            carry = 1;
        }
        else {
            *r_iter = sum;
            carry = 0;
        }
    }

    if (carry) {
        res.insert(res.begin(), 1);
    }

    return res;
}
