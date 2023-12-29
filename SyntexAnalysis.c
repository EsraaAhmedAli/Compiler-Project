#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 

// Token types 
typedef enum { 
 NUMBER, 
 PLUS, 
 MINUS, 
 MULTIPLY, 
 DIVIDE, 
 LPAREN, //"("
 RPAREN, //")"
 END 
} TokenType; 

// Token structure 
typedef struct { 
 TokenType type; 
 int value; // For NUMBER tokens 
} Token; 

// Global variables 
Token curToken; 
const char *input; 

// Function prototypes 
void fetchNextToken(); 
int Expression(); 
int term(); 
int factor(); 

// Parse error function 
void error(const char *message) { 
 fprintf(stderr, "Error: %s\n", message); 
 exit(1); 
} 

// Lexical analyzer (simple tokenization) 
void fetchNextToken() { 
 while (isspace(*input)) { 
 input++; 
 } 

 if (*input == '\0') { 
 curToken.type = END; 
 } else if (isdigit(*input)) { 
 curToken.type = NUMBER; 
 curToken.value = 0; 
 while (isdigit(*input)) { 
 curToken.value = curToken.value * 10 + (*input - '0'); 
 input++; 
 } 
 } else { 
 switch (*input) { 
 case '+': 
 curToken.type = PLUS; 
 break; 
 case '-': 
 curToken.type = MINUS; 
 break; 
 case '*': 
 curToken.type = MULTIPLY; 
 break; 
 case '/': 
 curToken.type = DIVIDE; 
 break; 
 case '(': 
 curToken.type = LPAREN; 
 break; 
 case ')': 
 curToken.type = RPAREN; 
 break; 
 default: 
 error("Invalid character"); 
 } 
 input++; 
 } 
} 
// Expression--> 3a+2 (   +   or   -)
// Term--------> 3a    (  *  or   /  )
// Factor------> a  or  3
 
int Expression() { 
 int result = term(); 
 while (curToken.type == PLUS || curToken.type == MINUS) { 
 if (curToken.type == PLUS) { 
 fetchNextToken(); 
 result += term(); 
 } else { 
 fetchNextToken(); 
 result -= term(); 
 } 
 } 
 return result; 
} 

int term() { 
 int result = factor(); 
 while (curToken.type == MULTIPLY || curToken.type == DIVIDE) { 
 if (curToken.type == MULTIPLY) { 
 fetchNextToken(); 
 result *= factor(); 
 } else { 
 fetchNextToken(); 
 int divisor = factor(); 
 if (divisor == 0) { 
 error("Division by zero"); 
 } 
 result /= divisor; 
 } 
 } 
 return result; 
} 

int factor() { 
 int result; 
 if (curToken.type == NUMBER) { 
 result = curToken.value; 
 fetchNextToken(); 
 } else if (curToken.type == LPAREN) { 
 fetchNextToken(); 
 result = Expression(); 
 if (curToken.type != RPAREN) { 
 error("Missing closing parenthesis"); 
 } 
 fetchNextToken(); 
 } else { 
 error("Unexpected token"); 
 } 
 return result; 
} 

int main() { 
 printf("Enter The Syntax : "); 
 char buffer[100]; 
 fgets(buffer, sizeof(buffer), stdin); 

 // Remove the newline character if present 
 char *newline = strchr(buffer, '\n'); 
 if (newline != NULL) { 
 *newline = '\0'; 
 } 

 input = buffer; 
 fetchNextToken(); 

 int result = Expression(); 

 if (curToken.type == END) { 
 printf("Result: %d\n", result); 
 } else { 
 error("Unexpected token at the end"); 
 } 

 return 0; 
}