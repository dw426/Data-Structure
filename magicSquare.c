#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE  15  		// Square의 최대 크기

void main(void)	// 순차적으로 magic square 작성
{
	static int square[MAX_SIZE][MAX_SIZE];
	int i, j, row, column;	// 배열의 첨자들
	int size;			// Square의 크기로 입력 받음.
	int count;			// 1부터 size * size까지 증가

	printf("Enter the size of the square(odd only): ");
	scanf("%d", &size);
	if (size < 1 || size > MAX_SIZE + 1) {	// 입력 오류 검사
		fprintf(stderr, "Error! Size is out of range\n");
		exit(1);
	}
	if (!(size % 2)) {		// square의 크기는 홀수여야 함.
		fprintf(stderr, "Error! Size is even\n");
		exit(1);
	}
	for (i = 0; i < size; i++)		// square의 모든 원소를
		for (j = 0; j < size; j++)	// 0으로 초기화
			square[i][j] = 0;	
	
	i = 0;			// i는 현재 행 번호
	j = (size-1) / 2;		// j는 현재 열 번호
	square[i][j] = 1;	// 첫 행의 중간부터 시작

	for (count = 2; count <= size * size; count++) {
		row = (i-1 < 0) ? (size-1) : (i-1); 		// 위쪽 행
		column = (j-1 < 0) ? (size-1) : (j-1); 	// 왼쪽 열
		if (square[row][column]) {    
			i = (++i) % size;	// 못갈 경우, 아래로
		}
		else {		// 갈 수 있을 경우,  i와 j를 대각선 위로.
			i = row;
			j = column;
		}
		square[i][j] = count; // 변경된 위치에 다음 수 추가
	}
	// 생성된 magic square를 출력
	
	printf("\n Magic Square of size %d : \n\n", size);
	for (i = 0; i < size; i++) {
		 for (j = 0; j < size; j++)
			printf("%4d", square[i][j]);
		printf("\n");		// 한 줄에 한 행씩 출력
	}
	printf("\n\n");
}
