/* CSCI403 Project 5: Programming with SQLite
 * Author: YOUR NAME
 *
 * This program demonstrates the direct interfacing with SQLite via its C api.
 * The program accepts a SQL query from the console and displays its results.
*/

#include <iostream>
#include <string>
#include "sqlite3.h"

static const char* dbPath = "albums.sqlite3.db";

static int displayRow(void* db, int numberOfColumns, char** values, char** columnNames){
	std::cout << "displayRow was called\n";
    for (int i=0; i < numberOfColumns; ++i) {
        std::cout << values[i] << std::endl;
    }
    return 0;
}

int main(int argc, const char* argv[]) {
    std::cout << "Hello. I am SQLiiite.\n";
    std::cout << "> ";

    std::string query;
    getline(std::cin, query);

    std::cout << "Query: " << query << std::endl;

    sqlite3* db;
    char* errorMessage = NULL;
    int rc;

    rc = sqlite3_open(dbPath, &db);
    if (rc) {
        std::cout << "Error: " << sqlite3_errmsg(db);
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, query.c_str(), displayRow, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cout << "Error: " << errorMessage;
        sqlite3_free(errorMessage);
    }
    sqlite3_close(db);
    return 0;
}