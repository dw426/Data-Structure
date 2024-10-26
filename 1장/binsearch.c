#include <stdio.h>

int compare(int a, int b){
    if (a < b) return -1;
    if (a == b) return 0;
    return 1;
}

int binsearch(int list[], int key, int left, int right){
    int middle;
    while (left <=right){
        middle = (left + right) / 2;
        switch(compare(list[middle], key)) {
            case -1:
                left = middle + 1;
                break;
            case 0:
                return middle;
            case 1:
                right = middle - 1;
        }
    }
    return -1;
}

int main(){
    int list[] = {1,3,5,7,9,11,13,15,17,19};
    int n = sizeof(list) / sizeof(list[0]);
    int key;

    printf("찾고 싶은 숫자를 입력하세요: ");
    scanf("%d", &key);

    int result = binsearch(list, key, 0, n-1);

    if (result != -1){
        printf("숫자 %d는 인덱스 %d에 있습니다.\n", key, result);
    }
    else{
        printf("숫자 %d는 배열에 없습니다.\n", key);
    }
    return 0;
}