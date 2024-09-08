#include <stdio.h>
#include "calc.h"

int main(int argc, char *argv[]){
   int a, b;
   sscanf(argv[1], "%d", &a);
   sscanf(argv[2], "%d", &b);
   printf("%d + %d = %d\n", a, b, add<int>(a,b));
   printf("%d - %d = %d\n", a, b, div<int>(a,b));   
   return 0;
}
