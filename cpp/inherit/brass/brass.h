#ifndef BRASS_H_
#define BRASS_H_
#include <string>
class Brass{
private:
    std::string fullName;   // 账户持有人全名
    long acctName;          // 账户号码
    double balance;         // 账户余额

public:
    Brass(const std::string &s = "Nullbody", long an = -1,
            doubele bal = 0.0);
    void Deposit(double amt);           // 存款
    virtual void Withdraw(double amt);  // 取款
    double Balance() const;             // 查询账户余额
    virtual void ViewAcct() const;      // 查询账户信息
    virtual ~Brass() {}
};

class BrassPlus : public Brass{
private:
    double maxLoan;     // 透支上限
    double rate;        // 透支贷款利率
    double owesBank;    // 当前的透支金额
public:
    BrassPlus(const std::string &s = "Nullbody", long an = -1,
                double bal = 0.0, double ml = 500, 
                double r = 0.11125);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.11125);
    virtual void ViewAcct() const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) {maxLoan = m;}
    void ResetRate(double r) {rate = r;}
    void ResetOwes() {owesBank = 0;}
};

#endif