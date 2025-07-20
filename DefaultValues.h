#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H

#include <string>

using namespace std;

// Default values for group member types and their respective discounts
float const DEFAULT_FEE = 200;
float const DEFAULT_CHILD_DISCOUNT = 0.05;
float const DEFAULT_ADULT_DISCOUNT = 0.0;
float const DEFAULT_SENIOR_DISCOUNT = 0.2;

// Default file names for tables and queue
string const DEFAULT_TABLES_FILENAME = "BRSTables.txt";
string const DEFAULT_QUEUE_FILENAME = "BRSQueue.txt";

// Default number of tables in the buffet reservation system
// This can be changed to any number of tables as needed
// However, in Dev C++, you must rebuild your program by selecting Execute > Clean/Rebuild All
int const DEFAULT_NUMBER_OF_TABLES = 10;

// Default column widths for displaying information
const int MEMBER_TYPE_COL = 22; // Width for "Member Type" column
const int COUNT_COL       = 10; // Width for "Count" column
const int DISCOUNT_COL    = 15; // Width for "Total Fee" column
const int TOTAL_FEE_COL   = 15; // Width for "Total Fee" column
const int COLUMN_WIDTH = 100;

#endif
