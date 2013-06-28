// --------------------------
// cs378-pfd/src/TestPFD.c++
// Copyright (C) 2013
// CS w378 C++ STL w/ Dr. Downing
// Summer 2013
// Kevin Tran
// Jose Coello
// --------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lcppunit -ldl
    % valgrind TestCollatz >& TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"


// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_num_tasks1 () {
        std::istringstream r("5 4\n");
        int vert;
        int edges;
        const bool b = PFD_read_num_tasks(r, vert, edges);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(vert ==    5);
        CPPUNIT_ASSERT(edges ==   4);}

    void test_read_num_tasks2 () {
        std::istringstream r("");
        int vert;
        int edges;
        const bool b = PFD_read_num_tasks(r, vert, edges);
        CPPUNIT_ASSERT(b == false);
    }

    void test_read_num_tasks3 () {
        std::istringstream r("100 100\n");
        int vert;
        int edges;
        const bool b = PFD_read_num_tasks(r, vert, edges);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(vert ==    100);
        CPPUNIT_ASSERT(edges ==   100);}



    void test_read_rules1 () {
		std::istringstream r("1 1 4");
		std::vector<int> noDep(3,0);
		std::vector<node>nodeList;
		const bool b = PFD_read_rules(r, noDep, nodeList);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(noDep[1] == 1);
		CPPUNIT_ASSERT(nodeList.empty() == false);
    }

    void test_read_rules2 () {
        std::istringstream r(" ");
        std::vector<int> noDep(10,0);
        std::vector<node>nodeList;
        const bool b = PFD_read_rules(r, noDep, nodeList);
        CPPUNIT_ASSERT(b == false);
    }

    void test_read_rules3 () {
        std::istringstream r("1 2 3 4");
        std::vector<int> noDep(10,0);
        std::vector<node>nodeList;
        const bool b = PFD_read_rules(r, noDep, nodeList);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(noDep[1] == 1);
        CPPUNIT_ASSERT(nodeList.empty() == false);
    }





    // ----
    // eval
    // ----

    void test_create_node1 () {
    	int vert = 5;
    	std::vector<int> target = {2,3};
    	std::vector<node> nodeList;
    	PFD_create_node(vert, target, nodeList);
        CPPUNIT_ASSERT(nodeList.empty() == false);

    }

    void test_create_node2 () {
       	int vert = 2;
		std::vector<int> target = {1,2,3};
		std::vector<node> nodeList;
		PFD_create_node(vert, target, nodeList);
		CPPUNIT_ASSERT(nodeList.empty() == false);
    }

    void test_create_node3 () {
       	int vert = 6;
		std::vector<int> target = {6};
		std::vector<node> nodeList;
		PFD_create_node(vert, target, nodeList);
		CPPUNIT_ASSERT(nodeList.empty() == false);
    }





    void test_check_adjList1 () {
    	int val_temp = 3;
    	int i = 0;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

       	int vert = 6;
		std::vector<int> target = {3};
		PFD_create_node(vert, target, nodeList);

		PFD_check_adjList(val_temp, i, nodeList, pQueue);
        CPPUNIT_ASSERT(pQueue.empty() == false);
        CPPUNIT_ASSERT(nodeList.empty() == false);


    }

    void test_check_adjList2 () {
    	int val_temp = 4;
    	int i = 0;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

       	int vert = 6;
		std::vector<int> target = {3};
		PFD_create_node(vert, target, nodeList);

       	vert = 2;
       	target = {5};
		PFD_create_node(vert, target, nodeList);

		PFD_check_adjList(val_temp, i, nodeList, pQueue);
        CPPUNIT_ASSERT(pQueue.empty() == true);
        CPPUNIT_ASSERT(nodeList.empty() == false);
    }

    void test_check_adjList3 () {
    	int val_temp = 4;
    	int i = 0;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

       	int vert = 6;
		std::vector<int> target = {4};
		PFD_create_node(vert, target, nodeList);

       	vert = 2;
		target = {5};
		PFD_create_node(vert, target, nodeList);

		PFD_check_adjList(val_temp, i, nodeList, pQueue);
        CPPUNIT_ASSERT(pQueue.empty() == false);
        CPPUNIT_ASSERT(nodeList.empty() == false);

    }




    void test_eval_nodeList1 () {
        std::ostringstream w;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

    	pQueue.push(2);

       	int vert = 1;
		std::vector<int> target = {2};
		PFD_create_node(vert, target, nodeList);

    	PFD_eval_nodeList(w, nodeList, pQueue);

        CPPUNIT_ASSERT(w.str() == "2 1 \n");
    }

    void test_eval_nodeList2 () {
        std::ostringstream w;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

    	pQueue.push(1);

    	PFD_eval_nodeList(w, nodeList, pQueue);

        CPPUNIT_ASSERT(w.str() == "1 \n");

    }

    void test_eval_nodeList3 () {
        std::ostringstream w;
    	std::vector<node> nodeList;
    	std::priority_queue<int, std::vector<int> , std::greater<int> > pQueue;

    	PFD_eval_nodeList(w, nodeList, pQueue);

        CPPUNIT_ASSERT(w.str() == "\n");

    }


    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n");}

    void test_solve_2 () {
        std::istringstream r("2 1\n1 1 2\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1 \n");}

    void test_solve_3 () {
        std::istringstream r("");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}


    // -----
    // suite
    // -----


    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_num_tasks1);
    CPPUNIT_TEST(test_read_num_tasks2);
    CPPUNIT_TEST(test_read_num_tasks3);
    CPPUNIT_TEST(test_read_rules1);
    CPPUNIT_TEST(test_read_rules2);
    CPPUNIT_TEST(test_read_rules3);
    CPPUNIT_TEST(test_create_node1);
    CPPUNIT_TEST(test_create_node2);
    CPPUNIT_TEST(test_create_node3);
    CPPUNIT_TEST(test_check_adjList1);
    CPPUNIT_TEST(test_check_adjList2);
    CPPUNIT_TEST(test_check_adjList3);
    CPPUNIT_TEST(test_eval_nodeList1);
    CPPUNIT_TEST(test_eval_nodeList2);
    CPPUNIT_TEST(test_eval_nodeList3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
