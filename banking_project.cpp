#include<iostream>
#include<fstream>
#include<map>
#include<cstdlib>
#include<vector>
using namespace std;

#define min_balance 1000

class Insufficientfunds{};
class account
{
    private:
    string first_name;
    string middle_name;
    string last_name;
    float balance;
    long account_num;
    static long nxt_acc_no;
    public:
    account(){}
    account(string fname,string mname,string lname,float bal);
    long getAcc_no(){return account_num;}
    string getFirstname(){return first_name;}
    string getMiddlename(){return middle_name;}
    string getLastname(){return last_name;}
    float getBalance(){return balance;}
    void withdraw(float amount);
    void deposit(float amount);
    static void set_nxtAccountnumber(long account_no);
    static long get_nxtAccountnumber(){return nxt_acc_no;}
    friend ofstream & operator<<(ofstream &ofs,account &a);
    friend ifstream & operator>>(ifstream &ifs,account &a);
    friend ostream & operator<<(ostream &out,account &a);
};
long account::nxt_acc_no=0;

account::account(string fname,string mname,string lname,float bal)
{
    nxt_acc_no++;
    account_num=nxt_acc_no;
    first_name=fname;
    middle_name=mname;
    last_name=lname;
    balance=bal;

}
void account::withdraw(float amount)
{
    if(balance-amount<min_balance)
        throw Insufficientfunds();
    balance=balance-amount;
    
}
void account::deposit(float amount)
{
    balance=balance+amount;
}
void account::set_nxtAccountnumber(long account_no)
{
    nxt_acc_no=account_no;
}
ofstream & operator<<(ofstream &ofs,account &a)
{
   ofs<<a.first_name<<endl;
   ofs<<a.middle_name<<endl;
   ofs<<a.last_name<<endl;
   ofs<<a.account_num<<endl;
   ofs<<a.balance<<endl;
   return ofs;
}
ifstream & operator>>(ifstream &ifs,account &a)
{
    ifs>>a.first_name;
    ifs>>a.middle_name;
    ifs>>a.last_name;
    ifs>>a.account_num;
    ifs>>a.balance;
    return ifs;
}
ostream & operator<<(ostream &out,account &a)
{
    cout<<"First Name: "<<a.getFirstname()<<endl;
    cout<<"Middle Name: "<<a.getMiddlename()<<endl;
    cout<<"Last Name: "<<a.getLastname()<<endl;
    cout<<"Account Number: "<<a.getAcc_no()<<endl;
    cout<<"Balance: "<<a.getBalance()<<endl;
    return out;
}
class bank
{
    private:
    map<long,account> acc_data;
    public:
    bank();
    account create_acc(string fname,string mname,string lname,float bal);
    account balance_enquiry(long account_no);
    account withdraw(long account_no,float amount);
    account deposit(long account_no,float amount);
    void delete_acc(long account_no);
    void showcase_accouts();
    ~bank();
};

bank::bank()
{
    account acc;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile)
   {
 
     return;
   }
   while(!infile.eof())
   {
      infile>>acc;
      acc_data.insert(pair<long,account>(acc.getAcc_no(),acc));
    }
    account::set_nxtAccountnumber(acc.getAcc_no());

    infile.close();
}
account bank::create_acc(string fname,string mname,string lname,float bal)
{
 ofstream ofs;
 account acc(fname,mname,lname,bal);
 acc_data.insert(pair<long,account>(acc.getAcc_no(),acc));
 
 ofs.open("Bank.data", ios::trunc);
 
 map<long,account>::iterator itr;
 for(itr=acc_data.begin();itr!=acc_data.end();itr++)
 {
    ofs<<itr->second;
 }
 ofs.close();
 return acc;
}


account bank::balance_enquiry(long account_no)
{
    map<long,account>::iterator itr;
    itr=acc_data.find(account_no);
    return itr->second;
}

account bank::withdraw(long account_no,float amount)
{
    map<long,account>::iterator itr;
    itr=acc_data.find(account_no);
    itr->second.withdraw(amount);
    return itr->second;
}
account bank::deposit(long account_no,float amount)
{
    map<long,account>::iterator itr;
    itr=acc_data.find(account_no);
    itr->second.deposit(amount);
    return itr->second;
}
void bank::delete_acc(long account_no)
{
    map<long,account>::iterator itr;
    itr=acc_data.find(account_no);
    cout<<"Account "<<itr->second<<" is deleted"<<endl;
    acc_data.erase(account_no);
}
void bank::showcase_accouts()
{
    map<long,account>::iterator itr;
    for(itr = acc_data.begin();itr != acc_data.end();itr++)
    {
        cout<<"Account"<<itr->first<<endl<<itr->second<<endl;
    }
}
bank::~bank()
{
    ofstream ofs("Bank.data",ios::trunc);
    map<long,account>::iterator itr;
    for(itr = acc_data.begin();itr != acc_data.end();itr++)
    {
        ofs<<itr->second;
    }
    ofs.close();
}
int main()
{
    
    bank b;
    account a;
    string FirstName,MiddleName,LastName;
    float balance;
    long accountNumber;
    float amount;
    int choice;
    cout<<"-------BANKING SYSTEM---------"<<endl;
    do
    {
        cout<<"Select from the following"<<endl;
        cout<<"**************************************"<<endl;
        cout<<"1. Create a bank account"<<endl;
        cout<<"2. Balance enquiry"<<endl;
        cout<<"3. Withdraw money from bank account"<<endl;
        cout<<"4. Deposit money in the bank account"<<endl;
        cout<<"5. Delete a bank account"<<endl;
        cout<<"6. Display all the accounts"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"**************************************"<<endl;
        cout<<"Enter your Choice:\t ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Enter first name: "<<endl;
            cin>>FirstName;
            cout<<"Enter middle name: "<<endl;
            cin>>MiddleName;
            cout<<"Enter last name: "<<endl;
            cin>>LastName;
            cout<<"Enter inital balance : "<<endl;
            cin>>balance;
            a=b.create_acc(FirstName,MiddleName,LastName,balance);
            cout<<"\nCongratulation Your account has been created"<<endl;
            cout<<a;
            break;
        case 2:
            cout<<"Enter your account number"<<endl;
            cin>>accountNumber;
            a=b.balance_enquiry(accountNumber);
            cout<<"Your account details are as follows: "<<endl;
            cout<<a;
            break;
        case 3:
            cout<<"Enter your account number"<<endl;
            cin>>accountNumber;
            cout<<"Enter the amount to be withdrawed from your account"<<endl;
            cin>>amount;
            a=b.withdraw(accountNumber,amount);
            cout<<amount<<" Has been withdrawn from your account"<<endl;
            cout<<a;
            break;
        case 4:
            cout<<"Enter your account number"<<endl;
            cin>>accountNumber;
            cout<<"Enter the amount to be deposited to your account"<<endl;
            cin>>amount;
            a=b.deposit(accountNumber,amount);
            cout<<amount<<" Has been deposited to your bankaccount"<<endl;
            cout<<a;
            break;
        case 5:
           cout<<"Enter your account number"<<endl;
           cin>>accountNumber;
           b.delete_acc(accountNumber);
           cout<<"Your account has been closed"<<endl;
           cout<<a;
           break;
        case 6:
           b.showcase_accouts();
           break;
        case 7:
           cout<<"Exited..."<<endl;
           break;
        default:
            cout<<"Enter a valid choice"<<endl;
            break;
        }
    }while(choice!=7); 
   return 0;
    
}



 

