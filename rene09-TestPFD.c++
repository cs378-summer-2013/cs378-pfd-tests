// -------------------
// File: TestPFD.c++
// Author: Rene Garcia
// -------------------

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

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringstream, ostringstream
#include <string>   // ==
#include <vector>   // vector
#include <queue>    // priority queue

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

// -------
// TestPFD
// -------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----
    
    void test_read_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> i;
        PFD_read(r, i);
        CPPUNIT_ASSERT(i.size() == 5);
    }
    
    void test_read_2 () {
        std::istringstream r("1 0\n");
        std::vector<node> i;
        PFD_read(r, i);
        CPPUNIT_ASSERT(i.size() == 1);
    }
    
    void test_read_3 () {
        std::istringstream r("4 4\n3 1 4\n2 1 3\n4 1 1\n1 1 2");
        std::vector<node> i;
        PFD_read(r, i);
        CPPUNIT_ASSERT(i.size() != 5);
    }
    
    // -----
    // check
    // -----
    
    void test_check_1 () {
        std::vector<node> i;
        node a; a.name = 3; i.push_back(a);
        node b; b.name = 2; i.push_back(b);
        node c; c.name = 4; i.push_back(c);
        node d; d.name = 5; i.push_back(d);
        CPPUNIT_ASSERT(i.size() == 4);
        int j = 5;
        PFD_check(i, j);
        CPPUNIT_ASSERT(i.size() == 5);
    }
    
    void test_check_2 () {
        std::vector<node> i;
        CPPUNIT_ASSERT(i.size() == 0);
        int j = 1;
        PFD_check(i, j);
        CPPUNIT_ASSERT(i.size() == 1);        
    }
    
    void test_check_3 () {
        std::vector<node> i;
        node a; a.name = 3; i.push_back(a);
        node b; b.name = 2; i.push_back(b);
        node c; c.name = 4; i.push_back(c);
        node d; d.name = 1; i.push_back(d);
        CPPUNIT_ASSERT(i.size() != 0);
        int j = 4;
        PFD_check(i, j);
        CPPUNIT_ASSERT(i.size() != 0);
    }
    
    // ---
    //  <
    // ---
    
    void test_lessthan_1 () {
        node a; a.name = 3;
        a.edges.push_back(1);
        a.edges.push_back(5);
        node b; b.name = 4;
        b.edges.push_back(3);
        bool test = a < b;
        CPPUNIT_ASSERT(test == true);
    }
    
    void test_lessthan_2 () {
        node a; a.name = 3;
        node b; b.name = 4;
        bool test = a < b;
        CPPUNIT_ASSERT(test == false);
    }
    
    void test_lessthan_3 () {
        node a; a.name = 1;
        node b; b.name = 2;
        b.edges.push_back(5);
        b.edges.push_back(3);
        bool test = a < b;
        CPPUNIT_ASSERT(test != true);
    }
    
    // ------
    // update
    // ------
    
    void test_update_1 () {
       std::priority_queue<node> i;
        node a; a.name = 3; a.edges.push_back(1); a.edges.push_back(5);
        i.push(a);
        node b; b.name = 2; b.edges.push_back(5); b.edges.push_back(3);        
        i.push(b);
        node c; c.name = 4; c.edges.push_back(3);
        i.push(c);
        node d; d.name = 5; d.edges.push_back(1);
        i.push(d);
        int j = 1;
        PFD_update(i, j);
        CPPUNIT_ASSERT(i.top().edges.size() == 0);
    }
    
    void test_update_2 () {
        std::priority_queue<node> i;
        node a; a.name = 3; a.edges.push_back(2);
        i.push(a);
        node b; b.name = 2; b.edges.push_back(1);        
        i.push(b);
        node c; c.name = 4; c.edges.push_back(3);
        i.push(c);
        int j = 1;
        PFD_update(i, j);
        CPPUNIT_ASSERT(i.top().name == 2);
    }
    
    void test_update_3 () {
        std::priority_queue<node> i;
        node a; a.name = 3; a.edges.push_back(2); a.edges.push_back(1);
        i.push(a);
        node b; b.name = 2; b.edges.push_back(1);        
        i.push(b);
        int j = 1;
        PFD_update(i, j);
        CPPUNIT_ASSERT(i.top().name != 3);
    }
    
    // -----
    // print
    // -----
    
    void test_print_1 () {
        std::ostringstream w;
        std::priority_queue<node> i;
        node a; a.name = 3; a.edges.push_back(1); a.edges.push_back(5);
        i.push(a);
        node b; b.name = 2; b.edges.push_back(5); b.edges.push_back(3);        
        i.push(b);
        node c; c.name = 4; c.edges.push_back(3);
        i.push(c);
        node d; d.name = 5; d.edges.push_back(1);
        i.push(d);
        node e; e.name = 1;
        i.push(e);
        PFD_print(w, i);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n\n");
    }
    
    void test_print_2 () {
        std::ostringstream w;
        std::priority_queue<node> i;
        node a; a.name = 1; a.edges.push_back(4);
        i.push(a);
        node b; b.name = 2; b.edges.push_back(1);        
        i.push(b);
        node c; c.name = 3; c.edges.push_back(2);
        i.push(c);
        node d; d.name = 4; d.edges.push_back(3);
        i.push(d);
        PFD_print(w, i);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 \n\n");
    }
    
    void test_print_3 () {
        std::ostringstream w;
        std::priority_queue<node> i;
        node a; a.name = 1;
        i.push(a);
        PFD_print(w, i);
        CPPUNIT_ASSERT(w.str() == "1 \n\n");
    }
    
    // -----
    // solve
    // -----
    
    void test_solve_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n\n");
    }
    
    void test_solve_2 () {
        std::istringstream r("4 4\n1 1 4\n2 1 1\n3 1 2\n4 1 3\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 \n\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1 0\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 \n\n");
    }
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_check_1);
    CPPUNIT_TEST(test_check_2);
    CPPUNIT_TEST(test_check_3);
    CPPUNIT_TEST(test_lessthan_1);
    CPPUNIT_TEST(test_lessthan_2);
    CPPUNIT_TEST(test_lessthan_3);
    CPPUNIT_TEST(test_update_1);
    CPPUNIT_TEST(test_update_2);
    CPPUNIT_TEST(test_update_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();  
};

    
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
    return 0;
}
