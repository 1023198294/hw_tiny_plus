#include <cstring>
#include <cstdio>
#include "utils.hpp"
#include "lexer.hpp"
#define BUFLEN 256
static char lineBuf[BUFLEN]; 
static bool EOF_FLAG = false;
bool REALFLAG = false;
char tokenString[MAXTOKENLEN + 1];
static int linepos = 0; 
static int bufsize = 0; 
static char getNextChar(void)

{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,in))
    { 
      //if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { 
      EOF_FLAG = true;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

static void undoGetNextChar(void){
     if (!EOF_FLAG) linepos-- ;
}


static TokenType reservedLookup(char* str) {
	int i;
	for (i = 0; i < RESERVED_NUM; i++) {
		if ((str == reservedWords[i].str))
			return reservedWords[i].token;
	}
	return ID;
}
static void lexerERROR(){
    //cout<<"[ERROR] : fatal error occurs in line "<<1<<", column "<<1<<endl;
    cout<<" [ERROR] : fatal error occurs! "<<endl;
    getchar();
    ERROREXIT1;
}

TokenType getToken(void){
    int tokenStringIndex = 0;
    TokenType currentToken;
    lexStatus currentStatus = STATUS_START;
    bool save;
    //int acc = 0;
    while(currentStatus != STATUS_DONE){
        char c = getNextChar();
        save = true;
        switch (currentStatus)
        {
        case STATUS_START:{
            if(isdigit(c))
                currentStatus = STATUS_NUMBER;
            else if (isalpha(c))
                currentStatus = STATUS_ID;
            else if (c == '"'){
                save = false;
                currentStatus = STATUS_STR;
            }
            else if (c==':'){
                currentStatus = STATUS_ASSIGN;
            }
            else if (c=='!'){
                currentStatus = STATUS_UNEQUAL;
            }
            else if (c==' ' || c == '\n' || c =='\t'){
                save = false;
            }
            else if (c=='{'){
                currentStatus = STATUS_COMMENT;
                save = false;
            }
            else{
                currentStatus = STATUS_DONE;
                switch (c)
                {
                case EOF:
                    save = false;
                    currentToken = ENDFILE;
                    break;
                case '+':
                    currentToken = ADD;
                    break;
                case '-':
					currentToken = SUB;
					break;
				case '*':
					currentToken = MUL;
					break;
				case '/':
					currentToken = DIV;
					break;
				case '%':
					currentToken = MOD;
					break;
				case '<':
					currentToken = LT;
					break;
				case '>':
					currentToken = GT;
					break;
				case ',':
					currentToken = COMMA;
					break;
				case ';':
					currentToken = SEMI;
					break;
				case '(':
					currentToken = LEFTPAREN;
					break;
				case ')':
					currentToken = RIGHTPAREN;
					break;
                case '=':
                    currentToken = EQUAL;
                    break;
                default:
                    currentToken = ERROR;
                    break;
                }
            }
            break;
        }
        case STATUS_ASSIGN:{
            currentStatus = STATUS_DONE;
            if (c == '=')
                currentToken = ASSIGN;
            else{
                undoGetNextChar();
                save = false;
                currentToken = ERROR;
            }
            break;
        }
        case STATUS_UNEQUAL:{
            currentStatus = STATUS_DONE;
			if (c == '=')
				currentToken = UNEQUAL;
			else {
				undoGetNextChar();
				save = false;
				currentToken = ERROR;
			}
			break;
        }
        case STATUS_COMMENT:{
            save = false;
            if (c==EOF){
                currentStatus = STATUS_DONE;
                currentToken = ENDFILE;
            }else if (c =='}') currentStatus = STATUS_START;
            break;
        }
        case STATUS_ID:{
            if (!isalpha(c) && !(isdigit(c))){
                undoGetNextChar();
                //test_put_char();
                save = false;
                currentStatus = STATUS_DONE;
                currentToken = ID;
            }
            break;
        }
        case STATUS_NUMBER:{
            if (!isdigit(c)) {
				if (c == '.') {
					REALFLAG = true;
                    break;
				}
				else if (isalpha(c)) {
					undoGetNextChar();
					save = false;
					currentStatus = STATUS_DONE;
					currentToken = ERROR;
				}
				else {
					undoGetNextChar();
					save = false;
					currentStatus = STATUS_DONE;
                    if(REALFLAG){
                        currentToken = REALNUM;
                        REALFLAG = false;
                    }else
                        currentToken = INTNUM;
				}
			}
			break;
        }
        case STATUS_STR:{
            save = true;
            if(c=='"'){
                save = false;
                currentStatus = STATUS_DONE;
                currentToken = QSTR;
            }
            break;
        }
        case STATUS_DONE:break;
        default:
            currentStatus = STATUS_DONE;
            currentToken = ERROR;
            break;
        }
        if (save && tokenStringIndex<MAXTOKENLEN)
            tokenString[tokenStringIndex++] = c;
        if (currentStatus == STATUS_DONE){
            if (currentToken == ERROR){
                lexerERROR();
            }
            tokenString[tokenStringIndex] = '\0';
            if(currentToken==ID)
                currentToken = reservedLookup(tokenString);
        
        }
    }
    if(currentToken != ENDFILE)
		printToken(currentToken, tokenString);
	return currentToken;
}