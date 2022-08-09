#include <iostream>

int main() {
    int a = 10;
    int *ptr = &a;
    a = 5;
    std::cout << *ptr << std::endl;
    return 0;
}