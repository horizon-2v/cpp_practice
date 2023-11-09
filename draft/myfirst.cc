#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int main(int argc, char const *argv[])
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *beg = begin(arr), *last = end(arr);
    cout << *beg << endl;
    return 0;
}
