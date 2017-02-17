#include <iostream>
#include <string>

struct ci_char_traits : public std::char_traits<char> {
    static bool eq (char c1, char c2) {
        return toupper(c1) == toupper(c2);
    }
    
    static bool lt(char c1, char c2) {
        return toupper(c1) < toupper(c2);
    }
    
    static int compare (const char *s1, const char * s2, size_t n) {
        return strncasecmp(s1, s2, n);
    }
};

typedef std::basic_string<char, ci_char_traits> ci_string;

int main(int argc, char const *argv[]) {
    ci_string ci("aBcd");
    ci_string c2("AbcD");
    
    if (ci == c2) {
        printf("equal\n");
    }
    
    return 0;
}