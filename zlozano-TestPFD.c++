// ---------------------
// cs378/pfd/TestPFD.c++
// Creation 6.18.2013
// Zachary Lozano
// zlozano@utexas.edu
// ---------------------
// Structure borrowed
// from Glenn P. Downing
// ---------------------

// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "PFD.h"

// -------
// TestPFD
// -------

struct TestPFD : CppUnit::TestFixture
{
	// ----
	// read
	// ----
    void test_read_1 ()
    {
        using namespace std;
        istringstream r("4 3\n2 2 1 4\n 3 1 2\n 4 1 1");
        vector<vector<int> > matrix;
        pfd_read(r, matrix);
        CPPUNIT_ASSERT(matrix[1][0] == 1 && matrix[1][3] == 1);
        CPPUNIT_ASSERT(matrix[2][1] == 1);
        CPPUNIT_ASSERT(matrix[3][0] == 1);
    }

    void test_read_2 () 
    {
        using namespace std;
        istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        vector<vector<int> > matrix;
        pfd_read(r, matrix);

        CPPUNIT_ASSERT(matrix[2][0] == 1 && matrix [2][4] == 1);
        CPPUNIT_ASSERT(matrix[1][4] == 1 && matrix [1][2] == 1);
        CPPUNIT_ASSERT(matrix[3][2] == 1);
        CPPUNIT_ASSERT(matrix[4][0] == 1);
    }
    // ----------
	// pfd_search
	// ----------
	void test_search_1 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 1, 0, 0},
											{0, 0, 0, 0},
											{1, 0, 0, 1},
											{1, 0, 0, 0}
										  };
		vector<int> v;
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_search(matrix, v, q);
		
		for (unsigned int i = 0; i < matrix.size(); ++i)
		{
			for (unsigned int j = 0; j < matrix.size(); ++j)
			{
				CPPUNIT_ASSERT(matrix[i][j] == 0);		
			}
		}	
	}

	void test_search_2 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 0, 0, 0},
											{0, 0, 0, 1},
											{1, 1, 0, 0},
											{1, 0, 0, 0}
										  };

		vector<int> v;
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_search(matrix, v, q);
		for (unsigned int i = 0; i < matrix.size(); ++i)
		{
			for (unsigned int j = 0; j < matrix.size(); ++j)
			{
				CPPUNIT_ASSERT(matrix[i][j] == 0);		
			}
		}	
	}

	void test_search_3 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 0, 1, 0},
											{1, 0, 0, 0},
											{0, 0, 0, 0},
											{1, 1, 0, 0}
										  };
		vector<int> v;
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_search(matrix, v, q);
		for (unsigned int i = 0; i < matrix.size(); ++i)
		{
			for (unsigned int j = 0; j < matrix.size(); ++j)
			{
				CPPUNIT_ASSERT(matrix[i][j] == 0);		
			}
		}	
	}

	void test_search_4 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 0, 0, 0},
											{0, 0, 1, 1},
											{1, 0, 0, 1},
											{1, 0, 0, 0}
										  };
		vector<int> v;
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_search(matrix, v, q);
		for (unsigned int i = 0; i < matrix.size(); ++i)
		{
			for (unsigned int j = 0; j < matrix.size(); ++j)
			{
				CPPUNIT_ASSERT(matrix[i][j] == 0);		
			}
		}	
	}
	// ------
	// update
	// ------
	void test_update_1 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 2, 1, 0},
											{0, 3, 0, 0},
											{0, 0, 0, 7},
											{1, 0, 0, 9},
											{0, 0, 0, 0},
											{1, 0, 0, 9},
											{0, 0, 0, 0}
										  };
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_update(matrix, 2, q);
		CPPUNIT_ASSERT(matrix[0][2] == 0);
		CPPUNIT_ASSERT(q.size() == 0);
	}
	
	void test_update_2 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 2, 4, 0},
											{0, 3, 0, 0},
											{0, 0, 0, 7},
											{1, 0, 0, 9},
											{0, 0, 0, 0},
											{1, 0, 0, 9},
											{0, 0, 1, 0}
										  };
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_update(matrix, 2, q);
		CPPUNIT_ASSERT(matrix[0][2] == 0);
	}
	
	void test_update_3 ()
	{
		using namespace std;
			vector<vector<int> > matrix = {
											{0, 2, 4, 0},
											{0, 3, 0, 0},
											{0, 0, 0, 7},
											{1, 0, 0, 9},
											{0, 0, 0, 0},
											{1, 0, 0, 9},
											{0, 0, 0, 1}
										  };
		priority_queue<int, vector<int>, greater<int> > q;
		pfd_update(matrix, 3, q);
		CPPUNIT_ASSERT(matrix[0][3] == 0);
		CPPUNIT_ASSERT(matrix[1][3] == 0);
		CPPUNIT_ASSERT(matrix[2][3] == 0);
		CPPUNIT_ASSERT(matrix[3][3] == 0);
		CPPUNIT_ASSERT(matrix[4][3] == 0);
		CPPUNIT_ASSERT(matrix[5][3] == 0);
		CPPUNIT_ASSERT(matrix[6][3] == 0);
	}

	// -----
	// print
	// -----
	void test_output_1 ()
	{
		using namespace std;
			ostringstream w;
			vector<int> output = {1, 2, 3, 4, 5};	
		pfd_output(w, output);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5\n");
	}

	void test_output_2 ()
	{
		using namespace std;
			ostringstream w;
			vector<int> output = {1};	
		pfd_output(w, output);
		CPPUNIT_ASSERT(w.str() == "1\n");
	}
	
	void test_output_3 ()
	{
		using namespace std;
			ostringstream w;
			vector<int> output = {};	
		pfd_output(w, output);
		CPPUNIT_ASSERT(w.str() == "\n");
	}
	// -----
	// solve
	// -----
	void test_solve_1 ()
	{
		using namespace std;
		istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n");
		ostringstream w;
		pfd_solve(r, w);

		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n");
	}

	void test_solve_2 ()
	{
		using namespace std;
		istringstream r("2 1\n1 1 2\n");
		ostringstream w;
		pfd_solve(r, w);

		CPPUNIT_ASSERT(w.str() == "2 1 \n");
	}

	void test_solve_3 ()
	{
		using namespace std;
		istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n 5 1 1\n");
		ostringstream w;
		pfd_solve(r, w);

		CPPUNIT_ASSERT(w.str() == "1 3 4 5 2 \n");
	}
	// -----
	// suite
	// -----
    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_search_1);
	CPPUNIT_TEST(test_search_2);
	CPPUNIT_TEST(test_search_3);
	CPPUNIT_TEST(test_search_4);
	CPPUNIT_TEST(test_update_1);
	CPPUNIT_TEST(test_update_2);
	CPPUNIT_TEST(test_update_3);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main ()
{
	using namespace std;
	ios_base::sync_with_stdio(false);
	cout << "TestPFD.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestPFD::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
