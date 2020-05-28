/*
    Main
*/


#include "test_cases.h"


int main(int argc, char const *argv[])
{
    // Run test cases for First In First Out (FIFO)
    test_FIFO();
    std::cout << std::endl;

    // Run test cases for Least Recently Used
    test_LRU();
    std::cout << std::endl;

    // Run test cases for Optimal Algorithm
    test_optimal_algorithm();
    std::cout << std::endl;

    // Calculate average 50 page faults
    calculate_average();

    return 0;
}
