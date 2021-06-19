/*
 * @Author: Y.t
 * @Date: 2021-05-31 23:12:15
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-31 23:18:09
 * @Description: 
 */
#include <iostream>
#include <string>
#include "Vec128.h"

using namespace std;

extern "C" void PackedAddI16_(Vec128 x[2], const Vec128&a, const Vec128& B);
extern "C" void PackedSubI16_(Vec128 x[2], const Vec128&a, const Vec128& B);
extern "C" void PackedAndU16_(Vec128 x[2], const Vec128&a, const Vec128& B);
extern "C" void PackedSubU16_(Vec128 x[2], const Vec128&a, const Vec128& B);

void PackedAddI16(void) {
    
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_I16[0] = 10;
    a.m_I16[1] = 200;
    a.m_I16[2] = 30;
    a.m_I16[3] = -32766;
    a.m_I16[4] = 50;
    a.m_I16[5] = 60;
    a.m_I16[6] = 32000;
    a.m_I16[7] = -32000;

    b.m_I16[0] = 100;
    b.m_I16[1] = -200;
    b.m_I16[2] = 32760;
    b.m_I16[3] = -400;
    b.m_I16[4] = 500;
    b.m_I16[5] = -600;
    b.m_I16[6] = 1200;
    b.m_I16[7] = -950;
    
    PackedAddI16_(x, a, b);
    cout << "\nResults for PackedAddI16 - Wraparound Addition\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[0]:  " << x[0].ToStringI16() << nl;
    cout << "\nResults for PackedAddI16 - Saturated Addition\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[1]:  " << x[1].ToStringI16() << nl;
}