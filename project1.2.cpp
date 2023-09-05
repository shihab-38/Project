#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposite() const;
    char rettype() const;
};

void account::create_account()
{
    cout << "\n Enter the account No. : ";
    cin >> acno;
    cout << "\n\n Enter the name of the account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n Enter type of the account(C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n Enter the Initial amount (>=500 for Saving and >=1000 for current. : ";
    cin >> deposit;
    cout << "\n\n Account Created......";

   cout<<  "\n\nPress any key for main menu...... ";
}

void account::show_account() const
{
    cout << "\n Account No. " << acno;
    cout << "\n Account Holder Name : ";
    cout << name;
    cout << "\n Type of Account : " << type;
    cout << "\n Balance amount : " << deposit;
   // cout<<  "\n\nPress any key for main menu: \n";
}

void account ::modify()
{
    cout << "\n Account No.. : " << acno;
    cout << "\n Modify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount: ";
    cin >> deposit;

    cout<<  "\n\nPress any key for main menu...... ";
}

void account::dep(int x)
{
    deposit += x;
    //cout<<  "\n\nPress any key for main menu: \n";

}

void account::draw(int x)
{
    deposit -= x;
    //cout<<  "\n\nPress any key for main menu: \n";
}
void account ::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account ::retacno() const
{
    return acno;
}

int account ::retdeposite() const
{
    return deposit;
}

char account ::rettype() const
{
    return type;
}
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposite_withdraw(int, int);
void intro();

int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n \t MAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSITE AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05.ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\08. EXIT";
        cout << "\n\n\t Select your Option(1-8)  ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\t Enter the account No. : ";
            cin >> num;
            deposite_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\t Enter The account No : ";
            cin >> num;
            deposite_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\t Enter the account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;

        case '6':
            cout << "\n\n\t Enter the accont No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\n\t Enter The account No. : ";
            cin >> num;
            modify_account(num);
            break;

        case '8':
            cout << "\n\n\t Thanks for using bank managment system .";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();

    } while (ch != '8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios ::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any key...";
        return;
    }
    cout << "\n BALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
    {
        cout << "\n\n Account number does not exist";
    }
    cout<<  "\n\nPress any key for main menu...... ";
}
void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios ::out);
    if (!File)
    {
        cout << "File could not open !! Press any key....";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n Enter the New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Update";
            cout<<  "\n\nPress any key for main menu...... ";
            found = true;
        }
    }
    File.close();
    if (found == false)
    {
        cout << "\n\n Record Not Found ";
    }
}
void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any key....";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\t Record Deleted ";
    cout<<  "\n\nPress any key for main menu...... ";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any key...";
        return;
    }
    cout << "\n\n\t ACCOUNT HOLDER LIST\n\n";
    cout << "==========================================\n";
    cout << "A/c no.       NAME       Type     Balance\n";
    cout << "===========================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
   cout<<  "\n\nPress any key for main menu...... ";
}

void deposite_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios ::out);
    if (!File)
    {
        cout << "File could not be open !! Press any key....";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n To deposite Amount: ";
                cout << "\n\nEnter the amount to be deposited:: ";
                cin >> amt;
                ac.dep(amt);
               found=true;
            }
            if (option == 2)
            {
                cout << "\n\n To Withdraw Amount: ";
                cout << "\n\n\t Enter the amount to be withdraw: ";
                cin >> amt;
                int bal = ac.retdeposite() - amt;
                if (bal < 500 && ac.rettype() == 'S' || (bal < 1000 && ac.rettype() == 'C'))
                {
                    cout << "Insufficience balance.";
                }
                else
                    ac.draw(amt);
                    //break;
                    found=true;
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated.";
            cout<< "Press any key for main menu......";
            found == true;
        }
    }
    File.close();
    if (found == false)
    {
        cout << "\n\n Record not found";
    }
}
void intro()
{
    cout << "\n\n\t   BANK";
    cout << "\n\tMANAGMENT";
    cout << "\n\t  SYSTEM";
    cout << "\n\n   MADE BY : Md. Shihab Hossain";
    cout << "\n\n     Student of BSMRSTU" <<endl;
    cout<<  "\n\nPress any key for main menu...... ";
    cin.get();
}