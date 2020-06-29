#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


#define ERROREXIT return 1
#define ERROREXIT1 exit(1)
#define MAXCHILDREN 10

extern bool IsL, IsS, IsG ,IsH ;
extern FILE* in;
extern FILE* code;
extern int lineno;

// token类型
typedef enum {
	// 类型
	INT, REAL, CHAR,
	// 保留字
	IF, THEN, ELSE, WRITE, READ, RETURN, BEGIN, END, MAIN, WHILE, DO, FOR, UPTO, DOWNTO, REPEAT, UNTIL,
	// 分隔符
	SEMI, COMMA, LEFTPAREN, RIGHTPAREN,
	// 运算符
	ADD, SUB, MUL, DIV, MOD, ASSIGN, EQUAL, UNEQUAL, GT, LT,
	// ID NUM
	ID, NUM, QSTR,INTNUM,REALNUM,
	// other
	ERROR, ENDFILE
}TokenType;

// 状态类型
typedef enum {StmtK,ExpK,DecK,PromK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK,WhileK,ForK} StmtKind;
typedef enum {OpK,ConstK,ConstIntK,ConstRealK,IdK} ExpKind;
typedef enum {IntK, RealK, CharK} DecKind;
//类型检查
typedef enum {Void,Integer,Boolean,Real} ExpType;

//语法树结构
typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp; DecKind dec;} kind;
     union { TokenType op;
             double val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;
#endif  
