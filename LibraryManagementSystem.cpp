// Author: Katherine Anne S. Liwanag

/* This Library Management System program allows users to manage a library by adding, editing, searching, deleting, and viewing books.
   It uses an abstract class for book details and a derived class for library operations.
   The program includes input validation for book categories and IDs, and it displays book details in a formatted table.
*/

#include <iostream>
#include <iomanip> // Used for table formatting
using namespace std;

// Abstract class for Books
class Book
{
private:
    string id, isbn, title, author, edition, publication, category;

public:
    // Default constructor for Book
    Book() : id(""), isbn(""), title(""), author(""), edition(""), publication(""), category("") {}

    // Constructor for Book details
    Book(string id, string isbn, string title, string author, string edition, string publication, string category)
    {
        this->id = id;
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }

    // Getters for Book details
    string getID() { return id; }
    string getISBN() { return isbn; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getEdition() { return edition; }
    string getPublication() { return publication; }
    string getCategory() { return category; }

    // Virtual functions for Book operations
    virtual void addBook() = 0;
    virtual void editBook(string bookID) = 0;
    virtual void searchBook(string bookID) = 0;
    virtual void deleteBook(string bookID) = 0;
    virtual void viewByCategory(string category) = 0;
    virtual void viewAllBooks() = 0;
};

// Function to convert string to lowercase
string toLowerCase(string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Derived class Library
class Library : public Book // Inherits from Book class
{
private:
    Book *books[10]; // Array to store books
    int bookCount = 0;

public:
    Library() {} // Default constructor for Library

    // Constructor for Library details
    Library(string id, string isbn, string title, string author, string edition, string publication, string category) : Book(id, isbn, title, author, edition, publication, category) {}

    void addBook() override;
    void editBook(string bookID) override;
    void searchBook(string bookID) override;
    void deleteBook(string bookID) override;
    void viewByCategory(string category) override;
    void viewAllBooks() override;
};

// Add Book Implementation
void Library::addBook() // Function that belongs to the Library class that performs the overriden addBook operation
{
    string id, isbn, title, author, edition, publication, category;
    string validCategories[2] = {"fiction", "non-fiction"};
    bool isValidCategory = false;    // Flag for valid category
    bool isValidID = false;          // Flag for valid ID
    bool isValidISBN = false;        // Flag for valid ISBN
    bool isValidTitle = false;       // Flag for valid title
    bool isValidAuthor = false;      // Flag for valid author
    bool isValidEdition = false;     // Flag for valid edition
    bool isValidPublication = false; // Flag for valid publication

    do
    {
        cout << "Enter Category [Fiction|Non-Fiction]: ";
        getline(cin, category);
        category = toLowerCase(category);

        // Validate category
        for (string valid : validCategories) // Loop through valid categories
        {
            if (category == valid) // Check if input category is valid
            {
                if (category == "fiction")
                {
                    category = "Fiction"; // Set category to "Fiction" if input is "fiction"
                }
                else
                {
                    category = "Non-Fiction"; // Set category to "Non-Fiction" if input is "non-fiction"
                }
                isValidCategory = true;
                break;
            }
        }

        if (!isValidCategory) // Check if input category is invalid
        {
            cout << "Category not found! Please enter 'Fiction' or 'Non-Fiction'." << endl;
        }
    } while (!isValidCategory);

    do
    {
        cout << "Enter Book ID: ";
        getline(cin, id);

        // Handle empty input
        if (id.empty())
        {
            cout << "Book ID cannot be empty! Please enter a valid ID." << endl;
            isValidID = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        id = toLowerCase(id);

        // Check for duplicate ID
        isValidID = true; // Assume valid until proven otherwise
        for (int i = 0; i < bookCount; ++i)
        {
            if (books[i] != nullptr && books[i]->getID() == id) // Checks if books array is not empty and checks for duplicate ID
            {
                cout << "Duplicate ID! Book with this ID already exists." << endl;
                cout << "Please enter a unique ID." << endl;
                isValidID = false; // Set to false if duplicate is found
                break;             // Exit the loop if duplicate is found
            }
        }

    } while (!isValidID);

    // Input remaining book details
    do
    {
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        // Handle empty input
        if (isbn.empty())
        {
            cout << "ISBN cannot be empty! Please enter a valid ISBN." << endl;
            isValidISBN = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        isValidISBN = true; // Assume valid until proven otherwise

    } while (!isValidISBN);

    do
    {
        cout << "Enter Title: ";
        getline(cin, title);

        // Handle empty input
        if (title.empty())
        {
            cout << "Title cannot be empty! Please enter a valid title." << endl;
            isValidTitle = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        isValidTitle = true; // Assume valid until proven otherwise
    } while (!isValidTitle);

    do
    {
        cout << "Enter Author: ";
        getline(cin, author);

        // Handle empty input
        if (author.empty())
        {
            cout << "Author cannot be empty! Please enter a valid author." << endl;
            isValidAuthor = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        isValidAuthor = true; // Assume valid until proven otherwise
    } while (!isValidAuthor);

    do
    {
        cout << "Enter Edition: ";
        getline(cin, edition);

        // Handle empty input
        if (edition.empty())
        {
            cout << "Edition cannot be empty! Please enter a valid edition." << endl;
            isValidEdition = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        isValidEdition = true; // Assume valid until proven otherwise
    } while (!isValidEdition);

    do
    {
        cout << "Enter Publication: ";
        getline(cin, publication);

        // Handle empty input
        if (publication.empty())
        {
            cout << "Publication cannot be empty! Please enter a valid publication." << endl;
            isValidPublication = false;
            continue; // Skip the rest of the loop and restart the loop
        }

        isValidPublication = true; // Assume valid until proven otherwise
    } while (!isValidPublication);

    // Create a new book object and store it in the array
    books[bookCount] = new Library(id, isbn, title, author, edition, publication, category);
    bookCount++; // Increment book count

    cout << "Book added successfully!" << endl;
    system("pause");
}

void Library::editBook(string bookID) // Function that belongs to the Library class that performs the overriden editBook operation
{
    if (bookCount == 0) // Check if no books are available
    {
        cout << "No books available to edit!" << endl;
        return; // Go back to main menu
    }

    bookID = toLowerCase(bookID);
    bool found = false;

    for (int i = 0; i < bookCount; ++i) // Loop through added books
    {
        if (books[i] != nullptr && books[i]->getID() == bookID) // Checks if books array is not empty and checks for book ID
        {
            string newCategory, newISBN, newTitle, newAuthor, newEdition, newPublication;
            string validCategories[2] = {"fiction", "non-fiction"};
            bool isValidCategory = false;
            bool isValidISBN = false;
            bool isValidTitle = false;
            bool isValidAuthor = false;
            bool isValidEdition = false;
            bool isValidPublication = false;

            // Get new category
            do
            {
                cout << "Enter New Category [Fiction|Non-Fiction]: ";
                getline(cin, newCategory);
                newCategory = toLowerCase(newCategory);

                for (string valid : validCategories) // Loop through valid categories
                {
                    if (newCategory == valid) // Check if input category is valid
                    {
                        if (newCategory == "fiction")
                        {
                            newCategory = "Fiction"; // Set category to "Fiction" if input is "fiction"
                        }
                        else
                        {
                            newCategory = "Non-Fiction"; // Set category to "Non-Fiction" if input is "non-fiction"
                        }
                        isValidCategory = true;
                        break;
                    }
                }

                if (!isValidCategory)
                {
                    cout << "Category not found! Please enter 'Fiction' or 'Non-Fiction'." << endl;
                }
            } while (!isValidCategory);

            // Get other book details
            do
            {
                cout << "Enter New ISBN: ";
                getline(cin, newISBN);

                // Handle empty input
                if (newISBN.empty())
                {
                    cout << "ISBN cannot be empty! Please enter a valid ISBN." << endl;
                    isValidISBN = false;
                    continue; // Skip the rest of the loop and restart the loop
                }

                isValidISBN = true; // Assume valid until proven otherwise

            } while (!isValidISBN);

            do
            {
                cout << "Enter New Title: ";
                getline(cin, newTitle);

                // Handle empty input
                if (newTitle.empty())
                {
                    cout << "Title cannot be empty! Please enter a valid title." << endl;
                    isValidTitle = false;
                    continue; // Skip the rest of the loop and restart the loop
                }

                isValidTitle = true; // Assume valid until proven otherwise

            } while (!isValidTitle);

            do
            {
                cout << "Enter New Author: ";
                getline(cin, newAuthor);

                // Handle empty input
                if (newAuthor.empty())
                {
                    cout << "Author cannot be empty! Please enter a valid author." << endl;
                    isValidAuthor = false;
                    continue; // Skip the rest of the loop and restart the loop
                }

                isValidAuthor = true; // Assume valid until proven otherwise

            } while (!isValidAuthor);

            do
            {
                cout << "Enter New Edition: ";
                getline(cin, newEdition);

                // Handle empty input
                if (newEdition.empty())
                {
                    cout << "Edition cannot be empty! Please enter a valid edition." << endl;
                    isValidEdition = false;
                    continue; // Skip the rest of the loop and restart the loop
                }

                isValidEdition = true; // Assume valid until proven otherwise

            } while (!isValidEdition);

            do
            {
                cout << "Enter New Publication: ";
                getline(cin, newPublication);

                // Handle empty input
                if (newPublication.empty())
                {
                    cout << "Publication cannot be empty! Please enter a valid publication." << endl;
                    isValidPublication = false;
                    continue; // Skip the rest of the loop and restart the loop
                }

                isValidPublication = true; // Assume valid until proven otherwise

            } while (!isValidPublication);

            // Update book details
            delete books[i];                                                                                       // Delete old book object
            books[i] = new Library(bookID, newISBN, newTitle, newAuthor, newEdition, newPublication, newCategory); // Keep original ID and replace the other book details
            cout << "Book updated successfully!" << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found! " << endl;
    }

    system("pause");
}

void Library::searchBook(string bookID) // Function that belongs to the Library class that performs the overriden searchBook operation
{
    if (bookCount == 0) // Check if no books are available
    {
        cout << "No books available to search!" << endl;
        return; // Go back to main menu
    }

    bookID = toLowerCase(bookID);
    bool found = false;

    for (int i = 0; i < bookCount; ++i) // Loop through added books
    {
        if (books[i] != nullptr && books[i]->getID() == bookID) // Checks if books array is not empty and checks for book ID
        {
            cout << "Book ID       : " << books[i]->getID() << endl;
            cout << "============== BOOK DETAILS ==============" << endl;
            cout << "ISBN          : " << books[i]->getISBN() << endl;
            cout << "Title         : " << books[i]->getTitle() << endl;
            cout << "Author        : " << books[i]->getAuthor() << endl;
            cout << "Edition       : " << books[i]->getEdition() << endl;
            cout << "Publication   : " << books[i]->getPublication() << endl;
            cout << "Category      : " << books[i]->getCategory() << endl;
            cout << "==========================================" << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }

    system("pause");
}

void Library::deleteBook(string bookID) // Function that belongs to the Library class that performs the overriden deleteBook operation
{
    if (bookCount == 0) // Check if no books are available
    {
        cout << "No books available to delete!" << endl;
        return; // Go back to main menu
    }

    bookID = toLowerCase(bookID); // Convert input to lowercase
    bool found = false;

    for (int i = 0; i < bookCount; ++i) // Loop through added books
    {
        if (books[i] != nullptr && books[i]->getID() == bookID) // Checks if books array is not empty and checks for book ID
        {
            string confirmation;
            do
            {
                cout << "Book ID       : " << books[i]->getID() << endl;
                cout << "============== BOOK DETAILS ==============" << endl;
                cout << "ISBN          : " << books[i]->getISBN() << endl;
                cout << "Title         : " << books[i]->getTitle() << endl;
                cout << "Author        : " << books[i]->getAuthor() << endl;
                cout << "Edition       : " << books[i]->getEdition() << endl;
                cout << "Publication   : " << books[i]->getPublication() << endl;
                cout << "Category      : " << books[i]->getCategory() << endl;
                cout << "==========================================" << endl;

                cout << "Do you want to delete this book? [Y/N]: ";
                getline(cin, confirmation);
                confirmation = toLowerCase(confirmation);

                if (confirmation != "y" && confirmation != "n")
                {
                    cout << "Invalid input! Please enter 'Y' or 'N' only." << endl;
                }

            } while (confirmation != "y" && confirmation != "n");

            if (confirmation == "y")
            {
                delete books[i];    // delete book and free memory
                books[i] = nullptr; // Set the pointer to null

                // Shift remaining books to fill the gap
                for (int j = i; j < bookCount - 1; ++j)
                {
                    books[j] = books[j + 1]; // Shift elements to the left by shifting the values of the next element to the current element
                }

                books[bookCount - 1] = nullptr; // Set the last element to nullptr
                bookCount--;                    // Decrease book count

                cout << "Book deleted successfully!" << endl;
            }
            else
            {
                cout << "Book deletion cancelled." << endl;
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }

    system("pause");
}

void Library::viewByCategory(string category) // Function that belongs to the Library class that performs the overriden viewByCategory operation
{
    if (bookCount == 0) // Check if no books are available
    {
        cout << "No books available to view!" << endl
             << endl;
        return; // Go back to main menu
    }

    bool found = false;

    cout << endl;
    cout << "==================================================== " << category << " BOOKS ====================================================" << endl;
    cout << setw(10) << left << "ID"
         << setw(20) << "ISBN"
         << setw(30) << "TITLE"
         << setw(20) << "AUTHOR"
         << setw(20) << "EDITION"
         << setw(20) << "PUBLICATION" << endl;
    cout << string(123, '-') << endl;

    for (int i = 0; i < bookCount; ++i)
    {
        if (books[i] != nullptr && books[i]->getCategory() == category)
        {
            cout << setw(10) << left << books[i]->getID()
                 << setw(20) << books[i]->getISBN()
                 << setw(30) << books[i]->getTitle()
                 << setw(20) << books[i]->getAuthor()
                 << setw(20) << books[i]->getEdition()
                 << setw(20) << books[i]->getPublication() << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No books found under the category: " << category << endl;
    }
    cout << "===========================================================================================================================" << endl;
    system("pause");
}

void Library::viewAllBooks() // Function that belongs to the Library class that performs the overriden viewAllBooks operation
{
    if (bookCount == 0) // Check if no books are available
    {
        cout << "No books available to view!" << endl
             << endl;
        return; // Go back to main menu
    }

    cout << endl;
    cout << "============================================================ LIBRARY BOOKS ============================================================" << endl;
    cout << setw(10) << left << "ID"
         << setw(20) << "ISBN"
         << setw(30) << "TITLE"
         << setw(20) << "AUTHOR"
         << setw(20) << "EDITION"
         << setw(20) << "PUBLICATION"
         << setw(15) << "CATEGORY" << endl;
    cout << string(135, '-') << endl;

    for (int i = 0; i < bookCount; ++i)
    {
        if (books[i] != nullptr)
        {
            cout << setw(10) << left << books[i]->getID()
                 << setw(20) << books[i]->getISBN()
                 << setw(30) << books[i]->getTitle()
                 << setw(20) << books[i]->getAuthor()
                 << setw(20) << books[i]->getEdition()
                 << setw(20) << books[i]->getPublication()
                 << setw(15) << books[i]->getCategory() << endl;
        }
    }
    cout << "=======================================================================================================================================" << endl;
    system("pause");
}

int main()
{
    Library lib; // Create an object of Library class
    bool running = true;
    while (running)
    {
        string viewMN;
        int viewMenu;

        cout << endl;
        cout << "Welcome to Library Management System!" << endl;
        cout << "======================== MENU ========================" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Edit Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. View Books by Category" << endl;
        cout << "6. View All Books" << endl;
        cout << "7. Exit" << endl;
        cout << "======================================================" << endl;
        cout << "View [1|2|3|4|5|6|7]: ";
        getline(cin, viewMN);

        bool isValid = true;
        for (char c : viewMN)
        { // Validate if input is an integer
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }

        if (!isValid || viewMN.empty())
        {
            cout << "Invalid Input! Please enter 1, 2, 3, 4, 5, 6, or 7 only." << endl
                 << endl;
            continue; // Skips the rest of the for loop and restarts the while loop
        }

        viewMenu = stoi(viewMN);

        if (viewMenu < 1 || viewMenu > 7)
        {
            cout << "Invalid Choice! Please choose from 1, 2, 3, 4, 5, 6, or 7 only.." << endl
                 << endl;
        }
        else if (viewMenu == 7)
        {
            cout << "Thank you for visiting our Library Management System! Exiting program..." << endl;
            running = false;
            break; // Stops the program
        }

        switch (viewMenu)
        {
        case 1:
        {
            cout << endl
                 << "====================== ADD BOOK ======================" << endl;
            lib.addBook(); // Call the addBook() function
            cout << "======================================================" << endl
                 << endl;

            break;
        }

        case 2:
        {
            cout << endl
                 << "===================== EDIT BOOK =====================" << endl;
            string bookID;
            cout << "Enter Book ID to edit: ";
            getline(cin, bookID);
            lib.editBook(bookID); // Call the editBook() function
            cout << "=====================================================" << endl
                 << endl;

            break;
        }

        case 3:
        {
            cout << endl
                 << "==================== SEARCH BOOK ====================" << endl;
            string bookID;
            cout << "Enter Book ID to search: ";
            getline(cin, bookID);
            lib.searchBook(bookID); // Call the searchBook() function
            cout << "=====================================================" << endl
                 << endl;

            break;
        }

        case 4:
        {
            cout << endl
                 << "==================== DELETE BOOK ====================" << endl;
            string bookID;
            cout << "Enter Book ID to delete: ";
            getline(cin, bookID);
            lib.deleteBook(bookID); // Call the deleteBook() function
            cout << "=====================================================" << endl
                 << endl;

            break;
        }

        case 5:
        {
            cout << endl
                 << "====================== VIEW BOOKS BY CATEGORY ======================" << endl;
            string category;
            string validCategories[2] = {"fiction", "non-fiction"};
            bool isValidCategory = false; // Flag for valid category
            do
            {
                cout << "Enter Category [Fiction|Non-Fiction]: ";
                getline(cin, category);
                category = toLowerCase(category);

                // Validate category
                for (string valid : validCategories) // Loop through valid categories
                {
                    if (category == valid) // Check if input category is valid
                    {
                        if(category == "fiction")
                        {
                            category = "Fiction"; // Set category to "Fiction" if input is "fiction"
                        }
                        else
                        {
                            category = "Non-Fiction"; // Set category to "Non-Fiction" if input is "non-fiction"
                        }
                        isValidCategory = true;
                        break;
                    }
                }

                if (!isValidCategory) // Check if input category is invalid
                {
                    cout << "Category not found! Please enter 'Fiction' or 'Non-Fiction'." << endl;
                }
            } while (!isValidCategory);
            cout << "====================================================================" << endl;
            lib.viewByCategory(category); // Call viewByCategory() function

            break;
        }

        case 6:
        {
            lib.viewAllBooks(); // Call the viewAllBooks() function

            break;
        }
        }
    }
    return 0;
}