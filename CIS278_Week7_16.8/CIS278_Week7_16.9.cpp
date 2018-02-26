/*************************************************************************
* Title: Duplicate Elimination
* File: CIS278_Week7_16.9.cpp
* Author: James Eli
* Date: 2/5/2018
*
* Exercise 16.9 on page 755, Duplicate Elimination
* Modify exercise 16.8 to use the unique_copy algorithm. The unique values 
* should be inserted into a vector that's initially empty. Use a back_inserter 
* to enable the vector to grow as new items are added. Use the copy algorithm 
* to display the unique values.

* Notes:
*  (1) Per typical, the majority of the program is involved with input
*      and validation.
*  (2) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/05/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cout/endl
#include <string>    // getline/string/stoi
#include <regex>     // regular expression
#include <array>     // array wrapper
#include <vector>    // vector
#include <algorithm> // sort
#include <iterator>  // back_inserter
#include <cassert>   // assertion

using namespace std;

// Maximum number of integers in array.
const size_t MAX_NUMBERS{ 10 };

// Function prototype.
size_t parseInts(const string&, int[], size_t);

int main()
{
	// Contains numbers to process and count of numbers.
	array<int, MAX_NUMBERS> numList;
	size_t count{ 0 };

	cout << "This program finds the unique numbers in a list of " << MAX_NUMBERS << " integers.\n";
	
	// Loop unital input is complete.
	do {
		// Temporarily holds user input.
		string input;

		// Prompt for integers.
		if (count == 0)
			cout << "Enter " << MAX_NUMBERS << " integers: ";
		else if (count < MAX_NUMBERS)
			// Prompt for individual integer.
			cout << "Enter integer # " << count + 1 << ": ";

		// Get user input and parse.
		getline(cin, input);
		count += parseInts(input, &numList[0], count);

	} while (count < MAX_NUMBERS);

	// Create empty vector to hold unique values (per instructions).
	vector<int> uniqueVec;

	// Sort array and copy unique integers to vector.
	sort(numList.begin(), numList.end());
	unique_copy(numList.cbegin(), numList.cend(), back_inserter(uniqueVec));

	// Display the unique integers.
	cout << "The unique values are: ";
	copy(uniqueVec.cbegin(), uniqueVec.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}

// Parse input string for integer values and insert them into an array.
size_t parseInts(const string& s, int list[], size_t index)
{
	assert(index <= MAX_NUMBERS);

	// Optional negative sign and digits.
	const regex rexp("[\\-]?(\\d+)");
	auto numsBegin = sregex_iterator(s.begin(), s.end(), rexp);
	auto numsEnd = sregex_iterator();

	for (sregex_iterator i = numsBegin; i != numsEnd; ++i) {
		// Do not exceed upper array limit.
		if (index < MAX_NUMBERS)
			list[index++] = stoi(static_cast<smatch>(*i).str());
	}
	// Return number of insertions made.
	return static_cast<size_t>(distance(numsBegin, numsEnd));
}
