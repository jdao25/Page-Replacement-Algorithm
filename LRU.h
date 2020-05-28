#ifndef LRU_H
#define LRU_H

#include "functions.h"


unsigned int numPageFaultsLRU(unsigned int, const std::string&);
void display_LRU(unsigned int, const std::string&);


unsigned int numPageFaultsLRU(unsigned int pageFrames,
    const std::string& referenceString)
{
    /*
        Least Recently Used Algorithm

        Input: # pageFrames and reference string
        Output: # of page faults
    */


    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    // Quickly copy over reference string to array
    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    std::unordered_set<char> pages;
    std::stack<char> recentlyUsedOrder;     // Stack will keep track of the recent pages order
    unsigned int pageFaults = 0;

    // Iterate through the reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // Max size is # of page frames
        if (pages.size() < pageFrames)
        {
            // If value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);
                pageFaults++;
            }
        }

        // If the pages.size() == # page frames
        else
        {
            // If value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                std::stack<char> tempStack(recentlyUsedOrder);
                std::unordered_set<char> tempPages(pages);

                // Find lease recently used
                // Last element in tempPages will be the least
                while (tempPages.size() > 1)
                {
                    char recent = tempStack.top();  // Top of stack is most recent

                    // We don't want the most recent but the least recent
                    tempPages.erase(recent);    // remove all the recent pages, what is left will be least recent
                    tempStack.pop();
                }

                pages.erase(*(tempPages.begin()));  // Remove the only element, this is the least recent
                pages.insert(pageArray[idx]);

                pageFaults++;
            }
        }

        recentlyUsedOrder.push(pageArray[idx]);
    }

    return pageFaults;
}


void display_LRU(unsigned int pageFrames, const std::string& referenceString)
{
    /*
        This function will show all of the pages inside the page frame
    */

    // Display the table's headers
    header();

    unsigned int strLen = referenceString.length();
    char pageArray[strLen];

    // Quickly copy over reference string to array
    for (int idx = 0; idx < strLen; idx++)
        pageArray[idx] = referenceString[idx];

    std::unordered_set<char> pages;
    std::stack<char> recentlyUsedOrder;

    // Iterate through the reference string
    for (int idx = 0; idx < strLen; idx++)
    {
        // Printing out the reference string
        std::cout << "\t\t|       " << pageArray[idx] << "       |";

        bool pageFault = false;
        std::string description;
        char valToRemove;

        // Max size is # of page frames
        if (pages.size() < pageFrames)
        {
            // If value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                pages.insert(pageArray[idx]);
                pageFault = true;
                description = "   Inserting ";
            }
        }

        // If the pages.size() == # page frames
        else
        {
            // If value of pageArray[idx] is not in "pages"
            if (pages.find(pageArray[idx]) == pages.end())
            {
                std::stack<char> tempStack(recentlyUsedOrder);
                std::unordered_set<char> tempPages(pages);

                // Find lease recently used
                // Last element in tempPages will be the least
                while (tempPages.size() > 1)
                {
                    char recent = tempStack.top();  // Top of stack is most recent

                    tempPages.erase(recent);
                    tempStack.pop();
                }

                pages.erase(*(tempPages.begin()));
                pages.insert(pageArray[idx]);

                valToRemove = *(tempPages.begin());
                pageFault = true;
                description = "   Replace ";
            }
        }

        recentlyUsedOrder.push(pageArray[idx]);

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


#endif // !LRU_H
