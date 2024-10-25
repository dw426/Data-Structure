#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1601
#define ITERATIONS 26
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void printArray(int a[], int n)
{
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void sort(int list[], int n) // Selection Sort
{
	int i, j, min, temp;
	for (i=0; i<n-1; i++) {  // list[i]부터 list[n-1]까지 정렬.
		min = i;	        // i 위치에 들어갈 최소값의 초기화
		for (j=i+1; j<n; j++)  // i+1부터 끝까지 최소값 위치 찾기
			if (list[j]<list[min])
				min = j;    // 더 작은 것이 있으면 최소값을 이 곳으로..
		SWAP(list[i], list[min], temp);  // 최소값과 i의 내용을 교체
	}
}

void main(void)	// 다양한 배열 크기에 대해 
{				// Selection sort의 실행 시간을 측정
	int i, j, position;
	int list[MAX_SIZE];
	int sizelist[] = {0, 10, 20, 30, 40, 50, 60, 70, 80,
	90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
	1100, 1200, 1300, 1400, 1500, 1600};  // 배열의 크기
	clock_t start, stop;	// 시작 시간과 종료 시간
	double duration;		// 경과 시간 = stop – start
	
	printf("    n   time\n-----------------\n");
	for (i = 0; i < ITERATIONS; i++) {  // 26개의 배열 크기
		for (j = 0; j < sizelist[i]; j++)
			list[j] = sizelist[i]-j; // 역순으로 초기에 저장
		
		start = clock();	// 시작 시간 측정
		sort(list, sizelist[i]);	// sort 함수 호출
		stop = clock();	// 종료 시간 측정
		
			// CLK_TCK = 초당 클럭의 수. 환경 변수(for Windows)
			// CLOCKS_PER_SEC(for Linux)
		// duration = ((double) (stop-start)) / CLK_TCK;
		duration = ((double) (stop-start)) / 10000; //CLOCKS_PER_SEC;
		printf("%6d	%f\n", sizelist[i], duration);
	}
}
