/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o TestPFD.c++.app
    % valgrind TestPFD.c++.app >& TestPFD.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    
	// ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
        PFD_read(r, num_vertices, num_rules, adjacency);
        CPPUNIT_ASSERT(num_vertices == 5);
        CPPUNIT_ASSERT(num_rules == 4);
        CPPUNIT_ASSERT(adjacency[2][1] == 1);
        CPPUNIT_ASSERT(adjacency[2][5] == 1);
        CPPUNIT_ASSERT(adjacency[1][5] == 1);
        CPPUNIT_ASSERT(adjacency[1][3] == 1);
        CPPUNIT_ASSERT(adjacency[3][3] == 1);
        CPPUNIT_ASSERT(adjacency[4][1] == 1); }
	
	void test_read_2 () {
        std::istringstream r("6 2\n3 2 1 5\n2 2 5 3");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
        PFD_read(r, num_vertices, num_rules, adjacency);
        CPPUNIT_ASSERT(num_vertices == 6);
        CPPUNIT_ASSERT(num_rules == 2);
        CPPUNIT_ASSERT(adjacency[2][1] == 1);
        CPPUNIT_ASSERT(adjacency[2][5] == 1);
        CPPUNIT_ASSERT(adjacency[1][5] == 1);
        CPPUNIT_ASSERT(adjacency[1][3] == 1); }
		
	void test_read_3 () {
        std::istringstream r("3 2\n3 2 1 2\n2 1 1");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
        PFD_read(r, num_vertices, num_rules, adjacency);
        CPPUNIT_ASSERT(num_vertices == 3);
        CPPUNIT_ASSERT(num_rules == 2);
        CPPUNIT_ASSERT(adjacency[2][1] == 1);
        CPPUNIT_ASSERT(adjacency[2][2] == 1);
        CPPUNIT_ASSERT(adjacency[1][1] == 1); }

    // ----
    // eval
    // ----

    void test_eval_1 () {
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
		vector<int> result;
        PFD_read(r, num_vertices, num_rules, adjacency);
        PFD_eval(adjacency, num_vertices, result);
        CPPUNIT_ASSERT(result[0] == 1);
        CPPUNIT_ASSERT(result[1] == 5);
        CPPUNIT_ASSERT(result[2] == 3);
        CPPUNIT_ASSERT(result[3] == 2);
        CPPUNIT_ASSERT(result[4] == 4); }

    void test_eval_2 () {
        std::istringstream r("6 2\n3 2 1 5\n2 2 5 3");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
		vector<int> result;
        PFD_read(r, num_vertices, num_rules, adjacency);
        PFD_eval(adjacency, num_vertices, result);
        CPPUNIT_ASSERT(result[0] == 1);
        CPPUNIT_ASSERT(result[1] == 4);
        CPPUNIT_ASSERT(result[2] == 5);
        CPPUNIT_ASSERT(result[3] == 3);
        CPPUNIT_ASSERT(result[4] == 2);
        CPPUNIT_ASSERT(result[5] == 6); }

    void test_eval_3 () {
        std::istringstream r("3 2\n3 2 1 2\n2 1 1");
        int num_vertices;
		int num_rules;
		vector< vector <int> > adjacency;
		vector<int> result;
        PFD_read(r, num_vertices, num_rules, adjacency);
        PFD_eval(adjacency, num_vertices, result);
        CPPUNIT_ASSERT(result[0] == 1);
        CPPUNIT_ASSERT(result[1] == 2);
        CPPUNIT_ASSERT(result[2] == 3); }

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
		vector<int> result;
		result.push_back(1);
		result.push_back(5);
		result.push_back(3);
		result.push_back(2);
		result.push_back(4);
        PFD_print(w, result);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 "); }
		
	void test_print_2 () {
        std::ostringstream w;
		vector<int> result;
		result.push_back(1);
		result.push_back(4);
		result.push_back(5);
		result.push_back(3);
		result.push_back(2);
		result.push_back(6);
        PFD_print(w, result);
        CPPUNIT_ASSERT(w.str() == "1 4 5 3 2 6 "); }

	void test_print_3 () {
        std::ostringstream w;
		vector<int> result;
		result.push_back(1);
		result.push_back(2);
		result.push_back(3);
        PFD_print(w, result);
        CPPUNIT_ASSERT(w.str() == "1 2 3 "); }

    // -----
    // solve
    // -----

    void test_solve_1 () {
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 "); }
		
	void test_solve_2 () {
        std::istringstream r("6 2\n3 2 1 5\n2 2 5 3");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 4 5 3 2 6 "); }
		
	void test_solve_3 () {
        std::istringstream r("3 2\n3 2 1 2\n2 1 1");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 "); }

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
    //ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
