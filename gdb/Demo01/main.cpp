#include <iostream>
using namespace std;
   
void print_foo(int v) {
  int i = v + 5;
  i = i + 3;
  cout << "i == " << i << endl;
}
   
int main() {
  int a = 0;
  a += 1;
  a += 2;
  print_foo(a);
  return 0;
}