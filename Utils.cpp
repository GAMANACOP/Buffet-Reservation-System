#include "Utils.h"
#include <string>

using namespace std;

string toLowercase(string str) {
	for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}
