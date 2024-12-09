#include <stdio.h>
  
int func(int *p)
{
    *p = 0;
}
  
int main()
{
    func(NULL);
    return 0;
}