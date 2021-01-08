#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydict.h"
#include<QDebug>


void formatstr(char *str)
{
    for (size_t i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] != '\n' && str[i] != ' ')
        {
            str[i + 1] = '\0';
            break;
        }
    }
}
int getrowscount(char *filename)
{
    FILE *f = fopen(filename, "rb");
    int rowcount = 0;
    if (f == NULL)
    {
        rowcount = 0;
        return rowcount;
    }
    char buf[1024];
    while (1)
    {
		fgets(buf, 1024, f);//因为两行才是一条记录，所以要读两次rowcount才加1
		fgets(buf, 1024, f);
        rowcount++;
		if (feof(f))
		{
			break;
		}
    }
    fclose(f);
    return rowcount;
}
 

int get_index(char* str, char ch,int len){
	int count = 0;
	for (int i = 0; i <= len; i++){
		count++;
		if (str[i]== ch){
			 return count;
		}
     }
	return count;
}
void load_dic(Dic **pd)
{
	char buf[1024];

	//int nread;
	//���ļ�
    FILE *fp = fopen("../dic.txt", "rb");
    int len = getrowscount("../dic.txt");
	*pd = (Dic *)malloc(len * sizeof(Dic));
	
	for (int i = 0; i < len; i++)
	{
		(*pd)[i].key = (char*)malloc(sizeof(char));
		(*pd)[i].value = (char*)malloc(sizeof(char));
	}
	//memset(*pd, 0, (len * sizeof(Dic)));
	int i = 0;

	 
	while (1)
	{
		fgets(buf, 1024, fp);
		formatstr(buf);
		strcpy((*pd)[i].key, buf);

		fgets(buf, 1024, fp);
		formatstr(buf);
		strcpy((*pd)[i].value, buf);

		i++;
		if (feof(fp)){
			break;
		}

	}
	fclose(fp);
}

int search_from_dic(Dic *d, int len, char *key, char *value)
{
	
    int i=0;
    for(i=0;i<len;i++)
    {
       if((d[i].key==NULL)||(d[i].value==NULL))
     {
        continue;
     }
      if(strcmp(d[i].key,key)==0)
       {
           strcpy(value,d[i].value);
           return 1;
       }
    }
    return 0;
}


void print_dic(Dic* p,int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("key:%s   value:%s,", p[i].key, p[i].value);
	}
}


