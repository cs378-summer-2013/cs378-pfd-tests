// --------------------------------
// projects/PFD/TestPFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o TestPFD -lcppunit -ldl
    % valgrind TestPFD >& TestPFD.out
*/

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdio.h>
#include <string.h>
#include <queue>


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

    void test_read_1 () {
        std::istringstream r("2 0\n");
        int i;
        int j;
		std::vector< std::vector<int> > vec;
        const bool b = PFD_read(r, i, j, vec);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    2);
        CPPUNIT_ASSERT(j ==   0);
		CPPUNIT_ASSERT(vec.size() ==   0);}
		
    void test_read_2 () {
        std::istringstream r("5 4\n 3 2 1 5\n 2 2 5 3\n 4 1 3\n 5 1 1\n");
        int i;
        int j;
		std::vector< std::vector<int> > vec;
        const bool b = PFD_read(r, i, j, vec);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5);
        CPPUNIT_ASSERT(j ==   4);
		CPPUNIT_ASSERT(vec.size() ==   4);}
		
    void test_read_3 () {
        std::istringstream r("3 1\n1 2\n");
        int i;
        int j;
		std::vector< std::vector<int> > vec;
        const bool b = PFD_read(r, i, j, vec);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    3);
        CPPUNIT_ASSERT(j ==   1);
		CPPUNIT_ASSERT(vec.size() ==   1);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
		std::istringstream r("2 0\n");
        int i = 2;
        int j = 0;
		std::vector< std::vector<int> > vec;
		std::vector< int > avec;
        const std::vector< int > v = PFD_eval(i, j, vec, avec);
        CPPUNIT_ASSERT(v.size() == 2);}

    void test_eval_2 () {
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        int i = 5;
        int j = 4;
		std::vector< std::vector<int> > vec;
		std::vector< int > avec;
        const std::vector< int > v = PFD_eval(i, j, vec, avec);
        CPPUNIT_ASSERT(v.size() == 5);}

    void test_eval_3 () {
		std::istringstream r("3 1\n1 1 2\n");
        int i = 3;
        int j = 1;
		std::vector< std::vector<int> > vec;
		std::vector< int > avec;
        const std::vector< int > v = PFD_eval(i, j, vec, avec);
        CPPUNIT_ASSERT(v.size() == 3);}

		
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
		std::vector< int > avec = {1, 2, 3};
        PFD_print(w, avec);
		std::string s = w.str();
        CPPUNIT_ASSERT(w.str() == "1 2 3\n");}
		
    void test_print_2 () {
        std::ostringstream w;
		std::vector< int > avec = {1, 5, 3, 2, 4};
        PFD_print(w, avec);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}
		
    void test_print_3 () {
        std::ostringstream w;
		std::vector< int > avec = {1, 3, 4, 5, 8, 9, 11, 10, 2, 7, 6};
        PFD_print(w, avec);
        CPPUNIT_ASSERT(w.str() == "1 3 4 5 8 9 11 10 2 7 6\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("2 0\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n");}

    void test_solve_2 () {
        std::istringstream r("5 4\n 3 2 1 5\n 2 2 5 3\n 4 1 3\n 5 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}
		
    void test_solve_3 () {
        std::istringstream r("3 1\n 1 1 2\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1 3\n");}
		
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
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
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}