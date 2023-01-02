#include <stdio.h>

int main(void) {

    char yn;
    int seat[10] = { 0 };
    int seat_num;

    while (1) {
        printf("좌석을 예약하시겠습니까?(y 또는n) ");
        scanf_("%c", &yn);

        if (yn == 'n') return 0;

        printf("\n-------------------------------\n");
        printf(" 1 2 3 4 5 6 7 8 9 10\n");
        printf("-------------------------------\n");

        for (int i = 0; i < 10; i++) {
            printf(" %d", seat[i]);
        }
        printf("\n");

        printf("몇 번째 좌석을 입력하시겠습니까? ");
        scanf_s("%d", &seat_num);

        if (seat[seat_num - 1] == 1) {
            printf("이미 예약된 자리입니다.\n");
            continue;
        }

        seat[seat_num - 1] = 1;
        for (int i = 0; i < 10; i++) {
            printf("%2d", seat[i]);
        }
        printf("\n예약되었습니다.\n\n");
    }

    return 0;
}