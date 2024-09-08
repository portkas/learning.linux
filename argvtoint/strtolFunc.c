#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
   if(argc > 1){
      long num = strtol(argv[1], NULL, 10);
      printf("%ld\n", num);
   }else{
      printf("not enough\n");
   }
   return 0;
}
