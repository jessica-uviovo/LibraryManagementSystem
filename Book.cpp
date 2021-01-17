/*
 Book.cpp File Work Breakdown:
    -Jessica: Made the class.
    -Amanda, Jessica, and Ramisa = worked together on borrow, return, reserve, etc
*/
#include "Book.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <stack>
#include <sstream>
using namespace std;

//BOOK.TXT
string bookList[100][6];
int bookRow = 0, bookCol = 6;

string Book1[100];
string Book2[100];

//BORROWED BOOKS TXT
int BorrowBooks[100][10], borRow = 100, borCol = 10;

//RESERVED BOOKS TXT
int reserveBooks[100][5], resRow = 100, resCol = 5;

//RESERVEE ORDER TXT
int resOrder[100][50], resOrderCol = 50;

//USER.TXT ARRAY
string userArray[100][4];
int userRow = 0, userCol = 4;

//Clocks
clock_t counterR[1000];
double timeReserved;

clock_t Date[100];

//DATE - Max Borrowing Period for a Book
int expDate[100];

int IDnum[100], IDnum_Row; //error here - >will not read more than 20 books id numbers


//CONSTRUCTORS//
Book::Book()
{
    title = "";
    author = "";
    string category = "";
    id = 0;
    isbn = 0;
    readers_name = "";
    brwDate = 0;
    MAXbrw = 0;
}//default

Book::Book(string bktitle, string auth, string categor, int identitynum, int code, clock_t brw_BK_Day, int MaxBrw) {
    title = bktitle;
    author = auth;
    category = categor;
    id = identitynum;
    isbn = code;
    brwDate = brw_BK_Day;
    MAXbrw = MaxBrw;
}//Book constructor

//GET FUNCTIONS
string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

string Book::getCategory() {
    return category;
}

int Book::getID() {
    return id;
}

int Book::getISBN() {
    return isbn;
}

string Book::getUserName() {
    return readers_name;
}

int Book::getRowNumber(Reader& reader)
{
    //this gets the row number of the user on user.txt
    readUsertxt();
    int s_Row = 0;
    for (int i = 0; i < userRow; i++)
    {
        if (userArray[i][0] == reader.getusername())
        {
            s_Row = i;
        }
    }
    return s_Row;
}

clock_t Book::getbrwDate() {
    return brwDate;
}

int Book::getMAXbrw() {
    return MAXbrw;
}


//SET FUCNTIONS//
void Book::setTitle(string title_name) {
    title = title_name;
}

void Book::setAuthor(string author_name) {
    author = author_name;
}

void Book::setCategory(string cat) {
    category = cat;
}

void Book::setUserName(string human) {
    readers_name = human;
}

void Book::setID(int IDnum) {
    id = IDnum;
}

void Book::setISBN(int code) {
    isbn = code;
}

void Book::setbrwDate(int bookID) {
    brwDate = Date[bookID];
}

void Book::setMAXbrw(int nMAXbrw) {
    MAXbrw = nMAXbrw;
}

void Book::setBook(int ID) {
    for (int i = 0; i < bookRow; i++)
    {
        if (IDnum[i] == ID)
        {
            setTitle(bookList[i][1]);
            setAuthor(bookList[i][2]);
        }
    }
}


//CLOCK FUNCTIONS
void Book::storeBrwDate(clock_t brrwDate, int bookID) {
    Date[bookID] = brrwDate;
}


//EXPERATION FUNCTIONS
void Book::storeExpDate(int MAXbrw, int bookID) { //stores the max borrowing period for each book
    expDate[bookID] = MAXbrw;
}

int Book::getExpDate(int bookID) {
    return expDate[bookID];
}

int Book::findMAXbrw(Reader& reader, int bookID) {
    //get the row of the book
    int rowBook;
    for (int i = 0; i < bookRow; i++) {
        if (bookList[i][0] == to_string(bookID)) {//look for ID of book to get row book is located at 
            rowBook = i;
        }
    }

    if (reader.getType() == "3") //student
       setMAXbrw(30);
    else if (reader.getType() == "2") //teacher
       setMAXbrw(50);

    int ResNum = stoi(bookList[rowBook][5]) / 20; //amount of times we went over 20 on ppl who reserved a book
    int Maxget = getMAXbrw();
    Maxget = Maxget - ResNum;
    setMAXbrw(Maxget);

    return getMAXbrw();
}


//READER FUNCTIONS BELOW
//reads book.txt file 
void Book::readBookList() {
    Book book;
    ifstream input("book.txt");
    if (input.fail()) {
        cerr << "ERROR: book.txt could not be opened." << endl;
        exit(1);
    }

    bookRow = 0;

    while (!input.eof()) {
        for (int j = 0; j < bookCol; j++) {
            input >> bookList[bookRow][j];
                
        }
        bookRow++;
    }
    bookRow--;

    //bookList = string array that contains book.txt
    //IDnum = int array that contains only the ID numbers
    for (int i = 0; i < bookRow; i++) { //i = total number of rows

        stringstream var(bookList[i][0]);
        int t;
        var >> t;
        IDnum[i] = t; 
    }
    input.seekg(0, ios::beg);
    input.close();
}

//reads borrowedbook.txt
void Book::readBorrowedBook() {
    int i, j;
    ifstream brw_Bks_File("borrowedbooks.txt");
    if (brw_Bks_File.fail())
    {
        cerr << "ERROR: borrowedbooks.txt could not be opened." << endl;
        exit(1);
    }
    //reads the file and stores into array
    while (!brw_Bks_File.eof())
    {
        for (i = 0; i < borRow; i++)
            for (j = 0; j < borCol; j++)
            {
                brw_Bks_File >> BorrowBooks[i][j];
            }
    }
    brw_Bks_File.seekg(0, ios::beg);
    brw_Bks_File.close();
}

void Book::readReservedBook()
{
    ifstream reservedFile("reservedbooks.txt");
    if (reservedFile.fail())
    {
        cerr << "ERROR: reservedbooks.txt could not be opened." << endl;
        exit(1);
    }
    //reads the file and stores into array
    while (!reservedFile.eof())
    {
        for (int i = 0; i < resRow; i++)
            for (int j = 0; j < resCol; j++)
            {
                reservedFile >> reserveBooks[i][j];
            }
    }
    reservedFile.seekg(0, ios::beg);
    reservedFile.close();
}

void Book::readReserveeOrder()
{
    ifstream inFile("reserveeOrder.txt");
    if (inFile.fail())
    {
        cerr << "ERROR: reserveeOrder.txt could not be opened." << endl;
        exit(1);
    }
    //reads the file and stores into array
    while (!inFile.eof())
    {
        for (int i = 0; i < bookRow; i++)
            for (int j = 0; j < resOrderCol; j++)
            {
                inFile >> resOrder[i][j];
            }
    }

    inFile.seekg(0, ios::beg);
    inFile.close();
}

void Book::readUsertxt() {
    ifstream input("User.txt");
    if (input.fail()) {
        cerr << "ERROR: User.txt could not be opened." << endl;
        exit(1);
    }
    userRow = 0;
    while (!input.eof()) {//reads default txt file
        for (int j = 0; j < userCol; j++) {
            input >> userArray[userRow][j];
        }
       
        userRow++;
    }
    input.seekg(0, ios::beg);
    input.close();
}


//CHECKER FUNCTIONS
//checks if the book is borrowed
bool Book::isBookBorrowed(int bookID) {
    for (int i = 0; i < borRow; i++)
        for (int j = 0; j < borCol; j++)
        {
            if (bookID == BorrowBooks[i][j])
                return false;
        }
    return true;
}

//checks if the book is reserved
bool Book::isBookReserved(int bookID) {
 
    readReservedBook();
    for (int i = 0; i < resRow; i++)
        for (int j = 0; j < resCol; j++)
        {
            if (bookID == reserveBooks[i][j])
                return false;
        }
    return true;
}


//PRINTER FUNCTIONS
//prints to borrowedbooks.txt
void Book::printBorrowedBook()
{
    ofstream brw_Bks_File("borrowedbooks.txt");
    if (brw_Bks_File.fail())
    {
        cerr << "Error: borrowedbooks.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < borRow; i++)
    {
        for (int j = 0; j < borCol; j++)
        {
            brw_Bks_File << BorrowBooks[i][j] << " ";
        }
        brw_Bks_File << endl;
    }
    brw_Bks_File.seekp(0, ios::beg);
    brw_Bks_File.close();
}

//prints to reservedbooks.txt
void Book::printReservedBook()
{
    ofstream reservedBooksFile("reservedbooks.txt");
    if (reservedBooksFile.fail())
    {
        cerr << "Error: reservedbooks.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < resRow; i++)
    {
        for (int j = 0; j < resCol; j++)
        {
            reservedBooksFile << reserveBooks[i][j] << " ";
        }
        reservedBooksFile << endl;
    }

    reservedBooksFile.seekp(0, ios::beg);
    reservedBooksFile.close();
}

//prints to reserveeOrder.txt
void Book::printReserveeOrder()
{
    ofstream outFile("reserveeOrder.txt");
    if (outFile.fail())
    {
        cerr << "Error: reserveeOrder.txt could not be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < bookRow; i++)
    {
        for (int j = 0; j < resOrderCol; j++)
        {
            outFile << resOrder[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.seekp(0, ios::beg);
    outFile.close();
}

//prints to user.txt
void Book::printUsertxt()
{
    ofstream input("User.txt");
    if (input.fail())
    {
        cerr << "Error: User.txt could not be opened to print." << endl;
        exit(1);
    }

    for (int i = 0; i < userRow; i++) {
        for (int j = 0; j < userCol; j++)
        {
            input << userArray[i][j] << " ";
        }
        input << endl;
    }//
    input.seekp(0, ios::beg);
    input.close();
}


//Verify Book ID
bool Book::verifyID(int bookID)
{
    bool valid = false;
    for (int i = 0; i < bookRow; i++)
    {
        if (bookID == IDnum[i])
        {
            valid = true;
            return true;
        }
    }
    if (!valid)
    {
        cout << "\nERROR: There is no book corresponding to this ID " << bookID << endl;
        return false;
    }
    return false;
}

//checks if the book is overdue
bool Book::checkOverdue(Reader& reader, Book book) {
    // checks if book is overdue
    int timeR = book.getRowNumber(reader);
    for (int j = 0; j < borCol; j++)
    {
        if (BorrowBooks[timeR][j] != 0) {
            clock_t t_new = 0;

            double check_time = 0;

            t_new = clock() - Date[BorrowBooks[timeR][j]];

            check_time = (((double)t_new) / CLOCKS_PER_SEC) / 5;

            if (check_time >= expDate[BorrowBooks[timeR][j]]) {
                cout << "ERROR: You have an overdue book!" << endl;
                return true;
            }
        }
    }
    return false;
}

//borrow books function
bool Book::borrowbooks(int bookID, Reader& reader)
{
    Book book;
    book.setID(bookID);
    readBookList();
    readBorrowedBook();
    book.setBook(bookID);

    //Checks to see if entered ID is valid
    if (!verifyID(bookID))
        return false;

    if (!isBookBorrowed(bookID)) { //check if book is already borrowed
            // checks if book is borrwed by user
        if (UserBorrowed(bookID, reader)) {
            cout << "You have already borrowed this book. To borrow again, please go to renew." << endl;
            return false;
        }
        else { // else book is borrowd by someone else
            cout << "\nERROR: Book with ID Number " << bookID << " has already been borrowed by someone! Borrow something else." << endl;
            return false;
        }
    }

    bool flag = false; 
    bool flag2 = false;
    if (!isBookReserved(bookID)) { //check if book is already reserved
            // checks if book is borrwed by user
        if (UserReserved(bookID, reader)) {
            // checks if user is first person in orderReserved.txt
            readReserveeOrder();
            int row = getRowNumber(reader) + 1;
            for (int i = 0; i < bookRow; i++) {
                if (bookID == resOrder[i][0]) {
                    IDnum_Row = i;
                    // they are the first reservee
                    if (row == resOrder[i][1]) {
                        counterR[bookID] = clock() - counterR[bookID];
                        timeReserved = (((double)counterR[bookID]) / CLOCKS_PER_SEC) / 5; // calculate the elapsed time
                        cout << timeReserved << endl;
                        
                        if (timeReserved > 5) {
                            cout << "This book is cannot be borrowed. You have passed " << timeReserved << " days." << endl;
                            cancelReservation(bookID, reader);
                            flag = false;
                            // flag2 goes to cancel reservation
                            flag2 = true;
                        }
                        if (timeReserved <= 5){
                            flag = true;
                            flag2 = true;
                            cout << "You are able to borrow the book." << endl;
                        }
                    }
                    else { // not the first reservee
                        cout << "You are not the first reservee on the list." << endl;
                        return false;
                    }

                }

            }
        }
        else {
            cout << "Book is reserved by someone." << endl;
            return false;
        }
    }
    else
        flag = true;
    
    if (flag) {
        if (reader.getCopies() >= reader.getmaxCpy()) {
            if (reader.getmaxCpy() == 0) {
                cout << "\nYou have too many penalites on your account. You can not borrow any more books" << endl;
                exit(1);
            }
            cout << "\nERROR: You have already borrowed " << reader.getmaxCpy() << " books! Please return books to borrow another." << endl;
            return false;
        }    
        
         //Find Maximun Borrowing Period
         book.setMAXbrw(findMAXbrw(reader, bookID));

         //Check for overdue book
         if (checkOverdue(reader, book))
                return false;
            
         //Checks max borrow period -> indicates how many reservations
         if (book.getMAXbrw() == 0) {
             cout << "ERROR: Too many reservations! Cannot the borrow book." << endl;
             return false;
         }
         else
             cout << "You have " << book.getMAXbrw() << " days to borrow this book" << endl;

         //Store Max borrowing period for book
         storeExpDate(book.getMAXbrw(), bookID);

         int row = getRowNumber(reader);
         for (int j = 0; j < borCol; j++)
         {
             if (BorrowBooks[row][j] == 0)
             {
                 BorrowBooks[row][j] = bookID;
                 break;
             }
         }

         printBorrowedBook();

         book.readers_name = reader.getusername();

         int copies = reader.getCopies();
         copies++;
         reader.setCopies(copies);

         cout << "\nYou have borrowed " << book.getTitle() << " by " << book.getAuthor() << endl;
         if (flag2)
             cancelReservation(bookID, reader);
         return true;
    }
    return false;
}

//checks if the user borrowed the book
bool Book::UserBorrowed(int bookID, Reader& reader) {
    int row = getRowNumber(reader);

    readBorrowedBook();
    for (int i = 0; i < borCol; i++) {
        if (bookID == BorrowBooks[row][i]) {//if ID is equal to the txt row of student currently logged in
            return true;
        }
    }
    return false;
}

//checks if the user reserved the book
bool Book::UserReserved(int bookID, Reader& reader) {
    int row = getRowNumber(reader);
    
    readReservedBook();
    for (int i = 0; i < resCol; i++) {
        if (bookID == reserveBooks[row][i]) {
            return true;
        }
    }

    return false;
}

//return books 
bool Book::returnbooks(int bookID, Reader& reader)
{
    Book book;
    book.setID(bookID);
    readBorrowedBook();
    int k = getRowNumber(reader), checkflag = 0;
    //verfies valid ID
    if (!verifyID(bookID))
        return false;
    //updates borrowbooks.txt to 0
    for (int j = 0; j < borCol; j++)
    {
        if (bookID == BorrowBooks[k][j])
        {
            BorrowBooks[k][j] = 0;
            checkflag = 1;
        }
    }
    //if reservations then starts timer for next reservee
    if (checkflag)
    {
        printBorrowedBook();
        
        if (!isBookReserved(bookID)) {
            counterR[bookID] = clock();
            cout << "Timer Has Started for next reservee.\n";
        }

    }
    else { 
        cout << "\nYou have not borrowed that book" << endl;
        return false;
    }

    int copies = reader.getCopies();
    copies--;
    reader.setCopies(copies);
    return true;
}

//prints to book.txt
void Book::printBookList()
{
    ofstream Bks_File("book.txt");
    if (Bks_File.fail())
    {
        cerr << "Error: books.txt could not be opened to print." << endl;
        exit(1);
    }
    
    for (int i = 0; i < bookRow; i++) {
        for (int j = 0; j < bookCol; j++)
        {
            Bks_File << bookList[i][j] << " ";
        }
        Bks_File << endl;
    }//
    Bks_File.close();
}

//reserve books
bool Book::reservebooks(int bookID, Reader& reader)
{
    Book book;
    //check if there's a copy of the book
    readBookList();

    //Checks to see if entered ID is valid
    if (!verifyID(bookID))
        return false;
    //checks to see if user borrowed the book
    if (UserBorrowed(bookID, reader)) {
        cout << "ERROR: Book is borrowed by you. You can't reserve a book that you have borrowed." << endl;
        return false;
    }
    //checks if the book is reserved by user
    if (UserReserved(bookID, reader)) {
        cout << "ERROR: Book is reserved by you. You can't reserve a book that you have already reserved." << endl;
        return false;
    }
    
    if (isBookReserved(bookID)) {
        if (isBookBorrowed(bookID))//if book borrowed
        {
            cout << "This book is avaiable to be borrow with ID " << bookID << endl;
            return false;
        }//tells you it is available 
    }
   
    //get title from ID
    string id = to_string(bookID);
    string title;
    for (int i = 0; i < bookRow; i++)
    {
        if (id == bookList[i][0])
        {
            title = bookList[i][1];
        }
    }//title

    //check if another book has the same title and is free
    for (int i = 0; i < bookRow; i++)
    {
        if (bookID == IDnum[i]) {
            continue;
        }

        if (bookList[i][1] == title)
        {
            if (isBookBorrowed(IDnum[i]))//if book not borrowed
            {
                cout << "There is another copy available with ID " << IDnum[i] << " to be borrowed." << endl;
                return false;
            }//tells you it is available
        }
    }

        //Find Maximun Borrowing Period
        book.setMAXbrw(findMAXbrw(reader, bookID));

        //Check for overdue book
        if (checkOverdue(reader, book))
            return false;

        readReservedBook();
        readReserveeOrder();
        //add the book to their reserved book list
        int row = getRowNumber(reader);
        for (int j = 0; j < resCol; j++)
        {
            if (reserveBooks[row][j] == 0)
            {
                reserveBooks[row][j] = bookID;
                break;
            }
        }
        //add user Row number to order Reserved txt
        for (int i = 0; i < bookRow; i++) {
            for (int j = 0; j < resOrderCol; j++)
            {
                if (bookID == resOrder[i][0]) {
                    IDnum_Row = i;
                    if (resOrder[IDnum_Row][j] == 0)
                    {
                        resOrder[IDnum_Row][j] = row + 1;
                        break;
                    }
                }
            }
        }
        printReserveeOrder();

        for (int i = 0; i < bookRow; i++) {
            if (id == bookList[i][0]) {

                int amountRes = stoi(bookList[i][5]);//increments count for amount of ppl who reserved each book
                amountRes++;
                bookList[i][5] = to_string(amountRes);
            }
        }

        printReservedBook();
        printBookList();
        cout << "\nYou have now reserved Book with ID " << bookID << endl;
        return true;
}

//renew books
bool Book::renewbooks(int ID, Reader& reader) {
    //read booklist
    Book book;
    readBookList();
    book.setBook(ID);

    // checks if book is not borrwed by the person
    if (!UserBorrowed(ID, reader)) {
        cout << "ERROR: You have not borrowed this book so you can't renew it." << endl;
        return false;
    }

    // checks if book is reserved
    if (!isBookReserved(ID)) {
        cout << "ERROR: This book is reserved." << endl;
        return false;
    }

    //Find Maximun Borrowing Period
    book.setMAXbrw(findMAXbrw(reader, ID));

    //Check for overdue book
    if (checkOverdue(reader, book))
        return false;
    else {
        cout << "\nYou have renewed " << book.getTitle() << " by " << book.getAuthor() << endl;
        //Store Max borrowing period for book
        storeExpDate(book.getMAXbrw(), ID);
        return true;
    }
        
    return false;
}

//cancel reservation
bool Book::cancelReservation(int bookID, Reader& reader)
{
    Book book;
    book.setID(bookID);
    readBookList();
    book.setBook(bookID);
    readReservedBook();
    readReserveeOrder();

    int k = getRowNumber(reader), checkflag = 0;
    int row = getRowNumber(reader);

    //Checks to see if entered ID is valid
    if (!verifyID(bookID))
        return false;
    
    //updates reservedbook.txt
    if (!isBookReserved(bookID))
    {
        for (int j = 0; j < resCol; j++)
        {
            if (bookID == reserveBooks[k][j])
            {
                reserveBooks[k][j] = 0;
            }
        }

        //decreaes the population number
        for (int i = 0; i < bookRow; i++) {
            if (bookList[i][0] == to_string(bookID)) {
                int temp = stoi(bookList[i][5]); 
                temp = temp - 1; 
                if (temp <= 0) {
                    temp = 0;
                }
                bookList[i][5] = to_string(temp);
            }
        }

        //updates reservee order
        for (int i = 0; i < bookRow; i++) {
            for (int j = 1; j < resOrderCol; j++)
            {
                if (bookID == resOrder[i][0]) {
                    IDnum_Row = i;
                    if (resOrder[IDnum_Row][j] == row + 1)
                    {
                        resOrder[IDnum_Row][j] = 0;
                        // shifting
                        for (int i = j; i < resOrderCol; i++) {
                            if (i + 1 == resOrderCol) {
                                break;
                            }
                            resOrder[IDnum_Row][i] = resOrder[IDnum_Row][i + 1];
                        }
                        resOrder[IDnum_Row][resOrderCol - 1] = 0;
                        break;
                    }
                }
            }
        }
        checkflag = 1;
    }

    if (checkflag==1)
    {
        printBookList();
        printReservedBook();
        printReserveeOrder();
        cout << "\nYou have canceled your reservation for " << book.getTitle() << " by " << book.getAuthor() << endl;
    }
    else {
        cout << "\nERROR: You have not reserved this book" << endl;
        return false;
    }
    return true;
}

//Increments the penelties in user.txt
int Book::addPenalties(Reader& reader) {
    readUsertxt();
    
    int pen = 0;
    int row = getRowNumber(reader);
    for (int i = 0; i < userRow; i++) {
        if (row == i) {
            stringstream test(userArray[row][3]);
            test >> pen;
            pen = stoi(userArray[i][3]);
            pen++;
            userArray[i][3] = to_string(pen);
        }
    }
    return pen;
    printUsertxt(); 
}

//sorting the search by popularity
void Book::sortSearch(int k) {
    //sort 2nd array, however you move, do the same movement to the 1st array
    string temp, temp2;
    for (int i = 0; i < k - 1; i++)
        for (int j = i + 1; j < k; j++)
        {
            if (stoi(Book2[j]) > stoi(Book2[i]))
            {
                temp = Book2[i];
                Book2[i] = Book2[j];
                Book2[j] = temp;

                temp2 = Book1[i];
                Book1[i] = Book1[j];
                Book1[j] = temp2;
            }

        }

    //print info on book based on ID's
    cout << "\nBook found!" << endl;

    string isbn, author, title, popularity;

    for (int j = 0; j < k; j++)
        for (int i = 0; i < bookRow; i++)
        {

            if (Book1[j] == bookList[i][0])
            {

                isbn = bookList[i][4];
                author = bookList[i][2];
                title = bookList[i][1];
                popularity = bookList[i][5];

                cout << Book1[j] << " " << title << " " << author << " " << category << " " << isbn << " " << popularity << endl;
            }
        }
}


//SEARCH FUNCTIONS//
bool Book::searchISBN(string ISBN)
{
    readBookList();
    
    string min = "0";

    string isbn;

    isbn = ISBN;

    int k = 0;
    bool flag = false; 
    for (int i = 0; i < bookRow; i++)
    {
        if (isbn == bookList[i][4])
        {
            //push ID's to 1st array
            Book1[k] = bookList[i][0];

            //push popularity no. in 2nd array
            Book2[k] = bookList[i][5];
            k++;

            flag = true;
        }
    }

    if (!flag)
    {
        cout << "There is no book with ISBN " << isbn << endl;
        return false;
    }

    sortSearch(k);
    return true;
}

bool Book::searchTitle(string title)
{

    readBookList();

    int k = 0;
    bool flag = false;
    for (int i = 0; i < bookRow; i++)
    {
        if (title.compare(bookList[i][1]) == 0)
        {
            //push ID's to 1st array
            Book1[k] = bookList[i][0];

            //push popularity no. in 2nd array
            Book2[k] = bookList[i][5];
            k++;

            flag = true;
        }
    }

    if (!flag)
    {
        cout << "There is no book with Title: " << title << endl;
        return false;
    }

    sortSearch(k);
    return true;
}

bool Book::searchAuthor(string author)
{
    readBookList();

    int k = 0;
    bool flag = false; 
    for (int i = 0; i < bookRow; i++)
    {
        if (author.compare(bookList[i][2]) == 0)
        {
            //push ID's to 1st array
            Book1[k] = bookList[i][0];

            //push popularity no. in 2nd array
            Book2[k] = bookList[i][5];
            k++;

            flag = true;
        }
    }

    if (!flag)
    {
        cout << "There is no book with Author: " << author << endl;
        return false;
    }

    sortSearch(k);
    return true;
}

bool Book::searchCategory(string category)
{
    readBookList();

    int k = 0;
    bool flag = false;
    for (int i = 0; i < bookRow; i++)
    {
        if (category.compare(bookList[i][3]) == 0)
        {
            //push ID's to 1st array
            Book1[k] = bookList[i][0];

            //push popularity no. in 2nd array
            Book2[k] = bookList[i][5];
            k++;

            flag = true;
        }
    }

    if (!flag)
    {
        cout << "There is no book with Category: " << category << endl;
        return false;
    }

    sortSearch(k);
    return true;
}

void Book::searchID(string ID) {
    readBookList();

    int k = 0;
    bool flag = false;
    string isbn, author, title, popularity;

    for (int i = 0; i < bookRow; i++)
    {
        if (ID.compare(bookList[i][0]) == 0)
        {
            //cout << "Book has been found!" << endl;
            flag = true;

            isbn = bookList[i][4];
            author = bookList[i][2];
            title = bookList[i][1];
            popularity = bookList[i][5];
            cout << ID << " " << title << " " << author << " " << category << " " << isbn << " " << popularity << endl;
            //return i; // if book was found
        }
    }
}


//MY INFORMATION FUNCTIONS//
void Book::myInfoReader(Reader& reader) {
    readBorrowedBook();
    readReservedBook();


    int r, arr[10];
    r = getRowNumber(reader); //gets row numbeer of reader

    bool flag = true, flag1 = true;

    //finds all borrowed books
    for (int i = 0; i < 10; i++) {//goes thru each column

        if (BorrowBooks[r][i] != 0) {//if there is no zero in current column
            arr[i] = BorrowBooks[r][i];
        }
        else if(BorrowBooks[r][i] == 0) { // if zero in current column
            if (i != 0) { // checks if at least 1 book has been borrowed
                break;
            }
            else if (i == 0){// if it is first column
                flag = false;
            }
        }
        
    }

    int arr1[10];

    //finds all reserved books
    for (int i = 0; i < 10; i++) {//goes thru each column

        if (reserveBooks[r][i] != 0) {//if there is no zero in current column
            arr1[i] = reserveBooks[r][i];
        }
        else if (reserveBooks[r][i] == 0) { // if zero in current column
            if (i != 0) { // checks if at least 1 book has been borrowed
                break;
            }
            else if (i == 0) {// if it is first column
                flag1 = false;
            }
        }

    }

    //print all borrowed books
    if (!flag) {
        cout << "\nNo books have been borrowed." << endl;
    }
    else {
        cout << "\nBooks Borrowed: " << endl;
        string temp;
        for (int j = 0; j < 10; j++) {
            temp = to_string(arr[j]);
            searchID(temp);
        }
    }
   
    if (!flag1) {
        cout << "\nNo books have been reserved." << endl;
    }
    else {
        //print all reserved books
        cout << "\nBooks Reserved: " << endl;
        string temp1;
        for (int j = 0; j < 10; j++) {
            temp1 = to_string(arr1[j]);
            searchID(temp1);
        }
    }
   
}

void Book::myInfoUser(string reader) {
    readBorrowedBook();
    readUsertxt();
    int r, arr[10];
    bool ch = false;

    
    for (int i = 0; i < userRow; i++){
        if (userArray[i][0].compare(reader) == 0){//if searched username = entered username
           r = i; //take row number
           ch = true;//tells us we found user
        }
     }

    bool flag = true;
    if (ch && (userArray[r][2] != "1")) {
        //finds all borrowed books
        for (int i = 0; i < 10; i++) {//goes thru each column

            if (BorrowBooks[r][i] != 0) {//if there is no zero in current column
                arr[i] = BorrowBooks[r][i];
            }
            else if (BorrowBooks[r][i] == 0) { // if zero in current column
                if (i != 0) { // checks if at least 1 book has been borrowed
                    break;
                }
                else if (i == 0) {// if it is first column
                    flag = false;
                }
            }

        }

        //print all borrowed books
        if (!flag) {
            cout << "\nNo books have been borrowed." << endl;
        }
        else {
            cout << "\nBooks Borrowed: " << endl;
            string temp;
            for (int j = 0; j < 10; j++) {
                temp = to_string(arr[j]);
                searchID(temp);
            }
        }
    }
    
}

int Book::prevBorrowBook(Reader& reader)
{
    readBookList();
    readBorrowedBook();
    int row = getRowNumber(reader);
    int prevlistcopies = 0;
    for (int i = 0; i < borCol; i++)
    {
        if (BorrowBooks[row][i] != 0)
        {
            storeExpDate(findMAXbrw(reader, BorrowBooks[row][i]), BorrowBooks[row][i]);
            prevlistcopies++;
            //Sets the previous ID's of books borrowed to their borrowed list of copies
        }
    }
    return prevlistcopies;
}


////// OTHER FUNCTIONS //////
//This is an extra function that we added which recommends the student books.
void Book::recommendedbook() {
    int ans = 1;
    int gen_1 = 1;
    int gen_2 = 1;
    cout << "\nPlease answer the questions below!" << endl;
    cout << "\nDo you like fiction or non-fiction?" << endl;
    cout << "Please Choose: " << endl;
    cout << "\t\t1 -- Fiction" << endl;
    cout << "\t\t2 -- Non-fiction" << endl;
    cin >> ans;
    switch (ans) {
    case 1:  //Fiction
        cout << "Do you like..." << endl;
        cout << "\t\t1 -- Fantasy" << endl;
        cout << "\t\t2 -- Romance" << endl;
        cout << "\t\t3 -- Sci-Fi" << endl;
        cin >> gen_1;
        switch (gen_1) {
        case 1: //Fantasy
            cout << "Recommended Book: " << endl;
            cout << "\t\t1 -- The Lightning Thief By Rick Riordan" << endl;
            cout << "\nThe Lightning Thief is a great choice for those who love fantasy and adventure." << endl;
            break;
        case 2: //Romance
            cout << "Recommended Books: " << endl;
            cout << "\t\t1 -- Blues Warrior By Bliss Carter" << endl;
            cout << "\t\t2 -- Lure Of Obsession By Lisa Kessler" << endl;
            cout << "\t\t3 -- Beautiful Disaster By Jamie McGuire" << endl;
            cout << "\nThese books are a great choice for those who want to relax and read a great love story." << endl;
            break;
        case 3: //Sci-fi
            cout << "Recommended Books: " << endl;
            cout << "\t\t1 -- Legend By Marie Lu" << endl;
            cout << "\t\t2 -- Prodigy By Marie Lu" << endl;
            cout << "\nThese books are a great choice for those who love and adventure." << endl;
            break;
        default: cout << "\nPlease enter the correct option." << endl;
            break;
        }
        break;
    case 2: //Non-Fiction
        cout << "Do you like..." << endl;
        cout << "\t\t1 -- Psychology" << endl;
        cout << "\t\t2 -- Personal Memoir" << endl;
        cout << "\t\t3 -- Science" << endl;
        cin >> gen_2;
        switch (gen_2) {
        case 1: //Psychology
            cout << "Recommended Book: " << endl;
            cout << "\t\t1 -- Atomic Habits By James Clear" << endl;
            cout << "\nThis book is a great choice for those who want to learn about building good habits and breaking bad ones." << endl;
            break;
        case 2: //Personal Memoir
            cout << "Recommended Book: " << endl;
            cout << "\t\t1 -- In Order To Live By Yeonmi Park" << endl;
            cout << "\nThis book is a great choice for those who want a tearjerker story of a girl who finds freedom." << endl;
            break;
        case 3: //Science
            cout << "Recommended Book: " << endl;
            cout << "\t\t1 -- Breath By James Nestor" << endl;
            cout << "\nThis book is a great choice for those who love self-care and science." << endl;
            break;
        default: cout << "\nPlease enter the correct option." << endl;
            break;
        }
        break;
    default: cout << "\nPlease enter the correct option." << endl;
        break;
    }
}