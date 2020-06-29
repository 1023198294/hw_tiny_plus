#include<cstdio>
#include<cstring>
#include "global.hpp"
#include "utils.hpp"
static int deepthOfTree = 0;
#define INCRESEDEEP deepthOfTree++;
#define DECRESEDEEP deepthOfTree--;
void test_put_char(void){
        cout<<" "<<endl;
}
void printSpaces(void) {
	int i;
	for (i = 0; i < deepthOfTree * 2; i++)
		cout<<" ";
}

void show_menu(void){
    cout<<"hyj compiler | Version 1.0"<<endl;
    cout<<"Type \"-h\" for more information"<<endl;
    cout<<"Select the pattern and the compiling would start"<<endl;
}
void show_help(void){
    cout<<"l lexical analysis"<<endl;
    cout<<"s syntax analysis"<<endl;
    cout<<"c code generation"<<endl;
    cout<<"example: ls (lexical analysis and syntax analysis)"<<endl;
}
void syntaxError(char* errormsg){
    cout<<"[ERROR] : ";
    cout<<errormsg;
    cout<<" is illeagal"<<endl;
    cout<<"Type \"enter\" to exit"<<endl;
    getchar();
    ERROREXIT1;
}
void printToken(TokenType token, const char* str) {
	switch (token) {
	case IF:
	case ELSE: 
	case WHILE:
	case DO:
        case REPEAT:
        case UNTIL:
	case FOR:
	case UPTO:
	case DOWNTO:
	case WRITE: 
	case READ: 
	case RETURN: 
	case BEGIN: 
	case END:
	case MAIN: 
	case INT:
	case REAL:
        case CHAR:
        case THEN:
		cout<<"(KEYWORD, "<<str<<")"<<endl;
        break;
	case SEMI: 
        cout<<"(SEP, ;)"<<endl;
        break;

	case COMMA: 
        cout<<"(SEP, ,)"<<endl;
        break;

	case LEFTPAREN:
        cout<<"(SEP, ()"<<endl;
        break;
	case RIGHTPAREN: 
        cout<<"(SEP, )"<<endl;
        break;
	case ADD:
        cout<<"(OP, +)"<<endl;
        break;
	case SUB: 
        cout<<"(OP, -)"<<endl;
        break;
	case MUL: 
        cout<<"(OP, *)"<<endl;
        break;
	case DIV: 
        cout<<"(OP, /)"<<endl;
        break;
	case MOD: 
        cout<<"(OP, %%)"<<endl;
        break;
	case ASSIGN: 
        cout<<"(OP, :=)"<<endl;
        break;
	case EQUAL: 
        cout<<"(OP, =)"<<endl;
        break;
	case UNEQUAL: 
        cout<<"(OP, !=)"<<endl;
        break;
	case GT: 
        cout<<"(OP, >)"<<endl;
        break;
	case LT: 
        cout<<"(OP, <)"<<endl;
        break;
	case ID: 
        cout<<"(ID, "<<str<<")"<<endl;
        break;
	case NUM: 
        cout<<"(NUM,"<<str<<")"<<endl;
        break;
        case INTNUM: 
        cout<<"(INTNUM,"<<str<<")"<<endl;
        break;
        case REALNUM: 
        cout<<"(REALNUM,"<<str<<")"<<endl;
        break;
	case QSTR: 
        cout<<"(QString, "<<str<<")"<<endl;
        break;
	//case ERROR:
	case ENDFILE: 
        cout<<"EOF"<<endl;
        break;
	default:
		cout<<"Unknown token "<<token<<endl;
        break;
	}
}
void printTree( TreeNode * tree )
{ int i;
  INCRESEDEEP;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          cout<<"If"<<endl;
          break;
        case RepeatK:
          cout<<"Repeat"<<endl;
          break;
        case AssignK:
          cout<<"Assign to "<<tree->attr.name<<endl;
          break;
        case ReadK:
          //fprintf(listing,"Read: %s\n",tree->attr.name);
          cout<<"Read: "<<tree->attr.name<<endl;
          break;
        case WriteK:
          //fprintf(listing,"Write\n");
          cout<<"Write"<<endl;
          break;
        case WhileK:
          cout<<"While"<<endl;
          break;
        case ForK:
          cout<<"For"<<endl;
          break;
        default:
          cout<<"Unknown ExpNode kind"<<endl;
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          cout<<"Op: ";
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          //fprintf(listing,"Const: %d\n",tree->attr.val);
          cout<<"Const: "<<tree->attr.val<<endl;
          break;
        case IdK:
          //fprintf(listing,"Id: %s\n",tree->attr.name);
          cout<<"Id: "<<tree->attr.name<<endl;
          break;
        case ConstIntK:
          cout<<"Int: "<<(int)tree->attr.val<<endl;
          break;
        case ConstRealK:
          cout<<"Real: "<<tree->attr.val<<endl;
          break;
        default:
          cout<<"Unknown ExpNode kind"<<endl;
          break;
      }
    }
    else if (tree->nodekind==DecK)
    { switch (tree->kind.exp) {
        case IntK:
          cout<<"Int: "<<tree->attr.name<<endl;
          break;
        case RealK:
          cout<<"Real: "<<tree->attr.name<<endl;
          break;
        case CharK:
          cout<<"Char: "<<tree->attr.name<<endl;
          break;
        default:
          cout<<"Unknown DecNode kind"<<endl;
          break;
      }
    }
    else if (tree->nodekind==PromK)
    {
      cout<<"Program:"<<endl;
    }
    else cout<<"Unknown node kind"<<endl;
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  DECRESEDEEP;
}

TreeNode * newDeclarationNode(DecKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    syntaxError("out of memory");
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DecK;
    t->kind.dec = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    syntaxError("out of memory");
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    syntaxError("out of memory");
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

char* copyString(char* str) {
	if (str == NULL) return NULL;
	int n;
	char* res;
	n = strlen(str) + 1;
	res = (char*)malloc(n);
	if (res == NULL) {
                cout<<"[ERROR] : out of memmory!"<<endl;
                ERROREXIT1;
	}
	else
	{
		strcpy(res, str);
	}
	return res;
}
