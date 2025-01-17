// randwalk.cpp -- using the Vector class
// compile with the vect.cpp file
#include <iostream>
#include <cstdlib>      // rand(), srand() prototypes
#include <ctime>        // time() prototype
#include "myvector.h"
int main()
{
    using namespace std;
    using VECTOR::Vector;
    srand(time(0));     // seed random-number generator
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;
    cout << "Enter target distance (q to quit): ";
    // target是一个double类型的变量，而q是一个字符，无法转换为double类型。
    // 当输入操作失败时，cin会设置错误状态标志如failbit
    // 导致 while(cin >> target)循环终止，从而退出循环
    // 事实上，输入任何字符如a,b,c,d都会导致循环终止；
    while (cin >> target)
    {
        cout << "Enter step length: ";
        if (!(cin >> dstep))
            break;

        while (result.magval() < target)
        {
            direction = rand() % 360;
            step.reset(dstep, direction, Vector::POL);
            result = result + step;
            steps++;
        }
        cout << "After " << steps << " steps, the subject "
            "has the following location:\n";
        cout << result << endl;
        result.polar_mode();
        cout << " or\n" << result << endl;
        cout << "Average outward distance per step = "
            << result.magval()/steps << endl;
        steps = 0;
        result.reset(0.0, 0.0);
        cout << "Enter target distance (q to quit): ";
    }
    cout << "Bye!\n";

    // 清除输入流中的错误状态，并丢弃输入流中直到下一个换行符为止的所有字符
    cin.clear();                // 清除输入流 cin 的错误状态标志，以便后续可以继续从输入流中读取数据
    while (cin.get() != '\n')   // 使用cin.get()从输入流中逐个读取字符，直到遇到换行符 \n
        continue;
    cin.get();                  // 在前面的循环中，当遇到换行符时，循环结束，但换行符本身仍然留在输入流中。使用cin.get()可以读取并丢弃这个换行符
    return 0; 
}