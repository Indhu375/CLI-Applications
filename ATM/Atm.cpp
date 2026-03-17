#include<bits/stdc++.h>
using namespace std;

class Admin
{
    public:
        static int deposit;
        static int atm_balance;
        static int admin_pin;
};
int Admin::deposit = 0;
int Admin::atm_balance = 20000;
int Admin::admin_pin = 1989;

class User
{
    public:
        int account_no, pin, balance;
    User(int account_no, int pin, int balance)
    {
        this->account_no = account_no;
        this->pin = pin;
        this->balance = balance;
    }    
};
vector<User> users;
vector<string> transaction;

void Adminoperations()
{
    Admin obj;
    int pin;
    cout << "Enter the pin: ";
    cin >> pin;
    if(pin == obj.admin_pin)
    {
        cout << "1.Deposit " << endl << "2.Balance Check " << endl;
        cout << "Enter choice(1/2): ";
        int ch;
        cin >> ch;
        int amt;
        if(ch == 1)
        {
            cout << "Enter deposit amount: ";
            cin >> amt;
            cout << "Amount Deposited!" << endl;
            obj.atm_balance += amt;
            cout << "Balance: " << obj.atm_balance;
        }
        else if(ch == 2)
        {
            cout << "Balance: " << obj.atm_balance;
        }
        else
        {
            cout << "Enter the correct choice";
        }
    }
    else
    {
        cout << "Enter the correct PIN";
    }
}

void userOperations()
{
    int pin,acco_no;
    cout << "Enter account no: ";
    cin >> acco_no;
    cout << "Enter pin: ";
    cin >> pin;
    int idx = -1;
    for(int i=0;i<users.size();i++)
    {
        if(users[i].account_no == acco_no && users[i].pin == pin)
        {
            idx = i;
            break;
        }
    }
    if(idx == -1)
    {
        cout << "Invalid login";
        return;
    }
    char choice;
    User &obj = users[idx];
    do{
        int ch;
        cout << "1.Check Balance " << endl;
        cout << "2.Deposit amount " << endl;
        cout << "3.Withdraw amount " << endl;
        cout << "4.Change PIN " << endl;
        cout << "5.Transfer amount " << endl;
        cout << "6.Mini Statement" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch(ch)
        {
            case 1:
            {
                cout << "Balance: " << obj.balance << endl;
                break;
            }
            case 2:
            {
                int amt;
                cout << "Enter the amount to deposit: ";
                cin >> amt;
                obj.balance += amt;
                cout << "Amount Deposited" << endl;
                transaction.push_back("Deposited " + to_string(amt));
                cout << "Balance: " << obj.balance << endl;
                break;
            }
            case 3:
            {
                int w_amt;
                cout << "Enter the amount to be withdraw: ";
                cin >> w_amt;
                if(w_amt > obj.balance)
                {
                    cout << "Insufficient amount" << endl;
                }
                else
                {
                    obj.balance -= w_amt;
                    cout << "Amount Withdrawed" << endl;
                    transaction.push_back("Withdraw: "+ to_string(w_amt));
                    cout << "Balance: " << obj.balance << endl;
                }
                break;
            }
            case 4:
            {
                int n_pin;
                cout << "Enter new pin: ";
                cin >> n_pin;
                obj.pin = n_pin;
                cout << "PIN changed successfully" << endl;
                break;
            }
            case 5:
            {
                int t_amt,t_acc;
                cout << "Enter the account to be transfereed: ";
                cin >> t_acc;
                cout << "Enter the amount to be transfered: ";
                cin >> t_amt;
                bool found = false;
                for(int i=0;i<users.size();i++)
                {
                    if(users[i].account_no == t_acc)
                    {
                        if(obj.balance < t_amt)
                        {
                            cout << "Insufficient Balance" << endl;
                        }
                        else
                        {
                            obj.balance -= t_amt;
                            users[i].balance += t_amt;
                            transaction.push_back("Tranfered Amount: "+ to_string(t_amt));
                            cout << "Money transferred sucessfully" << endl;
                            cout << "Balance: " << obj.balance << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if(!found)  cout << "Failed ! Give correct acc no to transfer" << endl;
                break;
            }
            case 6:
            {
                cout << "---------------------------------------";
                cout << "Mini Statement" << endl;
                for(int i=transaction.size()-1;i>=0;i--)
                {
                    cout << transaction[i] << endl;
                }
                cout << "---------------------------------------" << endl;
                break;
            }
        }
        cout << "Do you want to continue(Y/N): ";
        cin >> choice;
    }while(choice == 'y' || choice == 'Y');
}

int main()
{
    users.push_back(User(1,4893,10000));
    users.push_back(User(2,7489,38900));
    users.push_back(User(3,8992,50000));
    cout << "1.Admin" << endl;
    cout << "2.User" << endl;
    int ch;
    cout << "Enter your choice(1/2): ";
    cin >> ch;
    if(ch == 1)
    {
        Adminoperations();
    }
    else if(ch == 2)
    {
        userOperations();
    }
    else
    {
        cout << "Enter the correct choice";
    }
}