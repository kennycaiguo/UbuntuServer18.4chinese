#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dic
{
    char *key;
    char *value;
} Dic;
int getrowscount(char *filename);

void formatstr(char *str);

void load_dic(Dic **pd);

 

int search_from_dic(Dic *p, int len, char *key, char *value);
 

void print_dic(Dic* p, int len);

int get_index(char*, char ch,int);



