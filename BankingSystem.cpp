#include "BankingSystem.h"

bool mobile_check(string& n)
{
    regex mobile_no ("(01)[1]?[2]?[0]?[5]?[0-9]{8}");
    return regex_match(n,mobile_no);
}

int Client::counter = -1;

BankingApplication::BankingApplication()
{
    loadaccounts();

    Client* assigncounter;

    assigncounter->set_counter(clients.size()-1);

    while(true)
    {
        cout<<"Welcome to FCAI Banking Application! \n"<<
            "1. Create a New Account \n"<<
            "2. List Clients and Accounts \n"<<
            "3. Withdraw Money \n"<<
            "4. Deposit Money \n"<<
            "5. Close and save\n\n";
        cout<<"Please Enter Choice =========> ";

        string choice;
        cin>>choice;
        cout<<'\n';

        if(choice=="1")
        {
            add_client();
        }
        else if(choice=="2")
        {
            list_accounts();
        }
        else if(choice=="3")
        {
            cout<<"Please Enter Account ID (e.g., FCAI-015) =========> ";
            string id;
            cin>>id;
            cout<<'\n';
            if(search_id(id)!=-1)
            {
                int index = search_id(id);
                cout<<"Account ID: "<<id<<endl;
                if(S_accounts[index]->get_minimumBalance()!=-1)
                {
                    cout<<"Account type: (Saving)"<<endl;
                    cout<<"Your balance: "<<S_accounts[index]->get_minimumBalance()<<endl;
                }
                else
                {
                    cout<<"Account type: (Basic)"<<endl;
                    cout<<"Your balance: "<<accounts[index]->get_balance()<<endl<<endl;
                }
                cout<<"Please Enter The Amount to Withdraw =========> ";
                double amount;
                cin>>amount;
                cout<<'\n';
                if(S_accounts[index]->get_minimumBalance()!=-1)
                {
                    S_accounts[index]->withdraw(amount);
                }
                else
                {
                    accounts[index]->withdraw(amount);
                }
            }
            else
            {
                cout<<"ID not found!"<<endl<<endl;
            }
        }
        else if(choice=="4")
        {
            cout<<"Please Enter Account ID (e.g., FCAI-015) =========> ";
            string id;
            cin>>id;
            cout<<'\n';
            if(search_id(id)!=-1)
            {
                int index = search_id(id);
                cout<<"Account ID: "<<id<<endl;
                if(S_accounts[index]->get_minimumBalance()!=-1)
                {
                    cout<<"Account type: (Saving)"<<endl;
                    cout<<"Your balance: "<<S_accounts[index]->get_minimumBalance()<<endl;
                }
                else
                {
                    cout<<"Account type: (Basic)"<<endl;
                    cout<<"Your balance: "<<accounts[index]->get_balance()<<endl<<endl;
                }
                cout<<"Please Enter The Amount to Deposit =========> ";
                double amount;
                cin>>amount;
                cout<<'\n';
                if(S_accounts[index]->get_minimumBalance()!=-1)
                {
                    S_accounts[index]->deposit(amount);
                }
                else
                {
                    accounts[index]->deposit(amount);
                }
            }
            else
            {
                cout<<"ID not found!"<<endl<<endl;
            }
        }
        else if(choice=="5")
        {
            break;
        }
        else
        {
            cout<<"Invalid input"<<endl<<endl;
        }
    }
}

void BankingApplication::add_client()
{
    cout<<"Please Enter Client Name =========> ";
    string name,address,phone;
    cin.ignore();
    getline(cin,name);
    cout<<'\n';
    cout<<"Please Enter Client Address =======> ";
    cin.ignore();
    getline(cin,address);
    cout<<'\n';
    cout<<"Please Enter Client Phone =======> ";
    cin>>phone;
    cout<<'\n';
    while(!mobile_check(phone))
    {
        cout<<"Invalid phone number"<<endl;
        cout<<"Please Enter Client Phone =======> ";
        cin>>phone;
        cout<<'\n';
    }
    while(true)
    {
        cout<<"What Type of Account Do You Like? (1) Basic (2) Saving ( Type 1 or 2 ) =========> ";
        string choice;
        cin>>choice;
        cout<<'\n';

        Client* c=new Client(name,address,phone);

        clients.push_back(c);

        if(choice=="1")
        {
            cout<<"Please Enter the Starting Balance =========> ";

            double amount;
            cin>>amount;
            cout<<'\n';

            BankAccount* acc=new BankAccount(amount);
            SavingsBankAccount *s_acc=new SavingsBankAccount;

            string id;
            id="FCAI-00";
            id+= to_string(c->get_counter()+1);
            acc->set_id(id);
            s_acc->set_id(id);
            id="";

            cout<<"An account was created with ID "<<acc->get_id()<<" and Starting Balance "<<acc->get_balance()<<"L.E.\n\n";

            accounts.push_back(acc);
            S_accounts.push_back(s_acc);
            break;
        }
        else if(choice=="2")
        {
            cout<<"Please Enter the Starting Balance =========> ";

            double amount;
            cin>>amount;
            cout<<'\n';

            BankAccount *acc = new BankAccount;
            SavingsBankAccount* s_acc=new SavingsBankAccount(amount);

            string id;
            id="FCAI-00";
            id+= to_string(c->get_counter()+1);
            acc->set_id(id);
            s_acc->set_id(id);
            id="";

            cout<<"An account was created with ID "<<s_acc->get_id()<<" and Starting Balance "<<s_acc->get_minimumBalance()<<"L.E.\n\n";

            accounts.push_back(acc);
            S_accounts.push_back(s_acc);
            break;
        }
        else
        {
            cout<<"Invalid input!"<<endl<<endl;
        }
    }
}

void Client::print_clients()
{
    cout<<endl<<"----------------------------------------------------"<<endl;
    cout<<"Name: "<<name<<endl<<endl;
    cout<<"Address: "<<address<<endl<<endl;
    cout<<"Phone Number: "<<phone_num<<endl<<endl;
}

void BankAccount::print_accounts()
{
    cout<<"Account ID: "<<balance_id<<" (Basic)"<<endl<<endl;
    cout<<"Balance: "<<balance<<endl;
    cout<<"----------------------------------------------------"<<endl<<endl;
}

void SavingsBankAccount::print_S_accounts()
{
    cout<<"Account ID: "<<balance_id<<" (Saving)"<<endl<<endl;
    cout<<"Balance: "<<minimum_balance<<endl;
    cout<<"----------------------------------------------------"<<endl<<endl;
}


void BankingApplication::list_accounts()
{
    Client *h;

    for(int i=0; i<h->get_counter()+1; i++)
    {
        clients[i]->print_clients();
        if(S_accounts[i]->get_minimumBalance()!=-1)
        {
            S_accounts[i]->print_S_accounts();
        }
        else
        {
            accounts[i]->print_accounts();
        }
    }
}

void BankAccount::set_id(string id)
{
    balance_id=id;
}

string BankAccount::get_id()
{
    return balance_id;
}

int BankAccount::get_balance()
{
    return balance;
}

void BankAccount::withdraw(double amount)
{
    if(amount>balance)
    {
        cout<<"Sorry. This is more than what you can withdraw.\n\n";
    }
    else
    {
        balance-=amount;
        cout<<"Your new balance: "<<balance<<endl<<endl;
    }
}

void BankAccount::deposit(double amount)
{
    balance+=amount;
    cout<<"Your new balance: "<<balance<<endl<<endl;
}

void SavingsBankAccount::withdraw(double amount)
{
    if(amount<=minimum_balance)
    {
        minimum_balance-=amount;
        cout<<"Your new balance: "<<minimum_balance<<endl<<endl;
    }
    else
    {
        cout<<"Sorry. This is more than what you can withdraw.\n\n";
    }
}

void SavingsBankAccount::deposit(double amount)
{
    if(amount>=100)
    {
        minimum_balance+=amount;
        cout<<"Your new balance: "<<minimum_balance<<endl<<endl;
    }
    else
    {
        cout<<"Sorry. You must deposit 100 or more.\n";
    }
}


int Client::get_counter()
{
    return counter;
}

int SavingsBankAccount::get_minimumBalance()
{
    return minimum_balance;
}

int BankingApplication::search_id(string id)
{
    Client *c;

    for(int i=0; i<c->get_counter()+1; i++)
    {
        if(id==accounts[i]->get_id() || id==S_accounts[i]->get_id())
        {
            return i;
        }
    }
    return -1;
}

void BankingApplication :: loadaccounts()
{
    ifstream File;
    string line,file;
    file="accounts";
    file+=".txt";
    File.open(file);
    vector <string> vec;
    while(getline(File,line))
    {
        vec.push_back(line);
    }
    for(int i=0; i<vec.size(); i+=6)
    {
        string name = vec[i];
        string address = vec[i+1];
        string phone = vec[i+2];
        Client* c = new Client(name,address,phone);
        clients.push_back(c);
        string amount = vec[i+5];
        if(vec[i+3][0]=='B')
        {
            BankAccount* acc = new BankAccount(stod(amount));
            SavingsBankAccount *s_acc = new SavingsBankAccount;
            string id = vec[i+4];
            acc->set_id(id);
            s_acc->set_id(id);
            accounts.push_back(acc);
            S_accounts.push_back(s_acc);
        }
        else
        {
            BankAccount* acc = new BankAccount;
            SavingsBankAccount *s_acc = new SavingsBankAccount(stod(amount));
            string id = vec[i+4];
            acc->set_id(id);
            s_acc->set_id(id);
            accounts.push_back(acc);
            S_accounts.push_back(s_acc);
        }
    }
    File.close();
}

BankingApplication::~BankingApplication()
{
    fstream ofile;
    ofile.open("accounts.txt");
    for(int i=0; i<clients.size(); i++)
    {
        ofile << clients[i]->get_name() << '\n';
        ofile << clients[i]->get_address() << '\n';
        ofile << clients[i]->get_phonenum() << '\n';
        if(S_accounts[i]->get_minimumBalance()==-1)
        {
            ofile << "B" << '\n';
            ofile << accounts[i]->get_id() << '\n';
            ofile << to_string(accounts[i]->get_balance()) << '\n';
        }
        else
        {
            ofile << "S" << '\n';
            ofile << S_accounts[i]->get_id() << '\n';
            ofile << to_string(S_accounts[i]->get_minimumBalance()) << '\n';
        }
    }
}