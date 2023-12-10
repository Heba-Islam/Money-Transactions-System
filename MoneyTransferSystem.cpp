#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Transaction {
    string From;
    string To;
    float Amount;
};

struct Card {
    string CardHolder;
    string CardNumber;
    string Expiry;
    string Type;
    int CVV;
    int PIN;
    float Balance;
};

struct User{
    string Name;
    string Email;
    string PhoneNumber;
    string Password;
    string IPA;
    float Wallet;
};

class IAccountServices 
{
public:
    virtual void CreateAccount() = 0;
    virtual void ListUsers() = 0;
    virtual void AddCard() = 0;
    virtual void SendMoney() = 0;
    virtual float ShowBalance() = 0;
    virtual float ShowBalance(Card mycard) = 0;
    virtual void CollectMoney() = 0; 
};

class Account 
{
public:
    User user;
    vector<Card>myCards;
};

class AccountServices : public IAccountServices
{
public:
    Account myAccount;
     void CreateAccount();
     void ListUsers();
     void AddCard();
     void SendMoney();
     void CollectMoney();
     float ShowBalance();
     float ShowBalance(Card mycard);
     class UserNotFound {};
};

vector<Transaction>allTransactions;
vector<User>Users;
vector<AccountServices*> allUsers;

class ICardPayment
{
public:
    virtual bool SendMoney(Card& card,float amount) = 0;
};

class VisaCard : public ICardPayment
{
public:
    bool SendMoney(Card& mycard,float amount){
        float _deduction = 1.02 * amount;
        if (mycard.Balance - _deduction >= 0)
        {
            mycard.Balance -= _deduction;
            cout <<"\t"<< _deduction << " has been deducted of your card : " << mycard.CardNumber << "\n";
            return 1;
        }
        else
            cout << "Balance limit exceeded\n";
        return 0;
    }
};

class MasterCard : public ICardPayment{
public:
    bool SendMoney(Card& mycard, float amount){
        float _deduction = 1.05 * amount;
        if (mycard.Balance - _deduction >= 0)
        {
            mycard.Balance -= _deduction;
            cout << "\t" << _deduction << " has been deducted of your card : " << mycard.CardNumber << "\n";
            return 1;
        }
        else
            cout << "Balance limit exceeded\n";
        return 0;
    }
};


bool ValidatePassword(string password)
{
    if (password.size() < 4){
        cout << "password is too short, create one that's at least 4 charchters\n";
        return 0;
    }
    return 1;
}

bool ValidateIPA(string ipa){
    if (ipa.size() < 4)
        return 0;
    for (int i = 0; i <Users.size() ; i++){
        if (ipa == Users[i].IPA)
            return 0;
    }
    return 1;
}

bool validatePIN(Card crd, int pass) {
    return crd.PIN == pass;
}

User EnterUser(){
    User user;
    string name1,name2, email, password, phonenumber;
    cout << "Enter your first and second name : ";
    cin >> name1 >> name2;
    user.Name = name1+" "+name2;

    cout << "\t\nEmail address : ";
    cin >> email;
    user.Email = email;

    cout << "\t\nCreate a Password: ";
    cin >> password;
    while (!ValidatePassword(password)){
        cout << "Invalid password\n";
        cin >> password;
    }
    user.Password = password;

    cout << "\t\nPhone Number : ";
    cin >> phonenumber;
    user.PhoneNumber = phonenumber;

    string ipa="";
    do
    {   cout << "Create a unique handle for your IPA :\n";
        cin >> ipa;
        ipa += "@IPA";
    } while (!ValidateIPA(ipa));
    user.IPA = ipa;
    cout << "\t\nyour IPA : " << ipa << "\n";

    user.Wallet = 0.0;

    return user;
}

Card EnterCard(){
    Card crd;
    cout << "\n\tenter cardholder's first and second name :  ";
    string name1, name2;
    cin >> name1 >> name2;
    crd.CardHolder = name1 + " " + name2;

    cout << "\n\tenter card's number : ";
    string crdNum;
    cin >> crdNum;
    crd.CardNumber = crdNum;

    cout << "\n\tenter card's CVV : ";
    int cvv;
    cin >> cvv;
    crd.CVV = cvv;

    cout << "\n\tenter '1' if the card is a visa card,\t'2' if it's a master card : ";
    int type;
    string cardType;
    cin >> type;
    if (type == 1)
        cardType = "visa";
    else
        cardType = "mastercard";
    crd.Type = cardType;

    cout << "\n\tenter card's expiry date : ";
    string date;
    cin >> date;
    crd.Expiry = date;

    cout << "\n\tenter card's PIN : ";
    int pin;
    cin >> pin;
    crd.PIN = pin;

    crd.Balance = 100.0;
    cout << "\n";
    return crd;
}

void AccountServices::CreateAccount(){
    myAccount.user = EnterUser();
    Users.push_back(myAccount.user);
}

AccountServices* SignIn()
{
        if (!allUsers.size())
        {
            cout << "No other users in the system..\n";
            return nullptr;
        }
        else {
            try
            {
                AccountServices* myAccountx = NULL;
                cout << "Enter your IPA: ";
                string myIPA;
                cin >> myIPA;
                bool found = 0;
                string myPassword;
                for (int i = 0; i < allUsers.size(); i++) {
                    if (allUsers[i]->myAccount.user.IPA == myIPA) {
                        myAccountx = allUsers[i];
                        myPassword = allUsers[i]->myAccount.user.Password;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    throw AccountServices::UserNotFound();
                else
                {
                    cout << "Enter your password: ";
                    string myPass;
                    cin >> myPass;
                    while (myPass != myPassword) {
                        cout << "Incorrect password\nreenter the password or type \"X\" to cancel logging in\n";
                        cin >> myPass;
                        if (myPass == "X")
                        {
                            myAccountx = NULL;
                            break;
                        }
                    }
                    return myAccountx;
                }
            }
            catch (AccountServices::UserNotFound) {
                cout << "this user isn't registered in the system\n";
                return NULL;
            }
        }      
    }

void AccountServices::ListUsers()
{

        if (Users.size() <= 1) {
            cout << "No other useres in the system..\n";
        }
        else {
            for (int i = 0; i < Users.size(); i++) {
                if (Users[i].IPA != myAccount.user.IPA) {
                    cout << Users[i].Name << " " << Users[i].IPA << "\n";
                }
            }
        }
    
}

void AccountServices::AddCard(){
    Card myCard = EnterCard();
    myAccount.myCards.push_back(myCard);
}

void AccountServices::SendMoney(){

        if (Users.size() <= 1)
        {
            cout << "No other useres in the system..\n";
        }
        else {
            cout << "choose the IPA of the user you want to send the money to : \n\t";
            for (int i = 0; i < Users.size(); i++) {
                if (Users[i].IPA != myAccount.user.IPA) {
                    cout << Users[i].IPA << "\n\t";
                }
            }
            string toIPA;
            cin >> toIPA;
            cout << "enter the amount you want to transfer\n";
            float myAmount;
            cin >> myAmount;

            cout << "enter a card's number from the following : \n\t";
            string number;
            for (int i = 0; i < myAccount.myCards.size(); i++) {
                cout << myAccount.myCards[i].CardNumber << "\n";
            }
            cin >> number;
            Card myCard;
            ICardPayment* card;
            int idx = 0;
            for (int i = 0; i < myAccount.myCards.size(); i++) {
                if (number == myAccount.myCards[i].CardNumber) {
                    idx = i;
                    break;
                }
            }

            int pin = -100, cnt = 0;
            do {
                cout << "Enter PIN: ";
                cin >> pin;
                cnt++;
            } while (pin != myAccount.myCards[idx].PIN && cnt < 4);

            if (cnt > 4) {
                cout << "permitted attempts exceded..\n";
            }
            else {
                bool isSuccessful = 0;
                if (myAccount.myCards[idx].Type == "mastercard")
                    card = new MasterCard;
                else
                    card = new VisaCard;
                isSuccessful = card->SendMoney(myAccount.myCards[idx], myAmount);
                if (isSuccessful) {
                    for (int i = 0; i < Users.size(); i++) {
                        if (toIPA == Users[i].IPA) {
                            Users[i].Wallet += myAmount;
                        }
                    }
                    cout << "\tSuccessful payment..\n";
                    allTransactions.push_back({ myAccount.user.IPA,toIPA,myAmount });
                }
            }
        }          
}

float AccountServices::ShowBalance(){
    if (!myAccount.myCards.size()){
        cout << "you haven't added any cards\n";
        return -1;
    }
    cout << "enter a card's number from the following : \n\t";
    string number;
    for (int i = 0; i < myAccount.myCards.size(); i++) {
        cout << myAccount.myCards[i].CardNumber << "\n\t";
    }
    cin >> number;
    int idx = 0;
    for (int i = 0; i < myAccount.myCards.size(); i++) {
        if (number == myAccount.myCards[i].CardNumber) {
            idx = i;
            break;
        }
    }
    int pin = -100, cnt = 0;
    do {
        cout << "Enter PIN: ";
        cin >> pin;
        cnt++;
    } while (pin != myAccount.myCards[idx].PIN && cnt < 4);

    if (cnt == 4){
        cout << "permitted attempts exceded..\n";
        return -1;
    }
    else {
        return  myAccount.myCards[idx].Balance;      
    }  
    return 0;
}

float AccountServices::ShowBalance(Card mycard)
{
    if (myAccount.myCards.size())
        return myAccount.myCards[0].Balance;
    else
        return -1;
}

void AccountServices::CollectMoney()
{
    bool _myMoney = 0;
    vector <pair<string, float>>myDues;
    for (int i = 0; i < allTransactions.size(); i++) {
        if (allTransactions[i].To == myAccount.user.IPA) {
            myDues.push_back({ allTransactions[i].From,allTransactions[i].Amount });
        }
    }

    if (!myDues.size()){
        cout << "No money to collect! \n";
        return;
    }

    for (int j = 0; j < myAccount.myCards.size(); j++) {
        cout << "card number : " << myAccount.myCards[j].CardNumber << "    ID : " << j << "\n";
    }

    for (int i = 0; i < myDues.size(); i++){ 
        cout << "Amount = " << myDues[i].second << " From : " << myDues[i].first << "\n";
        cout << "\nenter the ID of the card you want to add the money to\n";
        int num;
        cin >> num;
        int pin = -100, cnt = 0;
        do {
            cout << "Enter PIN: ";
            cin >> pin;
            cnt++;
        } while (pin != myAccount.myCards[num].PIN && cnt < 4);

        if (cnt == 4){
            cout << "permitted attempts exceded..\n";
            continue;
        }
        myAccount.myCards[num].Balance += myDues[i].second;
        cout << "Successrul transaction...\n";
        myDues.erase(myDues.begin()+i);
    }
}


int main()
{
    int com = 1;
    AccountServices* myAccount1=new AccountServices;
    cout << "Enter \t1: to sign up\n\t2: to sign in\n\t";
    cin >> com;
    if (com == 2) {
        cout << "The system doesn't have any registered accounts... create a new account now!\n\n";
    }
    myAccount1->CreateAccount();
    while (com!=8)
    {
        cout << "Enter a number in range [1:8]\t\n";
        cout << "\t1: to add a new card\t\n";
        cout << "\t2: to show balance of a card\t\n";
        cout << "\t3: to show balance of your Default card\t\n";
        cout << "\t4: to transfer money\t\n";
        cout << "\t5: to collect money\t\n";
        cout << "\t6: to list all the users in the system\t\n";
        cout << "\t7: to log out\t\n";
        cout << "\t8: to terminate the program\t\n";
        cin >> com;
        if (com == 1) 
        {
            system("cls");
            myAccount1->AddCard();
        }
        else if (com == 2)
        {
            system("cls");
            float amount = myAccount1->ShowBalance();
            if(amount<0){
                cout << "\tEmpty card\n";
            }
            else {
                cout <<"\t" << amount << "\n";
            }
        }
        else if (com == 3)
        {
            if(myAccount1->myAccount.myCards.size())
            system("cls");
            float amount = myAccount1->ShowBalance(myAccount1->myAccount.myCards[0]);
            if (amount < 0) {
                cout << "\tEmpty card\n";
            }
            else {
                cout << "\t" << amount << "\n";
            }
        }
        else if (com == 4)
        {
            system("cls");
            myAccount1->SendMoney();
        }
        else if (com == 5)
        {
            system("cls");
            myAccount1->CollectMoney();
        }
        else if (com == 6)
        {
            system("cls");
            myAccount1->ListUsers();
        }
        else if (com == 7)
        {
            system("cls");
            AccountServices* myTempAccount = myAccount1;
            allUsers.push_back(myTempAccount);
            myAccount1 = new AccountServices;
            cout << "Enter \t1: to sign up\n\t2: to sign in\n\t3:to terminate the program\n\t";
            int x;
            cin >> x;
            if (x == 1)
                myAccount1->CreateAccount();
            else if (x == 2)
                myAccount1 = SignIn();
            else
                return 0;
        }
    }
 
}

