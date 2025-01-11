#include <iostream>
#include "brass.h"
using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

Brass::Brass(const string &s, long an, double bal){
    fullName = s;
    acctName = an;
    balance = bal;
}

void Brass::Deposit(double amt){
    if (amt < 0)
        cout << "Negative deposit not allowed; "
             << "deposit is cancelled.\n";
    else
        balance += amt;
}

void Brass::Withdraw(double amt){
    // 保存当前的输出格式
    format initialState = setFormat();

    // 设置输出精度为 2 位小数，并保存当前的精度
    // 用于设置std::cout的精度为2位小数。这个函数返回设置前的精度值；
    // precision方法是std::ostream类的成员函数，用于设置流的精度
    precis prec = cout.precision(2);
    if (amt < 0)
        cout << "Withdrawal amount must be positive; "

             << "withdrawal canceled.\n";
    else if (amt <= balance)
        balance -= amt;
    else
        cout << "Withdrawal amount of $" << amt
             << " exceeds your balance.\n"
             << "Withdrawal canceled.\n";
    
    // 恢复输出格式和精度
    restore(initialState, prec);
}

double Brass::Balance() const{
    return balance;
}

void Brass::ViewAcct() const{
    format initialState = setFormat();
    precis prec = cout.precision(2);
    cout << "Client: " << fullName << endl;
    cout << "Account Number: " << acctNum << endl;
    cout << "Balance: $" << balance << endl;
    restore(initialState, prec);
}

BrassPlus::BrassPlus(const string &s, long an, double bal,
                    double ml, double r):Brass(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double r)
            :Brass(ba)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct() const{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    Brass::ViewAcct();
    cout << "Maximum loan: $" << maxLoan << endl;
    cout << "Owed to bank: $" << owesBank << endl;
    cout.precision(3);
    cout << "Loan Rate: " << 100 * rate << "%\n";
    restore(initialState, prec); 
}

void BrassPlus::Withdraw(double amt){
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    // 如果 amt <= bal，直接调用基类Brass的Withdraw方法进行取款操作
    if(amt <= bal){
        Brass::Withdraw(amt);
    // 表示取款金额可以通过账户余额和可用贷款额度覆盖
    }else if(amt <= bal + maxLoan - owesBank){
        // 计算需要的贷款金额advance
        double advance = amt - bal;
        // 更新欠银行的贷款金额owesBank
        owesBank += advance*(1.0 + rate);
        cout << "Bank advance: $" << advance << endl;
        cout << "Finance charge: $" << advance * rate << endl;
        // 将贷款金额存入账户
        Deposit(advance);
        // 再次调用基类Brass的Withdraw(amt)方法进行取款操作
        Brass::Withdraw(amt);
    }else{
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    }
    restore(initialState, prec);
}


// 设置输出格式为固定小数点表示法，并返回当前的格式化标志
format setFormat(){
    return cout.setf(std::ios_base::fixed, 
                std::ios_base::floatfield);
}

void restore(format f, precis p){
    // 恢复输出格式
    // 将 cout 的格式恢复到之前保存的格式化标志 f
    cout.setf(f, std::ios_base::floatfield);

    // 恢复输出精度
    // 将 cout 的精度恢复到之前保存的精度 p
    cout.precision(p);
}