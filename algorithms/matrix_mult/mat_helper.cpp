#include <iostream>
#include <vector>
#include "mat_helper.h"

void print_m(const std::vector<float>& v, int c)
{
        int j = 0;
        for (auto i = v.begin(); i != v.end(); ++i) {
                ++j;
                std::cout << *i << ' ';
                if (j % c == 0) {
                        std::cout << '\n';
                }
        }
}
