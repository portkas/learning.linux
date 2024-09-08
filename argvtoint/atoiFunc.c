#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  if(argc > 1){
     int num = atoi(argv[1]);
     printf("%d\n", num);
  }else{
     printf("please input one argv!\n");
  }
  return 0;
}
