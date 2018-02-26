/*************************************************************************
* Title: Duplicate Elimination
* File: CIS278_Week7_16.8.cpp
* Author: James Eli
* Date: 2/5/2018
*
* Exercise 16.8 on page 755, Duplicate Elimination
* Read 20 integers into an array. Next, use the unique algorithm to reduce 
* the array to the unique values entered by the user. Use the copy 
* algorithm to display the unique values.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
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
#include <algorithm> // sort
#include <cassert>   // assert

using namespace std;

// Maximum number of integers in array.
const size_t MAX_NUMBERS{ 10 };

// Function prototype.
size_t parseInts(const string&, int[], size_t);

int main()
{
	// Array will contain numbers to process.
	array<int, MAX_NUMBERS> numList;
	// A count of items in array.
	size_t count{ 0 };

	cout << "This program finds the unique numbers in a list of " << MAX_NUMBERS << " integers.\n";
	
	// Loop until input is complete.
	do {
		// Temporarily holds user input.
		string input;

		// Prompt for integers.
		if (count == 0)
			cout << "Enter " << MAX_NUMBERS << " integers: ";
		else if (count < MAX_NUMBERS)
			// Prompt for an individual integer.
			cout << "Enter integer # " << count + 1 << ": ";

		// Get user input and parse it.
		getline(cin, input);
		count += parseInts(input, &numList[0], count);

	} while (count < MAX_NUMBERS);

	// Sort array of numbers.
	sort(numList.begin(), numList.end());

	// Display the unique integers.
	cout << "The unique values are: ";
	copy(numList.begin(), unique(numList.begin(), numList.end()), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}

// Parse string for integer values and insert them into an array.
size_t parseInts(const string& s, int list[], size_t index)
{
	assert(index < MAX_NUMBERS);

	// Optional negative sign and digits.
	const regex rexp("[\\-]?(\\d+)");
	auto numsBegin = sregex_iterator(s.begin(), s.end(), rexp);
	auto numsEnd = sregex_iterator();

	for (sregex_iterator i = numsBegin; i != numsEnd; ++i) {
		smatch match = *i;
		// Do not exceed array upper limit.
		if (index < MAX_NUMBERS)
			list[index++] = stoi(match.str());
	}

	// Return count of insertions.
	return static_cast<size_t>(distance(numsBegin, numsEnd));
}
