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

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(string &myString) {
	//get rid of spaces
	while(myString.size() && isspace(myString.front()))
		myString.erase(myString.begin());
	//if empty say so
	if (myString[0] == '\0')
		return UNINITIALIZED;

	return atoi(myString.c_str());
}

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
	int lineCounter = 0;

	while (!myfile.eof()) {
		getline(myfile, line); //get a line from the file
		ss.str(line);
		lineCounter++;

		//get rid of the old values
		myBooks = book();

		//get the name
		getline(ss, myBooks.title, CHAR_TO_SEARCH_FOR);

		//get the author
		getline(ss, myBooks.author, CHAR_TO_SEARCH_FOR);

		//finally add to array
		books.push_back(myBooks);
		if(books.empty()){
			return NO_BOOKS_IN_LIBRARY;
		}

		//clear stream so it will work for next read
		ss.clear();
	}
	if (lineCounter<= 1){
		return NO_BOOKS_IN_LIBRARY;
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
	ifstream myfile;
	myfile.open(filename);
	if (!myfile.is_open())
		return COULD_NOT_OPEN_FILE;
	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	string mydata;
		for (int var = 0; var < books.size(); ++var) {
			mydata = to_string(books[var].book_id) + "," +
					books[var].title + "," + books[var].author +
					to_string(books[var].loaned_to_patron_id);
			myfile<<mydata<<std::endl;
		}

		if (myfile.is_open())
			myfile.close();

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	ifstream myfile;
	myfile.open(filename);
	if (!myfile.is_open())
		return COULD_NOT_OPEN_FILE;

	std::string line;
	std::string numberStr;
	std::string patronStr;
	patron patronIn;
	stringstream ss;
	char CHAR_TO_SEARCH_FOR = ',';
	int lineCounter = 0;

	while (!myfile.eof()) {
		getline(myfile, line); //get a line from the file
		ss.str(line);
		lineCounter++;

		//get rid of the old values
		patronIn = patron();

		//get the name
		getline(ss, patronStr, CHAR_TO_SEARCH_FOR);
		patronIn.patron_id = stringToInt(patronStr);

		//get the author
		getline(ss, numberStr, CHAR_TO_SEARCH_FOR);
		patronIn.number_books_checked_out = stringToInt(numberStr);

		//finally add to array
		patrons.push_back(patronIn);
		if(patrons.empty()){
			return NO_BOOKS_IN_LIBRARY;
		}

		//clear stream so it will work for next read
		ss.clear();
	}
	if (lineCounter<= 1){
		return NO_PATRONS_IN_LIBRARY;
	}
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
