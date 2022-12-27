#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	char str[30] = "score : ";
	int score = 300;
	char str2[30];
	//정수를 문자열로(변환할 정수,적용대상,진수)
	itoa(score, str2, 10);

	stract(str, str2);
	printf("%s", str);

	return 0;
}