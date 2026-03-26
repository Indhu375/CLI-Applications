#include<bits/stdc++.h>
using namespace std;

struct Book
{
    string name;
    string isbn;
    int quantity;
    int price;
    int borrow_cnt = 0;
};
struct User
{
    string email;
    string password;
    string role;
    int depsoit = 1500;
    vector<string> borrow;
}

vector<User> users;
vector<Book> books;

User* login(string email, string password)
{
    for(auto &u : user)
    {
        if(u.email == email && u.password == password)
        {
            return &u;
        }
    }
    return nullptr;
}

void adminMenu()
{
    int ch;
    cout << "Admin Menu" << endl;
    do
    {
        cout << "1.View Books" << endl << "2.Add Books" << endl << "3.Delete Books" << "4.Report" << endl << "5.Logout";
        cin >> ch;
        if(ch == 1)     viewBooks();
        else if(ch == 2)    addBook();
        else if(ch == 3)    deleteBook();
        else if(ch == 4)    reportBook();
        else    cout << "Enter a valid choice";
    }while(ch != 5);
}

void userMenu(user &u)
{
    int ch;
    cout << "User Menu" << endl;
    do
    {
        cout << "1.View Books\n 2.Borrow Book\n 3.Return\n 4.logout";
        cin >> ch;
        switch(ch)
        {
            case 1 : viewBooks();break;
            case 2 : borrowBook(u);break;
            case 3 : returnBook(u);break;
        }
    }while(choice != 4);
}

void viewBook()
{
    for(auto &b : books)
    {
        cout << "Name: " << b.name << " " << "ISBN: " << b.isbn << "Quantity: " << b.quantity << " " << "price: " << b.price << endl;
    }
}

void addBook()
{
    books b;
    string name;
    cout << "Book name: ";
    cin >> b.name;
    cout << "Book isbn num: ";
    cin >> b.isbn;
    cout << "Book Quantity: ";
    cin >> b.quantity;
    cout << "Book Price: ";
    cin >> b.price;
    books.push_back(b);
    cout << "Book added Successfully";
}

void deleteBook()
{
    string isbn;
    cout << "Enter the isbn of the Book to delete: ";
    cin >> isbn;
    books.erase(remove_if(books.begin(),books.end(),[&](Book &b)
                {
                    return isbn == b.isbn;
                }),books.end());
}

int main()
{
    users.push_back({"admin123@gmail.com","123","admin"});
    users.push_back({"user1@gmail.com","123","user"});
    int choice = 0;
    do
    {
        cout << "LIBRARY MANAGEMENT" << endl;
        cout << "Enter the choice: " << endl; 
        cout << "1.Login" << endl;
        cout << "2.exit" << endl;
        cin >> choice;
        if(choice == 1)
        {
            string email, password;
            cout << "Enter the email: " << endl;
            cin >> email;
            cout << "Enter the password: " << endl;
            cin >> password;
            User* user = login(email,password);
            if(!user)
            {
                cout << "Invalid Credentials" << endl;
            }
            else if(user -> role == admin)
            {
                adminMenu();
            }
            else
            {
                userMenu(*user);
            }
        }
    }while(choice != 0);
}