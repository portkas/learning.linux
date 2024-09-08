#include <stdio.h>
#include "calc.h"

int main(){
   int a = 10;
   int b = 5;
   printf("%d + %d = %d\n", a, b, add(a,b));
   printf("%d - %d = %d\n", a, b, div(a,b));   
   return 0;
}
