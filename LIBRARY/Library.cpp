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
    set<string> borrow;
};

vector<User> users;
vector<Book> books;

User* login(string email, string password)
{
    for(auto &u : users)
    {
        if(u.email == email && u.password == password)
        {
            return &u;
        }
    }
    return nullptr;
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
    Book b;
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

void bookReport()
{
    cout << "Books with low quantity ";
    for(auto &it : books)
    {
        if(it.quantity < 2)
        {
            cout << it.name << endl;
        }
    }
    cout << "Most Borrowed Books";
    sort(books.begin(),books.end(),[](Book &a, Book &b)
        {
            return a.quantity > b.quantity;
        });
    for(auto &b : books)
    {
        cout << b.name << " " << b.borrowcnt;
    }
}

Book* findBook(string isbn)
{
    for(auto &it : books)
    {
        if(it.isbn == isbn)  return &it;
    }
    return nullptr;
}

void borrowBook(User &u)
{
    if(u.borrow.size() >= 3)
    {
        cout << "Max 3 books only allowed";
        return;
    }
    if(u.deposit < 500)
    {
        cout << "Insufficient deposit";
        return;
    }
    string isbn;
    cout << "Enter the isbn of book to be borrowed";
    cin >> isbn;
    Book *b = findBook(isbn);
    if(u.borrow.find(isbn) != u.borrow.end())
    {
        cout << "Already borrowed";
        return;
    }
    if(!b || b->quantity <= 0)
    {
        cout << "Book not available";
        return;
    }
    else
    {
        u.borrow.insert(isbn);
        b->quantity--;
        b->borrow_cnt++;
    }
}

void returnBook(User &u)
{
    string isbn;
    cout << "Enter the isbn to return";
    cin >> isbn;
    Book *b = findBook(isbn);
    if(u.borrow.find(isbn) == u.borrow.end())
    {
        cout << "You did not borrowed the book";
        return;
    }
    if(b)
    {
        b->quantity++;
        u.borrow.erase(isbn);
        cout << "Book returned";
    }

}

void adminMenu()
{
    int ch;
    cout << "Admin Menu" << endl;
    do
    {
        cout << "1.View Books" << endl << "2.Add Books" << endl << "3.Delete Books" << "4.Report" << endl << "5.Logout";
        cin >> ch;
        if(ch == 1)     viewBook();
        else if(ch == 2)    addBook();
        else if(ch == 3)    deleteBook();
        else if(ch == 4)    bookReport();
        else    cout << "Enter a valid choice";
    }while(ch != 5);
}

void userMenu(User &u)
{
    int ch;
    cout << "User Menu" << endl;
    do
    {
        cout << "1.View Books\n 2.Borrow Book\n 3.Return\n 4.logout";
        cin >> ch;
        switch(ch)
        {
            case 1 : viewBook();break;
            case 2 : borrowBook(u);break;
            case 3 : returnBook(u);break;
        }
    }while(choice != 4);
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
            else if(user -> role == "admin")
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