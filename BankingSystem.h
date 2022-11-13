#include <bits/stdc++.h>
using namespace std;

class BankAccount;
class Client;
class SavingsBankAccount;

class BankingApplication
{
protected:

    BankAccount* accounts[10];
    SavingsBankAccount* S_accounts[10];
    Client* clients[10];

public:

    BankingApplication();

    void add_client();

    void list_accounts();

    int search_id(string id);
};


class BankAccount
{
protected:
    string balance_id;
    double balance;
    Client* account_client;

public:

    BankAccount():balance(0)
    {

    }

    BankAccount(double b)
    {
        balance=b;
    }

    void set_id(string id);

    string get_id();

    int get_balance();

    virtual void withdraw(double amount);

    virtual void deposit(double amount);

    void print_accounts();
};

class SavingsBankAccount: public BankAccount
{
private:
    double minimum_balance;

public:

    SavingsBankAccount()
    {
        minimum_balance = -1;
    }

    SavingsBankAccount(double m)
    {
        if(m>=1000)
        {
            minimum_balance=m;
        }
        else
        {
            cout<<"Sorry.Minimum balance should be 1000 or more\n";
        }
    }

    void withdraw(double amount);

    void deposit(double amount);

    void print_S_accounts();

    int get_minimumBalance();
};

class  Client
{
private:
    string name;
    string address;
    string phone_num;
    BankAccount* client_account;

    static int counter;

public:

    Client(string n,string a,string p)
    {
        name=n;
        address=a;
        phone_num=p;
        counter++;
    }

    int get_counter();

    void print_clients();
};

