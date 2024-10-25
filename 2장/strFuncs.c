#include <stdio.h>
#include <string.h>

int main()
{
	char org[100] = "This is a test.";
	char dest[100],  *s, *token, *delim = " ";
	int  n;
	
	printf("Source string: org = \"%s\"\n", org);
	
	strcpy(dest, org);
	printf("strcpy(dest, org) => dest = \"%s\"\n", dest);
	
	n = 7;
	strncpy(dest, org, n); 
	dest[n] = '\0';  // 수동으로 NULL 문자 입력해야함
	printf("strncpy(dest, org, 8) => dest = \"%s\"\n", dest);
	
	strcat(dest, org);
	printf("strcat(dest, org) => dest = \"%s\"\n", dest);

	n = strcmp(org, "This is not a test.");
	printf("strcmp(org, \"This is not a test.\") => %d\n", n);
	n = strcmp(org, "This is a test.");
	printf("strcmp(org, \"This is a test.\") => %d\n", n);
	
	n = strlen(org);
	printf("strlen(org) => %d\n", n);

	// strrev(dest);  // gcc 에서는 안됨
	// printf("strrev(dest) => dest = \"%s\"\n", dest);
	
	s = strchr(org, 'a');
	printf("s = strchr(org, 'a') => s = \"%s\"\n", s);
	s = strrchr(org, 'i');
	printf("s = strrchr(org, 'i') => s = \"%s\"\n", s);

	s = strstr(org, "is");
	printf("s = strstr(org, \"is\") => s = \"%s\"\n", s);

	// strtok 사용법
	printf("Use of strtok(org, \" .\") ==> \n\tTokens =");
	token = strtok(org, " .");
	while(token) {
		printf(" [%s]", token);
		token = strtok(NULL, " ."); 
	} 
	printf("\n\tAfter that, org is changed to \"%s\"\n", org);
	printf("\tSee the lines of code.\n");
}
