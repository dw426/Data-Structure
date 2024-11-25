#include <stdio.h>
#include <stdlib.h>

#define MAX_Q_SIZE 5

typedef int element;   // 큐에 저장할 데이터 타입 정의
element queue[MAX_Q_SIZE];
int front = 0, rear = 0;  // 초기화

void queue_full() {
    printf("Queue is full!\n");
}

element queue_empty() {
    printf("Queue is empty!\n");
    return -1;  // -1을 빈 큐의 반환값으로 설정
}

void addq(element item) {
    int next_rear = (rear + 1) % MAX_Q_SIZE;
    if (next_rear == front) {  // 큐가 가득 찬 경우
        queue_full();
        return;
    }
    rear = next_rear;
    queue[rear] = item;
}

element deleteq() {
    if (front == rear) {  // 큐가 비어 있는 경우
        return queue_empty();
    }
    front = (front + 1) % MAX_Q_SIZE;
    return queue[front];
}

void print_queue() {
    printf("Queue: ");
    int i = (front + 1) % MAX_Q_SIZE;
    while (i != (rear + 1) % MAX_Q_SIZE) {
        printf("%d ", queue[i]);
        i = (i + 1) % MAX_Q_SIZE;
    }
    printf("\n");
}

int main() {
    addq(10); print_queue();
    addq(20); print_queue();
    addq(30); print_queue();
    addq(40); print_queue();

    deleteq(); print_queue();
    addq(50); print_queue();
    addq(60); print_queue();

    deleteq(); print_queue();
    deleteq(); print_queue();

    return 0;
}
