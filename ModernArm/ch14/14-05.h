/*
 * @Author: Y.t
 * @Date: 2021-06-01 09:38:57
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-01 09:44:12
 * @Description: 
 */

#include <cstdint>

struct ClipData {
    uint8_t* m_Des;
    uint8_t* m_Src;
    uint64_t m_NumPixels;
    uint64_t m_NumClippedPixels;
    uint8_t m_ThreshLo;
    uint8_t m_ThreshHi;
};

extern void Init(uint8_t* x, uint64_t n, unsigned int seed);
extern bool ClipPixelCpp(ClipData* cd);

extern "C" bool ClipPixelsA_(ClipData* cd);
extern "C" bool ClipPixelsB_(ClipData* cd);
extern void ClipPixels_BM(void);
extern void PrintClipDataStructOffsets(void);

//Algorithm constants
const uint8_t c_ThreshLo = 10;
const uint8_t c_ThreshHi = 245;
const uint64_t c_NumPixels = 8 * 1024 * 1024;
const unsigned int c_Seed = 157;


