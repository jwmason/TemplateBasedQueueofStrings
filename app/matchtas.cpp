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
            theTAPreferenceLists[ctr][conv] = prefNum;
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
            classPreferenceLists[ctr1][conv1] = prefNum1;
            prefNum1++;
        }
        ctr1++;
    }

    // Initialize GenericQueue object
    GenericQueue<unsigned> unassignedTAs;

    // Add all the TAs to the unassigned as this is the start of it
    for (unsigned i = 1; i <= n; ++i)
    {
        unassignedTAs.enqueue(i);
    }

    // Loop through all the unassigned TAs until empty
    while (!unassignedTAs.isEmpty())
    {
        // Get current TA and dequeue from GenericQueue object
        unsigned currentTA = unassignedTAs.front();
        unassignedTAs.dequeue();

        // Find the highest-ranked class that has not rejected the currentTA
        for (const auto &entry : theTAPreferenceLists[currentTA])
        {
            unsigned currentClass = entry.first;
            for (unsigned i = 1; i <= n; ++i)
            {
                if (assignments[i] == currentClass)
                {
                    std::cout << "Found dup" << std::endl;
                }
            }
            assignments[currentTA] = currentClass;
            std::cout << currentTA << " : " << currentClass << std::endl;
        }
    }



}