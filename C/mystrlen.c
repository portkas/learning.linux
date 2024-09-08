#include <stdio.h>

int mystrlen(char s[]){
	int i;
	i = 0;
	while(s[i]!='\0'){
		i++;
	}
	return i;
}

int main(void){
	char s[] = "123456789";
	printf("%d\n",mystrlen(s));
	return 0;
}
