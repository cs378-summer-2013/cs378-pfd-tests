#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

struct TestPFD : CppUnit::TestFixture {

	void test_read () {
		std::istringstream r ("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		int dep[100] = {0};
		int m = 4;
		pfd_read(r,m,adj,dep);
		CPPUNIT_ASSERT(dep[0] == 0);
		CPPUNIT_ASSERT(dep[1] == 2);
		CPPUNIT_ASSERT(dep[2] == 2);
		CPPUNIT_ASSERT(dep[3] == 1);
		CPPUNIT_ASSERT(dep[4] == 1);
		CPPUNIT_ASSERT(adj[2][0] == 1);
		CPPUNIT_ASSERT(adj[4][0] == 1);
		CPPUNIT_ASSERT(adj[1][2] == 1);
		CPPUNIT_ASSERT(adj[3][2] == 1);
		CPPUNIT_ASSERT(adj[1][4] == 1);
		CPPUNIT_ASSERT(adj[2][4] == 1);
	};

	void test_read2 () {
		std::istringstream r ("2 1 1\n3 1 2\n4 1 3\n5 1 4");
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		int dep[100] = {0};
		int m = 4;
		pfd_read(r,m,adj,dep);
		CPPUNIT_ASSERT(dep[0] == 0);
		CPPUNIT_ASSERT(dep[1] == 1);
		CPPUNIT_ASSERT(dep[2] == 1);
		CPPUNIT_ASSERT(dep[3] == 1);
		CPPUNIT_ASSERT(dep[4] == 1);
		CPPUNIT_ASSERT(adj[1][0] == 1);
		CPPUNIT_ASSERT(adj[2][1] == 1);
		CPPUNIT_ASSERT(adj[3][2] == 1);
		CPPUNIT_ASSERT(adj[4][3] == 1);
	};

	void test_read3 () {
		std::istringstream r ("5 4 1 2 3 4");
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		int dep[100] = {0};
		int m = 1;
		pfd_read(r,m,adj,dep);
		CPPUNIT_ASSERT(dep[0] == 0);
		CPPUNIT_ASSERT(dep[1] == 0);
		CPPUNIT_ASSERT(dep[2] == 0);
		CPPUNIT_ASSERT(dep[3] == 0);
		CPPUNIT_ASSERT(dep[4] == 4);
		CPPUNIT_ASSERT(adj[4][0] == 1);
		CPPUNIT_ASSERT(adj[4][1] == 1);
		CPPUNIT_ASSERT(adj[4][2] == 1);
		CPPUNIT_ASSERT(adj[4][3] == 1);
	};

	void test_print () {
		std::ostringstream w;
		std::vector<int> v = {1,5,3,2,4};
		pfd_print(w,v);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}

	void test_print2 () {
		std::ostringstream w;
		std::vector<int> v = {1,2,3,4,5};
		pfd_print(w,v);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n");
	}

	void test_print3 () {
		std::ostringstream w;
		std::vector<int> v = {5,3};
		pfd_print(w,v);
		CPPUNIT_ASSERT(w.str() == "5 3\n");
	}

	void test_solve () {
		std::istringstream r ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
		std::ostringstream w;
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}

	void test_solve2 () {
		std::istringstream r ("5 4\n2 1 1\n3 1 2\n4 1 3\n5 1 4");
		std::ostringstream w;
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n");
	}

	void test_solve3 () {
		std::istringstream r ("5 1\n5 4 1 2 3 4");
		std::ostringstream w;
		pfd_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n");
	}

	void test_top_sort () {
		int n = 5;
		std::vector<int> v;
		int dep[100] = {0};
		dep[1] = 2;
		dep[2] = 2;
		dep[3] = 1;
		dep[4] = 1;
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		adj[2][0] = 1;
		adj[4][0] = 1;
		adj[1][2] = 1;
		adj[3][2] = 1;
		adj[1][4] = 1;
		adj[2][4] = 1;
		top_sort(adj,dep,v,n);
		CPPUNIT_ASSERT(v.size() == 5);
		for (int i = 0; i < n; ++i)
			CPPUNIT_ASSERT(dep[i] == 0);
		CPPUNIT_ASSERT(v[0] == 1);
		CPPUNIT_ASSERT(v[1] == 5);
		CPPUNIT_ASSERT(v[2] == 3);
		CPPUNIT_ASSERT(v[3] == 2);
		CPPUNIT_ASSERT(v[4] == 4);
	}

	void test_top_sort2 () {
		int n = 5;
		std::vector<int> v;
		int dep[100] = {0};
		dep[1] = 1;
		dep[2] = 1;
		dep[3] = 1;
		dep[4] = 1;
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		adj[1][0] = 1;
		adj[2][1] = 1;
		adj[3][2] = 1;
		adj[4][3] = 1;
		top_sort(adj,dep,v,n);
		CPPUNIT_ASSERT(v.size() == 5);
		for (int i = 0; i < n; ++i)
			CPPUNIT_ASSERT(dep[i] == 0);
		CPPUNIT_ASSERT(v[0] == 1);
		CPPUNIT_ASSERT(v[1] == 2);
		CPPUNIT_ASSERT(v[2] == 3);
		CPPUNIT_ASSERT(v[3] == 4);
		CPPUNIT_ASSERT(v[4] == 5);
	}

	void test_top_sort3 () {
		int n = 5;
		std::vector<int> v;
		int dep[100] = {0};
		dep[4] = 4;
		int adj[100][100];
		for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
						adj[i][j] = 0;
		adj[4][0] = 1;
		adj[4][1] = 1;
		adj[4][2] = 1;
		adj[4][3] = 1;
		top_sort(adj,dep,v,n);
		CPPUNIT_ASSERT(v.size() == 5);
		for (int i = 0; i < n; ++i)
			CPPUNIT_ASSERT(dep[i] == 0);
		CPPUNIT_ASSERT(v[0] == 1);
		CPPUNIT_ASSERT(v[1] == 2);
		CPPUNIT_ASSERT(v[2] == 3);
		CPPUNIT_ASSERT(v[3] == 4);
		CPPUNIT_ASSERT(v[4] == 5);
	}

	CPPUNIT_TEST_SUITE(TestPFD);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print2);
	CPPUNIT_TEST(test_print3);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve2);
	CPPUNIT_TEST(test_solve3);
	CPPUNIT_TEST(test_top_sort);
	CPPUNIT_TEST(test_top_sort2);
	CPPUNIT_TEST(test_top_sort3);
	CPPUNIT_TEST_SUITE_END(); 

};

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

