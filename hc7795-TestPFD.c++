#include <iostream> // cout, endl, ios_base
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner
#include "PFD.h"

// -----------
// TestCollatz
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----
    void test_read_firstline_1 () {
        std::istringstream r("4 2\n1 2 3 4\n3 1 4");
   
        
        int n=0;
	int m=0;
        PFD_read_firstline (r, n, m);
        CPPUNIT_ASSERT(n==4);
	CPPUNIT_ASSERT(m==2);
    }

    void test_read_firstline_2 () {
        std::istringstream r("5 4\n1 1 5\n2 2 3 5\n3 2 4 5\n4 1 5");
   
        int n=0;
	int m=0;
        PFD_read_firstline (r, n, m);
        CPPUNIT_ASSERT(n==5);
	CPPUNIT_ASSERT(m=4);
    }
    void test_read_firstline_3 () {
        std::istringstream r("3 2\n2 1 3\n3 1 1");
   
        int n=0;
	int m=0;
        PFD_read_firstline (r, n, m);
        CPPUNIT_ASSERT(n==3);
	CPPUNIT_ASSERT(m==2);
    }
    void test_read_1 () {
        std::istringstream r("4 2\n1 2 3 4\n3 1 4");
   
        std::vector< std::vector<int> > a;

        PFD_read(r, a, 4, 2);
        CPPUNIT_ASSERT(a.size() == 2);
    }

    void test_read_2 () {
        std::istringstream r("5 4\n1 1 5\n2 2 3 5\n3 2 4 5\n4 1 5");
   
        std::vector<std::vector<int> > a;

        PFD_read(r, a, 5, 4);
        CPPUNIT_ASSERT(a.size() == 4);
    }
    void test_read_3 () {
        std::istringstream r("3 2\n2 1 3\n3 1 1");
   
        std::vector<std::vector<int> > a;

        PFD_read(r, a, 3, 2);
        CPPUNIT_ASSERT(a.size() == 2);
    }


    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::vector<std::vector<int> > a;
        std::vector<int> result;
        std::vector<int> r1;
	std::vector<int> r2;
	r1.push_back(1);
	r1.push_back(2);
	r1.push_back(3);
	r1.push_back(4);
	r2.push_back(3);
	r2.push_back(1);
	r2.push_back(4);
        int n = 4;
        int m = 2;
        a.push_back(r1);
        a.push_back(r2);
        PFD_eval(a, result, n, m);
        CPPUNIT_ASSERT(result[0] == 2);
        CPPUNIT_ASSERT(result[1] == 4);
        CPPUNIT_ASSERT(result[2] == 3);
        CPPUNIT_ASSERT(result[3] == 1);}


    void test_eval_2 () {
        std::vector<std::vector<int> > a;
        std::vector<int> result;
        std::vector<int> r1;
	std::vector<int> r2;
	std::vector<int> r3;
        std::vector<int> r4;
	r1.push_back(1);
	r1.push_back(1);
	r1.push_back(5);
	r2.push_back(2);
	r2.push_back(2);
	r2.push_back(3);
	r2.push_back(5);
	r3.push_back(3);
	r3.push_back(2);
	r3.push_back(4);
	r3.push_back(5);
	r4.push_back(4);
	r4.push_back(1);
	r4.push_back(5);
        a.push_back(r1);
        a.push_back(r2);
        a.push_back(r3);
        a.push_back(r4);
        int n = 5;
        int m = 4;
        PFD_eval(a, result, n, m);
        CPPUNIT_ASSERT(result[0] == 5);
        CPPUNIT_ASSERT(result[1] == 1);
        CPPUNIT_ASSERT(result[2] == 4);
        CPPUNIT_ASSERT(result[3] == 3);
        CPPUNIT_ASSERT(result[4] == 2);}

    void test_eval_3 () {
        std::vector<std::vector<int> > a;
        std::vector<int> result;
        std::vector<int> r1;
	std::vector<int> r2;
	r1.push_back(2);
	r1.push_back(1);
	r1.push_back(3);
	r1.push_back(3);
	r2.push_back(1);
	r2.push_back(1);
        a.push_back(r1);
        a.push_back(r2);
        int n = 3;
        int m = 2;
        PFD_eval(a, result, n, m);
        CPPUNIT_ASSERT(result[0] == 1);
        CPPUNIT_ASSERT(result[1] == 3);
        CPPUNIT_ASSERT(result[2] == 2);}

    void test_contain_1 () {
        std::vector<int> a;
	a.push_back(2);
	a.push_back(6);
	a.push_back(3);
        CPPUNIT_ASSERT(contain(a, 2, 3)==true);}
    void test_contain_2 () {
        std::vector<int> a;
	a.push_back(2);
	a.push_back(1);
	a.push_back(3);
        CPPUNIT_ASSERT(contain(a, 1, 3)==true);}
    void test_contain_3 () {
        std::vector<int> a;
	a.push_back(2);
	a.push_back(1);
	a.push_back(3);
        CPPUNIT_ASSERT(contain(a, 5, 3)==false);}
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        std::vector<int> result;
        result.push_back(1);
        result.push_back(2);
        result.push_back(3);
        PFD_print(w, result, 3);
        CPPUNIT_ASSERT(w.str() == "1 2 3\n");}

    void test_print_2 () {
        std::ostringstream w;
        std::vector<int> result;
        result.push_back(1);
        result.push_back(2);
        result.push_back(3);
        result.push_back(4);
        PFD_print(w, result, 4);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4\n");}

    void test_print_3 () {
        std::ostringstream w;
        std::vector<int> result;
        result.push_back(1);
        result.push_back(2);
        result.push_back(3);
        result.push_back(4);
        result.push_back(5);
        PFD_print(w, result, 5);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("4 2\n1 2 3 4\n3 1 4");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 4 3 1\n");}

    void test_solve_2 () {
        std::istringstream r("3 0");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3\n");}

    void test_solve_3 () {
        std::istringstream r("5 4\n1 1 5\n2 2 3 5\n3 2 4 5\n4 1 5");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "5 1 4 3 2\n");}






    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_firstline_1);
    CPPUNIT_TEST(test_read_firstline_2);
    CPPUNIT_TEST(test_read_firstline_3);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_contain_1);
    CPPUNIT_TEST(test_contain_2);
    CPPUNIT_TEST(test_contain_3);
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
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
