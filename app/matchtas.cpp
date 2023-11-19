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

    // For TA Preference List, {Class: Preference}
    // For class Preference List, {TA: Preference}
    // Make a queue of TAs
    GenericQueue<GenericQueue<std::vector<std::unordered_map<unsigned, unsigned>>>> QueueofTAs;
    // Loop through every TA and enqueue it and its class preferences into the QueueofTAs
    for (unsigned i = 1; i < theTAPreferenceLists.size(); ++i)
    {
        // Initialize a TAQueue
        GenericQueue<std::vector<std::unordered_map<unsigned, unsigned>>> TAQueue;

        // Iterate through theTAPreferenceLists[i] and add to each {Class: Preference} to TAQueue
        for (const auto &entry : theTAPreferenceLists[i])
        {
            std::vector<std::unordered_map<unsigned, unsigned>> TAPreferences;
            TAPreferences.push_back({{entry.first, entry.second}});
            TAQueue.enqueue(TAPreferences);
        }
        // Enqueue TAQueue to QueueofTAs
        QueueofTAs.enqueue(TAQueue);
    }
}