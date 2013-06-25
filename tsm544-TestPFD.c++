// TestPFD

#include <iostream>  // cout, endl, ios_base
#include <sstream>   // istringtstream, ostringstream
#include <string>    // ==
#include <algorithm> // equal
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private   public
#define protected public
#define class     struct

#include "PFD.h"

struct TestTask: CppUnit::TestFixture {

	void Task_Constructor_01() {
		intList l;  // empty list
		Task t (0, l);
		intList& tl = t._adjacencyList;
		CPPUNIT_ASSERT(equal(tl.begin(), tl.end(), l.begin()));
	}

	void Task_Constructor_02() {
		intList l (5, 10);
		Task t (0, l);
		intList& tl = t._adjacencyList;
		CPPUNIT_ASSERT(equal(tl.begin(), tl.end(), l.begin()));
	}

	void Task_Constructor_03() {
		intList l (5, 0);

		int j = 0;
		for(intList::iterator i = l.begin(); i != l.end(); ++i)
			*i = j++;

		Task t (0, l);
		intList& tl = t._adjacencyList;
		CPPUNIT_ASSERT(equal(tl.begin(), tl.end(), l.begin()));
	}

	void Task_less_01() {
		intList l;
		Task t1(1, l);
		Task t2(2, l);
		CPPUNIT_ASSERT(t1 < t2);
	}

	void Task_less_02() {
		intList l;
		Task t1(1, l);
		Task t2(1, l);
		CPPUNIT_ASSERT(!(t1 < t2));
	}

	void Task_less_03() {
		intList l1(2, 2);
		intList l2(1, 2);
		Task t1(1, l1);
		Task t2(2, l2);
		CPPUNIT_ASSERT(t1 < t2);
	}

	void Task_equal_01() {
		intList l;
		Task t1(1, l);
		Task t2(1, l);
		CPPUNIT_ASSERT(t1 == t2);
	}

	void Task_equal_02() {
		intList l;
		Task t1(1, l);
		Task t2(2, l);
		CPPUNIT_ASSERT(!(t1 == t2));
	}

	CPPUNIT_TEST_SUITE(TestTask);
	CPPUNIT_TEST(Task_Constructor_01);
	CPPUNIT_TEST(Task_Constructor_02);
	CPPUNIT_TEST(Task_Constructor_03);
	CPPUNIT_TEST(Task_less_01);
	CPPUNIT_TEST(Task_less_02);
	CPPUNIT_TEST(Task_less_03);
	CPPUNIT_TEST(Task_equal_01);
	CPPUNIT_TEST(Task_equal_02);
	CPPUNIT_TEST_SUITE_END();
};

struct TestTaskSet: CppUnit::TestFixture {

	void TaskSet_Constructor_01() {
		TaskList tl;
		TaskSet ts (tl);
		TaskList& ttl = ts._pfds;
		CPPUNIT_ASSERT(equal(ttl.begin(), ttl.end(), tl.begin()));
	}

	void TaskSet_Constructor_02() {
		intList l (2, 3);
		Task v (0, l);
		TaskList tl (5, v);
		TaskSet ts (tl);
		TaskList& ttl = ts._pfds;
		CPPUNIT_ASSERT(equal(ttl.begin(), ttl.end(), tl.begin()));
	}

	void TaskSet_pfd_eval_01() {
		intList l1;
		Task t(1, l1);
		int tl [] = {1};
		TaskList ttl (1, t);
		TaskSet ts (ttl);

		intList sol = ts.pfd_eval();
		CPPUNIT_ASSERT(sol.size() == 1);
		CPPUNIT_ASSERT(equal(sol.begin(), sol.end(), tl));
	}

	void TaskSet_pfd_eval_02() {
		int arr1[] = {3, 4};
		int arr2[] = {1};
		int arr3[] = {4};
		intList l1 (arr1, arr1 + 2);
		intList l2 (arr2, arr2 + 1);
		intList l3 (arr3, arr3 + 1);
		intList l4;
		Task t1 (1, l1);
		Task t2 (2, l2);
		Task t3 (3, l3);
		Task t4 (4, l4);
		int solarr [] = {4, 3, 1, 2};
		TaskList ttl;
		ttl.push_back(t1);
		ttl.push_back(t2);
		ttl.push_back(t3);
		ttl.push_back(t4);
		TaskSet ts (ttl);

		intList sol = ts.pfd_eval();

		CPPUNIT_ASSERT(sol.size() == 4);
		CPPUNIT_ASSERT(equal(sol.begin(), sol.end(), solarr));
	}

	void TaskSet_pfd_eval_03() {
		int arr2[] = {5, 3};
		int arr3[] = {1, 5};
		int arr4[] = {3};
		int arr5[] = {1};
		intList l1;
		intList l2 (arr2, arr2 + 2);
		intList l3 (arr3, arr3 + 2);
		intList l4 (arr4, arr4 + 1);
		intList l5 (arr5, arr5 + 1);
		Task t1 (1, l1);
		Task t2 (2, l2);
		Task t3 (3, l3);
		Task t4 (4, l4);
		Task t5 (5, l5);
		int solarr [] = {1, 5, 3, 2, 4};
		TaskList ttl;
		ttl.push_back(t1);
		ttl.push_back(t2);
		ttl.push_back(t3);
		ttl.push_back(t4);
		ttl.push_back(t5);
		TaskSet ts (ttl);

		intList sol = ts.pfd_eval();

		CPPUNIT_ASSERT(sol.size() == 5);
		CPPUNIT_ASSERT(equal(sol.begin(), sol.end(), solarr));
	}

	CPPUNIT_TEST_SUITE(TestTaskSet);
	CPPUNIT_TEST(TaskSet_Constructor_01);
	CPPUNIT_TEST(TaskSet_Constructor_02);
	CPPUNIT_TEST(TaskSet_pfd_eval_01);
	CPPUNIT_TEST(TaskSet_pfd_eval_02);
	CPPUNIT_TEST(TaskSet_pfd_eval_03);
	CPPUNIT_TEST_SUITE_END();
};

struct TestPFD: CppUnit::TestFixture {

	void pfd_read_meta_01() {
	    std::istringstream in ("1 1");
	    int i, j;
	    pfd_read_meta(in, i, j);

		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 1);
	}

	void pfd_read_meta_02() {
		std::istringstream in ("5 4");
		int i, j;
		pfd_read_meta(in, i, j);

		CPPUNIT_ASSERT(i == 5);
		CPPUNIT_ASSERT(j == 4);
	}

	void pfd_read_pfd_01() {
		std::istringstream in ("1 1 1");
		int t = 0;
		intList i;
		int testList[] = {1};

		pfd_read_pfd(in, i, t);

		CPPUNIT_ASSERT(t == 1);
		CPPUNIT_ASSERT(i.size() == 1);
		CPPUNIT_ASSERT(equal(i.begin(), i.end(), testList));
	}

	void pfd_read_pfd_02() {
		std::istringstream in ("2 3 1 3 4");
		int t = 0;
		intList i;
		int testList[] = {1, 3, 4};

		pfd_read_pfd(in, i, t);

		CPPUNIT_ASSERT(t == 2);
		CPPUNIT_ASSERT(i.size() == 3);
		CPPUNIT_ASSERT(equal(i.begin(), i.end(), testList));
	}

	void pfd_read_pfd_03() {
		std::istringstream in ("21 10 1 2 3 4 5 6 7 8 9 10");
		int t = 0;
		intList i;
		int testList[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		pfd_read_pfd(in, i, t);

		CPPUNIT_ASSERT(t == 21);
		CPPUNIT_ASSERT(i.size() == 10);
		CPPUNIT_ASSERT(equal(i.begin(), i.end(), testList));
	}

	void pfd_print_01(){
		std::ostringstream out;
		int testList[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		intList i (testList, testList + 10);

		pfd_print(out, i);

		CPPUNIT_ASSERT(out.str() == "1 2 3 4 5 6 7 8 9 10\n");
	}

	void pfd_solve_01(){
		std::istringstream in ("1 0\n");
		std::ostringstream out;

		pfd_solve(in, out);

		CPPUNIT_ASSERT(out.str() == "1\n\n");
	}

	void pfd_solve_02(){
		std::istringstream in ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
		std::ostringstream out;

		pfd_solve(in, out);

		CPPUNIT_ASSERT(out.str() == "1 5 3 2 4\n\n");
	}

	void pfd_solve_03(){
		std::istringstream in ("2 1\n1 1 2");
		std::ostringstream out;

		pfd_solve(in, out);

		CPPUNIT_ASSERT(out.str() == "2 1\n\n");
	}

	CPPUNIT_TEST_SUITE(TestPFD);
	CPPUNIT_TEST(pfd_read_meta_01);
	CPPUNIT_TEST(pfd_read_meta_02);
	CPPUNIT_TEST(pfd_read_pfd_01);
	CPPUNIT_TEST(pfd_read_pfd_02);
	CPPUNIT_TEST(pfd_read_pfd_03);
	CPPUNIT_TEST(pfd_print_01);
	CPPUNIT_TEST(pfd_solve_01);
	CPPUNIT_TEST(pfd_solve_02);
	CPPUNIT_TEST(pfd_solve_03);
	CPPUNIT_TEST_SUITE_END();
};

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false);
	cout << "TestPFD.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestTask::suite());
	tr.addTest(TestTaskSet::suite());
	tr.addTest(TestPFD::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
