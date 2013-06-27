// --------------------------------
// projects/pfd/Testpfd.c++
// Copyright (C) 2013
// Michael Both & Rayne Beridon
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall pfd.c++ Testpfd.c++ -o Testpfd -lcppunit -ldl
    % valgrind Testpfd >& Testpfd.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include <list>
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"



// -----------
// Testpfd
// -----------

struct Testpfd : CppUnit::TestFixture {

std::list<int> lst1;
std::list<int> lst2;
std::list<int> lst3;

std::list<int> ans1;
std::list<int> ans2;
std::list<int> ans3;

std::map<int, std::list<int> > mp1;
std::map<int, std::list<int> > mp2;
std::map<int, std::list<int> > mp3;

	void build_tests() {
		lst1.push_back (1);
		ans1.push_back (1);
		ans1.push_back (2);
		
		lst2.push_back (2);
		lst2.push_back (4);
		ans2.push_back (1);
		ans2.push_back (2);
		ans2.push_back (4);
		ans2.push_back (3);
		
		lst3.push_back (5);
		lst3.push_back (2);
		lst3.push_back (1);
		lst3.push_back (3);
		ans3.push_back (1);
		ans3.push_back (2);
		ans3.push_back (3);
		ans3.push_back (5);
		ans3.push_back (4);
		
		mp1.insert ( std::pair<int,std::list<int> >(2,lst1) );
		mp2.insert ( std::pair<int,std::list<int> >(3,lst2) );
		mp3.insert ( std::pair<int,std::list<int> >(4,lst3) );
        CPPUNIT_ASSERT(!mp3.empty());
	}
	
    // ----
    // read
    // ----

    
    void test_read1 () {
        std::istringstream r("3 2\n2 1 1\n1 2 2 3");
        int i;
        int j;
        std::map<int, std::list<int> > mp0;
        const bool b = pfd_read(r, i, j, mp0);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    3);
        CPPUNIT_ASSERT(j ==    2);
    }
    
    void test_read2 () {
        std::istringstream r("1 0\n");
        int i;
        int j;
        std::map<int, std::list<int> > mp0;
        const bool b = pfd_read(r, i, j, mp0);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==    0);
    }
    
    void test_read3 () {
        std::istringstream r("5 4\n1 1 5\n2 1 5\n3 1 5\n4 1 5");
        int i;
        int j;
        std::map<int, std::list<int> > mp0;
        const bool b = pfd_read(r, i, j, mp0);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5);
        CPPUNIT_ASSERT(j ==    4);
    }
    
    
    // ----
    // func1
    // ----
    std::map<int, std::list<int> > emptyMap;
    void test_func1a () {
        std::list<int> pos1;
        std::list<int> as1;
        pos1.push_back(1);
        int i 	= func1(2, as1, pos1, emptyMap);
        CPPUNIT_ASSERT(i == 1);
    }
    
    void test_func1b () {
        std::list<int> pos2;
        std::list<int> as2;
        pos2.push_back(1);
        pos2.push_back(2);
        pos2.push_back(4);
        int i = func1(5, as2, pos2, emptyMap);
        CPPUNIT_ASSERT(i == 1);
    }
    
    void test_func1c () {
        std::list<int> pos3;
        std::list<int> as3;
        pos3.push_back(5);
        pos3.push_back(2);
        pos3.push_back(18);
        pos3.push_back(3);
        int i = func1(20, as3, pos3, emptyMap);
        CPPUNIT_ASSERT(i == 2);
    }

    
    // ----
    // func2
    // ----
    
    void test_func2a () {
		std::list<int> lst1;
		lst1.push_back (1);
		std::map<int, std::list<int> > mp1;
		mp1.insert ( std::pair<int,std::list<int> >(2,lst1) );

        std::list<int> pos1;
        pos1.push_back(1);
        func2(mp1, pos1, 1);
        CPPUNIT_ASSERT(mp1.empty());
    }
    
    void test_func2b () {
		std::list<int> lst2;
		lst2.push_back (2);
		lst2.push_back (4);
		std::map<int, std::list<int> > mp2;
		mp2.insert(std::pair<int, std::list<int> >(3, lst2));

        std::list<int> pos2;
        pos2.push_back(1);
        pos2.push_back(2);
        pos2.push_back(4);
        func2(mp2, pos2, 4);
        CPPUNIT_ASSERT(mp2[3].front() == 2);
    }
    
    void test_func2c () {
		std::list<int> lst3;		
		lst3.push_back (5);
		lst3.push_back (2);
		lst3.push_back (18);
		lst3.push_back (4);
		std::map<int, std::list<int> > mp3;
		mp3.insert(std::pair<int, std::list<int> >(3, lst3));
		mp3[3].sort();
		CPPUNIT_ASSERT(mp3[3].front() == 2);

        std::list<int> pos3;
        pos3.push_back(5);
        pos3.push_back(2);
        pos3.push_back(18);
        pos3.push_back(3);
        func2(mp3, pos3, 2);
        CPPUNIT_ASSERT(mp3[3].front() == 4);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
		build_tests();
		std::list<int> temp = pfd_eval(2, mp1);
        CPPUNIT_ASSERT(2 == temp.back());}

    void test_eval_2 () {
		build_tests();
		std::list<int> temp = pfd_eval(4, mp2);
		temp.sort();
        CPPUNIT_ASSERT(4 == temp.back());}

    void test_eval_3 () {
		build_tests();
		std::list<int> temp = pfd_eval(5, mp3);
        CPPUNIT_ASSERT(4 == temp.back());}

    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;
		std::list<int> temp = {1, 2, 3};
        pfd_print(w, temp);
        CPPUNIT_ASSERT(w.str() == "1 2 3\n\n");}
        
    void test_print2 () {
        std::ostringstream w;
		std::list<int> temp = {5, 5, 5, 5, 5, 5};
        pfd_print(w, temp);
        CPPUNIT_ASSERT(w.str() == "5 5 5 5 5 5\n\n");}
    
    void test_print3 () {
        std::ostringstream w;
		std::list<int> temp = {0, 1, 2, 3, 4};
        pfd_print(w, temp);
        CPPUNIT_ASSERT(w.str() == "0 1 2 3 4\n\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("2 1\n1 1 2\n");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1\n\n");}

    void test_solve_2 () {
        std::istringstream r("4 3\n2 1 1\n3 1 1\n4 1 2\n");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4\n\n");}

    void test_solve_3 () {
        std::istringstream r("5 0\n");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n\n");}



    // -----
    // suite
    // -----


    CPPUNIT_TEST_SUITE(Testpfd);
	CPPUNIT_TEST(build_tests);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_func1a);
    CPPUNIT_TEST(test_func1b);
    CPPUNIT_TEST(test_func1c);
    CPPUNIT_TEST(test_func2a);
    CPPUNIT_TEST(test_func2b);
    CPPUNIT_TEST(test_func2c);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "Testpfd.c++" << endl;
    CppUnit::TextTestRunner tr;
    tr.addTest(Testpfd::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
