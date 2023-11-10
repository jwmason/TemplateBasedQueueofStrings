#include "catch_amalgamated.hpp"

#include <string>
#include <fstream>  


#include "GenericQueue.hpp"


namespace{




TEST_CASE("MyFirstEnqueue", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );
}



TEST_CASE("FrontThrowsWhenNone", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}




                        
} // end namespace

