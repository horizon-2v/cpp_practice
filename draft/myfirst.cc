#include <iostream>
int main(int argc, char const *argv[])
{
    int val = 42;
    int *p = nullptr;
    int *&r = p;
    r = &val;
    std::cout<< *r << std::endl;
}
