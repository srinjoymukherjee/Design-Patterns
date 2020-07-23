/*
Implementation of Adapter Pattern.

Here we have a client called Online Payment. Now we have two kind of payment,
Card Payment and UPI Payment. Card Payment has End Date, but UPI does not have any End Date
*/
#include <string>
#include <iostream>
#include <sstream>

#define SYS_DATE "23/07/2020"
#define DEFAULT_END_DATE "00/00/0000"

using namespace std;

void breakDate(string, int&, int&, int&);
bool validateDate(string);

//Adaptee
class UPI
{
    double m_bal;

    public:
    UPI(double balance){
        m_bal = balance;
    }

    double getBalance(){
        return m_bal;
    }

    void setBalance(double bal)
    {
        m_bal = bal;
    }
};

//Target
class PaymentMethod
{
    public:
    virtual double getBalance() = 0;
    virtual void setBalance(double) = 0;
    virtual string getEndDate() = 0;
};

//Concrete Target
class Card : public PaymentMethod
{
    double m_bal;
    string m_endDate;

    public:
    Card(double balance, string endDate){
        m_bal = balance;
        m_endDate = endDate;
    }

    double getBalance() override
    {
        return m_bal;
    }

    void setBalance(double bal) override
    {
        m_bal = bal;
    }

    string getEndDate() override
    {
        return m_endDate;
    }

};

//Adapter
class UPIAdapter : public PaymentMethod
{
    UPI* m_upi;

    public:
    UPIAdapter(UPI* upi){
        m_upi = upi;
    }

    double getBalance() override
    {
        return m_upi->getBalance();
    }

    string getEndDate() override
    {
        return DEFAULT_END_DATE;
    }

    void setBalance(double amount) override
    {
        m_upi->setBalance(amount);
    }
};

class OnlinePayment
{
    PaymentMethod* m_payment;

    public:
    OnlinePayment(PaymentMethod* payment){
        m_payment = payment;
    }

    bool pay(double amount)
    {
        try{
            double bal = m_payment->getBalance();
            string date = m_payment->getEndDate();

            if(!validateDate(date)){
                throw runtime_error("Wrong End Date\n\n");
            }

            if(amount > bal){
                throw runtime_error("Insufficient Balance\n\n");
            }

            bal -= amount;
            m_payment->setBalance(bal);

            return true;
        }catch(exception &e)
        {
            cout << "Error in Transaction:\t" << e.what();
            return false;
        }
        
    }
};

int main(){
    PaymentMethod* card = new Card(14000.32, "14/09/2020");
    UPI* upi = new UPI(12000.00);
    PaymentMethod* upiAdapter = new UPIAdapter(upi);
    OnlinePayment* onlinePayment1 = new OnlinePayment(card);
    OnlinePayment* onlinePayment2 = new OnlinePayment(upiAdapter);

    cout << "Balance in Card before Transaction:\t";
    cout << card->getBalance() << endl <<endl;

    cout << "Doing Transaction through Card" << endl << endl;
    onlinePayment1->pay(2000.00);

    cout << "Balance in Card after Transaction:\t";
    cout << card->getBalance() << endl << endl;

    cout << "Balance in UPI Account before Transaction:\t";
    cout << upiAdapter->getBalance() << endl << endl;

    cout << "Doing Transaction through UPI" << endl << endl;
    onlinePayment2->pay(2000.50);

    cout << "Balance in UPI Account after Transaction:\t";
    cout << upiAdapter->getBalance() << endl << endl;

    return 0;
}

bool validateDate(string date){
    if(date == DEFAULT_END_DATE){
        return true;
    }

    int d_num, m_num, y_num;
    int d_num_sys, m_num_sys, y_num_sys; 

    breakDate(date, d_num, m_num, y_num);    
    breakDate(SYS_DATE, d_num_sys, m_num_sys, y_num_sys);

    if(y_num > y_num_sys){
        return true;
    }
    else if(y_num == y_num_sys){
        if(m_num > m_num_sys){
            return true;
        }
        else if(m_num == m_num_sys){
            if(d_num > d_num_sys){
                return true;
            }
        }
    }

    return false;
}

void breakDate(string date, int& d_num, 
                int& m_num, int& y_num)
{
    stringstream ss;
    string d, m, y, temp;

    ss << date;

    getline(ss, d, '/');
    getline(ss, m, '/');
    getline(ss, y, '/');

    d_num = atoi(d.c_str());
    m_num = atoi(m.c_str());
    y_num = atoi(y.c_str());
}