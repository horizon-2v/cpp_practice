#include <iostream>
#include <stdarg.h>

void function(int count...){
    va_list args;
    va_start(args, count);
    for(int i = 0; i != count; ++i){
        auto num = va_arg(args, int);
        std::cout << num << std::endl;
    }
    va_end(args);
}
