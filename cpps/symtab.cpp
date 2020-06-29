#include <cstdio>
#include <cstring>
#include "global.hpp"
#include "symtab.hpp"

#define SIZE 211
#define SHIFT 4
static int myhash(char *key){
    int temp = 0;
    int i = 0;
    while(key[i] != '\0'){
        temp = ((temp<<SHIFT)+key[i])%SIZE;
        i++;
    }
    return temp;
}
typedef struct LineListRec{
    int lineno;
    struct LineListRec *next;
} *LineList;
typedef struct BucketListRec{
    char *name;
    LineList lines;
    int memloc;
    struct BucketListRec *next;

} *BucketList;

static BucketList hashTable[SIZE];
void st_insert( char * name, int lineno, int loc ){
    int h = myhash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
}
int st_lookup ( char * name ){ 
  int h = myhash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}
void printSymTab(void){
    cout<<"Variable Name  Location   Line Numbers"<<endl;
    cout<<"-------------  --------   ------------"<<endl;
    for(int i=0;i<SIZE;++i){
        if(hashTable[i] != NULL){
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList t = l->lines;
                printf("%-14s ",l->name);
                printf("%-8d  ",l->memloc);
                while (t!=NULL)
                {
                    printf("%4d ",t->lineno);
                    t = t->next;
                }
                cout<<endl;
                l = l->next;
            }
        }
    }
}
