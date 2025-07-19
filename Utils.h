#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

// Function to convert a string to lowercase
// This function iterates through each character in the string and converts it to lowercase.
string toLowercase(string str);

// Function to calculate the padding needed to center text within a given width
// Returns the number of spaces needed on the left side
int calculateTextPadding(const string& text, int width);

// Helper function to format float with configurable decimal places (default is 2)
string formatFloat(float value, int precision = 2);

#endif
