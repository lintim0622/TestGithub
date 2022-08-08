#include <iostream>

int main() {
    int num[3][4] = {{12, 23, 42, 18},
                     {43, 22, 16, 14},
                     {31, 13, 19, 28}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (*(*(num+i)+j) > 40) {
                *(*(num+i)+j) = 40;
            }  
            std::cout << *(*(num+i)+j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}