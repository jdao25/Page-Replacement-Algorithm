#ifndef FIFO_H
#define FIFO_H

#include "functions.h"


unsigned int numPageFaultsFIFO(unsigned int, const std::string&);
void display_FIFO(unsigned int, const std::string&);


unsigned int numPageFaultsFIFO(unsigned int pageFrames,
    const std::string& referenceString)
{
    /*
        FIFO is similar to a queue

        Input: A vector that holds the individual pages of the reference string
        Output: The number of page faults when using FIFO
    */

    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    // Quickly convert the string into an array
    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    std::unordered_set<char> pages; // Length of number page frames
    std::queue<char> pageOrder; // Maintain the page order
    unsigned int pageFaults = 0;

    // Traversing through the reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // Max is size of page frames
        if (pages.size() < pageFrames)
        {
            // if value of pageArray[idx] is not in pages yet
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);   // Add page
                pageFaults++;                   // Increment # page faults

                pageOrder.push(pageArray[idx]); // Add to the queue
            }
        }

        // if size == # page frames, kick a page out
        else
        {
            // If value of pageArray[idx] is not in pages
            if (pages.find(pageArray[idx]) == pages.end())
            {
                // The value to remove will be at the front of the queue
                char valToRemove = pageOrder.front();

                // Remove the element at front of "pageOrder" and add new value
                pages.erase(valToRemove);
                pages.insert(pageArray[idx]);

                pageFaults++;
                pageOrder.pop();    // Remove the front of the queue

                pageOrder.push(pageArray[idx]); // Add to the queue
            }
        }
    }

    return pageFaults;
}


void display_FIFO(unsigned int pageFrames, const std::string& referenceString)
{
    /*
        This function will show all of the pages inside the page frame
    */


    // Tables header
    header();

    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    std::unordered_set<char> pages;
    std::queue<char> pageOrder;

    // Traverse Through reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // Printing out the reference string
        std::cout << "\t\t|       " << pageArray[idx] << "       |";

        bool pageFault = false;
        std::string description;
        char valToRemove;

        // The max size is # of page frames
        if (pages.size() < pageFrames)
        {
            // If the value of pageArray[idx] is not in pages
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);
                pageOrder.push(pageArray[idx]);

                pageFault = true;
                description = "   Inserting ";
            }
        }

        // If pages.size() == # of page frames
        else
        {
            // If value of pageArray[idx] is not in pages
            if (pages.find(pageArray[idx]) == pages.end())
            {
                // The value to remove will be at the front of the queue
                valToRemove = pageOrder.front();

                // Remove the element at front of "pageOrder" and add new value
                pages.erase(valToRemove);
                pages.insert(pageArray[idx]);

                pageOrder.pop();    // Remove the front of the queue
                pageOrder.push(pageArray[idx]); // Add to the queue

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



#endif // !FIFO_H
