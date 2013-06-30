// --------------------------------
// projects/collatz/TestPFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*tp test the program:
% ls /usr/include/cppunit/
...
TestFixture.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o TestPFD -lcppunit -ldl
% valgrind TestPFD >& TestPFD.out
*/

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
// TestCollatz
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----


    //default test case
    void test_read_rules_1 () 
	{
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = PFD_read_rules(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);

	}



    //Read in 2 other numbers
    void test_read_rules_2 () 
	{
        std::istringstream r("1 1\n");
        int i;
        int j;
        const bool b = PFD_read_rules(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 1);

	}



    //Read in 2 high numbers
    void test_read_rules_3 () 
	{
        std::istringstream r("99 99\n");
        int i;
        int j;
        const bool b = PFD_read_rules(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 99);
        CPPUNIT_ASSERT(j == 99);

	}




	//Simple case of 1 number, 1 dependency
    void test_read_dependencies_1 () 
	{
        std::istringstream r("1 1 1\n");
        int i;
        int j;
		std::list<int> depList;

        const bool b = PFD_read_dependencies(r, i, j, depList);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 1);
		CPPUNIT_ASSERT(depList.size() == 1);

	}




	//case of 5 dependencies
    void test_read_dependencies_2 () 
	{
        std::istringstream r("2 5 9 8 7 6 5\n");
        int i;
        int j;
		std::list<int> depList;

        const bool b = PFD_read_dependencies(r, i, j, depList);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 2);
        CPPUNIT_ASSERT(j == 5);
		CPPUNIT_ASSERT(depList.front() == 9);
		CPPUNIT_ASSERT(depList.back() == 5);
		CPPUNIT_ASSERT(depList.size() == 5);

	}



	//case of 3 dependencies
    void test_read_dependencies_3 () 
	{
        std::istringstream r("88 3 2 1 6\n");
        int i;
        int j;
		std::list<int> depList;

        const bool b = PFD_read_dependencies(r, i, j, depList);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 88);
        CPPUNIT_ASSERT(j == 3);
		CPPUNIT_ASSERT(depList.front() == 2);
		CPPUNIT_ASSERT(depList.back() == 6);
		CPPUNIT_ASSERT(depList.size() == 3);

	}


	//constructs a vertex
	void test_make_vertex_1 ()
	{
		std::list<Vertex> vertList;
		
		PFD_make_vertex(vertList, 5);
		
		CPPUNIT_ASSERT((vertList.front()).getVertID() == 5);
		CPPUNIT_ASSERT((vertList.front()).getNumDep() == 0);


	}
	

	//constructs a vertex
	void test_make_vertex_2 ()
	{
		std::list<Vertex> vertList2;
		
		PFD_make_vertex(vertList2, 99);
		
		CPPUNIT_ASSERT((vertList2.front()).getVertID() == 99);
		CPPUNIT_ASSERT((vertList2.front()).getNumDep() == 0);


	}


	//constructs a vertex with ID 50
	void test_make_vertex_3 ()
	{
		std::list<Vertex> vertList3;
		
		PFD_make_vertex(vertList3, 50);
		
		CPPUNIT_ASSERT((vertList3.front()).getVertID() == 50);
		CPPUNIT_ASSERT((vertList3.front()).getNumDep() == 0);


	}




	//populates vertex with dependency 4
	void test_populate_vertices_1()
	{
		Vertex v = Vertex(4);	
		std::list<Vertex> vertList4;
		std::list<int> depList;
		int vertID = 4;

		int numDep = 1;



		vertList4.push_back(v);
		depList.push_back(2);

		PFD_populate_vertices(vertList4, vertID, numDep, depList);

		CPPUNIT_ASSERT((vertList4.front()).getNumDep() == 1);
		CPPUNIT_ASSERT((vertList4.front()).getVertID() == 4);


		
	}
	

	//populates vertex with ID: 45 and 3 dependencies
	//and also adds a vertex with ID: 2 at the end
	void test_populate_vertices_2()
	{
		Vertex v1 = Vertex(45);
		Vertex v2 = Vertex(2);	
		std::list<Vertex> vertList5;
		std::list<int> depList2;

		

		int vertID = 45;
		int numDep = 3;

	
		vertList5.push_back(v1);
		vertList5.push_back(v2);
		depList2.push_back(2);
		depList2.push_back(4);
		depList2.push_back(6);

		PFD_populate_vertices(vertList5, vertID, numDep, depList2);

		CPPUNIT_ASSERT((vertList5.front()).getNumDep() == 3);
		CPPUNIT_ASSERT((vertList5.front()).getVertID() == 45);
		CPPUNIT_ASSERT((vertList5.back()).getNumDep() == 0);
		CPPUNIT_ASSERT((vertList5.back()).getVertID() == 2);


		
	}


	//populates vertex with ID: 45 and 3 dependencies
	//and also adds a vertex with ID: 2 in the middle
	//then one with ID: 50 with 2 dependenceis
	void test_populate_vertices_3()
	{
		Vertex v1 = Vertex(45);
		Vertex v2 = Vertex(2);	
		Vertex v3 = Vertex(50);

		std::list<Vertex> vertList6;
		std::list<int> depList1;
		std::list<int> depList3;

		
		

		int vertID = 45;
		int numDep = 3;

	
		vertList6.push_back(v1);
		vertList6.push_back(v2);
		vertList6.push_back(v3);
		depList1.push_back(2);
		depList1.push_back(4);
		depList1.push_back(6);
		depList3.push_back(8);
		depList3.push_back(9);


		PFD_populate_vertices(vertList6, vertID, numDep, depList1);
		PFD_populate_vertices(vertList6, 50,2, depList3);



		CPPUNIT_ASSERT((vertList6.front()).getNumDep() == 3);
		CPPUNIT_ASSERT((vertList6.front()).getVertID() == 45);
		CPPUNIT_ASSERT((vertList6.back()).getNumDep() == 2);
		CPPUNIT_ASSERT((vertList6.back()).getVertID() == 50);


		
	}


	//Removes dependency 5 from vertex 1
	void test_remove_dependencies_1()
	{
	    std::list<Vertex> vertList7;
	    std::list<int> depList;

	    Vertex v1 = Vertex(1);
	    depList.push_back(5);
	    	  
	    vertList7.push_back(v1);
  
	    PFD_populate_vertices(vertList7, 1, 1, depList);    
	
	   
	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 1);

	    PFD_remove_dependencies(vertList7, 5);

	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 0);

 
	}


	//Removes dependency 2 from 2 vertices
	void test_remove_dependencies_2()
	{
	    std::list<Vertex> vertList7;
	    std::list<int> depList1;
	    std::list<int> depList2;
	    std::list<int> depList3;

	    Vertex v1 = Vertex(1);
	    Vertex v2 = Vertex(50);
	    Vertex v3 = Vertex(90);

	    depList1.push_back(2);
	    depList1.push_back(3);
	    depList2.push_back(5);
	    depList2.push_back(2);
	    depList3.push_back(4);
	    	  
	    vertList7.push_back(v1);
	    vertList7.push_back(v2);
	    vertList7.push_back(v3);
  
	    PFD_populate_vertices(vertList7, 1, 2, depList1);    
	    PFD_populate_vertices(vertList7, 50, 2, depList2);    
	    PFD_populate_vertices(vertList7, 90, 1, depList3);    
	
	   
	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 2);
	    CPPUNIT_ASSERT((vertList7.back()).getNumDep() == 1);
	    PFD_remove_dependencies(vertList7, 2);

	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 1);
	    CPPUNIT_ASSERT((vertList7.back()).getNumDep() == 1); 

	}


	//Removes dependency 77 from 1 vertex
	void test_remove_dependencies_3()
	{
	    std::list<Vertex> vertList7;
	    std::list<int> depList1;
	    std::list<int> depList2;

	    Vertex v1 = Vertex(65);
	    Vertex v2 = Vertex(40);

	    depList1.push_back(24);
	    depList1.push_back(77);
	    depList2.push_back(2);
	    depList2.push_back(21);
	    	  
	    vertList7.push_back(v1);
	    vertList7.push_back(v2);
  
	    PFD_populate_vertices(vertList7, 65, 2, depList1);    
	    PFD_populate_vertices(vertList7, 40, 2, depList2);    
	
	   
	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 2);
	    CPPUNIT_ASSERT((vertList7.back()).getNumDep() == 2);
	    PFD_remove_dependencies(vertList7, 77);

	    CPPUNIT_ASSERT((vertList7.front()).getNumDep() == 1);
	    CPPUNIT_ASSERT((vertList7.back()).getNumDep() == 2); 

	}


	//Various tests on Vertex class
	void test_vertex_class_1()
	{
	    Vertex v = Vertex(4);
	    
	    CPPUNIT_ASSERT(v.getVertID() == 4);
	    CPPUNIT_ASSERT(v.getNumDep() == 0);

	    CPPUNIT_ASSERT(v.addDep(1) == true);
	    CPPUNIT_ASSERT(v.addDep(1) == false);

	    CPPUNIT_ASSERT(v.getNumDep() == 1);
	
	    v.removeDep(1);
	
	    CPPUNIT_ASSERT(v.getNumDep() == 0);	     


	}



	//Various tests on Vertex class
	void test_vertex_class_2()
	{
	    Vertex v = Vertex(70);
	    
	    CPPUNIT_ASSERT(v.getVertID() == 70);
	    CPPUNIT_ASSERT(v.getNumDep() == 0);

	    CPPUNIT_ASSERT(v.addDep(16) == true);
	    CPPUNIT_ASSERT(v.addDep(14) == true);
	    CPPUNIT_ASSERT(v.addDep(16) == false);

	    CPPUNIT_ASSERT(v.getNumDep() == 2);

	
	    v.removeDep(16);
	
	    CPPUNIT_ASSERT(v.getNumDep() == 1);	

	    v.removeDep(14);

	    CPPUNIT_ASSERT(v.getNumDep() == 0);     


	}

	//Various tests on Vertex class
	void test_vertex_class_3()
	{
	    Vertex v = Vertex(24);
	    
	    CPPUNIT_ASSERT(v.getVertID() == 24);
	    CPPUNIT_ASSERT(v.getNumDep() == 0);

	    CPPUNIT_ASSERT(v.addDep(16) == true);
	    CPPUNIT_ASSERT(v.addDep(14) == true);
	    CPPUNIT_ASSERT(v.addDep(16) == false);
	    CPPUNIT_ASSERT(v.addDep(4) == true);

	    CPPUNIT_ASSERT(v.getNumDep() == 3);
	
	    v.removeDep(1);
	
	    CPPUNIT_ASSERT(v.getNumDep() == 3);	

	    v.removeDep(14);

	    CPPUNIT_ASSERT(v.getNumDep() == 2);     

	    CPPUNIT_ASSERT(v.addDep(14) == true);



	}


    CPPUNIT_TEST_SUITE(TestPFD);
	

    CPPUNIT_TEST(test_read_rules_1);
    CPPUNIT_TEST(test_read_rules_2); 
    CPPUNIT_TEST(test_read_rules_3); 


    CPPUNIT_TEST(test_read_dependencies_1); 
    CPPUNIT_TEST(test_read_dependencies_2); 
    CPPUNIT_TEST(test_read_dependencies_3); 

    CPPUNIT_TEST(test_make_vertex_1);
    CPPUNIT_TEST(test_make_vertex_2);
    CPPUNIT_TEST(test_make_vertex_2);

    CPPUNIT_TEST(test_populate_vertices_1);
    CPPUNIT_TEST(test_populate_vertices_2);
    CPPUNIT_TEST(test_populate_vertices_3);

    CPPUNIT_TEST(test_remove_dependencies_1);
    CPPUNIT_TEST(test_remove_dependencies_2);
    CPPUNIT_TEST(test_remove_dependencies_3);

    CPPUNIT_TEST(test_vertex_class_1);
    CPPUNIT_TEST(test_vertex_class_2);
    CPPUNIT_TEST(test_vertex_class_3);

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
    return 0;
}


