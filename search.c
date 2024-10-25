#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define COMPARE(x,y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)
#define MALLOC(p,s) if (!((p)=malloc((s)))) { \
		fprintf(stderr, "Insuffient Memory"); }

int N, cmpCnt, avgCase = 1;
int trace = 1;

void printArray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int linSearch(int list[], int searchnum, int n)
{	
	int i;
	for (i = 0; i < n; i++)
	{
		cmpCnt++;
		if (searchnum == list[i])
			return i;
	}
	return -1;
}

int binSearch(int list[], int searchnum, int left, int right)
{
   /* list[0]≤list[1]≤ … ≤ list[n-1]에서 searchnum 검색하여
  	   그 위치를 return. 아니면 return -1 */
	int middle;	
  	while (left <= right)
	{
		middle = (left + right)/2;
		cmpCnt++;
   		switch (COMPARE(list[middle], searchnum)) {
     		case  -1: left = middle + 1;
          		  break;
      		case   0: return middle;
      		case   1: right = middle - 1;
   		}
 	}
  	return -1;
}

// recursion 버전
int rBinSearch(int list[], int searchnum, int left, int right)
{
   /* list[0]≤list[1]≤ … ≤ list[n-1]에서 searchnum 검색하여
  	   그 위치를 return. 아니면 return -1 */
	int middle;	
  	if (left <= right)	// 경계 조건
	{
		middle = (left + right)/2;
		cmpCnt++;
   		switch (COMPARE(list[middle], searchnum)) {
     		case  -1: return
				rBinSearch(list, searchnum, middle+1, right);
      		case   0: return middle;
      		case   1: return
		     	rBinSearch(list, searchnum, left, middle-1);
   		}
 	}
  	return -1;
}

void selSort(int list[], int n)
{
	int i, j, min, temp;
	for (i=0; i<n-1; i++) {  // list[i]부터 list[n-1]까지 정렬.
		min = i;	      // i 위치에 들어갈 최소값의 초기화
		for (j=i+1; j<n; j++)
			if (list[j]<list[min])
				min = j;    // 더 작은 것이 있으면 최소값을 이 곳으로…
		SWAP(list[i], list[min], temp);  // 최소값과 i의 내용을 교체
	}
}

int main(void)
{
	int list[] = {26,  5, 77,  1, 61, 11, 59, 15, 48, 19
				  ,79, 43, 22, 82, 13, 92, 33, 25, 9, 12
				  //, 8, 17, 87, 74, 99, 83, 91, 53, 34, 16, 29, 69
				 };
	int n = sizeof(list)/sizeof(int);
	char c;
	int *cumCmps, *sortList, *vList;
	int i, tn, sNum, linFound, binFound, lSum, bSum;
	N = n;

	MALLOC(sortList, n*sizeof(int))
	for (i = 0; i < n; i++)
		sortList[i] = list[i];
	selSort(sortList, n);
	printf("List data (%d개) =>\n  ", n); printArray(list, n);
	printf("sortList data =>\n  "); printArray(sortList, n);
	while (1)
	{
		printf("\nInput a number to search: ");
		scanf("%d", &sNum); getchar();
		if (sNum < 0)
			break;
		cmpCnt = 0;
		linFound = linSearch(list, sNum, n);
		if (linFound < 0)
			printf("[Linear] Key %d is none --> comparison #: %d.\n", sNum, cmpCnt);
		else
			printf("[Linear] Key %d is at list[%d] --> comparison #: %d.\n", sNum, linFound, cmpCnt);	

		cmpCnt = 0;
		binFound = binSearch(sortList, sNum, 0, n-1);
		// binFound = rBinSearch(sortList, sNum, 0, n-1);  // recursion
		if (binFound < 0)
			printf("[Binary] Key %d is none --> comparison #: %d.\n", sNum, cmpCnt);
		else
			printf("[Binary] Key %d is at sortList[%d] --> comparison #: %d.\n", sNum, binFound, cmpCnt);	
	}
}
