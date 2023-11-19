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

    std::cout << "theTAPreferenceLists" << ":" << std::endl;
    for (unsigned i = 1; i < theTAPreferenceLists.size(); ++i) {
        std::cout << "Preferences for TA " << i << ": ";
        for (const auto& entry : theTAPreferenceLists[i]) {
            std::cout << "{" << entry.first << ": " << entry.second << "} ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "classPreferenceLists" << ":" << std::endl;
    for (unsigned i = 1; i < classPreferenceLists.size(); ++i) {
        std::cout << "Preferences for class " << i << ": ";
        for (const auto& entry : classPreferenceLists[i]) {
            std::cout << "{" << entry.first << ": " << entry.second << "} ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // For TA Preference List, {Class: Preference}
    // Make a queue of TAs
}