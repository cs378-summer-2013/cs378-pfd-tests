

#include <iostream>
#include <exception>
#include <algorithm>
#include <sstream>

#include "PFD.h"

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner




struct TestPFD : CppUnit::TestFixture {




    void testRead_01 () {
        std::istringstream reader ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
 		std::vector<int> testData;
 		std::vector<int> targetData = {5, 4, 3, 2, 1, 5, 2, 2, 5, 3, 4, 1, 3, 5, 1, 1};

        pfdRead(reader, testData);
        bool testPassed = equal(testData.begin(), testData.end(), targetData.begin());

        CPPUNIT_ASSERT(testPassed);
    }

    void testRead_02 () {
        std::istringstream reader ("");
 		std::vector<int> testData;
 		std::vector<int> targetData;

        CPPUNIT_ASSERT_THROW(pfdRead(reader, testData), std::invalid_argument);
    }

    void testRead_03 () {
        std::istringstream reader ("2147483647 2147483647 2147483647 2147483647\n 2147483647\n \n 2147483647\n");
 		std::vector<int> testData;
 		std::vector<int> targetData = {2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647};

        CPPUNIT_ASSERT_THROW(pfdRead(reader, testData), std::invalid_argument);
    }

	void testRead_04 () {
        std::istringstream reader ("abc d 0, 5, 1 2 3 e\n \n \n f 47\n a ds 4 5 6 7 , 10 i'm a cookie");
 		std::vector<int> testData;
 		std::vector<int> targetData = {0, 5, 1, 2, 3, 47, 4, 5, 6, 7, 10};

        pfdRead(reader, testData);
        bool testPassed = equal(testData.begin(), testData.end(), targetData.begin());

        CPPUNIT_ASSERT(testPassed);
    }

    void testRead_05 () {
        std::istringstream reader ("99abc4 d1 2 3e\n \n f21a ds4 5 6 7,\n10i'macookie\n");
 		std::vector<int> testData;
 		std::vector<int> targetData = {99, 4, 1, 2, 3, 21, 4, 5, 6, 7, 10};

        pfdRead(reader, testData);
        bool testPassed = equal(testData.begin(), testData.end(), targetData.begin());

        CPPUNIT_ASSERT(testPassed);
    }




    void testProcessScheduling_01 () {

    	std::vector<int> dependencyData = {5, 4, 3, 2, 1, 5, 2, 2, 5, 3, 4, 1, 3, 5, 1, 1};
		std::list<task> tasks;

		processDependencyDataIntoTasks(dependencyData, tasks);

		task task1; task1.id = 1; task1.dependencies = {};
		task task2; task2.id = 2; task2.dependencies = {5, 3};
		task task3; task3.id = 3; task3.dependencies = {1, 5};
		task task4; task4.id = 4; task4.dependencies = {3};
		task task5; task5.id = 5; task5.dependencies = {1};

		std::list<task> targetData = {
			task1, task2, task3, task4, task5
		};

		tasks.sort();
		targetData.sort();

		CPPUNIT_ASSERT(equal(tasks.begin(), tasks.end(), targetData.begin()));

    }

    void testProcessScheduling_02 () {

    	std::vector<int> dependencyData = {13, 0};
		std::list<task> tasks;

		processDependencyDataIntoTasks(dependencyData, tasks);

		task task1; task1.id = 1; task1.dependencies = {};
		task task2; task2.id = 2; task2.dependencies = {};
		task task3; task3.id = 3; task3.dependencies = {};
		task task4; task4.id = 4; task4.dependencies = {};
		task task5; task5.id = 5; task5.dependencies = {};
		task task6; task6.id = 6; task5.dependencies = {};
		task task7; task7.id = 7; task5.dependencies = {};
		task task8; task8.id = 8; task5.dependencies = {};
		task task9; task9.id = 9; task5.dependencies = {};
		task task10; task10.id = 10; task5.dependencies = {};
		task task11; task11.id = 11; task5.dependencies = {};
		task task12; task12.id = 12; task5.dependencies = {};
		task task13; task13.id = 13; task5.dependencies = {};

		std::list<task> targetData = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		tasks.sort();
		targetData.sort();

		CPPUNIT_ASSERT(equal(tasks.begin(), tasks.end(), targetData.begin()));

    }

    void testProcessScheduling_03 () {

    	std::vector<int> dependencyData = {
    		13, 12, 
    		1, 12, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    		2, 11, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    		3, 10, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
			4, 9, 5, 6, 7, 8, 9, 10, 11, 12, 13,
			5, 8, 6, 7, 8, 9, 10, 11, 12, 13,
			6, 7, 7, 8, 9, 10, 11, 12, 13,
			7, 6, 8, 9, 10, 11, 12, 13,
			8, 5, 9, 10, 11, 12, 13,
			9, 4, 10, 11, 12, 13,
			10, 3, 11, 12, 13,
			11, 2, 12, 13,
			12, 1, 13,
		};
    		
		std::list<task> tasks;
		processDependencyDataIntoTasks(dependencyData, tasks);

		task task1; task1.id = 1; task1.dependencies = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task2; task2.id = 2; task2.dependencies = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task3; task3.id = 3; task3.dependencies = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task4; task4.id = 4; task4.dependencies = {5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task5; task5.id = 5; task5.dependencies = {6, 7, 8, 9, 10, 11, 12, 13};
		task task6; task6.id = 6; task6.dependencies = {7, 8, 9, 10, 11, 12, 13};
		task task7; task7.id = 7; task7.dependencies = {8, 9, 10, 11, 12, 13};
		task task8; task8.id = 8; task8.dependencies = {9, 10, 11, 12, 13};
		task task9; task9.id = 9; task9.dependencies = {10, 11, 12, 13};
		task task10; task10.id = 10; task10.dependencies = {11, 12, 13};
		task task11; task11.id = 11; task11.dependencies = {12, 13};
		task task12; task12.id = 12; task12.dependencies = {13};
		task task13; task13.id = 13; task13.dependencies = {};

		std::list<task> targetData = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		tasks.sort();
		targetData.sort();

		CPPUNIT_ASSERT(equal(tasks.begin(), tasks.end(), targetData.begin()));

    }

    void testProcessScheduling_04 () {

    	std::vector<int> dependencyData = {
    		13, 12, 
    		1, 4, 8, 4, 5, 7,
    		2, 2, 4, 12,
    		3, 3, 12, 6, 4,
    		
    		5, 1, 4,
    		6, 2, 12, 4,
    		7, 2, 5, 4,
    		8, 3, 4, 7, 5,
    		9, 4, 12, 4, 3, 6,
    		10, 5, 4, 1, 8, 5, 7,
    		11, 6, 5, 4, 1, 10, 7, 8,
    		12, 1, 4,
    		13, 3, 7, 5, 4, 
		};
    		
		std::list<task> tasks;
		processDependencyDataIntoTasks(dependencyData, tasks);

		task task1; task1.id = 1; task1.dependencies = {8, 4, 5, 7};
		task task2; task2.id = 2; task2.dependencies = {4, 12};
		task task3; task3.id = 3; task3.dependencies = {12, 6, 4};
		task task4; task4.id = 4; task4.dependencies = {};
		task task5; task5.id = 5; task5.dependencies = {4};
		task task6; task6.id = 6; task6.dependencies = {12, 4};
		task task7; task7.id = 7; task7.dependencies = {5, 4};
		task task8; task8.id = 8; task8.dependencies = {4, 7, 5};
		task task9; task9.id = 9; task9.dependencies = {12, 4, 3, 6};
		task task10; task10.id = 10; task10.dependencies = {4, 1, 8, 5, 7};
		task task11; task11.id = 11; task11.dependencies = {5, 4, 1, 10, 7, 8};
		task task12; task12.id = 12; task12.dependencies = {4};
		task task13; task13.id = 13; task13.dependencies = {7, 5, 4};

		std::list<task> targetData = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		tasks.sort();
		targetData.sort();

		CPPUNIT_ASSERT(equal(tasks.begin(), tasks.end(), targetData.begin()));

    }

        void testProcessScheduling_05 () {

    	std::vector<int> dependencyData = {
    		13, 12, 
    		8, 3, 4, 7, 5,
    		6, 2, 12, 4,
    		2, 2, 4, 12,
    		5, 1, 4,
    		3, 3, 12, 6, 4,
    		7, 2, 5, 4,
    		11, 6, 5, 4, 1, 10, 7, 8,
    		9, 4, 12, 4, 3, 6,
    		13, 3, 7, 5, 4, 
    		1, 4, 8, 4, 5, 7,
    		12, 1, 4,
    		10, 5, 4, 1, 8, 5, 7,
		};
    		
		std::list<task> tasks;
		processDependencyDataIntoTasks(dependencyData, tasks);

		task task1; task1.id = 1; task1.dependencies = {8, 4, 5, 7};
		task task2; task2.id = 2; task2.dependencies = {4, 12};
		task task3; task3.id = 3; task3.dependencies = {12, 6, 4};
		task task4; task4.id = 4; task4.dependencies = {};
		task task5; task5.id = 5; task5.dependencies = {4};
		task task6; task6.id = 6; task6.dependencies = {12, 4};
		task task7; task7.id = 7; task7.dependencies = {5, 4};
		task task8; task8.id = 8; task8.dependencies = {4, 7, 5};
		task task9; task9.id = 9; task9.dependencies = {12, 4, 3, 6};
		task task10; task10.id = 10; task10.dependencies = {4, 1, 8, 5, 7};
		task task11; task11.id = 11; task11.dependencies = {5, 4, 1, 10, 7, 8};
		task task12; task12.id = 12; task12.dependencies = {4};
		task task13; task13.id = 13; task13.dependencies = {7, 5, 4};

		std::list<task> targetData = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		tasks.sort();
		targetData.sort();

		CPPUNIT_ASSERT(equal(tasks.begin(), tasks.end(), targetData.begin()));

    }





    void testTopologicalSort_01 () {

		std::list<int> orderedTasks;
		std::list<int> targetData = {1, 5, 3, 2, 4};

		task task1; task1.id = 1; task1.dependencies = {};
		task task2; task2.id = 2; task2.dependencies = {5, 3};
		task task3; task3.id = 3; task3.dependencies = {1, 5};
		task task4; task4.id = 4; task4.dependencies = {3};
		task task5; task5.id = 5; task5.dependencies = {1};

		std::list<task> tasks = {
			task1, task2, task3, task4, task5
		};

		topologicalSort(tasks, orderedTasks);

		CPPUNIT_ASSERT(equal(orderedTasks.begin(), orderedTasks.end(), targetData.begin()));
    }

    void testTopologicalSort_02 () {

		std::list<int> orderedTasks;
		std::list<int> targetData = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

		task task1; task1.id = 1; task1.dependencies = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task2; task2.id = 2; task2.dependencies = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task3; task3.id = 3; task3.dependencies = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task4; task4.id = 4; task4.dependencies = {5, 6, 7, 8, 9, 10, 11, 12, 13};
		task task5; task5.id = 5; task5.dependencies = {6, 7, 8, 9, 10, 11, 12, 13};
		task task6; task6.id = 6; task6.dependencies = {7, 8, 9, 10, 11, 12, 13};
		task task7; task7.id = 7; task7.dependencies = {8, 9, 10, 11, 12, 13};
		task task8; task8.id = 8; task8.dependencies = {9, 10, 11, 12, 13};
		task task9; task9.id = 9; task9.dependencies = {10, 11, 12, 13};
		task task10; task10.id = 10; task10.dependencies = {11, 12, 13};
		task task11; task11.id = 11; task11.dependencies = {12, 13};
		task task12; task12.id = 12; task12.dependencies = {13};
		task task13; task13.id = 13; task13.dependencies = {};

		std::list<task> tasks = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		topologicalSort(tasks, orderedTasks);

		CPPUNIT_ASSERT(equal(orderedTasks.begin(), orderedTasks.end(), targetData.begin()));
    }

    void testTopologicalSort_03 () {

		std::list<int> orderedTasks;
		std::list<int> targetData = {4, 5, 7, 8, 1, 10, 11, 12, 2, 6, 3, 9, 13};

		task task1; task1.id = 1; task1.dependencies = {8, 4, 5, 7};
		task task2; task2.id = 2; task2.dependencies = {4, 12};
		task task3; task3.id = 3; task3.dependencies = {12, 6, 4};
		task task4; task4.id = 4; task4.dependencies = {};
		task task5; task5.id = 5; task5.dependencies = {4};
		task task6; task6.id = 6; task6.dependencies = {12, 4};
		task task7; task7.id = 7; task7.dependencies = {5, 4};
		task task8; task8.id = 8; task8.dependencies = {4, 7, 5};
		task task9; task9.id = 9; task9.dependencies = {12, 4, 3, 6};
		task task10; task10.id = 10; task10.dependencies = {4, 1, 8, 5, 7};
		task task11; task11.id = 11; task11.dependencies = {5, 4, 1, 10, 7, 8};
		task task12; task12.id = 12; task12.dependencies = {4};
		task task13; task13.id = 13; task13.dependencies = {7, 5, 4};

		std::list<task> tasks = {
			task1, task2, task3, task4, task5, task6, task7, task8, task9, task10, task11, task12, task13
		};

		topologicalSort(tasks, orderedTasks);

		CPPUNIT_ASSERT(equal(orderedTasks.begin(), orderedTasks.end(), targetData.begin()));
    }

     void testTopologicalSort_04 () {

		std::list<int> orderedTasks;
		std::list<int> targetData = {8, 1, 5, 3, 2, 10, 9, 4, 6, 7};

		task task1; task1.id = 1; task1.dependencies = {8};
		task task2; task2.id = 2; task2.dependencies = {3, 1, 8};
		task task3; task3.id = 3; task3.dependencies = {5};
		task task4; task4.id = 4; task4.dependencies = {9};
		task task5; task5.id = 5; task5.dependencies = {8};
		task task6; task6.id = 6; task6.dependencies = {9};
		task task7; task7.id = 7; task7.dependencies = {9};
		task task8; task8.id = 8; task8.dependencies = {};
		task task9; task9.id = 9; task9.dependencies = {10, 1, 5};
		task task10; task10.id = 10; task10.dependencies = {2, 3};

		std::list<task> tasks = {
			task2, task3, task5, task7, task8, task1, task6, task9, task4, task10
		};

		topologicalSort(tasks, orderedTasks);

		CPPUNIT_ASSERT(equal(orderedTasks.begin(), orderedTasks.end(), targetData.begin()));
    }





    void testPFD_01 () {
		// std::cout << std::endl << std::endl << "testPFD_01!!!!!!" << std::endl;

        std::istringstream reader ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream writer;

        pfd(reader, writer);

        CPPUNIT_ASSERT(writer.str() == "1 5 3 2 4\n");
    }

    void testPFD_02 () {
    	// std::cout << std::endl << std::endl << "testPFD_02!!!!!!" << std::endl;

        std::istringstream reader ("10 0\n");
        std::ostringstream writer;

        pfd(reader, writer);



        CPPUNIT_ASSERT(writer.str() == "1 2 3 4 5 6 7 8 9 10\n");
    }

    void testPFD_03 () {
        std::istringstream reader (
        	"13 12\n 1 12 2 3 4 5 6 7 8 9 10 11 12 13\n2 11 3 4 5 6 7 8 9 10 11 12 13\n3 10 4 5 6 7 8 9 10 11 12 13\n4 9 5 6 7 8 9 10 11 12 13\n5 8 6 7 8 9 10 11 12 13\n6 7 7 8 9 10 11 12 13\n7 6 8 9 10 11 12 13\n8 5 9 10 11 12 13\n9 4 10 11 12 13\n10 3 11 12 13\n11 2 12 13\n12 1 13\n"
		);
        std::ostringstream writer;

        pfd(reader, writer);

        CPPUNIT_ASSERT(writer.str() == "13 12 11 10 9 8 7 6 5 4 3 2 1\n");
    }

     void testPFD_04 () {
        std::istringstream reader (
        	"13 12\n8 3 4 7 5\n6 2 12 4\n2 2 4 12\n5 1 4\n3 3 12 6 4\n7 2 5 4\n11 6 5 4 1 10 7 8\n9 4 12 4 3 6\n13 3 7 5 4 \n1 4 8 4 5 7\n12 1 4\n10 5 4 1 8 5 7    \n"
    	);
        std::ostringstream writer;

        pfd(reader, writer);

        CPPUNIT_ASSERT(writer.str() == "4 5 7 8 1 10 11 12 2 6 3 9 13\n");
    }

    void testPFD_05 () {
        std::istringstream reader (
        	"13 adfb asfbsf b12\n8 sfb3 ffb4 f7 ab5\n6 2 asfb12 4\ntreu2 2 4 rty12\n5 1 4\n3 3 rtuertu12 6 4\n7 2 5 4\nu11 u6 u5 u4 u1 t10 t7 t8\n9 4 12 4 3rty 6\n13 3 7 5 4 \n1 4 8 4ertyerty 5 7\n12 1 4\n10 5 4 1 8 5 7 I\'mma cookie!   \n"
    	);
        std::ostringstream writer;

        pfd(reader, writer);

        CPPUNIT_ASSERT(writer.str() == "4 5 7 8 1 10 11 12 2 6 3 9 13\n");
    }

    void testPFD_06 () {
        std::istringstream reader (
        	"10 9\n1 1 8\n 2 3 3 1 8\n3 1 5\n4 1 9\n5 1 8\n6 1 9\n7 1 9\n8 ghdgfh 0\n9 3 10 1 5\n10 2 2 3\n"
    	);
        std::ostringstream writer;

        pfd(reader, writer);

        CPPUNIT_ASSERT(writer.str() == "8 1 5 3 2 10 9 4 6 7\n");
    }





    void testWrite_01 () {
        std::ostringstream writer;
        std::list<int> orderedTaskData = {1, 5, 3, 2, 4};

        pfdWrite(orderedTaskData, writer);

        CPPUNIT_ASSERT(writer.str() == "1 5 3 2 4\n"); 
    }

    void testWrite_02 () {
        std::ostringstream writer;
        std::list<int> orderedTaskData = {-1, 5, -3, 2, -4};

        pfdWrite(orderedTaskData, writer);

        CPPUNIT_ASSERT(writer.str() == "-1 5 -3 2 -4\n"); 
    }

    void testWrite_03 () {
        std::ostringstream writer;
        std::list<int> orderedTaskData = {-2147483647, 2147483647, -2147483647, 2147483647, -2147483647};

        pfdWrite(orderedTaskData, writer);

        CPPUNIT_ASSERT(writer.str() == "-2147483647 2147483647 -2147483647 2147483647 -2147483647\n"); 
    }

    void testWrite_04 () {
        std::ostringstream writer;
        std::list<int> orderedTaskData = {-0, 0, -0, 0, -0};

        pfdWrite(orderedTaskData, writer);

        CPPUNIT_ASSERT(writer.str() == "0 0 0 0 0\n"); 
    }




    void testTaskOperatorLT_01 () {
        task task1; task1.id = 1; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {3, 1, 8};
		CPPUNIT_ASSERT((task1 < task2) == true);
    }

    void testTaskOperatorLT_02 () {
        task task1; task1.id = 1; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {3};
		CPPUNIT_ASSERT((task1 < task2) == true);
    }

    void testTaskOperatorLT_03 () {
        task task1; task1.id = 2; task1.dependencies = {3};
		task task2; task2.id = -999; task2.dependencies = {3, 14};
		CPPUNIT_ASSERT((task2 < task1) == true);
    }

    void testTaskOperatorLT_04 () {
        task task1; task1.id = 2; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {3, 14};
		CPPUNIT_ASSERT((task2 < task1) == false);
    }

    void testTaskOperatorLT_05 () {
        task task1; task1.id = -2147483647; task1.dependencies = {2147483647};
		task task2; task2.id = 2147483647; task2.dependencies = {2147483647};
		CPPUNIT_ASSERT((task2 < task1) == false);
    }




    void testTaskOperatorEQ_01 () {
        task task1; task1.id = 1; task1.dependencies = {3};
		task task2; task2.id = 1; task2.dependencies = {3};
		CPPUNIT_ASSERT((task1 == task2) == true);
    }

    void testTaskOperatorEQ_02 () {
        task task1; task1.id = 1; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {3};
		CPPUNIT_ASSERT((task1 == task2) == false);
    }

    void testTaskOperatorEQ_03 () {
        task task1; task1.id = 2; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {3, 14};
		CPPUNIT_ASSERT((task2 == task1) == false);
    }

    void testTaskOperatorEQ_04 () {
        task task1; task1.id = 2; task1.dependencies = {3, 14, 9};
		task task2; task2.id = 2; task2.dependencies = {3, 14};
		CPPUNIT_ASSERT((task2 == task1) == false);
    }

    void testTaskOperatorEQ_05 () {
        task task1; task1.id = -2147483647; task1.dependencies = {2147483647};
		task task2; task2.id = 2147483647; task2.dependencies = {2147483647};
		CPPUNIT_ASSERT((task2 == task1) == false);
    }

    void testTaskOperatorEQ_06 () {
        task task1; task1.id = 1; task1.dependencies = {};
		task task2; task2.id = 1; task2.dependencies = {};
		CPPUNIT_ASSERT((task1 == task2) == true);
    }

    void testTaskOperatorEQ_07 () {
        task task1; task1.id = 1; task1.dependencies = {3};
		task task2; task2.id = 2; task2.dependencies = {};
		CPPUNIT_ASSERT((task1 == task2) == false);
	}

	void testTaskOperatorEQ_08 () {
        task task1; task1.id = 1; task1.dependencies = {};
		task task2; task2.id = 2; task2.dependencies = {9};
		CPPUNIT_ASSERT((task1 == task2) == false);
	}

	void testTaskOperatorEQ_09 () {
        task task1; task1.id = 2; task1.dependencies = {3, 14, 9};
		task task2; task2.id = 2; task2.dependencies = {3, 14, 9, 10};
		CPPUNIT_ASSERT((task2 == task1) == false);
    }




    CPPUNIT_TEST_SUITE(TestPFD); {
		
		CPPUNIT_TEST(testRead_01);
		CPPUNIT_TEST(testRead_02);
		CPPUNIT_TEST(testRead_03);
		CPPUNIT_TEST(testRead_04);
		CPPUNIT_TEST(testRead_05);

		CPPUNIT_TEST(testTopologicalSort_01);
		CPPUNIT_TEST(testTopologicalSort_02);
		CPPUNIT_TEST(testTopologicalSort_03);
		CPPUNIT_TEST(testTopologicalSort_04);

		CPPUNIT_TEST(testPFD_01);
		CPPUNIT_TEST(testPFD_02);
		CPPUNIT_TEST(testPFD_03);
		CPPUNIT_TEST(testPFD_04);
		CPPUNIT_TEST(testPFD_05);
		CPPUNIT_TEST(testPFD_06);

		CPPUNIT_TEST(testWrite_01);
		CPPUNIT_TEST(testWrite_02);
		CPPUNIT_TEST(testWrite_03);
		CPPUNIT_TEST(testWrite_04);

		CPPUNIT_TEST(testProcessScheduling_01);
		CPPUNIT_TEST(testProcessScheduling_02);
		CPPUNIT_TEST(testProcessScheduling_03);
		CPPUNIT_TEST(testProcessScheduling_04);
		CPPUNIT_TEST(testProcessScheduling_05);

		CPPUNIT_TEST(testTaskOperatorLT_01);
		CPPUNIT_TEST(testTaskOperatorLT_02);
		CPPUNIT_TEST(testTaskOperatorLT_03);
		CPPUNIT_TEST(testTaskOperatorLT_04);
		CPPUNIT_TEST(testTaskOperatorLT_05);

		CPPUNIT_TEST(testTaskOperatorEQ_01);
		CPPUNIT_TEST(testTaskOperatorEQ_02);
		CPPUNIT_TEST(testTaskOperatorEQ_03);
		CPPUNIT_TEST(testTaskOperatorEQ_04);
		CPPUNIT_TEST(testTaskOperatorEQ_05);
		CPPUNIT_TEST(testTaskOperatorEQ_06);
		CPPUNIT_TEST(testTaskOperatorEQ_07);
		CPPUNIT_TEST(testTaskOperatorEQ_08);
		CPPUNIT_TEST(testTaskOperatorEQ_09);


	} CPPUNIT_TEST_SUITE_END();
};







int main() {
	try {

	    std::ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	    std::cout << "TestPFD.c++" << std::endl;

	    CppUnit::TextTestRunner testRunner;
	    testRunner.addTest(TestPFD::suite());
	    testRunner.run();

	    std::cout << "Done." << std::endl;

	    return 0;
	}
	catch (std::exception &e) {
		std::cerr << "Fatal error; exception thrown: " << e.what() << std::endl << "Exiting program..." << std::endl;
		return 1;
	}

}


