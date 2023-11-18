#include "catch_amalgamated.hpp"

#include <string>
#include <fstream>  


#include "GenericQueue.hpp"


namespace{

// Tests enqueue, front, and front const
TEST_CASE("MyFirstEnqueuePrev", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );
}

// Tests front, front const, and isEmpty
TEST_CASE("FrontThrowsWhenNonePrev", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}

// Tests size
TEST_CASE("Size1", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    q.enqueue("Mike");
    REQUIRE( q.size() == 1);
}
TEST_CASE("Size2", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    REQUIRE( q.size() == 0);
}

// Tests enqueue, dequeue, size
TEST_CASE("MyFirstDequeue", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );
    a.dequeue();
    REQUIRE( a.size() == 0);
}
TEST_CASE("MySecondDequeue", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    REQUIRE_THROWS_AS( a.dequeue(), QueueEmptyException );
}
TEST_CASE("MyThirdDequeue", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    a.enqueue("Mikey");
    a.dequeue();
    REQUIRE( a.front() == "Mikey" );
}

// Tests copy
TEST_CASE("Copy1", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );

    GenericQueue<std::string> q(a);
    REQUIRE( q.front() == "Mike");
}
TEST_CASE("Copy2", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );

    GenericQueue<std::string> q(a);
    REQUIRE( q.front() == "Mike");

    a.enqueue("Mikey");
    REQUIRE( a.size() == 2);
    REQUIRE( q.size() == 1);
}

// tests assignment operator
TEST_CASE("SelfAssignment", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    q.enqueue("Test");
    q = q;
    REQUIRE(q.front() == "Test");
}
TEST_CASE("Assignment1", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    q.enqueue("Test1");
    q.enqueue("Test2");

    GenericQueue<std::string> a;
    a.enqueue("Test3");

    a = q;
    REQUIRE(a.front() == "Test1");
    REQUIRE(a.size() == 2);
}
TEST_CASE("Assignment2", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    q.enqueue("Test1");
    q.enqueue("Test2");

    GenericQueue<std::string> a;
    a.enqueue("Test3");

    a = q;
    q.enqueue("Test4");
    REQUIRE(a.front() == "Test1");
    REQUIRE(a.size() == 2);
    REQUIRE(q.size() == 3);
}


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



TEST_CASE("TemplateTesting", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );
    GenericQueue<int> b;
    b.enqueue(2);
    REQUIRE( b.front() == 2 );
}



} // end namespace

