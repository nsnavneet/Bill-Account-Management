#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include<conio.h>

using namespace std;

class Bill_datatype
{
public:
    vector<string> Item_name;
    long number_of_items;
    vector<double> price;
    vector<int> Qty;
    vector<double> Amount;
    string Date;
    long int Bill_No;
    long int Account_No;

public:
    Bill_datatype() {}
    Bill_datatype(long int Bill_No, long int Account_no)
    {
        this->Bill_No = Bill_No;
        this->Account_No = Account_no;
    }
    long int get_Account_no()
    {
        return Account_No;
    }
    long int get_Billno()
    {
        return Bill_No;
    }
    void set_Billno(long int bil_no)
    {
        this->Bill_No = Bill_No;
    }
    friend ofstream& operator<<(ofstream& ofs, Bill_datatype& B);
    friend ifstream& operator>>(ifstream& ifs, Bill_datatype& B);
    friend ostream& operator<<(ostream& os, Bill_datatype& B);
    friend istream& operator>>(istream& is, Bill_datatype& B);
};
/*
ofstream& operator<<(ofstream& ofs, Bill_datatype& B)
{
    ofs << B.Account_No << endl;
    ofs << B.Bill_No << endl;
    ofs << B.Date << endl;
    ofs << B.number_of_items << endl;
    for (int i = 0; i < B.number_of_items; i++)
    {
        ofs << B.Item_name[i] << endl;
        ofs << B.price[i] << endl;
        ofs << B.Qty[i] << endl;
        B.Amount[i] = B.price[i] * B.Qty[i];
        ofs << B.Amount[i] << endl;
    }
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Bill_datatype& B)
{
    string iname;
    double amount, p;
    int qty;
    ifs >> B.Account_No;
    ifs >> B.Bill_No;
    ifs >> B.Date;
    ifs >> B.number_of_items;
    for (int i = 0; i < B.number_of_items; i++)
    {
        ifs >> iname;
        B.Item_name.push_back(iname);
        ifs >> p;
        B.price.push_back(p);
        ifs >> qty;
        B.Qty.push_back(qty);
        amount = p * qty;
        ifs >> amount;
        B.Amount.push_back(amount);
    }
    return ifs;
}
*/
ofstream& operator<<(ofstream& ofs, Bill_datatype& B)
{
    ofs << B.Account_No << "," << B.Bill_No << "," << B.Date << "," << B.number_of_items << endl;
    for (int i = 0; i < B.number_of_items; i++)
    {
        ofs << B.Item_name[i] << "," << B.price[i] << "," << B.Qty[i] << "," << B.Amount[i] << endl;
    }
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Bill_datatype& B)
{
    string line;
    if (getline(ifs, line))
    {
        stringstream ss(line);
        string field;

        getline(ss, field, ',');
        B.Account_No = stol(field);

        getline(ss, field, ',');
        B.Bill_No = stol(field);

        getline(ss, field, ',');
        B.Date = field;

        getline(ss, field, ',');
        B.number_of_items = stoi(field);

        B.Item_name.clear();
        B.price.clear();
        B.Qty.clear();
        B.Amount.clear();

        for (int i = 0; i < B.number_of_items; i++)
        {
            if (getline(ifs, line))
            {
                stringstream item_ss(line);

                getline(item_ss, field, ',');
                B.Item_name.push_back(field);

                getline(item_ss, field, ',');
                B.price.push_back(stod(field));

                getline(item_ss, field, ',');
                B.Qty.push_back(stoi(field));

                getline(item_ss, field, ',');
                B.Amount.push_back(stod(field));
            }
        }
    }
    return ifs;
}

ostream& operator<<(ostream& os, Bill_datatype& B)
{
    os << "\tAccount number: " << B.Account_No;
    os <<"\t\tBill number: " << B.Bill_No;
    os <<"\t\tDate: " << B.Date<<endl<<endl;
    for (int i = 0; i < B.number_of_items; i++)
    {
        os <<i+1<<") Item name: " << B.Item_name[i] <<"\t\t";
        os<<i+1<<") Price: " << B.price[i] << "\t\t";
        os << i + 1 << ") Qty: " << B.Qty[i] << "\t\t";
        B.Amount[i] = B.price[i] * B.Qty[i];
        os << i + 1 << ") Amount: " << B.Amount[i] << endl;
    }
    return os;
}
istream& operator>>(istream& is, Bill_datatype& B)
{
    is >> B.Account_No;
    is >> B.Bill_No;
    is >> B.Date;
    for (int i = 0; i < B.number_of_items; i++)
    {
        is >> B.Item_name[i];
        is >> B.price[i];
        is >> B.Qty[i];
        B.Amount[i] = B.price[i] * B.Qty[i];
        is >> B.Amount[i];
    }
    return is;
}
class Company_Account_datatype
{
private:
    string company_name;
    string Gst_no;
    long int Account_no;
    static long int Next_Account_no;

public:
    map<long int, Bill_datatype> B_map;
    Company_Account_datatype() {}
    Company_Account_datatype(string company_name, string Gst_no)
    {
        Next_Account_no++;
        this->Account_no = Next_Account_no;
        this->company_name = company_name;
        this->Gst_no = Gst_no;
    }
    static void setLastAccountno(long int Accno);
    static long int getLastAccountno();
    long int getAccno()
    {
        return Account_no;
    }
    long int get_total_number_of_bills()
    {
        return B_map.size();
    }
    void set_Bill(int billno, int Accno)
    {
        system("CLS");
        Bill_datatype B(billno, Accno);
        string iname;
        double amount, p;
        int qty;
        cout << "\t\t\tEnter the Date: ";
        cin >> B.Date;
        cout << endl;
        cout << "\t\t\t\tEnter the Number of Items in Bill: ";
        cin >> B.number_of_items;
        cout << endl;
        for (int i = 1; i <= B.number_of_items; i++)
        {
            cout << "\t\t\t\t\tEnter the name of " << i << " Item: ";
            cin >> iname;
            B.Item_name.push_back(iname);
            cout << endl;
            cout << "\t\t\t\t\tEnter the Price of Item: ";
            cin >> p;
            B.price.push_back(p);
            cout << endl;
            cout << "\t\t\t\tEnter the Qantity: ";
            cin >> qty;
            B.Qty.push_back(qty);
            cout << endl;
            amount = p * qty;
            B.Amount.push_back(amount);
        }
        B_map.insert(pair<long int, Bill_datatype>(billno, B));
        system("CLS");
        cout << endl << "\t\t\t\tThe Bill is created: " << endl;
        cout << B << endl;
    }
    friend ofstream& operator<<(ofstream& ofs, Company_Account_datatype& c);
    friend ifstream& operator>>(ifstream& ifs, Company_Account_datatype& c);
    friend ostream& operator<<(ostream& os, Company_Account_datatype& c);
    friend istream& operator>>(istream& is, Bill_datatype& B);
};

// Initialize static member

long int Company_Account_datatype::Next_Account_no = 0;

void Company_Account_datatype::setLastAccountno(long int Accno)
{
    Next_Account_no = Accno;
}

long int Company_Account_datatype::getLastAccountno()
{
    return Next_Account_no;
}

ofstream& operator<<(ofstream& ofs, Company_Account_datatype& c)
{
    ofs << c.Account_no << "," << c.company_name << "," << c.Gst_no << endl;
    return ofs;
}
ifstream& operator>>(ifstream& ifs, Company_Account_datatype& c)
{
    string line;
    getline(ifs, line); // Read the entire line

    stringstream ss(line);
    string token;

    // Split the line into tokens using commas as delimiters
    getline(ss, token, ','); // Read Account_no
    c.Account_no = stol(token);

    getline(ss, token, ','); // Read company_name
    c.company_name = token;

    getline(ss, token, ','); // Read Gst_no
    c.Gst_no = token;

    return ifs;
}

/*
ofstream& operator<<(ofstream& ofs, Company_Account_datatype& c)
{
    ofs << c.Account_no << endl;
    ofs << c.company_name << endl;
    ofs << c.Gst_no << endl;
    return ofs;
}
ifstream& operator>>(ifstream& ifs, Company_Account_datatype& c)
{
    ifs >> c.Account_no;
    ifs >> c.company_name;
    ifs >> c.Gst_no;
    return ifs;
}
*/
ostream& operator<<(ostream& os, Company_Account_datatype& c)
{
    os << "\t\t\t\tAccount Number:" << c.Account_no << endl;
    os << "\t\t\t\tCompany Name:" << c.company_name << endl;
    os << "\t\t\t\tGst No.:" << c.Gst_no << endl;
    return os;
}

class Manage
{
private:
    map<long int, Company_Account_datatype> mp;

public:
    Manage()
    {
        Company_Account_datatype ca;
        ifstream ifs("Account.csv");
        if (!ifs)
        {
            // Handle the case where the CSV file doesn't exist or cannot be opened.
            // You can create an empty CSV file or take appropriate action here.
            return;
        }

        // Assuming the CSV file format is: Account_No,Company_Name,GST_No
        string line;
        while (!ifs.eof()) // this things read the file extra time
        {
            ifs >> ca;
            mp.insert(pair<long int, Company_Account_datatype>(ca.getAccno(), ca));
        }
        ifs.close();

        ifstream ifs_for_bills("Bill.csv");
        Bill_datatype b;
        map<long int, Company_Account_datatype>::iterator it;
        it = mp.begin();
        while (!ifs_for_bills.eof())
        {
            Bill_datatype b;
            ifs_for_bills >> b;
            it = mp.find(b.Account_No);
            if (it != mp.end())
            {
                it->second.B_map.insert(pair<long int, Bill_datatype>(b.Bill_No, b));
            }
        }
    }

    Company_Account_datatype OpenAccount(string comname, string gstno)
    {
        ofstream outfile;
        Company_Account_datatype cad(comname, gstno);
        mp.insert(pair<long int, Company_Account_datatype>(cad.getAccno(), cad));

        outfile.open("Account.csv", ios::trunc);

        map<long int, Company_Account_datatype>::iterator itr;
        for (itr = mp.begin(); itr != mp.end(); itr++)
        {
            outfile << itr->second;
        }
        outfile.close();
        return cad;
    }
    Company_Account_datatype create_Bill(long int Accno)
    {
        ofstream outfile_for_bill;
        Company_Account_datatype c;
        Bill_datatype B;
        map<long int, Company_Account_datatype>::iterator it;
        it = mp.find(Accno);
        if (it == mp.end())
        {
            cout << "Sorry can't find the account. First make an account for that company." << endl;
        }
        else
        {
            c = it->second;
            int billno = it->second.get_total_number_of_bills();
            it->second.set_Bill(billno + 1, Accno);

            // Open the CSV file for bill data
            outfile_for_bill.open("Bill.csv", ios::out | ios::app); // Append mode
            map<long int, Bill_datatype>::iterator itb;
            if (outfile_for_bill.is_open())
            {
                // Write bill data in CSV format
                outfile_for_bill << B.Account_No << "," << B.Bill_No << "," << B.Date << "," << B.number_of_items << endl;
                for (it = mp.begin(); it != mp.end(); it++)
                {
                    for (itb = it->second.B_map.begin(); itb != it->second.B_map.end(); itb++)
                    {
                        outfile_for_bill << itb->second << endl;
                    }
                }

                outfile_for_bill.close();
            }
            else
            {
                cout << "Failed to open Bill.csv for writing." << endl;
            }
        }

        return c;
    }

    void show_all_account()
    {
        map<long int, Company_Account_datatype>::iterator itr;
        cout << "**************************************************************************************" << endl;
        for (itr = mp.begin(); itr != mp.end(); itr++)
        {
            cout << "\t\t\t\tAccouts : " << itr->first << "\n"
                << itr->second << endl;
            cout << "**************************************************************************************" << endl;
        }
    }
    void show_bill_of_account(long int accono)
    {
        map<long int, Company_Account_datatype>::iterator itr;
        map<long int, Bill_datatype>::iterator itb;
        itr = mp.find(accono);
        cout << "**************************************************************************************" << endl;
        if (itr == mp.end())
        {
            cout << "No Account Found Enter the correct Account number" << endl;
            return;
        }
        else
        {
            for (itb = itr->second.B_map.begin(); itb != itr->second.B_map.end(); itb++)
            {
                cout << "Account Number:" << itb->second.Account_No << "\t\t\t\tBill : " << itb->first << "\t\t\tDate: " << itb->second.Date << "\n";
                cout << "\t\t\t\tNumber of Items in a Bill: " << itb->second.number_of_items << "\n\n";
                cout << "\tItem Name\t|" << "\tPrice\t|" << "\tQty.\t|" << "\tAmount\t||" << endl;
                for (int i = 0; i < itb->second.number_of_items; i++)
                {
                    cout << i + 1 << ")\t" << itb->second.Item_name[i] << "\t\t|" << "\t" << itb->second.price[i] << "\t|" << "\t" << itb->second.Qty[i] << "\t|" << "\t" << itb->second.Amount[i] << "\t||" << endl;
                }
                cout << "**************************************************************************************" << endl;
            }
        }
    }
    ~Manage()
    {
        ofstream outfile;
        outfile.open("Account.csv", ios::trunc);
        map<long int, Company_Account_datatype>::iterator itr;
        for (itr = mp.begin(); itr != mp.end(); itr++)
        {
            outfile << itr->second << endl;
        }
        outfile.close();

        ofstream outfile_for_bills;
        outfile_for_bills.open("Bill.csv", ios::trunc);
        map<long int, Bill_datatype>::iterator itb;

        for (itr = mp.begin(); itr != mp.end(); itr++)
        {
            for (itb = itr->second.B_map.begin(); itb != itr->second.B_map.end(); itb++)
            {
                outfile_for_bills << itb->second.Account_No << "," << itb->second.Bill_No << "," << itb->second.Date << "," << itb->second.number_of_items << ",";
                for (int i = 0; i < itb->second.number_of_items; i++)
                {
                    outfile_for_bills << itb->second.Item_name[i] << "," << itb->second.price[i] << "," << itb->second.Qty[i] << "," << itb->second.Amount[i];
                    if (i < itb->second.number_of_items - 1) {
                        outfile_for_bills << ",";
                    }
                }
                outfile_for_bills << endl;
            }
        }
    }
};

    int main()
    {
        Manage m;
        Company_Account_datatype c;
        string cname, gst;
        long int accno;
        int choice;
        do
        {
            cout << endl
                << "\n\n\n\t\t\t\tSelect One option below : " << endl;
            cout << endl
                << "\t\t\t\t1 Open An Account                    press 1" << endl;
            cout << endl
                << "\t\t\t\t2 Create bill                        press 2" << endl;
            cout << endl
                << "\t\t\t\t3 Show All Accounts                  press 3" << endl;
            cout << endl
                << "\t\t\t\t4 Show All Bills of The Accounts     press 4" << endl;
            cout << endl
                << "\t\t\t\t5 Quit                               press 5" << endl;
            cout << "\n\t\t\t\tEnter Choice given: ";
            cin >> choice;
            system("CLS");
            switch (choice)
            {
            case 1:
                cout << "\n\n\t\t\t\tEnter the Company Name: ";
                cin >> cname;
                cout << "\n\n\t\t\t\tEnter the GST Number: ";
                cin >> gst;
                c = m.OpenAccount(cname, gst);
                system("CLS");
                cout << "\t\t\t\tCongo your Account is created:" << endl;
                cout << c << endl;
                cout << "Press any key to continue";
                _getch();
                system("CLS");
                break;
            case 2:
                cout << "\n\n\n\t\t\t\tEnter the Account Number: ";
                cin >> accno;
                c = m.create_Bill(accno);
                cout << c << endl;
                cout << "Press any key to continue";
                _getch();
                system("CLS");
                break;
            case 3:
                m.show_all_account();
                cout << endl;
                cout << "Press any key to continue";
                _getch();
                system("CLS");
                break;
            case 4:
                cout << "\n\n\n\t\t\t\tEnter the Account Number: ";
                cin >> accno;
                m.show_bill_of_account(accno);
                cout << endl;
                cout << "Press any key to continue";
                _getch();
                system("CLS");
                break;
            default:
                cout << "\t\t\t\tEnter the correct choice :)";
                exit(0);
            }
        } while (choice > 0 && choice < 6);
        return 0;
    }
