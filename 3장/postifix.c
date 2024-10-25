#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {lparen, rparen, plus, minus, times,
			  divide, mod, eos, operand } precedence;

// int stack [ MAX_STACK_SIZE ]; /* global stack */
char expr[MAX_EXPR_SIZE];   // input string 
char stack[MAX_STACK_SIZE]; // 문자형 스택을 쓸 경우, postfix(), evav()함수에서 모두 사용 가능함
int  exprN = 0;		// postfix() 결과를 다시 expr에 저장하기 위해 사용함

/*  isp and icp arrays - index is value of precedence
	lparen, rparen, plus, minus, times, divide, mod, eos */
int	isp[ ] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[ ] = { 20, 19, 12, 12, 13, 13, 13, 0 };
int	top = -1;	

void push(char c)
{
	stack[++top] = c;
}

char pop()
{
	return stack[top--];
}

// char getSym(precedence p)
void print_token(precedence p)
{
	switch(p)
	{
		case lparen: 	printf("("); expr[exprN++]='('; break; //return '(';
		case rparen: 	printf("("); expr[exprN++]=')'; break; //return '(';
		case plus: 		printf("+"); expr[exprN++]='+'; break; //return '+';
		case minus: 	printf("-"); expr[exprN++]='-'; break; //return '-';
		case divide: 	printf("/"); expr[exprN++]='/'; break; //return '/';
		case times: 	printf("*"); expr[exprN++]='*'; break; //return '*';
		case mod: 		printf("%%"); expr[exprN++]='%'; break; //return '%';
	}
}

precedence get_token(char *symbol, int *n)
{ // 수식 문자열에서 다음 문자를 검사하여 해당 token을 반환
	*symbol = expr[(*n)++];
   	switch (*symbol) 
	{
		case '(': 	return  lparen;
      	case ')': 	return  rparen;
      	case '+': 	return  plus;
      	case '-': 	return  minus;
      	case '/': 	return  divide;
      	case '*': 	return  times;
      	case '%': 	return  mod;
      	case '\0': 	return  eos;
      	default: 	return  operand; 
			/*no error checking, default is operand */
	}
}

int eval(void)
{	// expr[] 배열에 문자열로 저장된 postfix 수식 계산.
	// expr[]과 stack[], 그리고 top은 전역변수임.
	// get_token() 함수는 수식의 각 문자의 precedence를 return
	// 수식에서 피연산자는 한 문자로 구성된다고 가정.

	precedence token;
	char symbol;
	int  op1, op2;
	int  n = 0;         // 수식 문자열의 현재 판독 위치
	top = -1;
	token = get_token(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');  // 피연산자를 만나면 스택에 저장
		else{ // stack에서 피연산자 2개를 삭제한 후 이를
				// 이용하여 수식을 계산한 후 결과를 다시 stack에 저장
			op2 = pop();     //  stack delete
			op1 = pop();
			switch(token){
				case plus : push(op1 + op2); break;
				case minus : push(op1 - op2); break;
				case times : push(op1 * op2); break;
				case divide : push(op1 / op2); break;
				case mod : push(op1 % op2);
			}
		}
		token = get_token(&symbol, &n);
	}
	return pop();   /* return result */
}

void postfix()
{/*  Output the postfix of the expression. The expression string, stack, and
     top are global.    */
	char symbol;
	precedence token;
	int n = 0;
	// place eos on stack
	// top = 0; stack[0] = eos;
	push(eos); 	
	

	for (token = get_token(&symbol, &n); token != eos; 
						token = get_token(&symbol, &n)) 
	{
		if (token == operand) {
			printf("%c", symbol); expr[exprN++] = symbol; }
		else if (token == rparen) {
			/* unstack tokens until left parenthesis */
			while (stack[top] != lparen)
				print_token(pop());
			pop();  /* discard the left parenthesis */
		}
		else {
			while (isp[stack[top]] >= icp[token])
				print_token(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)		 
		print_token(token);
	expr[exprN] = '\0';
	printf("\n");
}

void main()
{
	int result;
	
	printf("\nInput an Expr: ");
	scanf("%s", expr);
	// strcpy(expr, "a*(c/b-d)*(f-g*h)");
	
	printf("Postfix of \"%s\" ==> ", expr);
	postfix();  // postfix()이 끝나면 expr에 postfix 수식이 저장됨

	result = eval(); // operand가 숫자일 경우 eval()결과가 정확함
	printf("Eval of \"%s\" ==> %d\n", expr, result);
}
