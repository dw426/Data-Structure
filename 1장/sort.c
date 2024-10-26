#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
        }
        SWAP(list[i], list[min], temp);
    }
}

void printArray(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int n = 10; // 배열 크기
    int arr[n];

    // 난수 생성을 위한 시드 설정
    srand(time(NULL));

    // 무작위 값으로 배열 초기화
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // 0부터 99까지의 랜덤한 정수
    }

    printf("원래 배열: ");
    printArray(arr, n);

    sort(arr, n);

    printf("정렬된 배열: ");
    printArray(arr, n);

    return 0;
}
