#ifndef OPTIMAL_ALGORITHM_H
#define OPTIMAL_ALGORITHM_H

#include "functions.h"


unsigned int numPageFaultsOptimalAlgorithm(unsigned int, const std::string&);
void display_optimal_algorithm(unsigned int, const std::string&);

// Helper Function
char search(const std::unordered_set<char>&, const std::string&, unsigned int);




unsigned int numPageFaultsOptimalAlgorithm(
    unsigned int pageFrames, const std::string& referenceString)
{
    /*
        Optimal Algorithm

        Input: # of page frames and the reference string
        Output: # of page faults
    */


    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    unsigned int pageFaults = 0;

    std::unordered_set<char> pages;

    // Traversing through the reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // The max size is the # of page frames
        if (pages.size() < pageFrames)
        {
            // If the value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);
                pageFaults++;
            }
        }

        // If pages.size() == # of page frames
        else
        {
            if (pages.find(pageArray[idx]) == pages.end())
            {
                // Search the future for a sting that is not used
                char valToRemove = search(pages, referenceString, idx);

                pages.erase(valToRemove);
                pages.insert(pageArray[idx]);

                pageFaults++;
            }
        }
    }

    return pageFaults;
}


// Searches the furture for the page that is not used 
char search(const std::unordered_set<char>& pages,
    const std::string& referenceString, unsigned int index)
{
    std::unordered_set<char> tempPages(pages);

    unsigned int idx = index + 1;
    while (idx < referenceString.length() && tempPages.size() > 1)
    {
        char val = referenceString[idx];

        if (tempPages.find(val) != pages.end())
            tempPages.erase(val);

        idx++;
    }

    return *(tempPages.begin());
}


void display_optimal_algorithm(unsigned int pageFrames,
    const std::string& referenceString)
{
    /*
        This function will show all of the pages inside the page frame
    */


    // Display the header for the tables
    header();

    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    unsigned int pageFaults = 0;

    std::unordered_set<char> pages;

    // Traversing through the reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // Printing out the reference string
        std::cout << "\t\t|       " << pageArray[idx] << "       |";

        bool pageFault = false;
        std::string description;
        char valToRemove;

        // The max size is the # of page frames
        if (pages.size() < pageFrames)
        {
            // If the value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);
                pageFault = true;
                description = "   Inserting ";
            }
        }

        // If pages.size() == # of page frames
        else
        {
            if (pages.find(pageArray[idx]) == pages.end())
            {
                valToRemove = search(pages, referenceString, idx);

                pages.erase(valToRemove);
                pages.insert(pageArray[idx]);

                pageFault = true;
                description = "   Replace ";
            }
        }

        if (pageFault)
        {
            std::cout << "  " << pages;
            printWhiteSpaces(pages.size());
            std::cout << "|";

            if (description == "   Inserting ")
                std::cout << description << pageArray[idx] << "     |" << std::endl;
            else
                std::cout << description << valToRemove << " w/ " << pageArray[idx] << "  |" <<std::endl;
        }
        else
            std::cout << "                    |                   |" << std::endl;
    }
    std::cout << "\t\t+--------------------------------------------------------+" << std::endl;
}



#endif // !OPTIMAL_ALGORITHM_H
