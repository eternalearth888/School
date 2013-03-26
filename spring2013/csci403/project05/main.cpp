/* Maria Deslis
* csci403 - Bakos
* project 05
*
* A trivial clone of the sqlite3 console program
* Allows the user to enter a simple SELECT statement and
* display the results of the query in a rough tabular format.
*
*/

#include <iostream>
#include <string>
#include <iomanip>
#include "sqlite3.h"

/**The following is based off of the given code in project05.pdf**/

static const char* dbPath = "albums.sqlite3.db";

static int tryToDisplayData(void* db, int numCol, char** values, char** colName) {

	for (int i = 0; i < numCol; i++) {
		std::cout << values[i] << std::endl;
	}

	return 0;
}

int main(int argc, char **argv) {

	char **result;
	int nrows = 0;
	int ncols = 0;

	sqlite3* db;
	char* errMessage = NULL;
	int responseCode;

	responseCode = sqlite3_open(dbPath, &db);

	if (responseCode) {
		std::cout << "\n"  << "Error: " << sqlite3_errmsg(db);
		sqlite3_close(db);
		return 1;
	}

	std::cout << "Welcome to SQLite.\n";
	std::cout << "> ";

	std::string query;
	getline(std::cin, query);

	/** Using sqlite3_get_table instead of exec **/
	responseCode = sqlite3_get_table(db, query.c_str(), &result, &nrows, &ncols, &errMessage);

	/** Print out ALL THE THINGS **/
	for (int i = 0; i < nrows; i++) {

		/*
		 *	If we are on the first row, print a separator
		 *	The seperators length is equla to the number of columns*6
		*/
		if (i == 1) {

			for (int sep = 0; sep < ncols*6; sep++) {
				std::cout << "-";
			}

			std::cout << std::endl;
		}

		for (int  j = 0; j < ncols; j++) {

			/*
			 *	Center the data
			 *	Print the data
			 *	Have a set width for all data
			*/
			std::cout << std::internal << std::setw(2) << result[(i)*ncols + j];

			/*
			 *	While we have not reached the last column
			 *	Print a pipe seperator between the two columns
			*/
			if (j < ncols-1) {
				std::cout << " | ";
			} 
		}

		std::cout << std::endl;
	}

	
	if (responseCode != SQLITE_OK) {
		std::cout << "\n " << "Error: " << errMessage;
		sqlite3_close(db);
		return 1;
	}

	/** Free memory **/
	sqlite3_free_table(result);

	/** Close the Table **/
	sqlite3_close(db);

	return 0;
}
