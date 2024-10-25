#include <stdio.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int width;
int out = 0;

void printStr(char s[], int i, int j, int n)
{
	char buf[20] = {'\0'}, *t=buf;
	int l=0;
	
	if (i > 0 && out)
		for (int k = 0; k < i; k++)
			printf("%-*s", width, " ");
	
	out = 0;
	if (j < 0)
		l=sprintf(t+=l, "[%d,-]", i);
	else
		l=sprintf(t+=l, "[%d,%d]", i, j);
	for (int k = i; k <= n; k++)
		l=sprintf(t+=l, "%c", s[k]);
	printf("%-*s", width, buf);
}

void perm(char *list, int i, int n)
{
	int j, temp;
	
  	if (i == n)
	{
		/* Debug */ printStr(list, i, -1, n);
		printf("--> ");
		for (int k = 0; k <= n; k++)
			printf("%c", list[k]);
		printf("\n");
		out = 1;
	}
  	else  
	{ 
     	for ( j = i; j <= n; j++)
		{
			SWAP(list[i], list[j], temp);
			/* Debug */ printStr(list, i, j, n);
			perm(list, i+1, n);
			SWAP(list[i], list[j], temp);
    	}
  	}
} 

void main()
{
	char s[10];
	
	printf("Input a string to use(3~6 chars): ");
	scanf("%s", s);
	width = strlen(s)+6;
		
	perm(s, 0, strlen(s)-1);
	printf("\n");
}
