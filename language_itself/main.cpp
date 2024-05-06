#include <iostream>


double fn8(int (&a)[2][3][5], size_t count) {
    double sum = 0;
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                sum += a[i][j][k];
            }
        }
    }
    // print the size of the array
    std::cout << "Size of the array: " << sizeof(a) << std::endl;
    // use std::size() function to get the size of the array
    std::cout << "Size of the array: " << std::size(a) << std::endl;
    return sum;
}

int main() {
    int arr[][3][5] {
        {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15}
        },
        {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15}
        }
    };

    std::cout << "Sum: " << fn8(arr, 2) << std::endl;
    return 0;
}