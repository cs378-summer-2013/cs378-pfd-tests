#include <iostream> // cout, endl, ios_base
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "PFD.h"



struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream r("2 1\n");
        int i;
        int j;
        const bool b = PFD_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 2);
        CPPUNIT_ASSERT(j == 1);}
        
    void test_read_2 () {
        std::istringstream r("5 4\n");
        int i;
        int j;
        const bool b = PFD_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 5);
        CPPUNIT_ASSERT(j == 4);}
        
    void test_read_3 () {
        std::istringstream r("6 3\n");
        int i;
        int j;
        const bool b = PFD_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 6);
        CPPUNIT_ASSERT(j == 3);}
        
    void test_read_4 () {
        std::istringstream r("100 99\n");
        int i;
        int j;
        const bool b = PFD_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 100);
        CPPUNIT_ASSERT(j == 99);}
        
    void test_PFD_r_help() {
        std::istringstream r("2 1 1\n");
        int j = 1;
        vector<jobR> jobs(3);
        const bool b = PFD_r_help(r, j, jobs);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(jobs.at(1).jnum == 1);
        CPPUNIT_ASSERT(jobs.at(1).deps == 0);
        CPPUNIT_ASSERT(jobs.at(2).jnum == 2);
        CPPUNIT_ASSERT(jobs.at(2).deps == 1);
        CPPUNIT_ASSERT(jobs.at(2).d.at(0) == 1);
    }
    void test_PFD_r_help_2() {
        std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        int j = 4;
        vector<jobR> jobs(6);
        const bool b = PFD_r_help(r, j, jobs);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(jobs.at(1).jnum == 1);
        CPPUNIT_ASSERT(jobs.at(1).deps == 0);
        CPPUNIT_ASSERT(jobs.at(2).jnum == 2);
        CPPUNIT_ASSERT(jobs.at(2).deps == 2);
        CPPUNIT_ASSERT(!jobs.at(2).d.empty());
        CPPUNIT_ASSERT(jobs.at(3).jnum == 3);
        CPPUNIT_ASSERT(jobs.at(3).deps == 2);
        CPPUNIT_ASSERT(!jobs.at(3).d.empty());
        CPPUNIT_ASSERT(jobs.at(4).jnum == 4);
        CPPUNIT_ASSERT(jobs.at(4).deps == 1);
        CPPUNIT_ASSERT(!jobs.at(4).d.empty());
        CPPUNIT_ASSERT(jobs.at(5).jnum == 5);
        CPPUNIT_ASSERT(jobs.at(5).deps == 1);
        CPPUNIT_ASSERT(!jobs.at(5).d.empty());
    }
    void test_PFD_r_help_3() {
        std::istringstream r("3 3 2 4 5\n1 1 3\n4 1 2\n");
        int j = 3;
        vector<jobR> jobs(7);
        const bool b = PFD_r_help(r, j, jobs);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(jobs.at(1).jnum == 1);
        CPPUNIT_ASSERT(jobs.at(1).deps == 1);
        CPPUNIT_ASSERT(!jobs.at(1).d.empty());
        CPPUNIT_ASSERT(jobs.at(2).jnum == 2);
        CPPUNIT_ASSERT(jobs.at(2).deps == 0);
        CPPUNIT_ASSERT(jobs.at(3).jnum == 3);
        CPPUNIT_ASSERT(jobs.at(3).deps == 3);
        CPPUNIT_ASSERT(!jobs.at(3).d.empty());
        CPPUNIT_ASSERT(jobs.at(4).jnum == 4);
        CPPUNIT_ASSERT(jobs.at(4).deps == 1);
        CPPUNIT_ASSERT(!jobs.at(4).d.empty());
        CPPUNIT_ASSERT(jobs.at(5).jnum == 5);
        CPPUNIT_ASSERT(jobs.at(5).deps == 0);
        CPPUNIT_ASSERT(jobs.at(6).jnum == 6);
        CPPUNIT_ASSERT(jobs.at(6).deps == 0);
    }
    void test_PFD_r_help_4() {
        std::istringstream r("4 3 1 2 3\n 2 1 4\n");
        int j = 2;
        vector<jobR> jobs(5);
        const bool b = PFD_r_help(r, j, jobs);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(jobs.at(1).jnum == 1);
        CPPUNIT_ASSERT(jobs.at(1).deps == 0);
        CPPUNIT_ASSERT(jobs.at(2).jnum == 2);
        CPPUNIT_ASSERT(jobs.at(2).deps == 1);
        CPPUNIT_ASSERT(!jobs.at(2).d.empty());
        CPPUNIT_ASSERT(jobs.at(3).jnum == 3);
        CPPUNIT_ASSERT(jobs.at(3).deps == 0);
        CPPUNIT_ASSERT(jobs.at(4).jnum == 4);
        CPPUNIT_ASSERT(jobs.at(4).deps == 3);
        CPPUNIT_ASSERT(!jobs.at(4).d.empty());
    }
    
    void test_eval_1 () {
        vector<jobR> tmp(3);
        tmp.at(1).jnum = 1;
        tmp.at(1).deps = 0;
        tmp.at(2).jnum = 2;
        tmp.at(2).deps = 1;
        tmp.at(2).d.push_back(1);
        vector<int> v = PFD_eval(2, 1, tmp);
        CPPUNIT_ASSERT(!v.empty());
    }
    void test_eval_2 () {
        vector<jobR> tmp(6);
        tmp.at(1).jnum = 1;
        tmp.at(1).deps = 0;
        tmp.at(2).jnum = 2;
        tmp.at(2).deps = 2;
        tmp.at(2).d = { 5, 3 };
        tmp.at(3).jnum = 3;
        tmp.at(3).deps = 2;
        tmp.at(3).d = { 1, 5 };
        tmp.at(4).jnum = 4;
        tmp.at(4).deps = 1;
        tmp.at(4).d.push_back(3);
        tmp.at(5).jnum = 5;
        tmp.at(5).deps = 1;
        tmp.at(5).d.push_back(1);
        vector<int> v = PFD_eval(5, 4, tmp);
        CPPUNIT_ASSERT(!v.empty());
    }
	void test_eval_3 () {
        vector<jobR> tmp(7);
        tmp.at(1).jnum = 1;
        tmp.at(1).deps = 1;
		tmp.at(1).d = { 3 };
        tmp.at(2).jnum = 2;
        tmp.at(2).deps = 0;
        tmp.at(3).jnum = 3;
        tmp.at(3).deps = 3;
        tmp.at(3).d = { 2, 4, 5 };
        tmp.at(4).jnum = 4;
        tmp.at(4).deps = 1;
        tmp.at(4).d.push_back(2);
        tmp.at(5).jnum = 5;
        tmp.at(5).deps = 0;
        tmp.at(6).jnum = 6;
        tmp.at(6).deps = 0;
        vector<int> v = PFD_eval(5, 4, tmp);
        CPPUNIT_ASSERT(!v.empty());
    }
    void test_print () {
        std::ostringstream w;
        vector<int> re;
        re.push_back(1);
        re.push_back(2);
        PFD_print(w, re);
        CPPUNIT_ASSERT(w.str() == "1 2");
    }
    void test_print_2 () {
        std::ostringstream w;
        vector<int> re = { 1, 5, 3, 2, 4};	
        PFD_print(w, re);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4");
    }
	void test_print_3 () {
        std::ostringstream w;
        vector<int> re = { 2, 4, 5, 3, 1, 6 };
        PFD_print(w, re);
        CPPUNIT_ASSERT(w.str() == "2 4 5 3 1 6");
    }
    void test_solve () {
        std::istringstream r("2 1\n2 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2");
    }
    void test_solve_2 () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4");
    }
	void test_solve_3 () {
        std::istringstream r("6 3\n3 3 2 4 5\n1 1 3\n4 1 2\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 4 5 3 1 6");
    }
        
        

     // -----
    // suite
    // -----

 CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_PFD_r_help);
    CPPUNIT_TEST(test_PFD_r_help_2);
    CPPUNIT_TEST(test_PFD_r_help_3);
    CPPUNIT_TEST(test_PFD_r_help_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
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
