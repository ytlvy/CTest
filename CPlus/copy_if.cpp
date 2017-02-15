#include <iostream>
#include <sstream>
#include <iterator>

template<typename InputIterator,
    typename OutputInterator,
    typename Predicate>
OutputInterator copy_if(InputIterator begin, InputIterator end,
    OutputInterator destBegin, Predicate) {
        while (begin != end) {
            if (p(*begin)) {
                *destBegin++ = *begin;
            }
            ++begin;
        }
        return destBegin;
    }

int main(int argc, char const *argv[]) {

    return 0;
}
