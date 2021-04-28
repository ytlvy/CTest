#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include "common.h"

using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

    int singleNum(vector<int> &nums);
    void testSingleNum(void);

    uint32_t reverseBits(uint32_t n);
    void testReverseBits(void);

    int hamingWeight(uint32_t n);
    void testhamingWeight(void);

    int rangeBitwiseAnd(int begin, int end);
    void testRangeBitwiseAnd();


    bool isPowerOfTwo(int n);
    vector<int> singleNumber3(vector<int> &nums);
    void testSignleNumber3();


    int maxProduct(vector<string>& words);
    void testMaxProduct();

    int totalHamingDistance(vector<int> &nums);
    vector<int> findErrorNUms(vector<int> &nums);

    vector<string> readBinaryMatch(int num);

    char findTheDifference(string s, string t);

    bool validUtf8(vector<int> &data);
    private:
    int bit_count(int bits);
};

void Solution::testSignleNumber3() {
    vector<int> v{1, 2, 2, 3, 3, 4, 5, 6, 7};

    auto res = singleNumber3(v);
    cout<< res[0] <<" " << res[1] <<endl;
}

int Solution::maxProduct(vector<string>& words) 
{
    sort(words.begin(), words.end(), [](const string& a, const string& b){
        return a.length() > b.length();
    });

    vector<int> bits(words.size());
    for (size_t i = 0; i < words.size(); i++)
    {
        for(const auto& c: words[i]) {
            bits[i] |= (1 << (c - 'a'));
        }
    }

    int max_product = 0;
    for (size_t i = 0; i+1 < words.size()&& pow(words[i].length(), 2)>max_product; i++)
    {
        for(int j= i+1; j<words.size() && words[i].length()*words[j].length()>max_product;++j) {
            if(!(bits[i] & bits[j])) {
                max_product = words[i].length() * words[j].length();
            }
        }
    }

    return max_product;
    
}

void Solution::testMaxProduct() 
{
    vector<string> v {"a","ab","abc","d","cd","bcd","abcd"};

    cout<<"testMaxProduct:"<<endl;
    cout<<maxProduct(v)<<endl;
}

int Solution::totalHamingDistance(vector<int> &nums) 
{
    int res = 0;
    for (int i = 0; i < 8 * sizeof(int); i++)
    {
        vector<int> counts(2);
        for (const auto &num :nums)
        {
            ++ counts[(num >> i) & 1];
        }

        res += counts[0] * counts[1];        
    }

    return res;
}

vector<int> Solution::findErrorNUms(vector<int> &nums) 
{
    int x_xor_y = 0;
    for (size_t i = 0; i < nums.size(); i++)
    {   
        x_xor_y ^= nums[i] ^ (i+1);
    }


    int bit = x_xor_y & ~(x_xor_y - 1);
    vector<int> res(2);
    for (size_t i = 0; i < nums.size(); i++)
    {
        res[static_cast<bool>(nums[i] & bit)] ^= nums[i];
        res[static_cast<bool>(i+1) & bit] ^= i+1;
    }

    if(find(nums.begin(), nums.end(), res[0]) == nums.end()) {
        swap(res[0], res[1]);
    }

    return res;
}

vector<string> Solution::readBinaryMatch(int num) 
{
    vector<string> res;
    for (size_t h = 0; h < 12; h++)
    {
        for (size_t m = 0; m < 60; m++)
        {
            if(bit_count(h) + bit_count(m) == num) {
                const auto hour = to_string(h);
                const auto minute = m < 10 ? "0" + to_string(m) : to_string(m);
                res.emplace_back(hour + ":" + minute);
            }
        }
        
    }
    
    return res;
}

char Solution::findTheDifference(string s, string t) 
{
    return accumulate(s.begin(), s.end(), 0, bit_xor<int>()) ^
    accumulate(t.begin(), t.end(), 0, bit_xor<int>());
}

Solution::validUtf8(vector<int> &data) 
{
    
}

int Solution::bit_count (int bits) {
    int count = 0;
    for (; bits; bits &= (bits-1))
    {
        count++;
    }

    return count;
}

vector<int> Solution::singleNumber3(vector<int> &nums) 
{
    const auto x_xor_y = accumulate(nums.begin(), nums.end(), 0u, bit_xor<int>());

    // Get the last bit where 1 occurs by "x & ~(x - 1)"
    // Because -(x - 1) = ~(x - 1) + 1 <=> -x = ~(x - 1) 
    // So we can also get the last bit where 1 occurs by "x & -x"
    const auto bit = x_xor_y & -x_xor_y;

    uint32_t x=0;
    for (const auto& i : nums)
    {
        if(i & bit) {
            x ^= i;
        }
    }

    return {int(x), int(x_xor_y^x)};
}


bool Solution::isPowerOfTwo(int n) {
    return n>0 && (n&(n-1)) == 0;
}


int Solution::rangeBitwiseAnd(int begin, int end) {

    int pos = end;
    while (begin < pos)
    {
        pos &= pos-1;
    }

    return pos;
}


void Solution::testRangeBitwiseAnd() {
    int res = rangeBitwiseAnd(5, 7);

    cout<<"rangeBitwiseAnd(5, 7)"<<res<<endl;
}

Solution::Solution(/* args */)
{

}

Solution::~Solution()
{
}

int Solution::singleNum(vector<int> &nums){
    return accumulate(nums.cbegin(), nums.cend(), 0, bit_xor<int>());
}

void Solution::testSingleNum(void) {
    // test1
    vector<int> v{1, 2, 2, 3, 3, 4, 4};
    cout<<"single Num:"<<endl;
    cout<<singleNum(v)<<endl;
}


uint32_t Solution::reverseBits(uint32_t n) {
    uint32_t result = 0;
    int count = 32;
    while (count--)
    {
        result <<= 1;
        result |= n & 1;
        n >>=1;
    }
    return result;
}

void Solution::testReverseBits(void) {
    // test1
    uint32_t v = 21;
    cout<<"testReverseBits:"<<endl;

    printf("My Flag "
           PRINTF_BINARY_PATTERN_INT32 "\n",
           PRINTF_BYTE_TO_BINARY_INT32(v));

    cout<<"after reverse:"<<endl;
    uint32_t r = reverseBits(v);
    printf("My Flag "
           PRINTF_BINARY_PATTERN_INT32 "\n",
           PRINTF_BYTE_TO_BINARY_INT32(r));

}

int Solution::hamingWeight(uint32_t n) {
    int len = 0;
    while(n) {
        len++;
        n &= n-1;
    }

    return len;
}

void Solution::testhamingWeight(void) {
    // test1
    uint32_t v = 121;
    cout<<"testhamingWeight:"<<endl;

    printf("My Flag "
           PRINTF_BINARY_PATTERN_INT32 "\n",
           PRINTF_BYTE_TO_BINARY_INT32(v));

    cout<<"number of 1 :"<<hamingWeight(v)<<endl;
}




int main(void)
{
    
    Solution solution;

    solution.testMaxProduct();

    return 0;
}
