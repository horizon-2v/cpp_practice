#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    using namespace std;
    string s("Abcd");
    string s1("1BCD");
    cout << (s > s1 ? s : s1) << endl;
    return 0;
}
