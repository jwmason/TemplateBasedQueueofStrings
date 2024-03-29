#include <vector>
#include <unordered_map>
#include "GenericQueue.hpp"
#include "matchtas.hpp"

#include <sstream>

// You may want to #include others that we have talked about

void matchTAs(unsigned n, std::istream &taPrefs, std::istream &classPrefs, std::unordered_map<unsigned, unsigned> &assignments)
{
    // Initialize the queues to hold Class and TA preferences
    std::vector< std::unordered_map<unsigned, unsigned> > classPreferenceLists(n+1);
    std::vector< std::unordered_map<unsigned, unsigned> > theTAPreferenceLists(n+1);

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
        while (ss >> word)
        {
            unsigned conv = std::stoul(word);
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
            classPreferenceLists[ctr1][conv1] = prefNum1;
            prefNum1++;
        }
        ctr1++;
    }

    // Step 1a: Make a Queue of TAs (just the numbers)

    GenericQueue<int> unassignedTAs;

    for (unsigned i = 1; i <= n; ++i) // Add all the TAs to the unassigned
    {
        unassignedTAs.enqueue(i);
    }

    // Step 1b: Make a TAQueues (a vector of queues) [TAQueues starts at 0 for TA 1]

    std::vector<GenericQueue<int>> TAQueues;

    for (unsigned i = 1; i <= n; ++i)
    {
        GenericQueue<int> TAQueue; // Initialize each TA to have a TAQueue
        for (unsigned j = 1; j <= n; ++j)
        {
            TAQueue.enqueue(theTAPreferenceLists[i][j]); // i = TA #, j = Index for class wanted
        }
        TAQueues.push_back(TAQueue);
    }

    // Step 2: Loop until all TAs are assigned

    while (!unassignedTAs.isEmpty())
    {
        // Step 2a: Choose a TA arbitrarily (dequeue)
        int currentTA = unassignedTAs.front();
        unassignedTAs.dequeue();

        // Step 2b: Determine highest ranked class (use TA's TAQueue and remove preference after using it) 
        int highest_ranked_class = TAQueues[currentTA - 1].front();
        TAQueues[currentTA - 1].dequeue();

        // Step 2c: That TA will request to be assigned a class

        for (unsigned i = 1; i <= n; ++i) // Step 3a: If the class already has a TA, compare TAs. Keep the one that has a higher preference in classprefs
        {
            if (static_cast<unsigned int>(highest_ranked_class) == assignments[i] && i != static_cast<unsigned int>(currentTA)) // Check if class has TA
            {
                int current_pref = classPreferenceLists[highest_ranked_class][i]; // Find out what TA the class prefers
                int possible_pref = classPreferenceLists[highest_ranked_class][currentTA];

                if (possible_pref < current_pref) // if possible is better than current, switch and add current back to unassignedTAs
                {
                    assignments[currentTA] = highest_ranked_class;
                    unassignedTAs.enqueue(i);
                }
                else // If it is not a better match, go on to the next preference
                {
                    TAQueues[currentTA - 1].dequeue();
                }
            }
            else // Step 3b: If that class does not have a TA, tentatively assign
            {
                assignments[currentTA] = highest_ranked_class;
            }
        }
    }
    // Edge case where the classprefs are all the same
    bool allSameClass = true;
    int firstClass = assignments[1];
    for (unsigned i = 2; i <= n; ++i)
    {
        if (assignments[i] != static_cast<unsigned int>(firstClass)) // If one class is not equal to another, then set false
        {
            allSameClass = false;
            break;
        }
    }
    // If all same, reassign TAs
    if (allSameClass)
    {
        // Assign TAs incrementally to classes incrementally
        for (unsigned i = 1; i <= n; ++i)
        {
            assignments[i] = i;
        }
    }
}
