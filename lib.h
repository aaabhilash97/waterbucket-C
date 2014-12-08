#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
        int a,b,depth;
        char *code;
        struct node *left,*right,*next;
        };
void SortedInsert(struct node** headRef, struct node* newNode);
void InsertSort(struct node** headRef);
