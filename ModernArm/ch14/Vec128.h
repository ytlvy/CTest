/*
 * @Author: Y.t
 * @Date: 2021-05-31 23:01:33
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-31 23:17:20
 * @Description: 
 */

#pragma once
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

struct alignas(16) Vec128 {
    public:
        union{
        int8_t m_I8[16];
        int16_t m_I16[8];
        int32_t m_I32[4];
        int64_t m_I64[2];
        uint8_t m_U8[16];
        uint16_t m_U16[8];
        uint32_t m_U32[4];
        uint64_t m_U64[2];
        float m_F32[4];
        double m_F64[2];
        };
};