#include <stdio.h>
int main(){
	int c;
	printf("EOF is %d\n", EOF);
	while(c = getchar()!= EOF)
		printf("%d\n",c);
	printf("%d - at EOF\n",c);
}
