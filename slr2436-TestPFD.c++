/*
 * TestPDF.c++
 *
 *  Created on: Jun 15, 2013
 *      Author: Spencer Reynoso
 */


#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

using namespace std;
struct TestPDF : CppUnit::TestFixture {


	void test_firstread_1(){
		istringstream r ("5 4\n");
		int i;
		int j;
		const bool b = pfd_firstread(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 5);
		CPPUNIT_ASSERT(j == 4);
	}

	void test_firstread_2(){
		istringstream r ("5 1\n");
		int i;
		int j;
		const bool b = pfd_firstread(r, i, j);
		CPPUNIT_ASSERT(b == true);
	}

	void test_firstread_3(){
		istringstream r ("100 100\n");
		int i;
		int j;
		const bool b = pfd_firstread(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 100);
		CPPUNIT_ASSERT(j == 100);
	}

	void test_firstread_4(){
		istringstream r ("1 1\n");
		int i;
		int j;
		const bool b = pfd_firstread(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 1);
	}

	void test_pfd_setupnodes_1(){
		istringstream r ("3 2 1 5\n");
		vector<vector<int> > nodes;
		nodes.resize(6);
		for(int a = 0; a < 6; ++a)
			nodes[a].push_back(0);
		pfd_setupnodes(r, nodes);
		CPPUNIT_ASSERT(nodes[3][0] == 2);
		CPPUNIT_ASSERT(nodes[1][1]== 3);
		CPPUNIT_ASSERT(nodes[5][1] == 3);
	}

	void test_pfd_setupnodes_2(){
		istringstream r ("5 1 1\n");
		vector<vector<int> > nodes;
		nodes.resize(6);
		for(int a = 0; a < 6; ++a)
			nodes[a].push_back(0);
		pfd_setupnodes(r, nodes);
		CPPUNIT_ASSERT(nodes[5][0] == 1);
		CPPUNIT_ASSERT(nodes[1][1]== 5);
		CPPUNIT_ASSERT(nodes[5].size() == 1);
	}

	void test_pfd_setupnodes_3(){
		istringstream r ("1 1 5\n");
		istringstream rr ("4 1 5\n");
		vector<vector<int> > nodes;
		nodes.resize(6);
		for(int a = 0; a < 6; ++a)
			nodes[a].push_back(0);
		pfd_setupnodes(r, nodes);
		CPPUNIT_ASSERT(nodes[1][0] == 1);
		CPPUNIT_ASSERT(nodes[5][1]== 1);
		CPPUNIT_ASSERT(nodes[1].size() == 1);
		CPPUNIT_ASSERT(nodes[5].size() == 2);
		pfd_setupnodes(rr, nodes);
		CPPUNIT_ASSERT(nodes[4][0] == 1);
		CPPUNIT_ASSERT(nodes[5][2]== 4);
		CPPUNIT_ASSERT(nodes[5].size() == 3);
	}

	void test_pfd_setupnodes_4(){
		istringstream r ("1 1 3\n");
		istringstream rr ("2 1 3\n");
		istringstream rrr ("4 1 3\n");
		vector<vector<int> > nodes;
		nodes.resize(6);
		for(int a = 0; a < 6; ++a)
			nodes[a].push_back(0);
		pfd_setupnodes(r, nodes);
		pfd_setupnodes(rr, nodes);
		pfd_setupnodes(rrr, nodes);
		CPPUNIT_ASSERT(nodes[1][0] == 1);
		CPPUNIT_ASSERT(nodes[2][0] == 1);
		CPPUNIT_ASSERT(nodes[3][0] == 0);
		CPPUNIT_ASSERT(nodes[4][0] == 1);
		CPPUNIT_ASSERT(nodes[5][0] == 0);
		CPPUNIT_ASSERT(nodes[3][1] == 1);
		CPPUNIT_ASSERT(nodes[3][2] == 2);
		CPPUNIT_ASSERT(nodes[3][3] == 4);
	}

	void test_pfdeval_1(){
		vector<int> output;
		vector<vector<int> > nodes;
		nodes.resize(3);
		nodes[1].push_back(0);
		nodes[1].push_back(2);
		nodes[2].push_back(1);
		pfd_evaluate(nodes, output);
		CPPUNIT_ASSERT(nodes[1][0] == -1);
		CPPUNIT_ASSERT(nodes[1][1] == 2);
		CPPUNIT_ASSERT(nodes[2][0] == -1);
		CPPUNIT_ASSERT(output[1] == 2);
		CPPUNIT_ASSERT(output[0] == 1);
	}

	void test_pfdeval_2(){
		vector<int> output;
		vector<vector<int> > nodes;
		nodes.resize(6);
		nodes[1].push_back(0);
		nodes[2].push_back(0);
		nodes[3].push_back(0);
		nodes[4].push_back(0);
		nodes[5].push_back(0);
		pfd_evaluate(nodes, output);
		CPPUNIT_ASSERT(nodes[1][0] == -1);
		CPPUNIT_ASSERT(nodes[2][0] == -1);
		CPPUNIT_ASSERT(nodes[3][0] == -1);
		CPPUNIT_ASSERT(nodes[4][0] == -1);
		CPPUNIT_ASSERT(nodes[5][0] == -1);
		CPPUNIT_ASSERT(output[0] == 1);
		CPPUNIT_ASSERT(output[1] == 2);
		CPPUNIT_ASSERT(output[2] == 3);
		CPPUNIT_ASSERT(output[3] == 4);
		CPPUNIT_ASSERT(output[4] == 5);
	}

	void test_pfdeval_3(){
			vector<int> output;
			vector<vector<int> > nodes;
			nodes.resize(5);
			nodes[1].push_back(1);
			nodes[2].push_back(1);
			nodes[3].push_back(0);
			nodes[3].push_back(1);
			nodes[3].push_back(2);
			nodes[4].push_back(0);
			pfd_evaluate(nodes, output);
			CPPUNIT_ASSERT(output[0] == 3);
			CPPUNIT_ASSERT(output[1] == 1);
			CPPUNIT_ASSERT(output[2] == 2);
			CPPUNIT_ASSERT(output[3] == 4);
		}

	void test_pfdprint_1(){
		ostringstream w;
		vector<int> output {1, 2, 3, 4, 5};
		pfd_print(w, output);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5");
	}

	void test_pfdprint_2(){
		ostringstream w;
		vector<int> output {1};
		pfd_print(w, output);
		CPPUNIT_ASSERT(w.str() == "1");
	}

	void test_pfdprint_3(){
		ostringstream w;
		vector<int> output {8, 7, 1, 2, 3, 4, 5, 6};
		pfd_print(w, output);
		CPPUNIT_ASSERT(w.str() == "8 7 1 2 3 4 5 6");
	}

	void test_pfdsolve_1(){
		istringstream r ("3 2\n2 2 1 3\n3 1 1\n");
		ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 3 2");

	}

	void test_pfdsolve_2(){
		istringstream r ("5 0\n");
		ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 2 3 4 5");

	}

	void test_pfdsolve_3() {
		istringstream r ("5 3\n1 1 3\n2 1 3\n4 1 3\n");
		ostringstream w;
		pfd_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "3 1 2 4 5");

	}



	CPPUNIT_TEST_SUITE(TestPDF);
	CPPUNIT_TEST(test_firstread_1);
	CPPUNIT_TEST(test_firstread_3);
	CPPUNIT_TEST(test_firstread_2);
	CPPUNIT_TEST(test_firstread_4);
	CPPUNIT_TEST(test_pfd_setupnodes_1);
	CPPUNIT_TEST(test_pfd_setupnodes_2);
	CPPUNIT_TEST(test_pfd_setupnodes_3);
	CPPUNIT_TEST(test_pfd_setupnodes_4);
	CPPUNIT_TEST(test_pfdprint_1);
	CPPUNIT_TEST(test_pfdprint_2);
	CPPUNIT_TEST(test_pfdprint_3);
	CPPUNIT_TEST(test_pfdsolve_1);
	CPPUNIT_TEST(test_pfdsolve_2);
	CPPUNIT_TEST(test_pfdsolve_3);
	CPPUNIT_TEST(test_pfdeval_1);
	CPPUNIT_TEST(test_pfdeval_2);
	CPPUNIT_TEST(test_pfdeval_3);
	CPPUNIT_TEST_SUITE_END();

};



// main

int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestPDF.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestPDF::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
