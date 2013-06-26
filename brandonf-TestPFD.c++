// --------------------------------
// projects/collatz/TestCollatz.c++
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
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lcppunit -ldl
    % valgrind TestCollatz >& TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector> // vector

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

using namespace std;

// -----------
// TestCollatz
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("3 2\n1 1 3\n2 1 3");
        int v;
        int e;
        vector<vector<int> > al;

        const bool b = pfd_read(r, al, v, e);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v ==    3);
        CPPUNIT_ASSERT(e ==   2);
        CPPUNIT_ASSERT(al.size() ==   2);
    }

    void test_read_2 () {
        std::istringstream r("2 0");
        int v;
        int e;
        vector<vector<int> > al;

        const bool b = pfd_read(r, al, v, e);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v ==    2);
        CPPUNIT_ASSERT(e ==   0);
        CPPUNIT_ASSERT(al.size() ==   0);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        vector<vector<int> > al;
        int v = 2;
        int e = 0;
        vector<int> turns = pfd_eval(al, v, e);
        CPPUNIT_ASSERT(turns[0] == 1);
        CPPUNIT_ASSERT(turns[1] == 2);}

    void test_eval_2 () {
        vector<vector<int> > al;
        vector<int> r1;
        vector<int> r2;
        r1.push_back(1);
        r1.push_back(2);
        r2.push_back(2);
        r2.push_back(2);
        al.push_back(r1);
        al.push_back(r2);
        int v = 3;
        int e = 2;
        vector<int> turns = pfd_eval(al, v, e);
        CPPUNIT_ASSERT(turns[0] == 3);
        CPPUNIT_ASSERT(turns[1] == 1);        
        CPPUNIT_ASSERT(turns[2] == 2);}        

    void test_eval_3 () {
        vector<vector<int> > al;
        vector<int> r1;
        vector<int> r2;
        r1.push_back(2);
        r1.push_back(3);
        r1.push_back(4);
        r2.push_back(5);
        al.push_back(r1);
        al.push_back(r2);
        int v = 5;
        int e = 2;
        vector<int> turns = pfd_eval(al, v, e);
        CPPUNIT_ASSERT(turns[0] == 1);
        CPPUNIT_ASSERT(turns[1] == 3);        
        CPPUNIT_ASSERT(turns[2] == 4);
        CPPUNIT_ASSERT(turns[3] == 5);
        CPPUNIT_ASSERT(turns[4] == 2);} 
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        vector<int> turns;
        turns.push_back(1);
        turns.push_back(2);
        pfd_print(w, turns);
        CPPUNIT_ASSERT(w.str() == "1 2\n");}

    void test_print_2 () {
        std::ostringstream w;
        vector<int> turns;
        turns.push_back(1);
        turns.push_back(5);
        turns.push_back(3);
        turns.push_back(2);
        turns.push_back(4);
        pfd_print(w, turns);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("3 2\n1 1 3\n2 1 3");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "3 1 2\n");}

    void test_solve_2 () {
        std::istringstream r("2 0");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n");}        

    void test_solve_3 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}        

    void test_solve_4 () {
        std::istringstream r("5 1\n1 3 2 3 4");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 3 4 1 5\n");}   

    void test_solve_5 () {
        std::istringstream r("5 2\n1 3 2 3 4\n2 1 5");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "3 4 5 2 1\n");}           

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
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
