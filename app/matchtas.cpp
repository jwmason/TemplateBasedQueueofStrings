#include <vector>
#include <unordered_map>
#include "GenericQueue.hpp"
#include "matchtas.hpp"

#include <sstream>
#include <string>
#include <iostream>

// You may want to #include others that we have talked about

void matchTAs(unsigned n, std::istream &taPrefs, std::istream &classPrefs, std::unordered_map<unsigned, unsigned> &assignments)
{
    // Initialize the queues to hold Class and TA preferences
    GenericQueue<GenericQueue<GenericQueue<unsigned int>>> QueueofTAs;
    std::vector< std::unordered_map<unsigned, unsigned> > classPreferenceLists(n+1);

    // Fill the queues

    // TA Preferences
    std::string line, word;
    std::stringstream ss;

    unsigned ctr{1};
    while (getline(taPrefs, line))
    {
        unsigned prefNum{1};
        ss.clear();
        ss << line;
        GenericQueue<GenericQueue<unsigned int>> TAQueue;
        while (ss >> word)
        {
            unsigned conv = std::stoul(word);
            // for the current course, their ith preference is the TA who is listed, or vice versa
            GenericQueue<unsigned int> rankQueue;
            rankQueue.enqueue(conv);
            TAQueue.enqueue(rankQueue);
            prefNum++;
        }

        QueueofTAs.enqueue(TAQueue);
        ctr++;
    }

    // Class Preferences
    std::string line1, word1;
    std::stringstream ss1;

    unsigned ctr1{1};
    while(  getline(classPrefs, line1) )
    {
        unsigned prefNum1{1};
        ss1.clear();
        ss1 << line1;
        while( ss1 >> word1 )
        {
            unsigned conv1 = std::stoul( word1 );   // what is their ith preference?  That is conv.
            // for the current course, their ith preference is the TA who is listed, or vice versa
            classPreferenceLists[ctr1][prefNum1] = conv1;
            prefNum1++;
        }
        ctr1++;
    }

    // Assigns TA arbitrarily
    for (unsigned i = 1; i <= n; ++i)
    {
        // Get GenericQueue object from outer queue
        GenericQueue<GenericQueue<unsigned int>> TAQueues = QueueofTAs.front();
        QueueofTAs.dequeue();

        // Get GenericQueue object from inner queue
        GenericQueue<unsigned int> classRanks = TAQueues.front();
        TAQueues.dequeue();

        // If Class has already been assigned a TA, determine which should get it
        for (unsigned j = 1; j <= n; ++j)
        {
            // Compares the current class to every other class to see if another TA has it
            if (classRanks.front() == assignments[j])
            {
                std::cout << "test" << std::endl;
            }
        }
        // Assign TA to first pick class and remove it from the queue
        assignments[i] = classRanks.front();
        classRanks.dequeue();
    }

    for (unsigned i = 1; i <= n; ++i)
    {
        std::cout << i << " : " << assignments[i] << std::endl;
    }
    std::cout << "\n";
}
