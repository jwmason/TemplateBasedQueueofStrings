#include "catch_amalgamated.hpp"

#include <string>
#include <fstream>  
#include <unordered_map>

#include "matchtas.hpp"
#include <iostream>

namespace{



void parseFileForPreferenceLists(std::istream &in, std::vector< std::unordered_map<unsigned, unsigned> > & mapping)
{
    std::string line, word;
    std::stringstream ss;

    unsigned ctr{1};
    while(  getline(in, line) )
    {
        unsigned prefNum{1};
        ss.clear();
        ss << line;
        while( ss >> word )
        {
            unsigned conv = std::stoul( word );   // what is their ith preference?  That is conv.
            // for the current course, their ith preference is the TA who is listed, or vice versa
            mapping[ctr][conv] = prefNum;
            prefNum++;
        }

        ctr++;
    }

}


bool verifyMatching(unsigned n, std::istream &taPrefs, std::istream &classPrefs, const std::unordered_map<unsigned, unsigned> & assignments)
{
    std::vector< std::unordered_map<unsigned, unsigned> > classPreferenceLists(n+1);
    std::vector< std::unordered_map<unsigned, unsigned> > theTAPreferenceLists(n+1);

    parseFileForPreferenceLists(classPrefs, classPreferenceLists);
    parseFileForPreferenceLists(taPrefs, theTAPreferenceLists);

    // now, each class 1..n must be verified for stability. 
    try
    {
        for(unsigned ta{1}; ta <= n; ta++)
        {
            unsigned whichClass {assignments.at(ta)}; 
            unsigned prefNum {theTAPreferenceLists[ ta ][whichClass] };

            // for each class this TA prefers:
            for(unsigned cn{1}; cn <=n; cn++)
            {
                if( theTAPreferenceLists[ta][cn] < prefNum )
                {
                    unsigned preferenceOfTheirOwnTA;
                    bool isMatched{false};
                    for (auto it = assignments.begin(); it != assignments.end(); ++it) {
                       if (it->second == cn) {
                            preferenceOfTheirOwnTA = classPreferenceLists[cn][it->first];
                            isMatched = true;
                            break;
                        }
                    }
                
                    if( (!isMatched) or (classPreferenceLists[cn][ta] < preferenceOfTheirOwnTA ) )
                    {
                        return false;
                    }

                }
            } 
        }

    }
    catch(const std::out_of_range & oor)
    {
        return false; // someone wasn't mapped.
    }
    return true;
}



TEST_CASE("SimpleCase", "[RequiredTAMatching]")
{
    std::ifstream profsin{"test1_classprefs.txt"};
    std::ifstream tasin{"test1_taprefs.txt"};
    std::unordered_map<unsigned, unsigned> matching;
    constexpr unsigned NUM_TAS_and_CLASSES = 3;
 
    std::ifstream _profsin{"test1_classprefs.txt"};
    std::ifstream _tasin{"test1_taprefs.txt"};

    matchTAs( NUM_TAS_and_CLASSES, tasin, profsin, matching);

    // need to reset file pointers for the grading

    REQUIRE( verifyMatching(NUM_TAS_and_CLASSES, _tasin, _profsin, matching) );
}



TEST_CASE("MoreComplexCase", "[RequiredTAMatching]")
{
    std::ifstream profsin{"test2_classprefs.txt"};
    std::ifstream tasin{"test2_taprefs.txt"};
    std::unordered_map<unsigned, unsigned> matching;
    constexpr unsigned NUM_TAS_and_CLASSES = 5;

    std::ifstream _profsin{"test2_classprefs.txt"};
    std::ifstream _tasin{"test2_taprefs.txt"};

    matchTAs( NUM_TAS_and_CLASSES, tasin, profsin, matching);

    // need to reset file pointers for the grading

    REQUIRE( verifyMatching(NUM_TAS_and_CLASSES, _tasin, _profsin, matching) );
}



} // end namespace
