#include "Utils.h"
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Convert a string to lowercase
// This function iterates through each character in the string and converts it to lowercase.
string toLowercase(string str) {
    // size_t is an unsigned integer type used for representing the size of objects in memory.
    // It is commonly used for array indexing and loop counters.
    for (size_t i = 0; i < str.length(); i++) {
        // The tolower function is used to convert a character to its lowercase equivalent.
        str[i] = tolower(str[i]);
    }
    return str;
}

// Calculate the padding needed to center text within a given width
// Returns the number of spaces needed on the left side
int calculateTextPadding(const string& text, int width) {
	return (width - text.length()) / 2;
}

// Helper function to format float with configurable decimal places
string formatFloat(float value, int precision) {
	ostringstream oss;
	oss << fixed << setprecision(precision) << value;
	return oss.str();
}
