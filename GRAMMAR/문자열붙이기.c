#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	char str[30];
	int score = 300;
	sprintf(str, "score : %d", score);
	printf("%s", str);

	return 0;
}