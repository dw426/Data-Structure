#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct Student {
    char name[20];
    int id;
    double grade;
};

int main() {
    struct Student students[10]; // 학생의 수를 최대 10명으로 가정
    int n;

    printf("학생의 수를 입력하세요 : "); // 학생 수를 3명 이상 하기 위해서 따로 빼주었습니다.
    scanf("%d", &n);

    if (n < 3) {
        printf("학생 수는 3명 이상이어야 합니다.\n"); // 학생 수가 3명 이하이면 프로그램 실행을 멈춘다.
        return 1;
    }

    // 학생 정보 입력
    for (int i = 0; i < n; i++) {
        printf("\n학생 %d의 정보를 입력하세요:\n", i + 1);
        printf("이름: ");
        getchar(); // 입력 버퍼 비우기
        fgets(students[i].name, sizeof(students[i].name), stdin);

        printf("학번: ");
        scanf("%d", &students[i].id);

        printf("학점: ");
        scanf("%lf", &students[i].grade);
    }

    // 가장 높은 학점을 가진 학생 찾기
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (students[i].grade > students[maxIndex].grade) {
            maxIndex = i;
        }
    }

    printf("\n가장 높은 학점을 받은 학생:\n");
    printf("이름: %s\n", students[maxIndex].name);
    printf("학번: %d\n", students[maxIndex].id);
    printf("학점: %.2f\n", students[maxIndex].grade);

    return 0;
}
