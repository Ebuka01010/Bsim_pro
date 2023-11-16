#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

#include "Bank.h"

using namespace std;

double DepositAccount::rate = 6.50;
double totalAccounts = 0.0;

//******************************************************************
// Display Formatting Functions
//******************************************************************


string underline(const string s) {
    return string(s.length(), '-');
}

string center(const string s, const int w) {
    int len = s.length();
    int padding = (w - len) / 2;
    string out;

    // if (len < w) {
        out = string(padding, ' ') + s + string(w - len - padding, ' ');
    // } else {
    //     out = s;
    // }

    return out;
}

string formatNumber(int num) {
    return to_string(num);
}

string formatNumber(float num) {
    stringstream stream;
    stream << fixed << setprecision(2) << num;
    return stream.str();
}

string formatNumber(double num) {
    stringstream stream;
    stream << fixed << setprecision(2) << num;
    return stream.str();
}

string formatNumber(long num) {
    stringstream stream;
    stream << fixed << setprecision(2) << num;
    return stream.str();
}
//******************************************************************
// Basic functions of the BankAccount class
//******************************************************************
inline BankAccount::BankAccount()
{
    accountId = type = updateDate = 0;
    clientName = new char[1];
    balance = 0.0;
}

inline BankAccount::BankAccount(long id, int newType,
                                char * name, long newDate, double newBalance):
        accountId(id), type(newType),
        updateDate(newDate), balance(newBalance)
{
    clientName = new char[strlen(name) + 1];
    strcpy(clientName, name);
}

inline BankAccount::~BankAccount()
{
    if (clientName)
    {
        delete [] clientName;
    }
}

inline void BankAccount::setAccountId(long account)
{
    accountId = account;
}

inline void BankAccount::setType(int newType)
{
    type = newType;
}

inline void BankAccount::setClientName(char * name)
{
    if (clientName)
    {
        delete [] clientName;
    }
    clientName = new char[strlen(name) + 1];
    strcpy(clientName, name);
}

inline void BankAccount::setUpdateDate(long newDate)
{
    updateDate = newDate;
}

inline void BankAccount::setBalance(double newBalance)
{
    balance = newBalance;
}

void BankAccount::print()
{
    cout.setf(ios::fixed);
    cout.precision(2);
    // cout << "  " << accountId << "\t" << type << "\t" << updateDate << " " << balance;
    // cout << center(to_string(accountId), 16) << center(to_string(type), 8) << center(to_string(updateDate), 15) << center(to_string(balance), 11);
    // long vals[4] = {accountId, type, updateDate, balance};
    int col[4] = {16, 8, 16, 12};
    // for(int i = 0; i < 4; i++){
    //     cout << center(formatNumber(vals[i]), col[i]);
    // }
    cout << center(formatNumber(accountId), col[0]) << center(formatNumber(type), col[1]) << center(formatNumber(updateDate), col[2]) << center(formatNumber(balance), col[3]);
    // cout << endl;
}

//******************************************************************
// Basic functions of the DepositAccount class
//******************************************************************
inline DepositAccount::DepositAccount(long id, int newType, char * name,
                                      long newDate, double balanceArg, int nbyear) :
        BankAccount(id, newType, name,
                    newDate, balanceArg), nbyears(nbyear)
{}

inline void DepositAccount::setNbYears(int nbyear)
{
    nbyears = nbyear;
}

void DepositAccount::print()
{
    Bonus();
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    // cout << "\t\t" << nbyears << "\t" << rate << endl;
    cout << center(formatNumber(nbyears), 14) << center(formatNumber(rate), 8) << endl;
}

//******************************************************************
// Functions of the class DepositAccount. It allows to calculate
// the annual bonus on deposit accounts.
// Inputs: Nothing
// Outputs: Nothing
//******************************************************************
void DepositAccount::Bonus()
{
    setBalance(getBalance() + (getBalance()* getRate() * (getNbYears())/36000.00));
}



//******************************************************************
// Basic functions of the LoanAccount class
//******************************************************************
inline LoanAccount::LoanAccount(long id, int newType, char * name,
                                long newDate, double newBalance, int nbyear,
                                double newRate) : BankAccount(id, newType,
                                                              name, newDate, newBalance), nbyears(nbyear), rate(newRate)
{ }

inline void LoanAccount::setNbYears(int nbyear)
{
    nbyears = nbyear;
}

inline void LoanAccount::setRate(double newRate)
{
    rate = newRate;
}

void LoanAccount::print()
{
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    // cout << "\t\t" << nbyears << "\t\t" << rate << endl;
    cout << center(formatNumber(nbyears), 14) << center(formatNumber(rate), 8) << endl;
}

//******************************************************************
// Basic functions of the Transaction class
//******************************************************************
inline Transaction::Transaction(long idTr, int typeTr, long dateTr,
                                int codeTr = 01, double amountTr):
        accountId(idTr), type(typeTr),
        date(dateTr), code(codeTr),
        amount(amountTr)
{ }

inline void Transaction::setAccountId(long compteTr)
{
    accountId = compteTr;
}

inline void Transaction::setType(int typeTr)
{
    type = typeTr;
}

inline void Transaction::setDate(long dateTr)
{
    date = dateTr;
}

inline void Transaction::setCode(int codeTr)
{
    code = codeTr;
}

inline void Transaction::setAmount(double amountTr)
{
    amount = amountTr;
}




//****************************************************************************
// Purpose: Sort a list of bank accounts in ascending order of ids and types.
//
// WARNING: This sort leaves the last account (of id 0) of the list which has
// its position to assure the tests of end of list later !!!
//
// Inputs: listAccount(BankAccount *), a list of bank accounts.
// Outputs: listAccount(BankAccount *), sorted list of bank accounts.
//****************************************************************************
void sortAccounts(BankAccount ** list) {
    //currAccountHold;
    long enf = 0;
    for (int i = 0; list[i]->getAccountId() != enf; i++) {
        for(int j = 0; list[j]->getAccountId() != enf; j++ ){
            if (list[i]->getAccountId() > list[j]->getAccountId()) {
                if(i < j){
                    auto *currAccountHold = list[i];
                    list[i] = list[j];
                    list[j] = currAccountHold;
                }

            }
        }
    }
}


//******************************************************************
// Purpose: This function reads the file 'clients.txt' and builds
// an array containing the different bank accounts of customers.
//
// Inputs: Nothing
// Output: listAccount(type: BankAccount *), the list of bank
//         accounts read from the file 'clients.txt'.
//******************************************************************
BankAccount ** readAccounts()
{
    ifstream inputFile("/Users/ebukaonyeka/CLionProjects/untitled3/clients.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        cout << "File not found !!!" << endl;
        exit(0);
    }

    BankAccount ** listAccounts = new BankAccount*[K_SizeMax];
    if (!listAccounts) {
        cout << "Full memory. !!!" << endl;
        return listAccounts;
    }

    BankAccount ** pAccount = listAccounts;

    long accountRead, dateRead;
    int TypeRead, nbyearRead, counter = 0;
    double balanceRead, RateRead;
    char nameRead[60];

    inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
    inputFile.getline(nameRead, 60);

    while (inputFile && (counter < K_SizeMax - 1)){
        if(TypeRead == 01){
            BankAccount* account = new BankAccount(accountRead, TypeRead, nameRead, dateRead,balanceRead);
            *pAccount = account;
        }else if(TypeRead == 02){
            BankAccount* account = new BankAccount(accountRead, TypeRead, nameRead, dateRead,balanceRead);
            *pAccount = account;
        }else if(TypeRead == 03){
            DepositAccount* account = new DepositAccount(accountRead, TypeRead, nameRead, dateRead,balanceRead,nbyearRead );
            *pAccount = account; // Give rate value in header file if you get an error
        } else{
            double balanceRead2 = balanceRead + ((balanceRead * nbyearRead * RateRead) / 36000);
            LoanAccount* account = new LoanAccount(accountRead, TypeRead, nameRead, dateRead,balanceRead2,nbyearRead, RateRead);
            *pAccount = account;
        }

        inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
        inputFile.getline(nameRead, 60);
        pAccount++;
        counter++;
    }
    *pAccount = new BankAccount();
    inputFile.close();
    return listAccounts;
}





//*****************************************************************************************
// Purpose: This function validates whether the transaction code
//          corresponds to the correct account:
//              - 01 ==> account (01: Check, 02: Savings, 03: Deposit and 04: Loan)
//              - 02 ==> account (01: Check, 02: Savings)
//              - 03 ==> account (01: Check).
//
// Inputs: trans (Type: Transaction) an instance of the Transaction class.
// Outputs: true (Type bool) if the transaction matches one of the accounts listed above.
// false (Type bool) otherwise.
//*****************************************************************************************
Bool BankAccount::validateTransaction(const Transaction trans) const
{
    if ( ( (trans.getCode() == 02) && ( isDepositAccount() || isLoanAccount()) ) ||
         ( (trans.getCode() == 03) && ( isDepositAccount() || isLoanAccount() || isSavingsAccount() ) ) )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}





//******************************************************************************
// Purpose: This function is used to execute the transaction already performed
// (update the balance of an account).
//
// Inputs: trans (Transaction Type), instance of Transaction class
// Outputs: Nothing
//*******************************************************************************
void BankAccount::executeTransaction(const Transaction trans)
{
    if (validateTransaction(trans))
    {
        if (trans.getCode() == 01)    // Deposit
        {
            setBalance(getBalance() + trans.getAmount());
        }
        else
        { if (trans.getCode() == 02)    // Withdrawal
            {
                if (getBalance() >= trans.getAmount())
                { setBalance(getBalance() - (trans.getAmount() + 0.50)); }
                else {cout << " insufficient balance!! " << endl; }
            }
            else 			// Check
            {
                if (getBalance() >= trans.getAmount())
                {
                    setBalance(getBalance() - trans.getAmount());
                }
                else {cout << " insufficient balance!! " << endl; }
            }
        }

    }

}

//***********************************************************************
// Purpose: This function is used to execute a read transaction
// (updating the balance of the loan account).
//
// Inputs: trans (Transaction Type), instance of the Transaction class
// Outputs: Nothing
//***********************************************************************
void LoanAccount::executeTransaction(const Transaction trans)
{
    if (validateTransaction(trans))
    {
        if (trans.getCode() == 01)    // Deposit
        {
            setBalance(getBalance() - trans.getAmount());

        }
    }
}





//*************************************************************************
// Purpose: This function allows to read the file 'transact.txt'
//          and to update the accounts concerned by the transactions read.
//
// Inputs: listAccount (type BankAccount *), the list of bank accounts.
// Output: Nothing.
//*************************************************************************
void updateAccounts(BankAccount ** listAccounts) {
    ifstream inputFile("/Users/ebukaonyeka/CLionProjects/untitled3/transact.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        cout << "File not found !!!" << endl;
        exit(0);
    }
    long TrId, TrDate;
    int TrType, TrCode;
    double TrAmount = 0.0;
    Transaction newTrans;
    inputFile >> TrId >> TrType >> TrDate >> TrCode >> TrAmount ;
    while(inputFile){
        newTrans = Transaction(TrId, TrType, TrDate, TrCode, TrAmount);
        for (int i = 0; listAccounts[i]->getAccountId() != 0; i++){

            if(listAccounts[i]->getAccountId() == TrId && listAccounts[i]->getType() == TrType){
                listAccounts[i]->executeTransaction(newTrans);
            }
        }
    inputFile >> TrId >> TrType >> TrDate >> TrCode >> TrAmount ;
    }
}

//******************************************************************************
// Purpose: This function displays the list of bank accounts for all customers.
//
// Inputs: listAccount (type: BankAccount *), the list of bank accounts.
// Outputs: Nothing
//******************************************************************************


void displayAccounts(BankAccount ** listAccounts)
{
    cout << endl << endl << endl;

    Bool find[K_SizeMax];
    for(int k = 0; k < K_SizeMax; k++) {find[k] = FALSE;} //I don't know the point of this

    cout << "        THE REPORT OF THE BANK ACCOUNTS OF CLIENTS" << endl;
    cout << "        ------------------------------------------" << endl << endl;

    int i = 0;
    long endt = 0;
    char* name;
    long id;
    sortAccounts(listAccounts);
    int flag = 0;
    double sum = 0;
    while(listAccounts[i]->getAccountId()!=endt){
        name = listAccounts[i]->getClientName();
        id = listAccounts[i]->getAccountId();
        if(flag == 0 ){
            cout << "\nClient Name: " << name<< "\n" << endl;
            // cout << "Bank Account Type\tUpdateDate  Balance\t\tNb. Years\tRate" << endl;
            // cout << "------------ ----\t----------  -------\t\t---------\t----" << endl;
            cout << center("Bank Account", 16) << center("Type", 8) << center("Update Date", 16) << center("Balance", 12) << center("Nb. Years", 14) << center("Rate", 8) << endl; 
            cout << center(underline("aBank Accounta"), 16) << center(underline("aTypea"), 8) << center(underline("aUpdate Datea"), 16) << center(underline("aBalancea"), 12) << center(underline("aNb. Yearsa"), 14) << center(underline("aRatea"), 8) << endl;
            if(listAccounts[i]->getType() == 01 || listAccounts[i]->getType() == 02){
                listAccounts[i]->print();
                sum += listAccounts[i]->getBalance();
            }else if(listAccounts[i]->getType() == 03){
                DepositAccount* h = dynamic_cast<DepositAccount*>(listAccounts[i]);
                h->print();
                sum += listAccounts[i]->getBalance();
            }else{
                LoanAccount* h = dynamic_cast<LoanAccount*>(listAccounts[i]);
                h->print();
                sum += listAccounts[i]->getBalance();
            }
        }else{
            if(listAccounts[i]->getType() == 01 || listAccounts[i]->getType() == 02){
                listAccounts[i]->print();
                sum += listAccounts[i]->getBalance();
            }else if(listAccounts[i]->getType() == 03){
                DepositAccount* h = dynamic_cast<DepositAccount*>(listAccounts[i]);
                h->print();
                sum += listAccounts[i]->getBalance();
            }else{
                LoanAccount* h = dynamic_cast<LoanAccount*>(listAccounts[i]);
                h->print();
                sum += listAccounts[i]->getBalance();
            }
        }
        cout<<endl;
        if(listAccounts[i+1]->getAccountId() != id){
            cout<<"\n\t\t TOTAL ACCOUNTS: " << sum <<endl<<endl;
        }
        if(listAccounts[i+1]->getAccountId() == id){
            flag = 1;
        }else{
            flag = 0;
            sum = 0;
        }
        i++;
    }
}




int main()
{
    BankAccount ** list = readAccounts();
    sortAccounts(list);
    displayAccounts(list);
    updateAccounts(list);
    cout << endl << endl;
    cout << "        ************************************************" << endl;
    cout << "        * RE-DISPLAY OF DATA AFTER THE UPDATE *" << endl;
    cout << "        ************************************************" << endl;
    displayAccounts(list);
    cout << endl;

    system("PAUSE");
    return 0;
}
