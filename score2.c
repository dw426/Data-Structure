#include <stdio.h>
#include <stdlib.h> 

int main() {
    int n;
    float *scores;

    printf("학생 수를 입력하세요: ");
    scanf("%d", &n);

    scores = (float*)malloc(n * sizeof(float));
    if (scores == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("학생의 점수를 입력하세요: ");
        scanf("%f", &scores[i]);
    }

    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }
    float average = sum / n;

    printf("\n평균은 : %.2f\n", average);

    free(scores);

    return 0;
}
