#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE		100
#define MAX_PATTERN_SIZE	100

int cmpCnt;		// string 문자의 비교 횟수
int failure[MAX_PATTERN_SIZE];

// knuth,morris, pratt의 문자열 매칭 알고리즘
int pMatch(char *str, char *pat)
{
	int i = 0, j = 0;	// i: str 인덱스, j: pat 인덱스
	int lenS = strlen(str);
	int lenP = strlen(pat);

 	printf("Matching starts\n");
	printf("string=\"%s\": len=%d.\n",str, lenS);
	printf("   pat=\"%s\": len=%d.\n",pat, lenP);

	while ((i < lenS) && (j < lenP))
	{
		printf("str[%d] ? pat[%d] --> ", i, j); // debug
	   	if (str[i] == pat[j])
	   	{	// 만약일치되다면
			printf("o\n"); // debug
		   	i++;
		   	j++;
			cmpCnt++;
	   	}
	   	else if (j == 0)
	   	{	// j가0인경우에는, 즉, pat첫문자와 불일치면
			printf("x -> 1st char not match -> i++\n"); // debug
		   	i++;
			cmpCnt++;
	   	}
	   	else
	   	{	// 현재 pat 문자와 불일치하면 
			// 현재 문자 앞 문자의 실패위치 다음 문자와 비교 계속
			// (str의 i는 변화 없음) 
			printf("x"); // debug
		   	j = failure[j-1]+1;
		   	printf (" --> j = %d\n", j); // debug
	   	}
	}
	return ((j == lenP) ? (i - lenP) : -1); // i는 pat의 끝 문자보다 +1이 되어 있음
}

void Fail(char *pat)
{
	// 패턴의실패함수를구현
	int j = 0;
	int len = strlen(pat);
	char *tPat;
	
	tPat = (char *)malloc(len+1);
	
	printf("pat's length is %d.\n", len);  // debug
	failure[j] = -1; // 첫문자의 failure값은 -1
	int i = 0;
	for (j = 1; j < len; j ++)
	{
		i = failure[j-1];
			// i는 현재 문자 앞 문자의 failure값(실패위치)
			// 만일, 현재 문자 앞문자의 실패위치 다음 문자와 현재 문자가 같으면
			// 		현재 문자의 failure 값은 현재 문자 앞 문자의 failure값+1이된다.
			// 만일 같지 않으면,
			//       다시 현재 문자 앞문자의 실패위치 문자의 실패위치를 구하고
			//       (즉, i = failure[i] 후)
			//       그 다음 문자와의 비교를 계속한다.(단, i가 0이상일 때)
		strncpy(tPat, pat, j+1);
		printf("\"%s\" pat[%d] --> i=%d --> ", tPat, j, i); // debug
		while ((pat[j] != pat[i+1]) && (i >= 0))
		{
			printf("pat[%d] != pat[%d] --> ", j, i+1); // debug
			i = failure[i];
			printf("i=%d --> ", i); // debug
		} 
		if (pat[j] == pat[i+1])
		{
			printf("pat[%d]==pat[%d] --> ", j, i+1); // debug
			failure[j] = i+1;
		} 
		else
		{
			printf("pat[%d]!=pat[%d] --> ", j, i+1); // debug
			failure[j] = -1;
		} 
		printf("f[%d]=i+1=%d\n", j, failure[j]); // debug
	}
	printf("\n  Index : ");
	for (i = 0; i < len; i++)
		printf("%3d", i);
	printf("\nPattern : ");
	for (i = 0; i < len; i++)
		printf("%3c", pat[i]);
	printf("\nFailure : ");
	for (i = 0; i < len; i++)
		printf("%3d", failure[i]);
	printf("\n\n");
}

int simpleFind(char *string, char *pat)
{   // string의 각 문자를 순차적으로 비교
	int i, j, k, lasts = strlen(string)-1, lastp = strlen(pat)-1;

	for (i = 0; i <= lasts; i++) {
		if (string[i] == pat[0]) {
			cmpCnt++;
			for (j = i+1, k = 1; k <= lastp; j++, k++)
			{
				if (string[j] != pat[k])
					break;
				cmpCnt++;
			}
			if (k > lastp) return i;	 // 성공
		}
		cmpCnt++;
	}
	return -1;
}

int nFind(char *string, char *pat)
{   // pat의 마지막 문자를 먼저 검사한 후 처음부터 검사 시작
	int i, j, lasts = strlen(string)-1, lastp = strlen(pat)-1;
	int start = 0, endmatch = lastp;

	for (i=0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
		{
			cmpCnt++;
			for (j=0, i=start; j<lastp && string[i]==pat[j]; i++, j++)
				cmpCnt++;
			if (j >= lastp)
				cmpCnt--;
		}
		cmpCnt++;
		if (j == lastp)	return start;	// 성공
	}
	return -1;
} 

void main()
{
	char string[] = "abcabcabcabacabacabab";
	char pattern[] = "abacaba"; // "abbaabbbaaaaabab"; // "abacababa"; // "ababaa"; // "abcabcabd";
	// char string[] = "Hi students, 2 students of all students study hard.";
	// char pattern[] = "study";
	// char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	// char pattern[] = {"aaaaaab"}; 
	int result = 0;

	printf("\nString[%d] = %s\n", (int)strlen(string), string);
	printf("Pattern[%d] = %s\n\n", (int)strlen(pattern), pattern);

	cmpCnt = 0;
	result = simpleFind(string, pattern);
	printf("Simple's result: %d --> %d comparisons of %d chars.\n", 
		   result, cmpCnt, (int)strlen(string));

	cmpCnt = 0;
	result = nFind(string, pattern);
	printf("nFind's result: %d --> %d comparisons of %d chars.\n", 
		   result, cmpCnt, (int)strlen(string));

	// cmpCnt = 0;
	// Fail(pattern);
	// result = pMatch(string, pattern);
	// printf("KMP result: %d --> %d comparisons of %d chars.\n", 
	// 	   result, cmpCnt, (int)strlen(string));
}

