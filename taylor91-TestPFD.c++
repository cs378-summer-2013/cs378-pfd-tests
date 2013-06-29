// --------
// Includes
// --------
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "PFD.h"

// -------
// TestPFD
// -------
struct TestPFD : CppUnit::TestFixture
{
	// ---------	
	// test_read
	// ---------	
	void test_read()
	{
		std::istringstream r("2 1\n1 1 2\n");
		std::vector< std::vector<char> > mat;
		const bool b = pfd_read(r, mat);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(mat[1][2] == 1);
		CPPUNIT_ASSERT(mat[1][1] == 0);
	}

	void test_read_2()
	{
		std::istringstream r("3 2\n1 2 2 3\n3 1 2\n");
		std::vector< std::vector<char> > mat;
		const bool b = pfd_read(r, mat);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(mat[1][2] == 1);
		CPPUNIT_ASSERT(mat[1][3] == 1);
		CPPUNIT_ASSERT(mat[2][1] == 0);
		CPPUNIT_ASSERT(mat[2][3] == 0);
		CPPUNIT_ASSERT(mat[3][1] == 0);
		CPPUNIT_ASSERT(mat[3][2] == 1);
	}

	void test_read_3()
	{
		std::istringstream r("4 1\n2 4 1 2 3 4");
		std::vector< std::vector<char> > mat;
		const bool b = pfd_read(r, mat);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(mat[2][1] == 1);
		CPPUNIT_ASSERT(mat[2][2] == 1);
		CPPUNIT_ASSERT(mat[2][3] == 1);
		CPPUNIT_ASSERT(mat[2][4] == 1);
		CPPUNIT_ASSERT(mat[1][1] == 0);
		CPPUNIT_ASSERT(mat[1][2] == 0);
		CPPUNIT_ASSERT(mat[1][3] == 0);
		CPPUNIT_ASSERT(mat[1][4] == 0);
		CPPUNIT_ASSERT(mat[3][1] == 0);
		CPPUNIT_ASSERT(mat[3][2] == 0);
		CPPUNIT_ASSERT(mat[3][3] == 0);
		CPPUNIT_ASSERT(mat[3][4] == 0);
		CPPUNIT_ASSERT(mat[4][1] == 0);
		CPPUNIT_ASSERT(mat[4][2] == 0);
		CPPUNIT_ASSERT(mat[4][3] == 0);
		CPPUNIT_ASSERT(mat[4][4] == 0);
	}

	// ------------
	// test_crawler
	// ------------
	void test_crawler ()
	{
	    std::istringstream r("2 1\n1 1 2\n");
	    std::vector< std::vector<char> > mat;
	    if(pfd_read(r, mat))
		{
			std::vector<int> results = pfd_crawler(mat);
			CPPUNIT_ASSERT(results[0] == 2);
			CPPUNIT_ASSERT(results[1] == 1);
	    }

	    else
			CPPUNIT_ASSERT(false);
	}

	void test_crawler_2 ()
	{
		std::istringstream r("5 3\n3 2 1 5\n2 2 5 3\n4 1 3\n");
	    std::vector< std::vector<char> > mat;
		if(pfd_read(r, mat))
		{
			std::vector<int> results = pfd_crawler(mat);
			CPPUNIT_ASSERT(results[0] == 1);
			CPPUNIT_ASSERT(results[1] == 5);
			CPPUNIT_ASSERT(results[2] == 3);
			CPPUNIT_ASSERT(results[3] == 2);
			CPPUNIT_ASSERT(results[4] == 4);
		}

	    else
			CPPUNIT_ASSERT(false);

	}

	void test_crawler_3 ()
	{
	    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
	    std::vector< std::vector<char> > mat;
	    if(pfd_read(r, mat))
		{
			std::vector<int> results = pfd_crawler(mat);
			CPPUNIT_ASSERT(results[0] == 1);
			CPPUNIT_ASSERT(results[1] == 5);
			CPPUNIT_ASSERT(results[2] == 3);
			CPPUNIT_ASSERT(results[3] == 2);
			CPPUNIT_ASSERT(results[4] == 4);
	    }

	    else
		CPPUNIT_ASSERT(false);
	}

	// -----------------
    // test_get_ind_rows
	// -----------------
	void test_get_ind_rows ()
	{
	    std::vector< std::vector<char> > mat(10, std::vector<char>(10, 0));
		std::priority_queue<int, std::vector<int>, std::greater<int> > ind_rows = get_ind_rows(mat);

		for(int i = 1; i <= 9; i++) {
			CPPUNIT_ASSERT(ind_rows.top() == i);
			ind_rows.pop();
		}
	}

	void test_get_ind_rows_2 ()
	{
	    std::vector< std::vector<char> > mat(10, std::vector<char>(10, 1));
		std::priority_queue<int, std::vector<int>, std::greater<int> > ind_rows = get_ind_rows(mat);
		CPPUNIT_ASSERT(ind_rows.size() == 0);
	}

	void test_get_ind_rows_3 ()
	{
	    std::vector< std::vector<char> > mat(10, std::vector<char>(10, 0));
		mat[1][9] = 1;
		mat[5][4] = 1;
		mat[6][3] = 1;
		std::priority_queue<int, std::vector<int>, std::greater<int> > ind_rows = get_ind_rows(mat);

		for(int i = 1; i <= 9; i++) {
			if(i != 1 && i != 5 && i != 6)
			{
				CPPUNIT_ASSERT(ind_rows.top() == i);
				ind_rows.pop();
			}
		}
	}

	// -----------------------
	// test_independent_row
	// -----------------------
	void test_independent_row ()
	{
		std::vector<char> c(5, 1);
		if(independent_row(c))
			CPPUNIT_ASSERT(false);
		
		else
			CPPUNIT_ASSERT(true);
	}

	void test_independent_row_2 ()
	{
		std::vector<char> c(6, 1);
		c[2] = 0;
		c[4] = 0;
		if(independent_row(c))
			CPPUNIT_ASSERT(false);
		
		else
			CPPUNIT_ASSERT(true);
	}

	void test_independent_row_3 ()
	{
		std::vector<char> c(6, 0);
		if(independent_row(c))
			CPPUNIT_ASSERT(true);
		
		else
			CPPUNIT_ASSERT(false);
	}

	// ----------
	// test_print
	// ----------
	void test_print ()
	{
		std::ostringstream w;
		std::vector<int> v(10, 5);
		pfd_print(w, v);
		CPPUNIT_ASSERT(w.str() == "5 5 5 5 5 5 5 5 5 5\n");
	}

	void test_print_2 ()
	{
		std::ostringstream w;
		std::vector<int> v;
		v.push_back(1);
		v.push_back(5);
		v.push_back(3);
		v.push_back(2);
		pfd_print(w, v);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2\n");
	}

	void test_print_3 ()
	{
		std::ostringstream w;
		std::vector<int> v;
		v.push_back(21);
		v.push_back(5);
		v.push_back(13);
		v.push_back(00002);
		pfd_print(w, v);
		CPPUNIT_ASSERT(w.str() == "21 5 13 2\n");
	}

	// ----------
	// test_solve
	// ----------
	void test_solve ()
	{
	    std::istringstream r("2 1\n1 1 2\n");
	    std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "2 1\n");
	}
	
	void test_solve_2 ()
	{
	    std::istringstream r("5 3\n3 2 1 5\n2 2 5 3\n4 1 3\n");
	    std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}

	void test_solve_3 ()
	{
	    std::istringstream r("5 3\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
	    std::ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");
	}


	CPPUNIT_TEST_SUITE(TestPFD);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_crawler);
	CPPUNIT_TEST(test_crawler_2);
	CPPUNIT_TEST(test_crawler_3);
	CPPUNIT_TEST(test_get_ind_rows);
	CPPUNIT_TEST(test_get_ind_rows_2);
	CPPUNIT_TEST(test_get_ind_rows_3);
	CPPUNIT_TEST(test_independent_row);
	CPPUNIT_TEST(test_independent_row_2);
	CPPUNIT_TEST(test_independent_row_3);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST_SUITE_END();
};


// ----
// main
// ----
int main() 
{
	using namespace std;
	cout << "TestPFD.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestPFD::suite());
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}
