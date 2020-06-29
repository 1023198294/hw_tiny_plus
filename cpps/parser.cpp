#include "lexer.hpp"
#include "parser.hpp"
#include "utils.hpp"
static void match(TokenType expected);
static TokenType token;
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * while_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * for_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);
static TreeNode * program(void);
static TreeNode * declaration_list(void);
static TreeNode * declaration(void);

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError(tokenString);
    printToken(token,tokenString);
    cout<<"  ";
  }
}
TreeNode* parser(void){
    TreeNode *t;
    token=getToken();
    t = program();
    if(token!=ENDFILE)
        syntaxError("Code ends before file\n");
    return t;
}

/* program -> declarations stmt-sequence */
TreeNode * program(void){
  TreeNode * root = (TreeNode *) malloc(sizeof(TreeNode));
  for (int i = 0;i<MAXCHILDREN;i++){
    root->child[i] = NULL;
  }
  root->sibling = NULL;
  root->nodekind = PromK;
  TreeNode * t = declaration_list();
  TreeNode * t1 = stmt_sequence();
  root->child[0] = t;
  root->child[1] = t1;
  
  while ((token!=ENDFILE) && (token!=END)) 
  {
    TreeNode * q = stmt_sequence();
    if (q!=NULL) 
    {
      if (t==NULL) t1 = q;
      else
      {
        t1->sibling = q;
      }
    }
  }
  /*return s->child[1];*/
  return root;
}

/* declaration_list -> declaration; declaration_list | epsilon */
TreeNode * declaration_list(void){
  TreeNode * t = declaration();
  TreeNode * p = t;

  /*!!!*/
  if(t==NULL)
    return t;
  while ((token!=ENDFILE) && (token!=END) &&
         (token!=READ)) 
  {
    TreeNode * q;
    q = declaration();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else
      {
        p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

/* declaration -> type var */
/* type -> REAL | INT | CHAR */
/* var -> ID {,ID} */
TreeNode * declaration(void)
{
  TreeNode * t = NULL;
  switch (token) {   
    case REAL:
      t = newDeclarationNode(RealK);
      match(REAL);
      if ((t!=NULL) && (token==ID)) t->attr.name = copyString(tokenString);
      match(ID);
      match(SEMI);
      break;
    case INT :
      t = newDeclarationNode(IntK);
      match(INT);
      if ((t!=NULL) && (token==ID)) t->attr.name = copyString(tokenString);
      match(ID);
      match(SEMI);
      break;
    case CHAR :
      t = newDeclarationNode(CharK);
      match(CHAR);
      if ((t!=NULL) && (token==ID)) t->attr.name = copyString(tokenString);
      match(ID);
      match(SEMI);
      break;
  }
  return t;
}

/* stmt-sequence -> statement {;statement}*/
TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while (
      (token!=ENDFILE) && 
      (token!=END) &&
         (token!=ELSE) &&
          (token!=UNTIL)
          )
  { 
    TreeNode * q;
    match(SEMI);
    if ((token!=ENDFILE) && 
      (token!=END) &&
         (token!=ELSE) &&
          (token!=UNTIL)){
        q = statement();
        if (q!=NULL) {
        if (t==NULL) t = p = q;
        else /* now p cannot be NULL either */
        { p->sibling = q;
            p = q;
        }
        }
    }
  }
  return t;
}

/* statement -> if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt | while-stmt */
TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case IF : t = if_stmt(); break;
    case REPEAT : t = repeat_stmt(); break;
    case WHILE : t = while_stmt(); break;
    case ID : t = assign_stmt(); break;
    case READ : t = read_stmt(); break;
    case WRITE : t = write_stmt(); break;
    case FOR : t= for_stmt(); break;
    default : 
            syntaxError(tokenString);
            //token = getToken();
            break;
  } 
  return t;
}

/* if-stmt -> if bool-exp then stmt-sequence [else stmt-sequence] end */
TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(IF);
  if (t!=NULL) t->child[0] = exp();
  match(THEN);
  if (t!=NULL) t->child[1] = stmt_sequence();
  if (token==ELSE) {
    match(ELSE);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(END);
  return t;
}

/* repeat-stmt -> repeat stmt-sequence until exp */
TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
  match(REPEAT);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(UNTIL);
  if (t!=NULL) t->child[1] = exp();
  return t;
}

/* while-stmt -> while exp do stmt-sequence end */
TreeNode * while_stmt(void){
    TreeNode *t = newStmtNode(WhileK);
    match(WHILE);
    if (t!=NULL) t->child[0] = exp();
    match(DO);
    if (t!=NULL) t->child[1] = stmt_sequence();
    match(END);
    return t;
}
/* for-stmt -> for assign-stmt dodir exp do stmt-sequence end */
/* dodir -> downto | upto */
TreeNode * for_stmt(void){
    TreeNode* t = newStmtNode(ForK);
    match(FOR);
    if (t != NULL) t->child[0] = assign_stmt();
    if (token == UPTO || token==DOWNTO){
        match(token);
        if(t!=NULL) t->child[1] = exp();
        match(DO);
        if(t!=NULL) t->child[2] = stmt_sequence();
        match(END);
    }else{
        syntaxError("for writePath");
    }
    return t;
}
/* assign-stmt -> ID:=exp */
TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  match(ASSIGN);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

/* read-stmt -> read ID */
TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
  match(READ);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  return t;
}

/* write-stmt -> write exp*/
TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
  match(WRITE);
  if (t!=NULL) t->child[0] = exp();
  return t;
}


/* exp -> simple_exp {compop simple_exp} */
/* compop -> > | = | < */
TreeNode * exp(void)
{ 
  TreeNode * t = simple_exp();
  if ((token==LT)||(token==EQUAL)||(token==GT)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}

/* simple_exp -> term {addop term}*/
/* addop -> + | - */
TreeNode * simple_exp(void)
{ TreeNode * t = term();
  while ((token==ADD)||(token==SUB))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = term();
    }
  }
  return t;
}

/* term -> factor {mulop factor}*/
/* mulop -> * | / */
TreeNode * term(void)
{ TreeNode * t = factor();
  while ((token==MUL)||(token==DIV))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}

/* factor -> (exp) | NUMBER | ID*/
TreeNode * factor(void)
{ TreeNode * t = NULL;
  switch (token) {
    case INTNUM :
      t = newExpNode(ConstIntK);
      if ((t!=NULL) && (token==INTNUM))
        t->attr.val = atoi(tokenString);
      match(INTNUM);
      break;
    case REALNUM :
      t = newExpNode(ConstRealK);
      if ((t!=NULL) && (token==REAL))
        t->attr.val = atof(tokenString);
      match(REALNUM);
      break;
    case ID :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
      match(ID);
      break;
    case LEFTPAREN :
      match(LEFTPAREN);
      t = exp();
      match(RIGHTPAREN);
      break;
    default:
      syntaxError("unexpected token -> ");
      printToken(token,tokenString);
      token = getToken();
      break;
    }
  return t;
}
