#include <stdio.h>
#include <string.h>

#define SWAP(a, b, temp) { temp = a; a = b; b = temp; }

void perm(char *list, int i, int n) {
    int j, temp;
    if (i == n) {
        for (j = 0; j < n; j++) {
            printf("%c", list[j]);
        }
        printf("\n");
    } else {
        for (j = i; j < n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i + 1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}

int main() {
    char str[100];
    
    printf("순열을 생성할 문자열을 입력하세요: ");
    scanf("%s", str);

    int n = strlen(str);
    perm(str, 0, n);
    
    return 0;
}
