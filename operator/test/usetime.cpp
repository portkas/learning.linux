#include <iostream>
#include "mytime.h"

int main(){
    using std::cout;
    using std::endl;
    Time planning;
    Time coding(2, 40);
    Time fixing(5, 55);
    Time total;
    Time optotal;

    cout<<"planning time = ";
    planning.Show();
    cout<<planning<<endl;

    cout<<"coding time = ";
    coding.Show();
    cout<<coding<<endl;

    cout<<"fixing time = ";
    fixing.Show();
    cout<<fixing<<endl;

    total = coding.Sum(fixing);
    cout<<"total time = ";
    total.Show();
    cout<<total<<endl;

    // 1
    optotal = coding + fixing;
    cout<<"optotal time = ";
    optotal.Show();
    cout<<optotal<<endl;

    return 0;
}