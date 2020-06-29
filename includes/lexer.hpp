#ifndef LEXER_HPP
#define LEXER_HPP
#include "global.hpp"
#define MAXTOKENLEN 255
#define RESERVED_NUM 19
extern char tokenString[MAXTOKENLEN + 1];//save buffer
typedef enum {
	STATUS_START,
	STATUS_ASSIGN,
	STATUS_EQUAL,
	STATUS_UNEQUAL,
	STATUS_COMMENT,
	STATUS_NUMBER,
	STATUS_REAL,
	STATUS_STR,
	STATUS_ID,
	STATUS_DONE 
}lexStatus;//DFA status
static struct
{
	string str;
	TokenType token;
} reservedWords[RESERVED_NUM]
= { {"if", IF}, {"else", ELSE},{"then",THEN},
	{"while", WHILE}, {"do",DO},{"repeat",REPEAT},{"until",UNTIL},
	{"for", FOR}, {"upto", UPTO}, {"downto", DOWNTO},
	{"read", READ}, {"write", WRITE},
	{"begin", BEGIN}, {"end", END},
	{"main", MAIN}, {"return", RETURN},
	{"int", INT}, {"real", REAL},{"char",CHAR}};

TokenType getToken(void);
#endif