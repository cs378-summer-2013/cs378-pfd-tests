// --------------------------------
// projects/collatz/TestCollatz.c++
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream r("5\n ");
        int i;
        const bool b = PFD_read(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5);}

    void test_read_2 () {
        std::istringstream r("100 150\n");
        int i;
        const bool b = PFD_read(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    100);}

    void test_read_3 () {
        std::istringstream r("77\n 148");
        int i;
        const bool b = PFD_read(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    77);}

    //----
    // initialize
    //----    



    void test_initialize(){
    	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	int i, j;
    	for(i = 0; i < 101; ++i)
    	{
    		for(j = 0; j < 101; ++j)
    		{
    			if(i == 3 && j == 1)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 3 && j == 5)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 2 && j == 5)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 2 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 4 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 5 && j == 1)
    				CPPUNIT_ASSERT(d_matrix[i][j]);

    		}
    	}
    }

    void test_initialize_2(){
    	std::istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	int i, j;
    	for(i = 0; i < 101; ++i)
    	{
    		for(j = 0; j < 101; ++j)
    		{
    			if(i == 3 && j == 1)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 2 && j == 5)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 2 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 4 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 5 && j == 1)
    				CPPUNIT_ASSERT(d_matrix[i][j]);

    		}
    	}
    }



    void test_initialize_3(){
    	std::istringstream r("5 3\n5 2 2 3\n1 1 3\n4 2 3 1\n");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	int i, j;
    	for(i = 0; i < 101; ++i)
    	{
    		for(j = 0; j < 101; ++j)
    		{
    			if(i == 5 && j == 2)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 5 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 1 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 4 && j == 3)
    				CPPUNIT_ASSERT(d_matrix[i][j]);
    			else if(i == 4 && j == 1)
    				CPPUNIT_ASSERT(d_matrix[i][j]);

    		}
    	}
    }


    void test_array()
    {
        NoPreNodes[0]=9;
        NoPreNodes[1]=7;
        NoPreNodes[2]=5;
        NoPreNodes[3]=3;
        arraySize=4;
        PFD_addNoPreNodes(8);
        CPPUNIT_ASSERT(arraySize==5);
        CPPUNIT_ASSERT(NoPreNodes[0]==9);
        CPPUNIT_ASSERT(NoPreNodes[1]==8);
        CPPUNIT_ASSERT(NoPreNodes[2]==7);
        CPPUNIT_ASSERT(NoPreNodes[3]==5);
        CPPUNIT_ASSERT(NoPreNodes[4]==3);

        
    }

        void test_array_2()
    {
        NoPreNodes[0]=9;
        NoPreNodes[1]=7;
        NoPreNodes[2]=5;
        NoPreNodes[3]=3;
        arraySize=4;
        PFD_addNoPreNodes(2);
        CPPUNIT_ASSERT(arraySize==5);
        CPPUNIT_ASSERT(NoPreNodes[0]==9);
        CPPUNIT_ASSERT(NoPreNodes[1]==7);
        CPPUNIT_ASSERT(NoPreNodes[2]==5);
        CPPUNIT_ASSERT(NoPreNodes[3]==3);
        CPPUNIT_ASSERT(NoPreNodes[4]==2);

        
    }


    void test_clear(){
    	PFD_clearMatrix();
    	int i, j;
    	for(i = 0; i < 101; ++i)
    	{
    		for(j = 0; j < 101; ++j)
    		{
    				CPPUNIT_ASSERT(!d_matrix[i][j]);
    		}
    	}
    }


    void test_lowestIndependentNode(){
    	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
        CPPUNIT_ASSERT(d_matrix[4][3]);
        CPPUNIT_ASSERT(!d_matrix[4][0]);
    	int v = PFD_lowestIndependentNode();
        CPPUNIT_ASSERT(d_matrix[4][3]);
        CPPUNIT_ASSERT(!d_matrix[4][0]);
    	CPPUNIT_ASSERT(v == 1);
        PFD_removeNode(v);
        CPPUNIT_ASSERT(d_matrix[4][3]);
        CPPUNIT_ASSERT(!d_matrix[4][0]);
        v = PFD_lowestIndependentNode();
        CPPUNIT_ASSERT(d_matrix[4][3]);
        CPPUNIT_ASSERT(!d_matrix[4][0]);
        CPPUNIT_ASSERT(v == 5);
    }

    void test_lowestIndependentNode_2(){
    	std::istringstream r("5 3\n5 2 2 3\n1 1 3\n4 2 3 1\n");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	int v = PFD_lowestIndependentNode();
    	CPPUNIT_ASSERT(v == 2);
    }

    //-------------
    //remove_node 
    //-------------

    void test_removeNode()
    {
    	std::istringstream r("5 3\n5 2 2 3\n1 1 3\n4 2 3 1\n");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	CPPUNIT_ASSERT(!d_matrix[2][0]);
    	CPPUNIT_ASSERT(d_matrix[5][2]);
    	int v = PFD_lowestIndependentNode();
    	CPPUNIT_ASSERT(v == 2);
    	PFD_removeNode(v);
    	CPPUNIT_ASSERT(d_matrix[2][0]);
    	CPPUNIT_ASSERT(!d_matrix[5][2]); 
    }

    void test_removeNode_2()
    {
    	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
    	PFD_initializeMatrix(r);
    	CPPUNIT_ASSERT(!d_matrix[1][0]);
    	CPPUNIT_ASSERT(d_matrix[5][1]);
    	CPPUNIT_ASSERT(d_matrix[3][1]);
    	int v = PFD_lowestIndependentNode();
    	CPPUNIT_ASSERT(v == 1);
    	PFD_removeNode(v);
    	CPPUNIT_ASSERT(d_matrix[1][0]);
    	CPPUNIT_ASSERT(!d_matrix[5][1]);
    	CPPUNIT_ASSERT(!d_matrix[3][1]);
    }


    // ----
    // eval
    // ----

    void test_eval_1 () {
    	//Initialize matrix
    	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
   		PFD_initializeMatrix(r);
        const std::string v = PFD_eval();
	
        //Clear matrix
        CPPUNIT_ASSERT(v.compare("1 5 3 2 4") == 0);}

    void test_eval_2 () {
    	//Initialize matrix
    	std::istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1");
    	PFD_clearMatrix();
   		PFD_initializeMatrix(r);
        const std::string v = PFD_eval();
        CPPUNIT_ASSERT(v.compare("1 3 4 5 2") == 0);}

    void test_eval_3 () {
    	//Initialize matrix
    	std::istringstream r("5 3\n5 2 2 3\n1 1 3\n4 2 3 1\n");
    	PFD_clearMatrix();
   		PFD_initializeMatrix(r);
        std::string v = PFD_eval();
        CPPUNIT_ASSERT(v.compare("2 3 1 4 5") == 0);}

void test_eval_100_elem () {
        //Initialize matrix
        std::istringstream r("100 76\n1 1 2\n5 1 34\n11 1 1\n12 2 2 3\n13 2 3 4\n14 1 5\n16 1 6\n17 2 7 8\n19 1 9\n20 1 10\n22 2 12 63\n23 1 12\n24 1 13\n25 1 15\n26 1 15\n27 1 97\n31 1 11\n33 1 23\n34 1 25\n35 1 25\n36 1 26\n37 1 27\n38 1 28\n39 1 29\n40 1 30\n42 1 31\n43 1 33\n44 1 33\n47 1 36\n48 1 37\n49 1 38\n50 2 39 40\n51 1 42\n52 1 42\n53 1 43\n54 1 45\n55 1 35\n56 1 46\n58 2 48 49\n59 1 49\n60 1 49\n61 1 51\n62 2 51 52\n63 1 53\n64 1 54\n67 1 57\n68 1 57\n71 1 61\n72 1 71\n73 1 63\n74 1 54\n75 1 65\n76 1 66\n77 1 67\n78 1 68\n79 1 69\n80 1 89\n81 1 71\n82 1 71\n83 1 73\n84 1 74\n85 1 74\n86 1 75\n87 1 76\n88 1 78\n90 1 80\n91 2 81 71\n92 1 72\n93 1 84\n94 1 84\n95 1 85\n96 1 87\n97 1 87\n98 1 88\n99 1 89\n100 1 90");

        PFD_clearMatrix();
                PFD_initializeMatrix(r);
        const std::string v = PFD_eval();

        CPPUNIT_ASSERT(v.compare("2 1 3 4 6 7 8 9 10 11 12 13 15 16 17 18 19 20 21 23 24 25 26 28 29 30 31 32 33 34 5 14 35 36 38 39 40 41 42 43 44 45 46 47 49 50 51 52 53 54 55 56 57 59 60 61 62 63 22 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 81 82 83 84 85 86 87 88 89 80 90 91 92 93 94 95 96 97 27 37 48 58 98 99 100") == 0);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        std::string s = "1 5 3 4 2\n";
        PFD_print(w, s);
        CPPUNIT_ASSERT(w.str().compare("1 5 3 4 2\n") == 0);}

    void test_print_2 () {
        std::ostringstream w;
        std::string s = "1 3 4 5 2\n";
        PFD_print(w, s);
        CPPUNIT_ASSERT(w.str().compare("1 3 4 5 2\n") == 0);}

    void test_print_3 () {
        std::ostringstream w;
        std::string s = "2 3 1 4 5\n";
        PFD_print(w, s);
        CPPUNIT_ASSERT(w.str().compare("2 3 1 4 5\n") == 0);}


    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("1 5 3 2 4") == 0);}

    void test_solve_2 () {
        std::istringstream r("5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("1 3 4 5 2") == 0);}

    void test_solve_3 () {
        std::istringstream r("5 3\n5 2 2 3\n1 1 3\n4 2 3 1\n");
        std::ostringstream w;
        PFD_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("2 3 1 4 5") == 0);}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_initialize);
    CPPUNIT_TEST(test_initialize_2);
    CPPUNIT_TEST(test_initialize_3);
    CPPUNIT_TEST(test_array);
    CPPUNIT_TEST(test_array_2);
    CPPUNIT_TEST(test_clear);    
    CPPUNIT_TEST(test_lowestIndependentNode);
    CPPUNIT_TEST(test_lowestIndependentNode_2);
    CPPUNIT_TEST(test_removeNode);
    CPPUNIT_TEST(test_removeNode_2);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_100_elem);
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
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
