/* UT EID : davismc2 */

/******************************************************************************
 * File: TestPFD.c++
 * Program: Project File Dependencies
 * Student: Merrill Davis
 * CS ID: davismc
 * Class: CS 378
 * Summer 2013
 *
 * Purpose:  unit tests for the Project File Dependencies program
 *
 *****************************************************************************/

/*
 * Includes snippets of code provided by the instructor, Glenn Downing
 */

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>   // vector array

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

    void test_read_one_line_1 () {
        std::istringstream pfd_in("5 4\n");
        std::vector<int> values;
        const bool result = read_one_line(values, pfd_in);
        CPPUNIT_ASSERT(result == true);
        CPPUNIT_ASSERT(values[0] == 5);
        CPPUNIT_ASSERT(values[1] == 4);}

    void test_read_one_line_2 () {
        std::istringstream pfd_in("3 2 1 5\n");
        std::vector<int> values;
        const bool result = read_one_line(values, pfd_in);
        CPPUNIT_ASSERT(result == true);
        CPPUNIT_ASSERT(values[0] == 3);
        CPPUNIT_ASSERT(values[1] == 2);
        CPPUNIT_ASSERT(values[2] == 1);
        CPPUNIT_ASSERT(values[3] == 5);}

    void test_read_one_line_3 () {
        std::istringstream pfd_in("0\n");
        std::vector<int> values;
        const bool result = read_one_line(values, pfd_in);
        CPPUNIT_ASSERT(result == true);
        CPPUNIT_ASSERT(values[0] == 0);}

    void test_read_one_line_4 () {
        std::istringstream pfd_in("");
        std::vector<int> values;
        const bool result = read_one_line(values, pfd_in);
        CPPUNIT_ASSERT(result == false);}

    void test_read_one_line_5 () {
        std::istringstream pfd_in("7 4\n3 7 6\n");
        std::vector<int> values;
        const bool result = read_one_line(values, pfd_in);
        CPPUNIT_ASSERT(result == true);
	CPPUNIT_ASSERT(values.size() == 2);
        CPPUNIT_ASSERT(values[0] == 7);
        CPPUNIT_ASSERT(values[1] == 4);}


    // -----
    // output_coll
    // -----

    void test_output_coll_1 () {
	std::vector<int> values = {3, 7, 9, 12, 15};
        std::ostringstream pfd_out;
        output_coll(values, pfd_out);
        CPPUNIT_ASSERT(pfd_out.str() == "3 7 9 12 15\n");}

    void test_output_coll_2 () {
	std::vector<int> values = {0};
        std::ostringstream pfd_out;
        output_coll(values, pfd_out);
        CPPUNIT_ASSERT(pfd_out.str() == "0\n");}


    void test_output_coll_3 () {
	std::vector<int> values = {12345678, -1};
        std::ostringstream pfd_out;
        output_coll(values, pfd_out);
        CPPUNIT_ASSERT(pfd_out.str() == "12345678 -1\n");}

    void test_output_coll_4 () {
	std::vector<int> values;
        std::ostringstream pfd_out;
        output_coll(values, pfd_out);
        CPPUNIT_ASSERT(pfd_out.str() == "\n");}


    // -----
    // solve_pfd
    // -----

    void test_solve_pfd_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        solve_pfd(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}

    void test_solve_pfd_2 () {
        std::istringstream r("3 1\n 1 1 3\n");
        std::ostringstream w;
        solve_pfd(r, w);
        CPPUNIT_ASSERT(w.str() == "2 3 1\n");}
    
    void test_solve_pfd_3 () {
        std::istringstream r("3 1\n2 1 3\n");
        std::ostringstream w;
        solve_pfd(r, w);
        CPPUNIT_ASSERT(w.str() == "1 3 2\n");}

   void test_solve_pfd_4 () {
        std::istringstream r("2 1\n2 1 1\n");
        std::ostringstream w;
        solve_pfd(r, w);
	std::cout << std::endl;
        CPPUNIT_ASSERT(w.str() == "1 2\n");}

   void test_solve_pfd_5 () {
        std::istringstream r("1 0\n");
        std::ostringstream w;
        solve_pfd(r, w);
	std::cout << std::endl;
        CPPUNIT_ASSERT(w.str() == "1\n");}
        
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_one_line_1);
    CPPUNIT_TEST(test_read_one_line_2);
    CPPUNIT_TEST(test_read_one_line_3);
    CPPUNIT_TEST(test_read_one_line_4);
    CPPUNIT_TEST(test_read_one_line_5);
    CPPUNIT_TEST(test_output_coll_1);
    CPPUNIT_TEST(test_output_coll_2);
    CPPUNIT_TEST(test_output_coll_3);
    //CPPUNIT_TEST(test_output_coll_4);
    CPPUNIT_TEST(test_solve_pfd_1);
    CPPUNIT_TEST(test_solve_pfd_2);
    CPPUNIT_TEST(test_solve_pfd_3);
    CPPUNIT_TEST(test_solve_pfd_4);
    CPPUNIT_TEST(test_solve_pfd_5);
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
