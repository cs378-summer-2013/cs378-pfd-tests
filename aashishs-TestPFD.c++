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

extern int _delNodeId;

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----
    void test_read_1 () {
        //sample input
        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(numVerts == 5);
        CPPUNIT_ASSERT(numRules == 4);
        CPPUNIT_ASSERT(graph.size() == 5);
        }

     void test_read_2 () {
        //sample input
        int numVerts = 100;
        int numRules = 4;
        std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(numVerts == 100);
        CPPUNIT_ASSERT(numRules == 4);
        CPPUNIT_ASSERT(graph.size() == 100);}

    void test_read_3 () {
        //sample input
        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 1 1\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(numVerts == 5);
        CPPUNIT_ASSERT(numRules == 4);
        CPPUNIT_ASSERT(graph.size() == 5);}
    
    // -----
    // Create graph
    // -----
    void test_PFD_make_graph () {
        std::vector<node> graph;
        int numVerts = 10;
        PFD_construct(numVerts,graph);
        CPPUNIT_ASSERT(numVerts == 10);
        CPPUNIT_ASSERT(!graph.empty());
        CPPUNIT_ASSERT(graph.size() == 10);
        CPPUNIT_ASSERT(graph[0].id == 0);
        CPPUNIT_ASSERT(graph[0].incoming.empty());
        CPPUNIT_ASSERT(graph[0].outgoing.empty());
        CPPUNIT_ASSERT(graph[9].id == 9);
        CPPUNIT_ASSERT(graph[9].incoming.empty());
        CPPUNIT_ASSERT(graph[9].outgoing.empty());}
    
    // -----
    // Update graph
    // -----
    void test_PFD_construct_1 () {
        std::vector<int> dependencies; 
        dependencies.push_back(0);
        dependencies.push_back(4);
        
        std::vector<node> graph;
        int numVerts = 5;
        PFD_construct(numVerts, graph);
        PFD_construct(2,dependencies,graph);
        CPPUNIT_ASSERT(dependencies.size() == 2);
        CPPUNIT_ASSERT(graph.size() == 5);
        CPPUNIT_ASSERT(graph[2].incoming.size() == 2);
        CPPUNIT_ASSERT(graph[0].outgoing.size() == 1);
        CPPUNIT_ASSERT(graph[4].outgoing.size() == 1); 
        CPPUNIT_ASSERT(graph[2].incoming[0] == 0);
        CPPUNIT_ASSERT(graph[2].incoming[1] == 4);
        CPPUNIT_ASSERT(graph[0].outgoing[0] == 2);
        CPPUNIT_ASSERT(graph[4].outgoing[0] == 2);
        }
    
    // -----
    // eval
    // -----
    void test_eval_1 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(5);
        actualResult.push_back(3);
        actualResult.push_back(2);
        actualResult.push_back(4);

        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

     void test_eval_2 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(3);
        actualResult.push_back(4);
        actualResult.push_back(5);
        actualResult.push_back(2);

        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 1 1\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    void test_eval_3 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(2);
        actualResult.push_back(3);
        actualResult.push_back(4);
        actualResult.push_back(5);
        actualResult.push_back(6);

        int numVerts = 6;
        int numRules = 4;
        std::istringstream in("2 1 1\n4 2 1 2\n5 2 3 4\n6 1 3");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    void test_eval_4 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(2);
        actualResult.push_back(3);
        actualResult.push_back(4);
        actualResult.push_back(5);

        int numVerts = 5;
        int numRules = 2;
        std::istringstream in("4 1 2\n5 2 2 3");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    void test_eval_5 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(2);
        actualResult.push_back(3);
        actualResult.push_back(4);

        int numVerts = 4;
        int numRules = 2;
        std::istringstream in("2 1 1\n4 2 1 2");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    void test_eval_6 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(2);
        actualResult.push_back(3);
        actualResult.push_back(4);
        actualResult.push_back(5);

        int numVerts = 5;
        int numRules = 3;
        std::istringstream in("3 1 2\n4 2 1 3\n5 2 1 3");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    void test_eval_7 () {
        std::vector<int> actualResult;
        actualResult.push_back(1);
        actualResult.push_back(2);
        actualResult.push_back(3);
        actualResult.push_back(4);
        actualResult.push_back(5);

        int numVerts = 5;
        int numRules = 3;
        std::istringstream in("3 2 1 2\n4 2 1 2\n5 2 1 2");
        std::vector<node> graph = PFD_read(numVerts,numRules,in);
        std::vector<int> result = PFD_eval(graph);
        CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),actualResult.begin()));}

    // -----
    // print
    // -----
    void test_print_1() {
        std::vector<int> result;
        result.push_back(1);
        result.push_back(5);
        result.push_back(3);
        result.push_back(2);
        result.push_back(4);

        std::ostringstream out;

        PFD_print(result,out);

        CPPUNIT_ASSERT(out.str() == "1 5 3 2 4\n");}

    void test_print_2() {
        std::vector<int> result;
        result.push_back(1);
        result.push_back(3);
        result.push_back(4);
        result.push_back(5);
        result.push_back(2);

        std::ostringstream out;

        PFD_print(result,out);

        CPPUNIT_ASSERT(out.str() == "1 3 4 5 2\n");}

    void test_print_3() {
        std::vector<int> result;
        result.push_back(2);
        result.push_back(3);
        result.push_back(1);
        result.push_back(5);
        result.push_back(4);

        std::ostringstream out;

        PFD_print(result,out);

        CPPUNIT_ASSERT(out.str() == "2 3 1 5 4\n");}

    // -----
    // solve
    // -----
    void test_solve_1 () {
        std::istringstream in("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream out;
        PFD_solve(in,out);
        CPPUNIT_ASSERT(out.str() == "1 5 3 2 4\n");}
    
    void test_solve_2 () {
        std::istringstream in("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n\n5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream out;
        PFD_solve(in,out);
        CPPUNIT_ASSERT(out.str() == "1 5 3 2 4\n1 3 4 5 2\n");}

    void test_solve_3 () {
        std::istringstream in("6 4\n2 1 1\n4 2 1 2\n5 2 3 4\n6 1 3");
        std::ostringstream out;
        PFD_solve(in,out);
        CPPUNIT_ASSERT(out.str() == "1 2 3 4 5 6\n");}

    // -----
    // checkNode
    // -----
    void test_checkNode_1 () {
        int numVerts = 2;
        std::vector<node> graph;
        PFD_construct(numVerts, graph);
        _delNodeId = 100;
        CPPUNIT_ASSERT(!checkNode(graph[0]));}

    void test_checkNode_2 () {
        int numVerts = 2;
        std::vector<node> graph;
        PFD_construct(numVerts, graph);
        _delNodeId = 1;
        CPPUNIT_ASSERT(!checkNode(graph[0]));}

    void test_checkNode_3 () {
        int numVerts = 2;
        std::vector<node> graph;
        PFD_construct(numVerts, graph);
        _delNodeId = 1;
        CPPUNIT_ASSERT(checkNode(graph[1]));}

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_PFD_make_graph);
    CPPUNIT_TEST(test_PFD_construct_1);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_checkNode_1);
    CPPUNIT_TEST(test_checkNode_2);
    CPPUNIT_TEST(test_checkNode_3);
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
