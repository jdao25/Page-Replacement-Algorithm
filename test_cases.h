#ifndef TEST_CASES_H
#define TEST_CASES_H


#include "FIFO.h"
#include "LRU.h"
#include "optimal_algorithm.h"


// Declarations
void test_FIFO();
void test_LRU();
void test_optimal_algorithm();
void calculate_average();




void test_FIFO()
{
    /*
        This is to solely test the FIFO Page Replacement Algorithm
    */


    std::cout << "First In First Out (FIFO)" << std::endl;

    // PageFrames 3, 4, 5, and 6
    for (int pageFrames = 3; pageFrames <= 6; pageFrames++)
    {
        std::cout << "\tPage Frame: " << pageFrames << std::endl;

        // Create a RefererenceString.txt file with page frame
        createFile(pageFrames);

        // Open the ReferenceString.txt file that was created
        std::ifstream referenceFile("ReferenceString.txt");

        std::string referenceString;   // End result, this will hold our reference string

        // Loop until the end of the file
        while (!referenceFile.eof())
        {
            // Grab each line from the file
            // line will be the last line in the file
            // The last line in the file will be the reference string
            getline(referenceFile, referenceString);
        }

        referenceFile.close();


        std::cout << "\t\tReference string: " << referenceString << std::endl;

        // Visually display the algorithm
        display_FIFO(pageFrames, referenceString);

        std::cout
            << "\t\tNumber of page faults: "
            << numPageFaultsFIFO(pageFrames, referenceString)
            << std::endl << std::endl;
    }
}


void test_LRU()
{
    /*
        This is to solely test the LRU Page Replacement Algorithm
    */


    std::cout << "Least Recently Used (LRU)" << std::endl;

    // PageFrames 3, 4, 5, and 6
    for (int pageFrames = 3; pageFrames <= 6; pageFrames++)
    {
        std::cout << "\tPage Frame: " << pageFrames << std::endl;

        // Create a RefererenceString.txt file with page frame
        createFile(pageFrames);

        // Open the ReferenceString.txt file that was created
        std::ifstream referenceFile("ReferenceString.txt");

        std::string referenceString;

        // Loop until the end of the file
        while (!referenceFile.eof())
        {
            // Grab each line from the file
            // line will be the last line in the file
            // The last line in the file will be the reference string
            getline(referenceFile, referenceString);
        }

        referenceFile.close();

        std::cout << "\t\tReference string: " << referenceString << std::endl;

        display_LRU(pageFrames, referenceString);

        std::cout
            << "\t\tNumber of page faults: "
            << numPageFaultsLRU(pageFrames, referenceString)
            << std::endl << std::endl;
    }
}


void test_optimal_algorithm()
{
    /*
        This is to solely test the Optimal Algorithm Page Replacement Algorithm
    */


    std::cout << "Optimal Algorithm" << std::endl;

    // PageFrames 3, 4, 5, and 6
    for (int pageFrames = 3; pageFrames <= 6; pageFrames++)
    {
        std::cout << "\tPage Frame: " << pageFrames << std::endl;

        // Create a RefererenceString.txt file with page frame
        createFile(pageFrames);

        // Open the ReferenceString.txt file that was created
        std::ifstream referenceFile("ReferenceString.txt");

        std::string referenceString;   // End result, this will hold our reference string

        // Loop until the end of the file
        while (!referenceFile.eof())
        {
            // Grab each line from the file
            // line will be the last line in the file
            // The last line in the file will be the reference string
            getline(referenceFile, referenceString);
        }

        referenceFile.close();

        std::cout << "\t\tReference string: " << referenceString << std::endl;

        display_optimal_algorithm(pageFrames, referenceString);

        std::cout
            << "\t\tNumber of page faults: "
            << numPageFaultsOptimalAlgorithm(pageFrames, referenceString)
            << std::endl << std::endl;
    }
}


// Caculate the average of 50 trials
void calculate_average()
{
    unsigned int numTrials = 50;

    for (int pageFrames = 3; pageFrames <= 6; pageFrames++)
    {
        std::cout << "Page Frames:  " << pageFrames << std::endl;

        std::vector<unsigned int> FIFO_Page_Faults; // Holds 50 page fault values
        std::vector<unsigned int> LRU_Page_Faults; // Holds 50 page fault values
        std::vector<unsigned int> optimal_algorithm_Page_Faults; // Holds 50 page fault values

        for (int trial = 1; trial <= 50; trial++)
        {
            // Create a ReferenceString.txt file
            createReferenceStringTesting(pageFrames);

            std::ifstream referenceFile("ReferenceString.txt"); // Open txt file

            std::string referenceString;   // End result, this will hold our reference string

            // Loop until the end of the file
            while (!referenceFile.eof())
            {
                // Grab each line from the file
                // line will be the last line in the file
                // The last line in the file will be the reference string
                getline(referenceFile, referenceString);
            }

            referenceFile.close();

            // Add the page fault to the vector to add together later
            FIFO_Page_Faults.push_back(numPageFaultsFIFO(pageFrames, referenceString));
            LRU_Page_Faults.push_back(numPageFaultsLRU(pageFrames, referenceString));
            optimal_algorithm_Page_Faults.push_back(numPageFaultsOptimalAlgorithm(pageFrames, referenceString));
        }

        // Print out the Averages
        std::cout
            << "\tFirst In First Out (FIFO): (" << numTrials << " trials)" << std::endl
            << "List of all Page Faults:" << std::endl
            << FIFO_Page_Faults << std::endl
            << "\t\tAverage:  " << accumulate(FIFO_Page_Faults) / numTrials << " page faults." << std::endl
            << std::endl;

        std::cout
            << "\tLeast Recently Used (LRU): (" << numTrials << " trials)" << std::endl
            << "List of all Page Faults:" << std::endl
            << LRU_Page_Faults << std::endl
            << "\t\tAverage:  " << accumulate(LRU_Page_Faults) / numTrials << " page faults." << std::endl
            << std::endl;

        std::cout
            << "\tOptimal Algorithm: (" << numTrials << " trials)" << std::endl
            << "List of all Page Faults:" << std::endl
            << optimal_algorithm_Page_Faults << std::endl
            << "\t\tAverage:  " << accumulate(optimal_algorithm_Page_Faults) / numTrials << " page faults." << std::endl
            << std::endl;
    }
}



#endif // !TEST_CASES_H
