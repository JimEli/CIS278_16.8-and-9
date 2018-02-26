/*************************************************************************
* Title: Duplicate Elimination
* File: CIS278_Week7_16.8.cpp
* Author: James Eli
* Date: 2/3/2018
*
* Exercise 16.8 on page 755, Duplicate Elimination
* Read 20 integers into an array. Next, use the unique algorithm to reduce 
* the array to the unique values entered by the user. Use the copy 
* algorithm to display the unique values.
*
* Notes:
*  (1) Version uses built-in integer array.
*  (2) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/03/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cout/endl
#include <string>    // getline/string/stoi
#include <regex>     // regular expressions

using namespace std;

// Maximum number of integers in array.
const int MAX_NUMBERS{ 10 };

// Parse input string for integer values and insert them into list.
int parseInts(const string& s, int *list, int index)
{
	regex rexp("[\\-]?(\\d+)"); // Optional negative sign and digits.
	auto numsBegin = sregex_iterator(s.begin(), s.end(), rexp);
	auto numsEnd = sregex_iterator();

	for (sregex_iterator i = numsBegin; i != numsEnd; ++i) {
		smatch match = *i;
		if (index < MAX_NUMBERS) 
			*(list + index++) = stoi(match.str());
	}

	return distance(numsBegin, numsEnd);
}

int main()
{
	// Contains numbers to process.
	int numList[MAX_NUMBERS], count{ 0 };

	cout << "This program finds the unique numbers in a list of " << MAX_NUMBERS << " integers.\n";
	do {
		// Temporarily holds user input.
		string input;

		if (count == 0)
			// Prompt for individual integer.
			cout << "Enter " << MAX_NUMBERS << " integers: ";
		else if (count < MAX_NUMBERS)
			// Prompt for individual integer.
			cout << "Enter integer # " << count + 1 << ": ";

		// Get user input and parse.
		getline(cin, input);
		count += parseInts(input, numList, count);
	} while (count < MAX_NUMBERS);

	// sort array of numbers.
	sort(numList, numList + MAX_NUMBERS);
	// Display the unique array elements.
	cout << "The unique values are: ";
	for (int i = 0; i < MAX_NUMBERS; i++)
		if (numList[i] != numList[i - 1])
			cout << numList[i] << " ";

	cout << endl;
}
