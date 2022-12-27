#include <stdio.h>

int main(void) {

    char ch[30] = "score : ";
    char ch2[30] = "300";

    int i = 0;
    while (ch[i] != '\0')
        i++;

    for (int j = i; ch2[j - i] != '\0'; j++)
        ch[j] = ch2[j - i];

    printf("%s\n", ch);

    return 0;
}