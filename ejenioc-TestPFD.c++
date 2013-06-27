#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "PFD.h"

struct TestPFD : CppUnit::TestFixture {
  
  /// ---------
  /// clear_queue
  /// ---------
  void test_clear() {
    independents.push(1);
    independents.push(2);
    clear_queue();
    CPPUNIT_ASSERT(independents.size() == 0);
  }
  
  void test_clear1() {
    independents.push(1000);
    independents.push(2000);
    independents.push(5000000);
    clear_queue();
    CPPUNIT_ASSERT(independents.size() != 3);
    independents.push(9000);
    CPPUNIT_ASSERT(independents.top() == 9000);
  }
  
  /// ---------
  /// pfd_read
  /// ---------
  void test_read () {
    clear_queue();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    int i, j;
    bool test = pfd_read (r, i, j);
    CPPUNIT_ASSERT(test == true);
    CPPUNIT_ASSERT(i == 5);
    CPPUNIT_ASSERT(j == 4);}
    
  void test_read1 () {
    std::istringstream r("");
    int i, j;
    bool test = pfd_read (r, i, j);
    CPPUNIT_ASSERT(test == false);}
  
  void test_read2 () {
    std::istringstream r("5");
    int i, j;
    bool test = pfd_read (r, i, j);
    CPPUNIT_ASSERT(test == false);}
    
  /// ---------
  /// pdf_get_independents
  /// ---------
  
  void test_get_independents() {
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pdf_get_independents(w);
    CPPUNIT_ASSERT(w.str() == "1 ");
  }
    
  void test_get_independents1() {
    tasks.clear();
    clear_queue();
    std::istringstream r("6 4\n3 1 6\n2 2 5 3\n4 1 3\n5 1 1\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pdf_get_independents(w);
    CPPUNIT_ASSERT(w.str() == "1 ");
  }
  
  void test_get_independents2() {
    tasks.clear();
    clear_queue();
    std::istringstream r("6 4\n6 1 3\n2 2 5 6\n4 1 6\n5 1 1\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pdf_get_independents(w);
    CPPUNIT_ASSERT(w.str() == "1 ");
    pdf_get_independents(w);
    CPPUNIT_ASSERT(w.str() == "1 3 ");
    CPPUNIT_ASSERT(independents.size() == 2);
  }
  
  void test_get_independents3() {
    tasks.clear();
    clear_queue();
    std::istringstream r("6 4\n3 1 6\n2 2 5 3\n4 1 3\n5 1 1\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pdf_get_independents(w);
    CPPUNIT_ASSERT(w.str() == "1 ");
    pdf_get_independents(w);
    CPPUNIT_ASSERT(independents.size() == 2);
    CPPUNIT_ASSERT(w.str() == "1 6 ");
  }
  
   void test_get_independents4() {
    clear_queue();
    tasks.clear();
    std::istringstream r("2 2\n2 1 1\n1 1 2\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pdf_get_independents(w);
    CPPUNIT_ASSERT(independents.size() == 0);
  }

  /// ---------
  /// update_dependencies
  /// ---------
  
  void test_update_dependencies() {
    clear_queue();
    tasks.clear();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    int i, j;
    bool test = pfd_read (r, i, j);
    independents.push(1);
    update_dependencies();
    for (auto& elem : tasks) {
      for (int j = 0; j < elem.dependencies.size(); j++) {
	CPPUNIT_ASSERT(elem.dependencies.top() != 1);	
      } 
    }
    CPPUNIT_ASSERT(tasks.size() == 5);
  }
  
  void test_update_dependencies1() {
    clear_queue();
    tasks.clear();
    std::istringstream r("4 3\n1 0\n 2 0\n3 0");
    int i, j;
    bool test = pfd_read (r, i, j);
    update_dependencies();
    CPPUNIT_ASSERT(tasks.size() == 4);
    CPPUNIT_ASSERT(independents.size() == 0);
  }
  
  void test_update_dependencies2() {
    clear_queue();
    tasks.clear();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    int i, j;
    bool test = pfd_read (r, i, j);
    independents.push(1);
    independents.push(5);
    update_dependencies();
    for (auto& elem : tasks) {
      for (int j = 0; j < elem.dependencies.size(); j++) {
	CPPUNIT_ASSERT(elem.dependencies.top() != 1);
	CPPUNIT_ASSERT(elem.dependencies.top() != 5);
      }
    }
    CPPUNIT_ASSERT(tasks.size() == 5);
  } 
  
  /// ---------
  /// pfd_eval
  /// ---------
  
  void test_eval () {
    clear_queue();
    tasks.clear();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pfd_eval(w);
    CPPUNIT_ASSERT(tasks.size() == 0);
    CPPUNIT_ASSERT(independents.size() == i);    
  }
  
  void test_eval1() {
    clear_queue();
    tasks.clear();
    std::istringstream r("15 4\n3 0\n2 0\n4 0\n5 0\n");
    std::ostringstream w;
    int i, j;
    bool test = pfd_read (r, i, j);
    pfd_eval(w);
    CPPUNIT_ASSERT(tasks.size() == 0);
    CPPUNIT_ASSERT(independents.size() == i);    
  }
  
  /// ---------
  /// pfd_solve
  /// ---------
  
  void test_solve() {
    clear_queue();
    tasks.clear();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    std::ostringstream w;
    pfd_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n\n");
  }
  
  void test_solve1() {
    clear_queue();
    tasks.clear();
    std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n\n4 1\n2 1 3\n");
    std::ostringstream w;
    pfd_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 \n\n1 3 2 4 \n\n");
    
  }
 
  void test_solve2() {
    clear_queue();
    tasks.clear();
    std::istringstream r("0 0\n");
    std::ostringstream w;
    pfd_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "\n\n");
  }
 
  CPPUNIT_TEST_SUITE(TestPFD);
  CPPUNIT_TEST(test_clear);
  CPPUNIT_TEST(test_clear1);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST(test_read1);
  CPPUNIT_TEST(test_read2);
  CPPUNIT_TEST(test_get_independents);
  CPPUNIT_TEST(test_get_independents1);
  CPPUNIT_TEST(test_get_independents2);
  CPPUNIT_TEST(test_get_independents3);
  CPPUNIT_TEST(test_get_independents4);
  CPPUNIT_TEST(test_update_dependencies);
  CPPUNIT_TEST(test_update_dependencies1);
  CPPUNIT_TEST(test_update_dependencies2);
  CPPUNIT_TEST(test_eval);
  CPPUNIT_TEST(test_eval1);
  CPPUNIT_TEST(test_solve);
  CPPUNIT_TEST(test_solve1);
  CPPUNIT_TEST(test_solve2);
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