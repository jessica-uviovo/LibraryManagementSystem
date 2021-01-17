/*
 Librarian.h File Work Breakdown:
	-Amanda: Made the class.
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
using namespace std;

class Librarian : public User
{
private:
	string libUsername;
	string libPassword;
public:
	Librarian();
	Librarian(string userlib, string passlib);
	
	//GET FUNCTIONS//
	string getLibUse();
	string getLibPass();

	//SET FUNCTIONS//
	void setLibUse(string teachUser);
	void setLibPass(string teachPass);
	
	//READ FUNCTIONS//
	void readLibBookList();
	void readLibBorrowedBook();
	void readLibReservedBook();
	void readLibReserveeOrder();
	void readUser();

	//PRINT FUNCTIONS//
	void printLibReserveeOrder();
	void printLibReservedBook();
	void printLibBorrowedBook();
	void printBookList();
	void printUser();

	//MAIN FUNCTIONS//
	void addBooks(string ISBN, string title, string authorName, string category);
	void deleteBooks(string ID);
	bool searchUsers(string username);
	void addUser(string username, string password, string who);
	void deleteUser(string username);
	int searchBookID(string ID);
};
