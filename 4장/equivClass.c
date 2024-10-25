#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if (!((p)=malloc((s)))) { \
		fprintf(stderr, "Insuffient Memory"); }

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
typedef struct node {
	int data;		// 원소, 정수형의 데이터만 입력된다고 가정
   	nodePointer link;   
} node;
typedef struct pair {
	int i; int j;
} pair;

pair eqs[] = {{0,4},{3,1},{6,10},{8,9},{7,4},{6,8},{3,5},{2,11},{11,0}};
int Neqs = sizeof(eqs)/sizeof(pair);

int top = -1;
nodePointer Stack[MAX_SIZE];

void push(nodePointer np){
	Stack[++top] = np;
}

nodePointer pop(){
	return Stack[top--];	
}

void main(void)
{	
	short int  out[MAX_SIZE];
   	nodePointer  seq[MAX_SIZE], x, y; // top;
	int i, j, n=12;
   	// printf("Enter the size (<= %d)  ", MAX_SIZE);
   	// scanf("%d",  &n);
 
 	for (i = 0; i < n; i++) 	// seq[]와 out[] 배열을 초기화
	{   out[i] = TRUE; seq[i] = NULL;  }

/* Phase 1: Input the equivalence pairs: */
	// printf("Enter a pair of numbers (-1 -1 to quit): "); 
	// scanf("%d%d", &i, &j);
   	// while (i >= 0) {	// 음수가 입력되면 리스트 생성 종료
	for (int t = 0; t < Neqs; t++){
		i = eqs[t].i; j = eqs[t].j;
      	MALLOC(x, sizeof(*x));
      	x->data = j; x->link = seq[i]; seq[i] = x; //j를 i 리스트에 추가(스택방식)

      	MALLOC(x, sizeof(*x));
      	x->data = i; x->link = seq[j]; seq[j] = x; //i를 j 리스트에 추가

      	// printf("Enter a pair of numbers (-1 -1 to quit): ");
      	// scanf("%d%d", &i, &j);
	}

 /* Phase 2: output the equivalence classes */
	for (i = 0; i < n; i++) {
 		if (!out[i])		continue;
		printf("\nNew class: %5d", i);	// 새로운 클래스 출력 시작
 		out[i] = FALSE;         	 	// i를 출력하였음.
		x = seq[i]; // top = NULL;        	// 스택을 초기화
       	for ( ; ; ) {		  		// 클래스의 나머지 원소를 찾자
			while (x) {	// x변수로 seq[i] 리스트를 스캔
				j = x->data;
	         	if (out[j]) {	// j가 아직 출력되지 않았다면…
					printf("%5d", j); out[j] = FALSE; // j를 출력한 후,
					push(x); // y = x->link; x->link = top; top = x; x = y;	//add-stack
				} 
       	        x = x->link;
			}		
            if (top == -1) break;	// 현재 클래스의 모든 원소를 출력하였음.
           	x = seq[pop()->data]; // seq[top->data]; top = top->link;           // delete-stack
      	}
	}
	printf("\n");
}
