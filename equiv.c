#include <stdio.h>
#include <stdlib.h>  // malloc을 위해 stdlib.h를 포함

#define MAX_SIZE 24
#define IS_FULL(ptr) (!(ptr))
#define FALSE 0
#define TRUE 1

struct node {
    int data;
    struct node *link;
};

int main(void) {
    short int out[MAX_SIZE];
    struct node *seq[MAX_SIZE], *x, *y, *top;  // top을 포인터로 선언
    int i, j, n;

    printf("Enter the size (<= %d): ", MAX_SIZE);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    while (i >= 0 && j >= 0) {  // 입력 종료 조건 수정
        x = (struct node *)malloc(sizeof(struct node));
        if (IS_FULL(x)) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        x->data = j;
        x->link = seq[i];
        seq[i] = x;

        x = (struct node *)malloc(sizeof(struct node));
        if (IS_FULL(x)) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        x->data = i;
        x->link = seq[j];
        seq[j] = x;

        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    for (i = 0; i < n; i++) {
        if (!out[i])  // 방문 여부 검사
            continue;

        printf("\nNew Class: %5d ", i);
        out[i] = FALSE;
        x = seq[i];
        top = NULL;  // top 초기화

        for (;;) {
            while (x) {
                j = x->data;
                if (out[j]) {
                    printf("%5d", j);
                    out[j] = FALSE;

                    // top에 현재 노드를 저장하고 x를 다음으로 이동
                    y = x->link;
                    x->link = top;
                    top = x;
                    x = y;
                } else {
                    x = x->link;
                }
            }
            if (!top)
                break;

            // top에서 데이터 추출
            x = seq[top->data];
            top = top->link;
        }
    }

    return 0;
}
