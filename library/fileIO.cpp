#include "../includes_usr/fileIO.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/constants.h"

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>


using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	ifstream myfile;
	myfile.open(filename);
	if (!myfile.is_open())
		return COULD_NOT_OPEN_FILE;

	std::string line;
	book myBooks;
	stringstream ss;
	char CHAR_TO_SEARCH_FOR = ',';

	while (!myfile.eof()) {
		getline(myfile, line); //get a line from the file
		ss.str(line);

		//get rid of the old values
		myBooks = book();

		//get the name
		getline(ss, myBooks.title, CHAR_TO_SEARCH_FOR);

		//get the author
		getline(ss, myBooks.author, CHAR_TO_SEARCH_FOR);

		//finally add to array
		books.push_back(myBooks);

		//clear stream so it will work for next read
		ss.clear();
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	return SUCCESS;
}
