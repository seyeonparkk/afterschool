#include <stdio.h>

int main(void) {

    char yn;
    int seat[10] = { 0 };
    int seat_num;

    while (1) {
        printf("�¼��� �����Ͻðڽ��ϱ�?(y �Ǵ�n) ");
        scanf_("%c", &yn);

        if (yn == 'n') return 0;

        printf("\n-------------------------------\n");
        printf(" 1 2 3 4 5 6 7 8 9 10\n");
        printf("-------------------------------\n");

        for (int i = 0; i < 10; i++) {
            printf(" %d", seat[i]);
        }
        printf("\n");

        printf("�� ��° �¼��� �Է��Ͻðڽ��ϱ�? ");
        scanf_s("%d", &seat_num);

        if (seat[seat_num - 1] == 1) {
            printf("�̹� ����� �ڸ��Դϴ�.\n");
            continue;
        }

        seat[seat_num - 1] = 1;
        for (int i = 0; i < 10; i++) {
            printf("%2d", seat[i]);
        }
        printf("\n����Ǿ����ϴ�.\n\n");
    }

    return 0;
}