#include <cstring>
#include <cstdio>
#include "global.hpp"
#include "tac.hpp"
#include "symtab.hpp"
static void tacStmt(TreeNode *tree);
static void tacExp(TreeNode *tree);
static int label_num = 0;
static int newlabel(void);
static int tacGen(TreeNode* tree);
static void showlabel(int label);
static void gotolabel(int label);
void tac(TreeNode* syntaxTree){
    tacGen(syntaxTree);
}
static int newlabel(void){
    int temp = label_num;
    label_num++;
    //showlabel(temp);
    return temp;
}
static void showlabel(int label){
    cout<<"Label L"<<label<<";"<<endl;
}
static void gotolabel(int label){
    cout<<"goto Label L"<<label;
}
static int tacGen(TreeNode* tree){
    int nl;
    if(tree != NULL){
        switch (tree->nodekind)
        {
        case PromK:
            //nl = newlabel();
            //showlabel(nl);
            tacGen(tree->child[0]);
            tacGen(tree->child[1]);
            break;
        case StmtK:
            tacStmt(tree);
            break;
        case ExpK:
            tacExp(tree);
            break;
        default:
            return 0;
        }
        tacGen(tree->sibling);
    }
    
    return -1;
}
static void tacStmt(TreeNode *tree){
    TreeNode *p1,*p2,*p3;
    int beg,els,end;
    switch (tree->kind.stmt)
    {
        case ReadK:
            cout<<"read "<<tree->attr.name<<";"<<endl;
            break;
        case WriteK:
            cout<<"write "<<tree->attr.name<<";"<<endl;
            break;
        case AssignK:
            cout<<tree->attr.name<<" := "<<tree->child[0]->attr.val<<endl;
            break;
        case IfK:
            p1 = tree->child[0];
            p2 = tree->child[1];
            p3 = tree->child[2];
            beg = newlabel();
            els = newlabel();
            end = newlabel();
            
            cout<<"if ";
            tacGen(p1);//to else
            cout<<" goto Label L"<<beg<<endl;
            
            if(p3!=NULL){
                showlabel(els);
                tacGen(p3);
                cout<<"goto Label L"<<end<<endl;
            }else{
                cout<<"goto Label L"<<end<<endl;
            }
            showlabel(beg);
            tacGen(p2);
            showlabel(end);
            break;
        case RepeatK:
            p1 = tree->child[0];
            p2 = tree->child[1];
            beg = newlabel();
            end = newlabel();
            showlabel(beg);
            tacGen(p1);
            cout<<"if ";
            tacGen(p2);
            cout<<" goto Label L"<<end<<" else goto Label L"<<beg<<endl;
            showlabel(end);
            break;
        case WhileK:
            p1 = tree->child[0];
            p2 = tree->child[1];
            beg = newlabel();
            end = newlabel();
            
            showlabel(beg);
            cout<<"if ";
            tacGen(p1);
            cout<<" goto Label L"<<end<<endl;
            tacGen(p2);
            cout<<"goto Label L"<<beg<<endl;
            showlabel(end);

        default:
            break;
    }
}
static void tacExp(TreeNode *tree){
    TreeNode *p1,*p2;
    switch (tree->kind.exp)
    {
    case ConstRealK:
    case ConstIntK:
    case ConstK:
        cout<<tree->attr.val;
        break;
    case IdK:
        cout<<tree->attr.name;
        break;
    case OpK:
        p1 = tree->child[0];
        p2 = tree->child[1];
        tacGen(p1);
        switch (tree->attr.op)
        {
        case ADD:
            cout<<"+";
            break;
        case SUB:
            cout<<"-";
            break;
        case MUL:
            cout<<"*";
            break;
        case DIV:
            cout<<"/";
            break;
        case LT:
            cout<<"<";
            break;
        case EQUAL:
            cout<<"=";
            break;
        default:
            break;
        }
        tacGen(p2);
        break;
    default:
        break;
    }
}