// File:        a1gradingdriver.cpp
// Author:      Geoffrey Tien
// Date:        2016-01-22
// Description: Grading driver for CMPT 225 assignment #1

#include <iostream>
#include <sstream>
#include <string>

#include "cd.h"
#include "cdcatalogue.h"

using namespace std;

// maximum test score declarations
const static double test1max = 4;
const static double test2max = 1;
const static double test3max = 1;
const static double test4max = 5;
const static double test5max = 2;
const static double test6max = 3;
const static double test7max = 2;
const static double test8max = 2;
const static double test9max = 3;

// CD objects used for testing
const static CD cd_a1("AC/DC", "Back in Black");
const static CD cd_a2("AC/DC", "Highway to Hell");
const static CD cd_a3("Aerosmith", "Rocks");
const static CD cd_a4("Aerosmith", "Toys in the Attic");
const static CD cd_b1("Bon Jovi", "New Jersey");
const static CD cd_c1("Cheap Trick", "Heaven Tonight");
const static CD cd_d1("Dokken", "Back for the Attack");
const static CD cd_d2("Deep Purple", "Machine Head");
const static CD cd_g1("Guns n Roses", "Appetite for Destruction");
const static CD cd_s1("Sammy Hagar", "Danger Zone");
const static CD cd_s2("Sammy Hagar", "Standing Hampton");
const static CD cd_s3("Sammy Hagar", "Three Lock Box");
const static CD cd_s4("Sammy Hagar", "VOA");

// forward function declarations
double Test1();
double Test2();
double Test3();
double Test4();
double Test5();
double Test6();
double Test7();
double Test8();
double Test9();

// program entry point
int main()
{
	double test1score = 0;
	double test2score = 0;
	double test3score = 0;
	double test4score = 0;
	double test5score = 0;
	double test6score = 0;
	double test7score = 0;
	double test8score = 0;
	double test9score = 0;

	cout << "Running test 1: default constructor, Insert, Count, Find...";
	test1score = Test1();
	cout << " done.\n" << endl;

	cout << "Running test 2: Insert (array growing)...";
	test2score = Test2();
	cout << " done.\n" << endl;

	cout << "Running test 3: Remove (empty & non-existent)...";
	test3score = Test3();
	cout << " done.\n" << endl;

	cout << "Running test 4: Remove (general cases)...";
	test4score = Test4();
	cout << " done.\n" << endl;

	cout << "Running test 5: Copy constructor...";
	test5score = Test5();
	cout << " done.\n" << endl;

	cout << "Running test 6: Boycott...";
	test6score = Test6();
	cout << " done.\n" << endl;

	cout << "Running test 7: Join...";
	test7score = Test7();
	cout << " done.\n" << endl;

	cout << "Running test 8: Common...";
	test8score = Test8();
	cout << " done.\n" << endl;

	cout << "Running test 9: Split...";
	test9score = Test9();
	cout << " done.\n" << endl;

	// compute total and maximum scores
	double testscoresum = test1score + test2score + test3score + test4score + test5score +
		test6score + test7score + test8score + test9score;
	double testmax = test1max + test2max + test3max + test4max + test5max +
		test6max + test7max + test8max + test9max;
	// format a string for summary output
	cout << "Test summary\n----------------------------------------------------------" << endl;
	string summary;
	ostringstream oss;
	oss << "Test1: " << test1score << "/" << test1max << "\tTest2: " << test2score << "/" << test2max
		<< "\tTest3: " << test3score << "/" << test3max << "\tTest4: " << test4score << "/" << test4max << endl
		<< "Test5: " << test5score << "/" << test5max << "\tTest6: " << test6score << "/" << test6max
		<< "\tTest7: " << test7score << "/" << test7max << "\tTest8: " << test8score << "/" << test8max << endl
		<< "Test9: " << test9score << "/" << test9max << endl
		<< "----------------------------------------------------------" << endl
		<< "Total: " << testscoresum << "/" << testmax << endl;
	cout << oss.str() << endl;

	system("pause");

	return 0;
}

// default constructor, Insert, Count, Find
double Test1()
{
	double score = 0;

	CDCatalogue cat1;

	// check size (expect 0)
	if (cat1.Count() == 0)
		score += 0.5;
	// find a non-existent item
	if (cat1.Find(cd_a1) == -1)
		score += 0.5;

	// first successful insert
	if (cat1.Insert(cd_a3))
	{
		score += 0.5;
		if (cat1.Count() == 1 && cat1.Find(cd_a3) == 0)
			score += 0.5;
	}

	// insert an existing item
	if (!cat1.Insert(cd_a3) && cat1.Count() == 1)
		score += 0.5;

	// insert three more items to array capacity
	if (cat1.Insert(cd_b1) && cat1.Insert(cd_c1) &&
		cat1.Insert(cd_d1) && cat1.Count() == 4)
	{
		score += 0.5;
		if (cat1.Find(cd_a3) == 0 && cat1.Find(cd_b1) == 1 &&
			cat1.Find(cd_c1) == 2 && cat1.Find(cd_d1) == 3)
			score += 0.5;
	}

	// find non-existent item from full array
	if (cat1.Find(cd_g1) == -1)
		score += 0.5;

	return score;
}

// Insert - grow condition
double Test2()
{
	double score = 0;

	// create CDCatalogue with default array size, and add 4 items to it
	CDCatalogue cat1;
	cat1.Insert(cd_a3);
	cat1.Insert(cd_b1);
	cat1.Insert(cd_c1);
	cat1.Insert(cd_d1);

	// Insert a 5th item
	if (cat1.Insert(cd_a4))
	{
		score += 0.5;
		if (cat1.Count() == 5 && cat1.Find(cd_a4) == 4)
			score += 0.5;
	}

	return score;
}

// Remove - empty, non-existent
double Test3()
{
	double score = 0;

	CDCatalogue cat1;

	// remove from empty catalogue
	if (!cat1.Remove(cd_a1) && cat1.Count() == 0)
		score += 0.5;

	// in case of size errors in cat1, create a new catalogue and fill with 4 items
	CDCatalogue cat2;
	cat2.Insert(cd_a3);
	cat2.Insert(cd_b1);
	cat2.Insert(cd_c1);
	cat2.Insert(cd_d1);

	// remove non-existent item
	if (!cat2.Remove(cd_a1) && cat2.Count() == 4)
		score += 0.5;

	return score;
}

// Remove - general cases
double Test4()
{
	double score = 0;

	CDCatalogue cat1;
	cat1.Insert(cd_a3);
	cat1.Insert(cd_b1);
	cat1.Insert(cd_c1);
	cat1.Insert(cd_d1);

	// remove from middle of collection
	if (cat1.Remove(cd_b1))
	{
		if (cat1.Count() == 3)
			score += 0.5;
		if (cat1.Find(cd_a3) == 0 && cat1.Find(cd_d1) == 1 &&
			cat1.Find(cd_c1) == 2 && cat1.Find(cd_b1) == -1)
			score += 0.5;
	}

	// remove from front of collection
	if (cat1.Remove(cd_a3))
	{
		if (cat1.Count() == 2)
			score += 0.5;
		if (cat1.Find(cd_c1) == 0 && cat1.Find(cd_d1) == 1 &&
			cat1.Find(cd_a3) == -1)
			score += 0.5;
	}

	// remove from back of collection
	if (cat1.Remove(cd_d1))
	{
		if (cat1.Count() == 1)
			score += 0.5;
		if (cat1.Find(cd_c1) == 0 && cat1.Find(cd_d1) == -1)
			score += 0.5;
	}

	// remove last remaining item
	if (cat1.Remove(cd_c1))
	{
		if (cat1.Count() == 0)
			score += 0.5;
		if (cat1.Find(cd_c1) == -1)
			score += 0.5;
	}

	// add an item to non-default empty catalogue
	if (cat1.Insert(cd_a2))
	{
		if (cat1.Count() == 1)
			score += 0.5;
		if (cat1.Find(cd_a2) == 0)
			score += 0.5;
	}

	return score;
}

// Copy constructor
double Test5()
{
	double score = 0;

	// create a catalogue and insert two items
	CDCatalogue cat1;
	cat1.Insert(cd_a3);
	cat1.Insert(cd_b1);

	// create a catalogue as copy of cat1
	CDCatalogue cat2(cat1);

	// check size and contents of cat2
	if (cat2.Count() == 2 && cat2.Find(cd_a3) == 0 && cat2.Find(cd_b1) == 1 && cat2.Find(cd_a1) == -1)
		score += 0.5;

	// Remove an item from cat1, add an item to cat2
	// Then check size and contents of each catalogue
	cat1.Remove(cd_a3);
	cat2.Insert(cd_g1);
	if (cat1.Count() == 1 && cat2.Count() == 3)
		score += 0.5;
	if (cat1.Find(cd_b1) == 0 && cat1.Find(cd_g1) == -1)
		score += 0.5;
	if (cat2.Find(cd_a3) == 0 && cat2.Find(cd_b1) == 1 && cat2.Find(cd_g1) == 2)
		score += 0.5;

	return score;
}

// Boycott
double Test6()
{
	double score = 0;

	// unsuccessful boycott
	CDCatalogue cat1;
	cat1.Insert(cd_a3);
	cat1.Insert(cd_b1);
	cat1.Insert(cd_c1);
	cat1.Insert(cd_d1);
	if (!cat1.Boycott("One Direction"))
		score += 0.5;
	if (cat1.Count() == 4 && cat1.Find(cd_a3) != -1 && cat1.Find(cd_b1) != -1 &&
		cat1.Find(cd_c1) != -1 && cat1.Find(cd_d1) != -1)
		score += 0.5;

	// successful boycott of partial collection
	CDCatalogue cat2;
	cat2.Insert(cd_s1);
	cat2.Insert(cd_b1);
	cat2.Insert(cd_c1);
	cat2.Insert(cd_s2);
	if (cat2.Boycott("Sammy Hagar"))
	{
		if (cat2.Count() == 2 && cat2.Find(cd_b1) != -1 && cat2.Find(cd_c1) != -1 &&
			cat2.Find(cd_s1) == -1 && cat2.Find(cd_s2) == -1)
			score += 0.5;
		if (cat2.Insert(cd_d1) && cat2.Count() == 3 && cat2.Find(cd_d1) == 2)
			score += 0.5;
	}

	// successful boycott of entire collection
	CDCatalogue cat3;
	cat3.Insert(cd_s1);
	cat3.Insert(cd_s2);
	cat3.Insert(cd_s3);
	cat3.Insert(cd_s4);
	if (cat3.Boycott("Sammy Hagar"))
	{
		if (cat3.Count() == 0 && cat3.Find(cd_s1) == -1 && cat3.Find(cd_s2) == -1 &&
			cat3.Find(cd_s3) == -1 && cat3.Find(cd_s4) == -1)
			score += 0.5;
		if (cat3.Insert(cd_a3) && cat3.Count() == 1 && cat3.Find(cd_a3) == 0)
			score += 0.5;
	}

	return score;
}

// Join
double Test7()
{
	double score = 0;

	CDCatalogue emptycat;
	CDCatalogue partialcat;
	CDCatalogue fullcat;
	partialcat.Insert(cd_a3);
	partialcat.Insert(cd_b1);
	partialcat.Insert(cd_c1);
	fullcat.Insert(cd_c1);
	fullcat.Insert(cd_d1);
	fullcat.Insert(cd_g1);
	fullcat.Insert(cd_s1);

	// join empty catalogue with partially full
	CDCatalogue join1(emptycat.Join(partialcat));
	if (join1.Count() == 3 && join1.Find(cd_a3) != -1 && join1.Find(cd_b1) != -1 && join1.Find(cd_c1) != -1)
		score += 0.5;

	// join partially full with empty
	CDCatalogue join2(partialcat.Join(emptycat));
	if (join2.Count() == 3 && join2.Find(cd_a3) != -1 && join2.Find(cd_b1) != -1 && join2.Find(cd_c1) != -1)
		score += 0.5;

	// join partially full with full (will produce set of > 4 items)
	CDCatalogue join3(partialcat.Join(fullcat));
	if (join3.Count() == 6)
		score += 0.5;
	if (join3.Find(cd_a3) != -1 && join3.Find(cd_b1) != -1 && join3.Find(cd_c1) != -1 &&
		join3.Find(cd_d1) != -1 && join3.Find(cd_g1) != -1 && join3.Find(cd_s1) != -1 &&
		join3.Find(cd_a1) == -1)
		score += 0.5;

	return score;
}

// Common
double Test8()
{
	double score = 0;

	CDCatalogue emptycat;
	CDCatalogue partialcat;
	CDCatalogue fullcat;
	partialcat.Insert(cd_a3);
	partialcat.Insert(cd_b1);
	partialcat.Insert(cd_c1);
	fullcat.Insert(cd_c1);
	fullcat.Insert(cd_d1);
	fullcat.Insert(cd_g1);
	fullcat.Insert(cd_s1);

	// intersect empty catalogue with partially full
	CDCatalogue common1(emptycat.Common(partialcat));
	if (common1.Count() == 0 && common1.Find(cd_a3) == -1 && common1.Find(cd_b1) == -1 && common1.Find(cd_c1) == -1)
		score += 0.5;

	// intersect partially full with empty
	CDCatalogue common2(partialcat.Common(emptycat));
	if (common2.Count() == 0 && common2.Find(cd_a3) == -1 && common2.Find(cd_b1) == -1 && common2.Find(cd_c1) == -1)
		score += 0.5;

	// intersect partially full with full (will produce set of 1 item)
	CDCatalogue common3(partialcat.Common(fullcat));
	if (common3.Count() == 1)
		score += 0.5;
	if (common3.Find(cd_a3) == -1 && common3.Find(cd_b1) == -1 && common3.Find(cd_c1) == 0 &&
		common3.Find(cd_d1) == -1 && common3.Find(cd_g1) == -1 && common3.Find(cd_s1) == -1 &&
		common3.Find(cd_a1) == -1)
		score += 0.5;

	return score;
}

// Split
double Test9()
{
	double score = 0;

	CDCatalogue emptycat;
	CDCatalogue partialcat;
	CDCatalogue fullcat;
	CDCatalogue subsetcat;
	partialcat.Insert(cd_a3);
	partialcat.Insert(cd_b1);
	partialcat.Insert(cd_c1);
	fullcat.Insert(cd_c1);
	fullcat.Insert(cd_d1);
	fullcat.Insert(cd_g1);
	fullcat.Insert(cd_s1);
	subsetcat.Insert(cd_d1);
	subsetcat.Insert(cd_g1);

	// split partial catalogue from empty catalogue
	CDCatalogue split1(emptycat.Split(partialcat));
	if (split1.Count() == 0 && split1.Find(cd_a3) == -1 &&
		split1.Find(cd_b1) == -1 && split1.Find(cd_c1) == -1)
		score += 0.5;

	// split empty catalogue from partial catalogue
	CDCatalogue split2(partialcat.Split(emptycat));
	if (split2.Count() == 3 && split2.Find(cd_a3) != -1 &&
		split2.Find(cd_b1) != -1 && split2.Find(cd_c1) != -1)
		score += 0.5;

	// split partial catalogue from full catalogue
	CDCatalogue split3(fullcat.Split(partialcat));
	if (split3.Count() == 3 && split3.Find(cd_d1) != -1 &&
		split3.Find(cd_g1) != -1 && split3.Find(cd_s1) != -1 && split3.Find(cd_c1) == -1)
		score += 0.5;

	// split full catalogue from partial catalogue
	CDCatalogue split4(partialcat.Split(fullcat));
	if (split4.Count() == 2 && split4.Find(cd_a3) != -1 &&
		split4.Find(cd_b1) != -1 && split4.Find(cd_c1) == -1)
		score += 0.5;

	// split subset catalogue from full catalogue
	CDCatalogue split5(fullcat.Split(subsetcat));
	if (split5.Count() == 2 && split5.Find(cd_d1) == -1 &&
		split5.Find(cd_g1) == -1 && split5.Find(cd_s1) != -1 && split5.Find(cd_c1) != -1)
		score += 0.5;

	// split full catalogue from subset catalogue
	CDCatalogue split6(subsetcat.Split(fullcat));
	if (split6.Count() == 0 && split6.Find(cd_d1) == -1 && split6.Find(cd_g1) == -1)
		score += 0.5;

	return score;
}
