#include <stdio.h>
#include <stdlib.h>
#include <string>
typedef  int (*callBackFunc)(char* name);
int playBegin(char* name)
{
    printf("视频开始解码，即将出现画面....\n");
    return 1;
}
int playEnd(char* name)
{
    printf("视频播放结束....\n");
    return 1;
}
int play(callBackFunc fn, char* name)
{
    return (*fn)(name);
}
int main()
{
   char pName[1024] = "色即是空";
   //视频播放开始....
   play(playBegin,pName);//playBegin函数指针作为参数传递
   //视频播放中....
   //视频播放结束....
   play(playEnd,pName);//playEnd函数指针作为参数传递
   return 0;
}