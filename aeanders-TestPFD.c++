// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector> // vector
#include <list> //lists

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "PFD.h"

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

	void test_PFDinitial_read_1 () {
	std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = PFDinitial_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);
	}

	void test_PFDinitial_read_2 () {
	std::istringstream r("15 10\n");
        int i;
        int j;
        const bool b = PFDinitial_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 15);
        CPPUNIT_ASSERT(j == 10);
	}

	void test_PFDinitial_read_3 () {
	std::istringstream r("21 10\n");
        int i;
        int j;
        const bool b = PFDinitial_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 21);
        CPPUNIT_ASSERT(j == 10);
	}

 	//------------
	// fill_matrix
	//------------

	void test_fill_matrix_1() {
		int numVerts = 5;
		int numRules = 4;
		std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
		std::vector<std::vector<bool> > matrix;
		std::vector<int> dependency_count;
		dependency_count.resize(numVerts+1);
		matrix.resize(numVerts+1);
		bool b;
		for (int i = 0; i < numVerts+1; ++i)
			matrix[i].resize(numVerts+2);
		for(int i = 0; i < numRules; ++i)
		 	b = fill_matrix(in, matrix, dependency_count);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(matrix[3][1]);	
		CPPUNIT_ASSERT(matrix[2][5]);
		CPPUNIT_ASSERT(matrix[4][3]);	
		CPPUNIT_ASSERT(matrix[5][1]);
		CPPUNIT_ASSERT(dependency_count[3] == 2);
		CPPUNIT_ASSERT(dependency_count[2] == 2);
		CPPUNIT_ASSERT(dependency_count[4] == 1);
		CPPUNIT_ASSERT(dependency_count[5] == 1);
	}

	void test_fill_matrix_2() {
		int numVerts = 5;
		int numRules = 2;
		std::istringstream in("3 2 1 5\n4 2 2 1\n");
		std::vector<std::vector<bool> > matrix;
		std::vector<int> dependency_count;
		dependency_count.resize(numVerts+1);
		matrix.resize(numVerts+1);
		bool b;
		for (int i = 0; i < numVerts+1; ++i)
			matrix[i].resize(numVerts+2);
		for(int i = 0; i < numRules; ++i)
		 	b = fill_matrix(in, matrix, dependency_count);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(matrix[3][1]);	
		CPPUNIT_ASSERT(matrix[3][5]);
		CPPUNIT_ASSERT(matrix[4][2]);	
		CPPUNIT_ASSERT(matrix[4][1]);
		CPPUNIT_ASSERT(dependency_count[3] == 2);
		CPPUNIT_ASSERT(dependency_count[2] == 0);
		CPPUNIT_ASSERT(dependency_count[4] == 2);
		CPPUNIT_ASSERT(dependency_count[5] == 0);
	}

	
	//-------------
	// give_next_element
	//------------
	
	void test_give_next_element_1(){
		int numVerts = 5;
		std::vector<int> dependency_count;
		dependency_count.resize(numVerts+1);
		dependency_count[1] = 1;
		dependency_count[2] = 0;
		dependency_count[3] = 2;

		CPPUNIT_ASSERT(give_next_element(dependency_count) == 2);
	}
	
	void test_give_next_element_2(){
		int numVerts = 5;
		std::vector<int> dependency_count;
		dependency_count.resize(numVerts+1);
		dependency_count[1] = 1;
		dependency_count[2] = 2;
		dependency_count[4] = 0;
		dependency_count[3] = 2;

		CPPUNIT_ASSERT(give_next_element(dependency_count) == 4);
	}

	void test_give_next_element_3(){
		int numVerts = 5;
		std::vector<int> dependency_count;
		dependency_count.resize(numVerts+1);
		dependency_count[1] = 0;
		dependency_count[2] = 0;
		dependency_count[4] = 2;

		CPPUNIT_ASSERT(give_next_element(dependency_count) == 1);
	}

	//--------------
	// PFD_eval
	//--------------

	void test_PFD_eval_1(){
		int numVerts = 5;
		int numRules = 4;
		std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
		std::vector<std::vector<bool> > matrix;
		std::vector<int> dependency_count;	
		std::list<int> solution;
		dependency_count.resize(numVerts+1);
		matrix.resize(numVerts+1);
		bool b;
		for (int i = 0; i < numVerts+1; ++i)
			matrix[i].resize(numVerts+2);
		for(int i = 0; i < numRules; ++i)
		 	b = fill_matrix(in, matrix, dependency_count);

		PFD_eval(matrix, solution, dependency_count);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(solution.front() == 1);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 5);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 3);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 2);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 4);
		solution.pop_front();
	}

	void test_PFD_eval_2(){
		int numVerts = 5;
		int numRules = 2;
		std::istringstream in("3 2 1 5\n4 2 2 1\n");
		std::vector<std::vector<bool> > matrix;
		std::vector<int> dependency_count;	
		std::list<int> solution;
		dependency_count.resize(numVerts+1);
		matrix.resize(numVerts+1);
		bool b;
		for (int i = 0; i < numVerts+1; ++i)
			matrix[i].resize(numVerts+2);
		for(int i = 0; i < numRules; ++i)
		 	b = fill_matrix(in, matrix, dependency_count);

		PFD_eval(matrix, solution, dependency_count);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(solution.front() == 1);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 2);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 4);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 5);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 3);
		solution.pop_front();
	}

	void test_PFD_eval_3(){
		int numVerts = 6;
		int numRules = 4;
		std::istringstream in("5 3 3 4 1\n6 1 1\n3 2 4 1\n2 2 4 3\n");
		std::vector<std::vector<bool> > matrix;
		std::vector<int> dependency_count;	
		std::list<int> solution;
		dependency_count.resize(numVerts+1);
		matrix.resize(numVerts+1);
		bool b;
		for (int i = 0; i < numVerts+1; ++i)
			matrix[i].resize(numVerts+2);
		for(int i = 0; i < numRules; ++i)
		 	b = fill_matrix(in, matrix, dependency_count);

		PFD_eval(matrix, solution, dependency_count);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(solution.front() == 1);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 4);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 3);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 2);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 5);
		solution.pop_front();
		CPPUNIT_ASSERT(solution.front() == 6);
		solution.pop_front();
	}
	
	//-----------------
	// PFD_print
	//----------------

	void test_PFD_print_1 () {
        std::ostringstream w;
	std::list<int> solution;
	for(int i = 1; i <= 5; i++)
	solution.push_back(i);
        PFD_print(w, solution);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 \n");}

	void test_PFD_print_2 () {
        std::ostringstream w;
	std::list<int> solution;
	for(int i = 5; i <= 10; i++)
	solution.push_back(i);
        PFD_print(w, solution);
        CPPUNIT_ASSERT(w.str() == "5 6 7 8 9 10 \n");}


	void test_PFD_print_3 () {
        std::ostringstream w;
	std::list<int> solution;
	for(int i = 11; i <= 15; i++)
	solution.push_back(i);
        PFD_print(w, solution);
        CPPUNIT_ASSERT(w.str() == "11 12 13 14 15 \n");}


	//-------------------
	// PFD_solve
	//------------------

	void test_PFD_solve_1() {
	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n");
	}

	void test_PFD_solve_2() {
	std::istringstream r("6 4\n5 3 3 4 1\n6 1 1\n3 2 4 1\n2 2 4 3\n");
        std::ostringstream w;
        PFD_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "1 4 3 2 5 6 \n");
	}

	void test_PFD_solve_3() {
	std::istringstream r("8 5\n5 2 4 2\n8 1 4\n7 2 2 4\n1 3 4 6 8\n3 2 7 8\n");
        std::ostringstream w;
        PFD_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "2 4 5 6 7 8 1 3 \n");
	}

	void test_PFD_solve_4() {
	std::istringstream r("5 2\n3 2 1 5\n4 2 2 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "1 2 4 5 3 \n");
	}

	

	//------------
	// suite
	//------------

	CPPUNIT_TEST_SUITE(TestPFD);
    	CPPUNIT_TEST(test_PFDinitial_read_1);
	CPPUNIT_TEST(test_PFDinitial_read_2);
	CPPUNIT_TEST(test_PFDinitial_read_3);
    	CPPUNIT_TEST(test_fill_matrix_1);
	CPPUNIT_TEST(test_fill_matrix_2);
	CPPUNIT_TEST(test_give_next_element_1);
	CPPUNIT_TEST(test_give_next_element_2);
	CPPUNIT_TEST(test_give_next_element_3);
	CPPUNIT_TEST(test_PFD_eval_1);
	CPPUNIT_TEST(test_PFD_eval_2);	
	CPPUNIT_TEST(test_PFD_eval_3);
	CPPUNIT_TEST(test_PFD_print_1);
	CPPUNIT_TEST(test_PFD_print_2);
	CPPUNIT_TEST(test_PFD_print_3);
	CPPUNIT_TEST(test_PFD_solve_1);
	CPPUNIT_TEST(test_PFD_solve_2);
	CPPUNIT_TEST(test_PFD_solve_3);
	CPPUNIT_TEST(test_PFD_solve_4);
    	//CPPUNIT_TEST(test_read_3);
	 CPPUNIT_TEST_SUITE_END();

};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}


