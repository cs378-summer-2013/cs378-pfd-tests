/* EID:drojas */

// --------------------------------
// projects/PFD/TestPFD.c++
// Copyright (C) 2013
// Diego Rojas
// --------------------------------

/*
To test the program:
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

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>
#include <string>
#include <vector>
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner




#include "PFD.h"


// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {



    // -----
    // pfd_eval
    // -----

    void test_pfd_eval_1 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;	 
        std::vector<int> solution1;
        std::istringstream r("31 15\n2 1 1\n4 3 2 3 1\n6 2 1 2\n8 7 7 3 7 2 3 4 4\n10 6 3 9 7 9 4 2\n12 7 10 8 4 2 1 6 11\n14 9 2 3 4 8 5 11 2 8 2\n16 6 7 7 9 4 11 7\n18 15 9 5 6 5 3 14 13 5 1 9 5 6 1 7 10\n20 12 19 14 13 13 9 5 9 3 16 16 4 16\n22 8 1 12 21 14 1 2 19 12\n24 4 17 15 1 20\n26 1 2\n28 11 1 2 19 18 15 24 11 4 1 2 9\n30 2 16 7\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

        
        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution1);

        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}

    void test_pfd_eval_2 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;	 
        std::vector<int> solution1;
        std::istringstream r("16 4\n2 1 1\n6 4 2 4 2 5\n10 9 1 1 5 7 4 1 6 1 4\n14 2 12 5\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

     
        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution1);

        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}


    void test_pfd_eval_3 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;	 
        std::vector<int> solution1;
        std::istringstream r("35 6\n2 1 1\n8 6 7 2 3 7 4 5\n14 13 9 5 11 3 4 12 6 1 1 9 12 10 7\n20 18 12 18 10 15 13 19 2 1 1 13 19 8 8 19 2 19 12 9\n26 6 19 15 16 21 18 24\n32 17 22 2 18 18 4 11 1 30 18 6 22 8 3 11 29 26 12\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

       
        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution1);

        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}


    void test_pfd_eval_4 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;	 
        std::vector<int> solution1;
        std::istringstream r("72 36\n2 1 1\n4 2 2 1\n6 3 5 5 1\n8 4 1 5 2 4\n10 6 8 6 1 9 4 6\n12 1 11\n14 11 12 13 6 3 2 8 1 10 8 12 13\n16 9 13 1 11 9 9 8 4 14 12\n18 2 8 15\n20 17 1 15 14 2 19 3 4 12 1 17 16 14 13 6 2 7 13\n22 20 9 13 13 12 7 15 20 15 1 20 7 6 20 6 19 4 12 18 19 13\n24 12 19 4 12 13 18 11 20 17 20 4 14 22\n26 15 17 13 6 11 12 25 8 7 5 16 20 1 1 20 21\n28 17 15 21 17 8 18 26 2 5 22 19 21 22 18 7 21 15 16\n30 13 6 16 2 1 16 19 26 16 16 14 20 9 26\n32 6 6 21 6 20 23 1\n34 1 24\n36 23 3 12 17 34 22 12 23 33 7 33 18 13 29 29 2 31 13 32 10 10 16 32 21\n38 3 14 3 11\n40 22 19 3 25 30 19 31 36 13 35 7 11 38 25 13 20 18 26 22 10 16 38 4\n42 28 37 40 23 28 6 21 29 28 10 4 23 24 32 24 40 9 1 20 36 36 31 13 12 27 26 26 39 14\n44 15 39 30 14 31 38 10 21 11 28 37 27 32 11 29 12\n46 3 37 2 15\n48 33 18 14 32 32 36 42 32 25 21 40 36 37 18 14 16 32 20 6 23 12 3 42 1 34 39 5 42 19 47 5 4 18 35\n50 35 26 4 1 2 45 28 32 15 25 40 37 12 37 27 4 42 10 1 11 3 30 14 48 10 15 1 43 12 12 35 49 40 39 1 42\n52 18 26 26 15 40 18 50 10 27 1 50 28 13 33 39 22 43 33 13\n54 1 15\n56 23 1 29 43 50 16 17 27 26 33 37 16 43 52 1 49 6 2 37 39 44 37 53 10\n58 24 13 53 7 36 23 56 17 16 35 54 8 37 57 49 21 56 16 20 51 10 4 49 52 7\n60 26 53 51 43 34 21 59 22 51 52 30 40 29 34 54 42 4 6 8 44 49 59 24 17 55 8 33\n62 29 19 31 11 6 56 48 21 1 27 37 61 11 61 39 18 51 35 35 6 1 43 38 36 46 28 41 44 60 46\n64 40 63 1 3 50 61 21 12 12 17 57 5 28 35 21 63 41 38 44 2 32 23 27 50 23 28 5 24 44 19 34 20 19 35 23 5 33 44 18 45 62\n66 59 25 26 62 8 28 12 36 10 44 37 10 56 57 27 8 38 52 18 54 42 50 45 1 45 62 51 53 26 56 21 20 15 48 16 23 10 26 58 18 5 27 26 59 18 54 1 55 38 17 41 14 65 20 14 44 16 63 29 41\n68 4 47 9 45 9\n70 19 15 9 1 39 37 17 12 64 68 30 62 39 55 28 60 60 32 59 66\n72 43 65 41 4 8 58 48 35 3 26 52 34 65 37 8 36 21 15 10 33 61 52 55 20 66 53 18 36 59 9 1 30 18 42 51 27 44 27 62 63 69 43 25 62\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72};

   
        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution1);

        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}
	

    // -----
    // pfd_read
    // -----

    void test_pfd_read_1 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::vector<int> solution1;
        std::istringstream r("31 15\n2 1 1\n4 3 2 3 1\n6 2 1 2\n8 7 7 3 7 2 3 4 4\n10 6 3 9 7 9 4 2\n12 7 10 8 4 2 1 6 11\n14 9 2 3 4 8 5 11 2 8 2\n16 6 7 7 9 4 11 7\n18 15 9 5 6 5 3 14 13 5 1 9 5 6 1 7 10\n20 12 19 14 13 13 9 5 9 3 16 16 4 16\n22 8 1 12 21 14 1 2 19 12\n24 4 17 15 1 20\n26 1 2\n28 11 1 2 19 18 15 24 11 4 1 2 9\n30 2 16 7\n16 4\n2 1 1\n6 4 2 4 2 5\n10 9 1 1 5 7 4 1 6 1 4\n14 2 12 5\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        while (pfd_read(r, dependency_count, dependency_list)) {
          pfd_eval(dependency_count, dependency_list, solution1);
          dependency_count.clear();
				  dependency_list.clear();}
  
        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}



    void test_pfd_read_2 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::vector<int> solution1;
        std::istringstream r("16 4\n2 1 1\n6 4 2 4 2 5\n10 9 1 1 5 7 4 1 6 1 4\n14 2 12 5\n35 6\n2 1 1\n8 6 7 2 3 7 4 5\n14 13 9 5 11 3 4 12 6 1 1 9 12 10 7\n20 18 12 18 10 15 13 19 2 1 1 13 19 8 8 19 2 19 12 9\n26 6 19 15 16 21 18 24\n32 17 22 2 18 18 4 11 1 30 18 6 22 8 3 11 29 26 12\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

        while (pfd_read(r, dependency_count, dependency_list)) {
          pfd_eval(dependency_count, dependency_list, solution1);
          dependency_count.clear();
				  dependency_list.clear();}
  
        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}



    void test_pfd_read_3 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::vector<int> solution1;

        std::istringstream r("35 6\n2 1 1\n8 6 7 2 3 7 4 5\n14 13 9 5 11 3 4 12 6 1 1 9 12 10 7\n20 18 12 18 10 15 13 19 2 1 1 13 19 8 8 19 2 19 12 9\n26 6 19 15 16 21 18 24\n32 17 22 2 18 18 4 11 1 30 18 6 22 8 3 11 29 26 12\n72 36\n2 1 1\n4 2 2 1\n6 3 5 5 1\n8 4 1 5 2 4\n10 6 8 6 1 9 4 6\n12 1 11\n14 11 12 13 6 3 2 8 1 10 8 12 13\n16 9 13 1 11 9 9 8 4 14 12\n18 2 8 15\n20 17 1 15 14 2 19 3 4 12 1 17 16 14 13 6 2 7 13\n22 20 9 13 13 12 7 15 20 15 1 20 7 6 20 6 19 4 12 18 19 13\n24 12 19 4 12 13 18 11 20 17 20 4 14 22\n26 15 17 13 6 11 12 25 8 7 5 16 20 1 1 20 21\n28 17 15 21 17 8 18 26 2 5 22 19 21 22 18 7 21 15 16\n30 13 6 16 2 1 16 19 26 16 16 14 20 9 26\n32 6 6 21 6 20 23 1\n34 1 24\n36 23 3 12 17 34 22 12 23 33 7 33 18 13 29 29 2 31 13 32 10 10 16 32 21\n38 3 14 3 11\n40 22 19 3 25 30 19 31 36 13 35 7 11 38 25 13 20 18 26 22 10 16 38 4\n42 28 37 40 23 28 6 21 29 28 10 4 23 24 32 24 40 9 1 20 36 36 31 13 12 27 26 26 39 14\n44 15 39 30 14 31 38 10 21 11 28 37 27 32 11 29 12\n46 3 37 2 15\n48 33 18 14 32 32 36 42 32 25 21 40 36 37 18 14 16 32 20 6 23 12 3 42 1 34 39 5 42 19 47 5 4 18 35\n50 35 26 4 1 2 45 28 32 15 25 40 37 12 37 27 4 42 10 1 11 3 30 14 48 10 15 1 43 12 12 35 49 40 39 1 42\n52 18 26 26 15 40 18 50 10 27 1 50 28 13 33 39 22 43 33 13\n54 1 15\n56 23 1 29 43 50 16 17 27 26 33 37 16 43 52 1 49 6 2 37 39 44 37 53 10\n58 24 13 53 7 36 23 56 17 16 35 54 8 37 57 49 21 56 16 20 51 10 4 49 52 7\n60 26 53 51 43 34 21 59 22 51 52 30 40 29 34 54 42 4 6 8 44 49 59 24 17 55 8 33\n62 29 19 31 11 6 56 48 21 1 27 37 61 11 61 39 18 51 35 35 6 1 43 38 36 46 28 41 44 60 46\n64 40 63 1 3 50 61 21 12 12 17 57 5 28 35 21 63 41 38 44 2 32 23 27 50 23 28 5 24 44 19 34 20 19 35 23 5 33 44 18 45 62\n66 59 25 26 62 8 28 12 36 10 44 37 10 56 57 27 8 38 52 18 54 42 50 45 1 45 62 51 53 26 56 21 20 15 48 16 23 10 26 58 18 5 27 26 59 18 54 1 55 38 17 41 14 65 20 14 44 16 63 29 41\n68 4 47 9 45 9\n70 19 15 9 1 39 37 17 12 64 68 30 62 39 55 28 60 60 32 59 66\n72 43 65 41 4 8 58 48 35 3 26 52 34 65 37 8 36 21 15 10 33 61 52 55 20 66 53 18 36 59 9 1 30 18 42 51 27 44 27 62 63 69 43 25 62\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72};

        while (pfd_read(r, dependency_count, dependency_list)) {
          pfd_eval(dependency_count, dependency_list, solution1);
          dependency_count.clear();
				  dependency_list.clear();}
  
        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}



     void test_pfd_read_4 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::vector<int> solution1;

        std::istringstream r("35 6\n2 1 1\n8 6 7 2 3 7 4 5\n14 13 9 5 11 3 4 12 6 1 1 9 12 10 7\n20 18 12 18 10 15 13 19 2 1 1 13 19 8 8 19 2 19 12 9\n26 6 19 15 16 21 18 24\n32 17 22 2 18 18 4 11 1 30 18 6 22 8 3 11 29 26 12\n31 15\n2 1 1\n4 3 2 3 1\n6 2 1 2\n8 7 7 3 7 2 3 4 4\n10 6 3 9 7 9 4 2\n12 7 10 8 4 2 1 6 11\n14 9 2 3 4 8 5 11 2 8 2\n16 6 7 7 9 4 11 7\n18 15 9 5 6 5 3 14 13 5 1 9 5 6 1 7 10\n20 12 19 14 13 13 9 5 9 3 16 16 4 16\n22 8 1 12 21 14 1 2 19 12\n24 4 17 15 1 20\n26 1 2\n28 11 1 2 19 18 15 24 11 4 1 2 9\n30 2 16 7\n");
        int solution2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

        while (pfd_read(r, dependency_count, dependency_list)) {
          pfd_eval(dependency_count, dependency_list, solution1);
          dependency_count.clear();
				  dependency_list.clear();}
  
        CPPUNIT_ASSERT(equal(solution1.begin(), solution1.end(), solution2));}

    


    // -----
    // pfd_print
    // -----


    void test_pfd_print_1 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::istringstream r("31 15\n2 1 1\n4 3 2 3 1\n6 2 1 2\n8 7 7 3 7 2 3 4 4\n10 6 3 9 7 9 4 2\n12 7 10 8 4 2 1 6 11\n14 9 2 3 4 8 5 11 2 8 2\n16 6 7 7 9 4 11 7\n18 15 9 5 6 5 3 14 13 5 1 9 5 6 1 7 10\n20 12 19 14 13 13 9 5 9 3 16 16 4 16\n22 8 1 12 21 14 1 2 19 12\n24 4 17 15 1 20\n26 1 2\n28 11 1 2 19 18 15 24 11 4 1 2 9\n30 2 16 7\n");
        std::ostringstream w;
        std::vector<int> solution;

        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution);
        pfd_print(w, solution);        
        CPPUNIT_ASSERT(w.str().compare("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 \n\n") == 0);}



    void test_pfd_print_2 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::istringstream r("16 4\n2 1 1\n6 4 2 4 2 5\n10 9 1 1 5 7 4 1 6 1 4\n14 2 12 5\n");
        std::ostringstream w;
        std::vector<int> solution;

        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution);
        pfd_print(w, solution);
  
        CPPUNIT_ASSERT(w.str().compare("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 \n\n") == 0);}



    void test_pfd_print_3 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::istringstream r("35 6\n2 1 1\n8 6 7 2 3 7 4 5\n14 13 9 5 11 3 4 12 6 1 1 9 12 10 7\n20 18 12 18 10 15 13 19 2 1 1 13 19 8 8 19 2 19 12 9\n26 6 19 15 16 21 18 24\n32 17 22 2 18 18 4 11 1 30 18 6 22 8 3 11 29 26 12\n");
        std::ostringstream w;
        std::vector<int> solution;

        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution);
        pfd_print(w, solution);
  
        CPPUNIT_ASSERT(w.str().compare("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 \n\n") == 0);}



    void test_pfd_print_4 () {
        std::map <int, int> dependency_count;
  	    std::multimap <int, int> dependency_list;
        std::istringstream r("72 36\n2 1 1\n4 2 2 1\n6 3 5 5 1\n8 4 1 5 2 4\n10 6 8 6 1 9 4 6\n12 1 11\n14 11 12 13 6 3 2 8 1 10 8 12 13\n16 9 13 1 11 9 9 8 4 14 12\n18 2 8 15\n20 17 1 15 14 2 19 3 4 12 1 17 16 14 13 6 2 7 13\n22 20 9 13 13 12 7 15 20 15 1 20 7 6 20 6 19 4 12 18 19 13\n24 12 19 4 12 13 18 11 20 17 20 4 14 22\n26 15 17 13 6 11 12 25 8 7 5 16 20 1 1 20 21\n28 17 15 21 17 8 18 26 2 5 22 19 21 22 18 7 21 15 16\n30 13 6 16 2 1 16 19 26 16 16 14 20 9 26\n32 6 6 21 6 20 23 1\n34 1 24\n36 23 3 12 17 34 22 12 23 33 7 33 18 13 29 29 2 31 13 32 10 10 16 32 21\n38 3 14 3 11\n40 22 19 3 25 30 19 31 36 13 35 7 11 38 25 13 20 18 26 22 10 16 38 4\n42 28 37 40 23 28 6 21 29 28 10 4 23 24 32 24 40 9 1 20 36 36 31 13 12 27 26 26 39 14\n44 15 39 30 14 31 38 10 21 11 28 37 27 32 11 29 12\n46 3 37 2 15\n48 33 18 14 32 32 36 42 32 25 21 40 36 37 18 14 16 32 20 6 23 12 3 42 1 34 39 5 42 19 47 5 4 18 35\n50 35 26 4 1 2 45 28 32 15 25 40 37 12 37 27 4 42 10 1 11 3 30 14 48 10 15 1 43 12 12 35 49 40 39 1 42\n52 18 26 26 15 40 18 50 10 27 1 50 28 13 33 39 22 43 33 13\n54 1 15\n56 23 1 29 43 50 16 17 27 26 33 37 16 43 52 1 49 6 2 37 39 44 37 53 10\n58 24 13 53 7 36 23 56 17 16 35 54 8 37 57 49 21 56 16 20 51 10 4 49 52 7\n60 26 53 51 43 34 21 59 22 51 52 30 40 29 34 54 42 4 6 8 44 49 59 24 17 55 8 33\n62 29 19 31 11 6 56 48 21 1 27 37 61 11 61 39 18 51 35 35 6 1 43 38 36 46 28 41 44 60 46\n64 40 63 1 3 50 61 21 12 12 17 57 5 28 35 21 63 41 38 44 2 32 23 27 50 23 28 5 24 44 19 34 20 19 35 23 5 33 44 18 45 62\n66 59 25 26 62 8 28 12 36 10 44 37 10 56 57 27 8 38 52 18 54 42 50 45 1 45 62 51 53 26 56 21 20 15 48 16 23 10 26 58 18 5 27 26 59 18 54 1 55 38 17 41 14 65 20 14 44 16 63 29 41\n68 4 47 9 45 9\n70 19 15 9 1 39 37 17 12 64 68 30 62 39 55 28 60 60 32 59 66\n72 43 65 41 4 8 58 48 35 3 26 52 34 65 37 8 36 21 15 10 33 61 52 55 20 66 53 18 36 59 9 1 30 18 42 51 27 44 27 62 63 69 43 25 62\n");
        std::ostringstream w;
        std::vector<int> solution;

        pfd_read(r, dependency_count, dependency_list);
        pfd_eval(dependency_count, dependency_list, solution);
        pfd_print(w, solution);
  
        CPPUNIT_ASSERT(w.str().compare("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 \n\n") == 0);}




    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
     CPPUNIT_TEST(test_pfd_eval_1);
     CPPUNIT_TEST(test_pfd_eval_2);
     CPPUNIT_TEST(test_pfd_eval_3);
     CPPUNIT_TEST(test_pfd_eval_4);
     CPPUNIT_TEST(test_pfd_read_1);
     CPPUNIT_TEST(test_pfd_read_2);
     CPPUNIT_TEST(test_pfd_read_3);
     CPPUNIT_TEST(test_pfd_read_4);
     CPPUNIT_TEST(test_pfd_print_1);
     CPPUNIT_TEST(test_pfd_print_2);
     CPPUNIT_TEST(test_pfd_print_3);
     CPPUNIT_TEST(test_pfd_print_4);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {

    using namespace std;

	

    //ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
