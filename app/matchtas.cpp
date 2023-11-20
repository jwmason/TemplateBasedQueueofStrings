#include <vector>
#include <unordered_map>
#include "GenericQueue.hpp"
#include "matchtas.hpp"

#include <sstream>
#include <string>
#include <iostream>

// You may want to #include others that we have talked about


void matchTAs(unsigned n, std::istream &taPrefs, std::istream &classPrefs, std::unordered_map<unsigned, unsigned> & assignments)
{
    // Initialize the vectors to hold Class and TA preferences
    std::vector< std::unordered_map<unsigned, unsigned> > theTAPreferenceLists(n+1);
    std::vector< std::unordered_map<unsigned, unsigned> > classPreferenceLists(n+1);

    // Fill the vectors

    // TA Preferences
    std::string line, word;
    std::stringstream ss;

    unsigned ctr{1};
    while(  getline(taPrefs, line) )
    {
        unsigned prefNum{1};
        ss.clear();
        ss << line;
        while( ss >> word )
        {
            unsigned conv = std::stoul( word );   // what is their ith preference?  That is conv.
            // for the current course, their ith preference is the TA who is listed, or vice versa
            theTAPreferenceLists[ctr][prefNum] = conv;
            prefNum++;
        }

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

    // Initialize GenericQueue object
    GenericQueue<GenericQueue<std::vector<unsigned int>>> QueueofTAs;

    // Add all the TAs as GenericQueue objects and attribute to them the class ranks
    for (unsigned i = 1; i <= n; ++i)
    {
        GenericQueue<std::vector<unsigned int>> TAQueues;
        // enqueue all the class ranks to the TAQueues object
        for (unsigned j = 1; j <= theTAPreferenceLists[i].size(); ++j)
        {
            int class_Rank = theTAPreferenceLists[i][j];
            std::vector<unsigned int> rankVector;
            // Assuming class_Rank is an integer representing a rank
            rankVector.push_back(static_cast<unsigned int>(class_Rank));
            TAQueues.enqueue(rankVector);
        }
        // Enqueue TAQueues into QueueofTAs
        QueueofTAs.enqueue(TAQueues);
    }

    // Assigns TA arbitrarily
    for (unsigned i = 1; i <= n; ++i)
    {
        // Get GenericQueue object from vector
        GenericQueue<std::vector<unsigned int>> TAQueues = QueueofTAs.front();
        QueueofTAs.dequeue();

        // Print the class ranks for the current TA
        std::vector<unsigned int> classRanks = TAQueues.front();
        TAQueues.dequeue();

        // Assign TA to first pick class and remove it from the vector
        assignments[i] = classRanks[0];
        classRanks.erase(classRanks.begin());
    }

    for (unsigned i = 1; i <= n; ++i)
    {
        std::cout << i << " : " << assignments[i] << std::endl;
    }
    std::cout << "\n";


}