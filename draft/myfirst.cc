#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;
    int val = 1;
    const int &r = val;  
    cout << r << endl;  
}
