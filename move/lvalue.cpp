#include<iostream>
#include<string>
#include<vector>

void swapp(int *p, int *q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void swapr(int &p, int &q){
    int temp;
    temp = p;
    p = q;
    q = temp;
}

double crefcude(const double &ra){
    return ra*ra*ra;
}

double refcude(double &ra){
    return ra*ra*ra;
}

void leftValue()
{
    int a = 10;
    int b = 20;
    std::cout<<"address of a : "<<&a<<" = "<<a<<std::endl;
    std::cout<<"address of b : "<<&b<<" = "<<b<<std::endl;

    swapr(a, b);
    std::cout<<"address of a : "<<&a<<" = "<<a<<std::endl;
    std::cout<<"address of b : "<<&b<<" = "<<b<<std::endl;
}

void refer(){
    double side = 3.0;
    double c1 = crefcude(side + 1.0);
    std::cout<<c1<<std::endl;
}

const int* clone(int &p){
    int *newguy = new int;
    *newguy = p;
    return newguy;
}

int main(){
    int n = 10;
    const int *guy = clone(n);
    std::cout<< *guy <<std::endl;
    delete guy;
    guy = nullptr;
    return 0;
}