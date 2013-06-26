
/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o PFD -lcppunit -ldl
    % valgrind PFD >& TestPFD.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

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
		std::vector<int> x;
		x.resize(5);
   		std::vector< std::vector<int> > b;
		for(int i = 0; i < 5; ++i)
			b.push_back(x);

        std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        pfd_read(r, b, 4);
		int check[5][5] = {
						{0,0,0,0,0},
						{0,0,1,0,1},
						{1,0,0,0,1},
						{0,0,1,0,0},
						{1,0,0,0,0}}; 
		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j)
        		CPPUNIT_ASSERT(b[i][j] == check[i][j]);
		}
    }

	void test_read_2 () {
		std::vector<int> x;
		x.resize(5);
   		std::vector< std::vector<int> > b;
		for(int i = 0; i < 5; ++i)
			b.push_back(x);

        std::istringstream r("3 2 2 5\n2 2 1 3\n4 1 3\n5 1 1");
        pfd_read(r, b, 4);
		int check[5][5] = {
						{0,0,0,0,0},
						{1,0,1,0,0},
						{0,1,0,0,1},
						{0,0,1,0,0},
						{1,0,0,0,0}}; 
		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j)
        		CPPUNIT_ASSERT(b[i][j] == check[i][j]);
		}
    }

	void test_read_3 () {
		std::vector<int> x;
		x.resize(2);
   		std::vector< std::vector<int> > b;
		for(int i = 0; i < 2; ++i)
			b.push_back(x);

        std::istringstream r("1 1 2\n");
        pfd_read(r, b, 1);
		int check[2][2] = {
						{0,1},
						{0,0}}; 
		for(int i = 0; i < 2; ++i){
			for(int j = 0; j < 2; ++j)
        		CPPUNIT_ASSERT(b[i][j] == check[i][j]);
		}
    }



	//-----
	//print
	//-----

	void test_print_1(){
		std::ostringstream w;
		std::vector<int> val = {1, 5, 3, 2, 4};
		int v = 5;
		pfd_print(w, val, v);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4");
	}

	void test_print_2(){
		std::ostringstream w;
		std::vector<int> val = {1, 5, 3};
		int v = 3;
		pfd_print(w, val, v);
		CPPUNIT_ASSERT(w.str() == "1 5 3");
	}

	void test_print_3(){
		std::ostringstream w;
		std::vector<int> val = {4, 2, 3, 1, 5};
		int v = 5;
		pfd_print(w, val, v);
		CPPUNIT_ASSERT(w.str() == "4 2 3 1 5");
	}


	// ----
    // eval
    // ----
	
    void test_eval_1 () {
		std::ostringstream w;
		std::vector< std::vector<int> > b = {
						{0,0,0,0,0},
						{0,0,1,0,1},
						{1,0,0,0,1},
						{0,0,1,0,0},
						{1,0,0,0,0}}; 
		pfd_eval(w, b, 5);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4");
    }

	void test_eval_2 () {
		std::ostringstream w;
		std::vector< std::vector<int> > b = {
						{0,1},
						{0,0}}; 
		pfd_eval(w, b, 2);
		CPPUNIT_ASSERT(w.str() == "2 1");
    }

	void test_eval_3 () {
		std::ostringstream w;
		std::vector< std::vector<int> > b = {
						{0,0,0,0,0},
						{0,0,1,0,1},
						{1,0,0,0,0},
						{0,0,1,0,0},
						{1,0,0,0,0}}; 
		pfd_eval(w, b, 5);
		CPPUNIT_ASSERT(w.str() == "1 3 4 5 2");
    }


	// -----
    // solve
    // -----
	
    void test_solve_1 () {
		std::ostringstream w;
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4");
    }

	void test_solve_2 () {
		std::ostringstream w;
		std::istringstream r("2 1\n1 1 2");
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "2 1");
    }

	void test_solve_3 () {
		std::ostringstream w;
		std::istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1");
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "1 3 4 5 2");
    }
        

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);

    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
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
