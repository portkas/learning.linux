#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue.h>
const int MIN_PER_HR = 60;

bool newcustomer(double x);

int main(){
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    std::srand(std::time(0));

    cout << "案例研究：希瑟银行自动取款机" << endl;
    cout << "输入queue最大数量: ";
    int  qs;
    cin >> qs;
    Queue line(qs);     // 队列对象，用于管理顾客

    cout << "输入模拟时间(hours): ";
    int hour;
    cin >> hour;
    long cyclelimit = MIN_PER_HR * hour;

    cout << "输入平均每小时客户的数量: ";
    double perhour;
    cin >> perhour;
    double min_per_cust = MIN_PER_HR / perhour; // 顾客到达的平均间隔时间（分钟）

    Item temp;              // 新顾客
    long turnaways = 0;     // 因队列已满而被拒绝的顾客数量
    long customers = 0;     // 加入队列的顾客数量
    long served = 0;        // 被服务的顾客数量
    long sum_line = 0;      // 队列长度的累积值
    int wait_time = 0;      // 自动取款机空闲的时间
    long line_wait = 0;     // 顾客在队列中等待的总时间

    cout << "***开始模拟***" << endl;
    for(int cycle = 0; cycle < cyclelimit; ++cycle){
        if(newcustomer(min_per_cust)){ // 有客户来
            if(line.isfull()){
                turnaways++;
            }else{
                customers++;
                temp.set(cycle);
                line.enqueue(temp);
            }
        }

        if(wait_time <= 0 && !line.isempty()){
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }

        if(wait_time > 0){
            wait_time--;
        }

        sum_line += line.queuecount();
    }


    if(customers > 0){
        cout << "共来客户: " << customers << endl;
        cout << "共服务客户: " << served << endl;
        cout << "拒之门外的客户: " << turnaways << endl;
        cout << "平均队列的长度: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << (double)sum_line/cyclelimit << endl;
    }else{
        cout << "没有客户" << endl;
    }
    cout << "***模拟结束***" << endl;
    return 0;
}

// 根据平均间隔时间 x 生成新顾客
// 这个函数的数学基础是泊松分布
// 泊松分布用于描述在固定时间间隔内发生某事件的次数；
// x表示每x分钟平均有一个顾客到达；
// 每分钟有一个顾客到达的概率是1/x；
bool newcustomer(double x){
    // 将随随机数的范围调整到[0-x]
    // 如果每2分钟来一个人，那么每分钟有人到来的概率为1/2
    // 如果每3分钟来一个人，那么每分钟有人到来的概率为1/3
    // 如果每x分钟来一个人，那么每分钟有人到来的概率为1/x
    return (std::rand() * x / RAND_MAX < 1);
}