/*
    This header file contains all the helper functions.

    Functions such as:
        createReferenceString,
        display,
        etc
*/



#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
#include <fstream>  // Read in ReferenceString.txt file
#include <ctime>    // rand() srand()
#include <chrono>   // Also for rand nums. Number generated based on time.
#include <unordered_set>
#include <map>
#include <queue>    // First In First Out
#include <stack>    // Least Recently Used
#include <vector>


#ifndef _WIN32
#include <string>
#endif  // !_WIN32


const unsigned int MAX_PAGE_FRAME = 6;


// Overload Insertion Operator
std::ostream& operator<<(std::ostream&, const std::unordered_set<char>&);
std::ostream& operator<<(std::ostream&, const std::vector<unsigned int>&);


// Create ReferenceString.txt file
void createFile(unsigned int);
void createReferenceStringTesting(unsigned int);


// Other helper functions
void printArray(const char[], unsigned int);
void header();
void printWhiteSpaces(unsigned int);
float accumulate(const std::vector<unsigned int>&);


// Overload Stream Insertion Operator for unordered_set<char>
std::ostream& operator<<(std::ostream& out, const std::unordered_set<char>& pages)
{
    out << "[ ";
    for (auto iter = pages.begin(); iter != pages.end(); iter++)
        out << *iter << " ";
    out << "]";

    return out;
}


// Overload Stream Insertion Operator for vector<unsigned int>
std::ostream& operator<<(std::ostream& out, const std::vector<unsigned int>& pages)
{
    unsigned int num = 0;

    out << "\n\t\t[  ";
    for (auto iter: pages)
    {
        if (num++ > 9)  // So that only 10 numbers will be printed on one line
        {
            out << "\n\t\t   ";
            num = 0;
        }
        out << iter << "  ";
    }
    out << "]" << std::endl;

    return out;
}



void createFile(unsigned int pageFrames)
{
    /*
        Used to create a text file "ReferenceString.txt"

        Input: The number of page frames to use
        Output: N/A
    */


    // Create a file call "ReferenceString.txt" to write to
    std::ofstream referenceFile("ReferenceString.txt");

    srand((unsigned int)time(0)); // Create seed

    std::string referenceString = "";
    unsigned int stringLength = 30;

    // Want to loop 30 times to generate a reference string of length 30
    for (int page = 1; page <= stringLength; page++)
    {
        unsigned int num = (rand() % 8);
        referenceString += std::to_string(num);
    }

    referenceFile
        << "Number of Page Frame value:" << std::endl
        << pageFrames << std::endl
        << "Reference String:" << std::endl
        << referenceString;

    referenceFile.close();
}


void createReferenceStringTesting(unsigned int pageFrames)
{
    /*
        Used to create a text file "ReferenceString.txt"

        Input: The number of page frames to use
        Output: N/A
    */


    std::ofstream referenceFile("ReferenceString.txt");

    // These two command will generate random numbers without repeats
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    std::string referenceString = "";
    unsigned int stringLength = 30;

    // Want to loop 30 times to generate a reference string of length 30
    for (int page = 1; page <= stringLength; page++)
    {
        unsigned int num = (rand() % 8);
        referenceString += std::to_string(num);
    }

    referenceFile
        << "Number of Page Frame value:" << std::endl
        << pageFrames << std::endl
        << "Reference String:" << std::endl
        << referenceString;

    referenceFile.close();
}



void printArray(const char arr[], unsigned int size)
{
    /*
        Used to print the array

        Input: An array (reference string) and an integer (the size of the array)
        Output: N/A
    */

    std::cout << "[ ";
    for (int idx = 0; idx < size; idx++)
        std::cout << arr[idx] << " ";
    std::cout << "]" << std::endl;
}


void header()
{
    std::cout
        << "\n\t\t+--------------------------------------------------------+" << std::endl
        << "\t\t| Reference Str |    Page Frames     |    Description    |" << std::endl
        << "\t\t+--------------------------------------------------------+" << std::endl;
}


void printWhiteSpaces(unsigned int pageSize)
{
    std::map<unsigned int, unsigned int> spaces;

    unsigned int initial = 13;
    for (int idx = 1; idx <= MAX_PAGE_FRAME; idx++)
    {
        spaces.insert(std::pair<unsigned int, unsigned int>(idx, initial));
        initial -= 2;
    }

    for (int idx = 0; idx < spaces[pageSize]; idx++)
        std::cout << " ";
}


float accumulate(const std::vector<unsigned int>& pageFaults)
{
    /*
        Function that returns the summation of all the 50 page faults
    */

    float sum = 0.0;

    for (auto iter: pageFaults)
        sum += iter;

    return sum;
}


#endif // !FUNCTIONS_H
