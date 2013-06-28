#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <map>
#include <vector>
#include <queue>

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
		std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
		int number_of_rules = 4;
		int number_of_files = 5;
		std::vector< std::vector< int > > list_of_rules (number_of_files + 1);
		pfd_read(r, list_of_rules, number_of_rules);
		std::vector< std::vector< int > > check {{}, {}, {5, 3}, {1, 5}, {3}, {1}};
		CPPUNIT_ASSERT(check == list_of_rules);
	}

	void test_read_2 () {
		std::istringstream r("2 1 1\n5 2 1 3\n6 2 2 3\n7 2 5 6\n");
		int number_of_rules = 4;
		int number_of_files = 7;
		std::vector< std::vector< int > > list_of_rules (number_of_files + 1);
		pfd_read(r, list_of_rules, number_of_rules);
		std::vector< std::vector< int > > check {{}, {}, {1}, {}, {}, {1, 3}, {2, 3}, {5, 6}};
		CPPUNIT_ASSERT(check == list_of_rules);
	}

	void test_read_3 () {
		std::istringstream r("1 2 3 7\n8 2 3 1\n5 3 3 7 8\n2 2 7 1\n6 5 3 7 1 8 2\n4 7 3 7 1 8 5 2 6");
		int number_of_rules = 6;
		int number_of_files = 8;
		std::vector< std::vector< int > > list_of_rules (number_of_files + 1);
		pfd_read(r, list_of_rules, number_of_rules);
		std::vector< std::vector< int > > check {{}, {3, 7}, {7, 1}, {}, {3, 7, 1, 8, 5, 2, 6}, {3, 7, 8}, {3, 7, 1, 8, 2}, {}, {3, 1}};
		CPPUNIT_ASSERT(check == list_of_rules);
	}


	// ----
	// eval
	// ----

	void test_eval_1() {
		std::vector< std::vector< int > > test {{}, {}, {5, 3}, {1, 5}, {3}, {1}};
		std::vector< int > result = pfd_eval(test);
		std::vector< int > check = {1, 5, 3, 2, 4};
		CPPUNIT_ASSERT(check == result);
	}

	
	void test_eval_2() {
		std::vector< std::vector< int > > test {{}, {}, {1}, {}, {}, {1, 3}, {2, 3}, {5, 6}};
		std::vector< int > result = pfd_eval(test);
		std::vector< int > check = {1, 2, 3, 4, 5, 6, 7};
		CPPUNIT_ASSERT(check == result);
	}

	void test_eval_3() {
		std::vector< std::vector< int > > test {{}, {3, 7}, {7, 1}, {}, {3, 7, 1, 8, 5, 2, 6}, {3, 7, 8}, {3, 7, 1, 8, 2}, {}, {3, 1}};
		std::vector< int > result = pfd_eval(test);
		std::vector< int > check = {3, 7, 1, 2, 8, 5, 6, 4};
		CPPUNIT_ASSERT(check == result);
	}

	// -----
	// print
	// -----

	void test_print_1() {
		std::ostringstream w;
		std::vector<int> to_print = {1, 5, 3, 2, 4};
		pfd_print(w, to_print);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}

	void test_print_2() {
		std::ostringstream w;
		std::vector<int> to_print = {1, 2, 3, 4, 5, 6, 7};
		pfd_print(w, to_print);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 6 7\n");
	}

	void test_print_3() {
		std::ostringstream w;
		std::vector<int> to_print = {3, 7, 1, 2, 8, 5, 6, 4};
		pfd_print(w, to_print);
		CPPUNIT_ASSERT(w.str() == "3 7 1 2 8 5 6 4\n");
	}


	void test_solve_1() {
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
		std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}

	
	void test_solve_2() {
		std::istringstream r("7 4\n2 1 1\n5 2 1 3\n6 2 2 3\n7 2 5 6\n");
		std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 6 7\n");
	}

	void test_solve_3() {
		std::istringstream r("8 6\n1 2 3 7\n8 2 3 1\n5 3 3 7 8\n2 2 7 1\n6 5 3 7 1 8 2\n4 7 3 7 1 8 5 2 6");
		std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "3 7 1 2 8 5 6 4\n");
	}

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
	CPPUNIT_TEST_SUITE_END();
};

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
