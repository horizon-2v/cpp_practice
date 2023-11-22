#include <iostream>
#include "test.h"
#include <cassert>

using namespace std;

int main(int argc, char const *argv[])
{
    int num;
    cin >> num;
    if(num > 5){
        cerr << __DATE__ << " " << __TIME__ << endl
        << "Error: " << __FILE__ << " in function "
        << __func__ << " at line:" << __LINE__ << endl
        << "input bigger than 5" << endl;
    }

    return 0;
}
