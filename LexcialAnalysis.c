#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  if the character is a DELIMITER, Returns 'true'.
bool isDelimiter(char inp)
{
	if (inp == ' ' || inp == '/' || inp == '-' || inp == '*' || 
		inp == '+' || inp == ',' || inp == ';' || inp == '>' || 
		inp == '<' || inp == '=' || inp == '(' || inp == ')' || 
		inp == '[' || inp == ']' || inp == '{' || inp == '}')
		return (true);
	return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char inp)
{
	if (inp == '=' || inp == '/' || inp == '*' || 
		inp == '-' || inp == '>' || inp == '<' || 
		inp == '+')
		return (true);
	return (false);
}


// Returns 'true' if the string is an INTEGER.
bool isInt(char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// if the string is a VALID IDENTIFIER,Returns 'true' .
bool validIdentifier(char* inp)
{
	if (inp[0] == '0' || inp[0] == '1' || inp[0] == '2' ||
		inp[0] == '3' || inp[0] == '4' || inp[0] == '5' || 
		inp[0] == '6' || inp[0] == '7' || inp[0] == '8' || 
		inp[0] == '9' || isDelimiter(inp[0]) == true)
		return (false);
	return (true);
}

// if the string is a KEYWORD, Returns 'true' .
bool isKeyword(char* str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") || 
		!strcmp(str, "break") || 
		!strcmp(str, "continue") || !strcmp(str, "double")
		|| !strcmp(str, "int") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "case") 
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned")
		|| !strcmp(str, "void") || !strcmp(str, "goto")
		|| !strcmp(str, "struct") || !strcmp(str, "static"))
		return (true);
	return (false);
}



// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str)
{
	int i, len = strlen(str);
	bool ContainDec = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' || 
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			ContainDec = true;
	}
	return (ContainDec);
}

// Extracts the SUBSTRING.
char* subString(char* str, int l, int r)
{
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (r - l + 2));

	for (i = l; i <= r; i++)
		subStr[i - l] = str[i];
	subStr[r - l + 1] = '\0';
	return (subStr);
}

// Parsing the input STRING.
void parse(char* str)
{
	int l = 0, r = 0;
	int len = strlen(str);

	while (r <= len && l <= r) {
		if (isDelimiter(str[r]) == false)
			r++;

		if (isDelimiter(str[r]) == true && l == r) {
			if (isOperator(str[r]) == true)
				printf("'%c' This Syntax Is AN OPERATOR\n", str[r]);

			r++;
			l = r;
		} else if (isDelimiter(str[r]) == true && l != r
				|| (r == len && l != r)) {
			char* subStr = subString(str, l, r - 1);

			if (isKeyword(subStr) == true)
				printf("'%s' This Syntax Is KEYWORD\n", subStr);

			else if (isInt(subStr) == true)
				printf("'%s' This Syntax Is INTEGER\n", subStr);

			else if (isRealNumber(subStr) == true)
				printf("'%s' This Syntax Is REAL NUMBER\n", subStr);

			else if (validIdentifier(subStr) == true
					&& isDelimiter(str[r - 1]) == false)
				printf("'%s' This Syntax Is VALID IDENTIFIER\n", subStr);

			else if (validIdentifier(subStr) == false
					&& isDelimiter(str[r - 1]) == false)
				printf("'%s' This Syntax Is NOT A VALID IDENTIFIER\n", subStr);
			l = r;
		}
	}
	return;
}

// DRIVER FUNCTION
int main()
{
	// maximum length of string is 100 here 
	char str[100] = "if(a>b)a+=10;";

	parse(str); // calling the parse function

	return (0);
}