#ifndef UTILS_HPP
#define UTILS_HPP
#include "global.hpp"
void test_put_char(void);
void show_menu(void);
void show_help(void);
void printToken(TokenType token, const char* str);
void printTree(TreeNode *tree);
char* copyString(char* str);
void syntaxError(char* errormsg);
TreeNode * newDeclarationNode(DecKind kind);
TreeNode * newStmtNode(StmtKind kind);
TreeNode * newExpNode(ExpKind kind);
#endif