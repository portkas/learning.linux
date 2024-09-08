#include <stdio.h>
#include "calc.h"

int main(int argc, char *argv[]){
   int a, b;
   a = (int)*argv[1];
   b = (int)*argv[2];
   printf("%d + %d = %d\n", a, b, add(a,b));
   printf("%d - %d = %d\n", a, b, div(a,b));   
   return 0;
}
