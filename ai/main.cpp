#include <stdio.h>
#include <string>
#include "ai_module.h"

int main(int argc, char ** argv) {
    ai_module a;
    int t[] = {1, 5, 6, 4, 3, 8, 2, 7, 9};
    int n = sizeof(t) / sizeof(t[0]); 
    _vec<int> tt(t, t + n);
    std::string s = (a.test_ai(&tt,0)==(char)1) ? "PASSED" : "FAILED";
    std::cout << s << "\n";
}