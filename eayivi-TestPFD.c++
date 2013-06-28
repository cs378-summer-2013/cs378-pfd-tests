/*
 *  TestPFD.c++
 *  
 *
 * Sophia Hernandez smh3665
 * Enam Ayivi aea787
 *
 */

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

#include "PFD.h"

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

// -----------
// TestPFD
// -----------


struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        int n;
        int m;
        const std::vector<Vertex> v = pfd_read(r, n, m);
       // CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(n ==   5);
        CPPUNIT_ASSERT(m ==   4);
        CPPUNIT_ASSERT(v[0].num_deps == 0);    //node 1 has no dependencies
        CPPUNIT_ASSERT(v[1].num_deps == 2);    //node 2 has 2 dependencies
        CPPUNIT_ASSERT(v[2].num_deps == 2);    //node 3 has 2 dependencies
        CPPUNIT_ASSERT(v[3].num_deps == 1);    //node 4 has 1 dependency
        CPPUNIT_ASSERT(v[4].num_deps == 1);    //node 5 has 1 dependency
    }


    void test_read_2 () {
        std::istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1");
        int n;
        int m;
        const std::vector<Vertex> v = pfd_read(r, n, m);
        CPPUNIT_ASSERT(n ==   5);
        CPPUNIT_ASSERT(m ==   4);
        CPPUNIT_ASSERT(v[2].num_deps == 1);    //node 3 has 1 dependency
        CPPUNIT_ASSERT(v[0].edges_in.size() == 0);
    }

    
    void test_read_3 () {
        std::istringstream r("8 6 \n2 1 4\n3 1 2\n5 2 1 4\n8 2 4 1\n6 1 4\n4 1 1");
        int n;
        int m;
        const std::vector<Vertex> v = pfd_read(r, n, m);
        CPPUNIT_ASSERT(n ==   8);
        CPPUNIT_ASSERT(m ==   6);
        CPPUNIT_ASSERT(v[1].num_deps == 1);    //node 2 has 1 dependency
        CPPUNIT_ASSERT(v[2].num_deps == 1);    //node 3 has 1 dependency
        CPPUNIT_ASSERT(v[3].num_deps == 1);    //node 4 has 1 dependency
        CPPUNIT_ASSERT(v[4].num_deps == 2);    //node 5 has 1 dependency
        CPPUNIT_ASSERT(v[5].num_deps == 1);    //node 6 has 1 dependency
        CPPUNIT_ASSERT(v[6].num_deps == 0);    //node 7 has 1 dependency
        CPPUNIT_ASSERT(v[7].num_deps == 2);    //node 8 has 2 dependency
        CPPUNIT_ASSERT(v[7].edges_in.size() == 2);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        int n;
        int m;
        std::vector<Vertex> v = pfd_read(r, n, m);
        std::vector<int> check = {1, 5, 3, 2, 4};
        std::vector<int> out = pfd_eval(v);
        for(std::vector<int>::const_iterator it = out.begin(); it != out.end(); ++it){
            CPPUNIT_ASSERT(*it == check.front());
             check.erase(check.begin());
        }
    }

    void test_eval_2 () {
        std::istringstream r("5 4\n3 1 1 \n2 2 5 3\n4 1 3\n5 1 1");
        int n;
        int m;
        std::vector<Vertex> v = pfd_read(r, n, m);
        std::vector<int> check = {1, 3, 4, 5, 2};
        std::vector<int> out = pfd_eval(v);
        for(std::vector<int>::const_iterator it = out.begin(); it != out.end(); ++it){
            CPPUNIT_ASSERT(*it == check.front());
            check.erase(check.begin());
        }
    }

    void test_eval_3 () {
        std::istringstream r("8 6 \n2 1 4\n3 1 2\n5 2 1 4\n8 2 4 1\n6 1 4\n4 1 1");
        int n;
        int m;
        std::vector<Vertex> v = pfd_read(r, n, m); 
        std::vector<int> check = {1, 4, 2, 3, 5, 6, 7, 8};
        CPPUNIT_ASSERT(n ==   8);
        CPPUNIT_ASSERT(m ==   6);
        std::vector<int> out = pfd_eval(v);
        for(std::vector<int>::const_iterator it = out.begin(); it != out.end(); ++it){
            CPPUNIT_ASSERT(*it == check.front());
            check.erase(check.begin());
        }
    }


    // -----
    // print
    // -----

    void test_print_1 () {
        std::vector<int> check = {1, 4, 2, 6, 7, 8};
        std::ostringstream w;
        pfd_print(w, check);
        CPPUNIT_ASSERT(w.str() == "1 4 2 6 7 8 \n");}

    void test_print_2 () {
        std::vector<int> check = {3, 2, 1, 5};    
        std::ostringstream w;
        pfd_print(w, check);
        CPPUNIT_ASSERT(w.str() == "3 2 1 5 \n");}

    void test_print_3 () {
        std::vector<int> check = {0};
        std::ostringstream w;
        pfd_print(w, check);
        CPPUNIT_ASSERT(w.str() == "0 \n");}

        
    // -----
    // solve
    // -----
    void test_solve_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n");}

    void test_solve_2 () {
        std::istringstream r("1 0");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 \n");}
                
    void test_solve_3 () {
        std::istringstream r("8 6 \n2 1 4\n3 1 2\n5 2 1 4\n8 2 4 1\n6 1 4\n4 1 1");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 4 2 3 5 6 7 8 \n");}


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

   
