#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p,s) if (!((p)=malloc((s)))) { \
		fprintf(stderr, "Insuffient Memory"); }

typedef struct node* NodeP;
struct node
{
	int 	data;
	struct node * link;
};

void printList(NodeP np, int choice)
{
	if (!np)
	{
		printf("\nfirst-> ^ ");
		if (choice == 2)
			printf("<-end");
		printf("\n");
		return;
	}
	else 
	{
		if (np->link)
			if (choice == 1)
				printf("\nfirst->[ %d |+]->", np->data);
			else
				printf("\nfirst->[ %d |+]->", np->data);
		else
			if (choice == 1)
				printf("\nfirst->[ %d |^]\n", np->data);
			else
				printf("\nfirst->[ %d |^]<-end\n", np->data);
	}
	np = np->link;			
	while (np)
	{
		if (np->link)
			printf("[ %d |+]->", np->data);
		else
			if (choice == 2)
				printf("[ %d |^]<-end\n", np->data);
			else
				printf("[ %d |^]\n", np->data);
		np = np->link;
	}
}

int main()
{
	NodeP first, end, temp;
	int digit, choice, delMode = 0; 
		// choice: 1: 스택 형식 2: 큐 형식
		// delMode: 스택 또는 큐에서 삭제할 경우
	char buf[12];
	
	while(1)
	{
		printf("\nChoose 1 or 2(1: Insert Front, 2: Insert Rear, 0: Stop) ");
		scanf("%d", &choice);
		if (!choice) break;

		first = end = NULL;
		printList(NULL, choice);
		printf("\nInput a number(-1: Stop/'d': pop or delQ): ");
		scanf("%s", buf);
		if (!strcmp(buf, "d"))	// "d" 입력시 스택 또는 큐에서 삭제
			delMode = 1;
		else
			digit = atoi(buf);	// 입력 받은 문자열을 정수로 변환 (stdlib.h)
		while (digit != -1)
		{
			if (digit == -1) break;
			if (delMode)		// 스택의 pop or 큐의 deleteQ 
			{					// 스택, 큐 모두 제일 앞쪽이 삭제됨
				if (first)
				{
					NodeP temp = first;
					printf("%d deleted", first->data);
					first = first->link;
					free(temp);
				}
				else
				{
					printf("Empty!!");
					end = NULL;
				}
				delMode = 0;
			}
			else
			{
				MALLOC(temp, sizeof(*temp));
				temp->data = digit;
				if (choice == 1)	// 스택 형식에서 push
				{
					temp->link = first;
					first = temp;
				}
				else if (choice == 2) 	// 큐 형식에서 addQ
				{
					temp->link = NULL;
					if (!end)
						first = end = temp;
					else
					{
						end->link = temp;
						end = temp;
					}
				}
			}
			printList(first, choice);
			printf("\nInput a number(-1: Stop/'d': pop or delQ): ");
			scanf("%s", buf);
			if (!strcmp(buf, "d"))
				delMode = 1;
			else
				digit = atoi(buf);
		}
	}
}
