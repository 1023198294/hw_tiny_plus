#include "global.hpp"
#include "utils.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "analyze.hpp"
#include "codegen.hpp"
#include "tac.hpp"
#define TEST 1
int lineno=0;
bool IsL = false, IsS = false, IsG = false, IsH = false;

FILE * in;
FILE * code;
int main(){
    string options;
    #if TEST
        cout<<"In test mode, testing with file \"test.tiny\""<<endl;
        char filename[120] = "test3.tiny";
        
        in = fopen(filename,"r");
        cout<<"[ACTION] : SYNTAX ANALYSIS"<<" START !"<<endl;
        TreeNode *syntaxTree;
        syntaxTree = parser();
        cout<<"[ACTION] : SYNTAX ANALYSIS"<<" COMPLETE !"<<endl;
        cout<<"[ACTION] : PRINT SYNTAX TREE"<<" START !"<<endl;
        printTree(syntaxTree);
        cout<<"[ACTION] : PRINT SYNTAX TREE"<<" COMPLETE !"<<endl;
        cout<<"[ACTION] : BUILD SYMBLE TABLE "<<" START !"<<endl;
        buildSymtab(syntaxTree);
        cout<<"[ACTION] : BUILD SYMBLE TABLE "<<" COMPLETE !"<<endl;
        cout<<"[ACTION] : TYPE CHECKING "<<" START !"<<endl;
        typeCheck(syntaxTree);
        cout<<"Code has passed the type check with 0 error"<<endl;
        cout<<"[ACTION] : TYPE CHECKING "<<" COMPLETE !"<<endl;
        cout<<"[ACTION] : TAC GENERATION" <<" START !"<<endl;
        tac(syntaxTree);
        cout<<"[ACTION] : TAC GENERATION" <<" COMPLETE !"<<endl;
        cout<<"[ACTION] : TM CODE GENERATION "<<" START !"<<endl;
        char codename[120] = "test.tm";
        code = fopen(codename,"w");
        if(code==NULL){
            cout<<"unable to open "<<codename<<endl;
        }
        codeGen(syntaxTree);
        fclose(code);
        cout<<"[ACTION] : TM CODE GENERATION "<<" COMPLETE !"<<endl;
        cout<<"[ACTION] : all tasks finished, press \"enter\" to exit."<<endl;
        getchar();
        cout<<endl;
    #else
    show_menu();
    cin>> options;
    string::iterator it = options.begin();
    while (it != options.end())
    {
        switch (*it)
        {
        case 'l':
        case 'L':
            cout<<"[OPTION] : lexical analysis available"<<endl;
            IsL = true;
            break;
        case 's':
        case 'S':
            cout<<"[OPTION] : syntax analysis available"<<endl;
            IsS = true;
            break;
        case 'g':
        case 'G':
            cout<<"[OPTION] : Code Generation available"<<endl;
            IsG = true;
            break;
        case 'h':
        case 'H':
            IsH = true;
            break;
        default:
            break;
        }
        ++it;
    }
    if (IsH){
        show_help();
    }
    if (!(IsL || IsS || IsG)){
        cout<<"[ERROR] : INVALID OPTIONS!"<<endl;
        cout<<"Please restart the compiler and type \"-h\" for help"<<endl;
        ERROREXIT;
    }
    cout<<"please input the file name"<<endl;
    cin>>filename;
    in.open(filename,ios::in | ios::out);
    if(!in){
        cout<<"[ERROR] : FILE NOT EXIST!"<<endl;
        ERROREXIT;
    }else{
        cout<<"[ACTION] : LOAD FILE \""<<filename<<"\" COMPLETE !"<<endl;
        getchar();
    }
    if(IsL){
        cout<<"[ACTION] : LEXICAL ANALYSIS"<<" BEGIN !"<<endl;
        in.seekg(0,ios::beg);
        while(getToken()!=ENDFILE);
        cout<<"[ACTION] : LEXICAL ANALYSIS"<<" COMPLETE !"<<endl;
    }
    if(IsS){
        cout<<"[ACTION] : SYNTAX ANALYSIS"<<" BEGIN !"<<endl;
        //in.seekg(0,ios::beg);
        //while(getToken()!=ENDFILE);
        TreeNode *syntaxTree;
        syntaxTree = parser();
        cout<<"[ACTION] : SYNTAX ANALYSIS"<<" COMPLETE !"<<endl;
        printTree(syntaxTree);
        cout<<endl;
    }

    cout<<"[ACTION] : tasks are finished, press any key to exit."<<endl;
    getchar();
    #endif
}