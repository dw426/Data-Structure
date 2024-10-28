#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} Node;

int main() {
    Node *ptr = NULL, *tail, *temp;
    int i, n, s = 0;

    // 입력 받기
    scanf("%d", &n);

    // 연결 리스트 생성
    for (i = 1; i <= n; i++) {  // i <= n으로 수정
        temp = (Node *)malloc(sizeof(Node));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        temp->data = i;
        temp->link = ptr;
        ptr = temp;
    }

    // 리스트에서 홀수 노드 삭제
    tail = ptr;
    while (tail && tail->link) {
        temp = tail->link;
        if (temp->data % 2) {
            tail->link = temp->link;
            free(temp);  // 삭제된 노드 메모리 해제
        } else {
            tail = tail->link;
        }
    }

    // 리스트의 합 계산
    for (; ptr; ptr = ptr->link)
        s += ptr->data;

    printf("%d\n", s);

    return 0;
}
