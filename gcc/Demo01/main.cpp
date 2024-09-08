#include <stdio.h>
#include "calc.h"

int main(int argc, char *argv[]){
   int a, b;
   sscanf(argv[1], "%d", &a);
   sscanf(argv[2], "%d", &b);
   printf("%d + %d = %d\n", a, b, add(a,b));
   printf("%d - %d = %d\n", a, b, div(a,b));   
   return 0;
}
