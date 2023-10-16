#include <iostream>
int main(int argc, char const *argv[])
{
    using namespace std;
    int sum = 0, value = 0;
    while(cin >> value)
        sum += value;
    cout << "The sum is: " << sum << endl;    
    return 0;
}
