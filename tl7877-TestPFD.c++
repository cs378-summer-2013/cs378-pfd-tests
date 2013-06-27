// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "PFD.h"

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {

    void test_solve() {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 ");
    }

    void test_solve_2() {
        std::istringstream r("7 3\n2 3 1 5 7\n4 1 2\n5 2 1 6");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 3 6 5 7 2 4 ");
    }
	
	void test_solve_3() {
        std::istringstream r("6 3\n3 1 5\n2 1 1\n1 2 3 4");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "4 5 3 1 2 6 ");
    }
	
	void test_loop() {
        std::istringstream r("2 1\n1 1 2\n");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1 ");
    }

    void test_loop_2() {
        std::istringstream r("2 1\n1 1 2\n\n3 1\n2 1 3");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1 ");
    }
	
	void test_loop_3() {
        std::istringstream r("2 1\n1 1 2\n\n6 3\n3 1 5 7\n2 1 1\n1 2 3 4");
        std::ostringstream w;
        pfd_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 1 ");
    }
	
	

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_loop);
    CPPUNIT_TEST(test_loop_2);
	CPPUNIT_TEST(test_loop_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main 
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
