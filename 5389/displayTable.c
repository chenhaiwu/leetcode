#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define FOOD_TYPES_LEN 1000
#define FOOD_LEN 21
#define CUSTOM_LEN 21
#define TABLE_LEN 501

char g_foods[FOOD_TYPES_LEN][FOOD_LEN];
int g_foodlen;

typedef struct _foodnode {
    int id;
    char food[FOOD_LEN];
} FoodNode;
FoodNode g_foodlist[FOOD_TYPES_LEN];

typedef struct _node {
    int tableid;
    char food[FOOD_LEN];
    int foodnum;
} Node;

void InitData()
{
    memset(g_foods, 0x0, sizeof(g_foods));
}

void AddFoods(char *** orders, int ordersSize, int* ordersColSize)
{
    for (int i = 0; i < ordersSize; i++) {
        char *foods = orders[i][2];
        
    }
}

char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, int* returnSize, int** returnColumnSizes)
{
    InitData();
    AddFoods(char *** orders, int ordersSize, int* ordersColSize);
}
char *** findLadders(char * beginWord, char * endWord, char ** wordList, int wordListSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (wordListSize >= 599) {
        return NULL;
    }
    bool bRet = PreHandleCharDiff(wordList, wordListSize, beginWord, endWord);
    if (!bRet) {
        return NULL;
    }

    memset(g_visited, 0x0, sizeof(int) * g_diffrow);
    g_minLen = INT_MAX;
    bfs();
    printf("the min len=%d\n", g_minLen);
    if (g_minLen == -1) {
        return NULL;
    }
    PreResetGlobal();

    g_path[0] = 0;
    g_visited[0] = 1;
    dfs(1, 1, wordList, beginWord);

    char *** ret = (char ***)malloc(g_retSize * sizeof(char **));
    *returnColumnSizes = (int *)malloc(g_retSize * sizeof(int));
    for (int i = 0; i < g_retSize; i++) {
        (*returnColumnSizes)[i] = g_minLen;
        ret[i] = (char *)malloc(g_minLen * sizeof(char*));
        for (int j = 0; j < g_minLen; j++) {
            ret[i][j] = (char *)malloc(sizeof(char) * (g_wordLen + 1));
            strcpy(ret[i][j], g_ret[i][j]);
            ret[i][j][g_wordLen] = '\0'; 
        }
    }
    *returnSize = g_retSize;

    // PrintResult(ret, returnSize, returnColumnSizes);
    FreeGlobal();

    return ret;
}

int main()
{
    int wordListSize = 3;
    int wordLen = 4;
    char **grid = NULL;
    char* t1[3] = {"hot","dot","dog"};
    char *beginWord = "hot";
    char *endWord = "dog";
    char ***result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;

    grid = malloc(wordListSize * sizeof(char *));
    for (int i = 0; i < wordListSize; i++) {
        grid[i] = malloc(wordLen * sizeof(char));
        strcpy(grid[i], t1[i]);
    }

    result = findLadders(beginWord, endWord, grid, wordListSize, &returnSize, &returnColumnSizes);

    free(grid);
}



int cmpnum(void* a,void* b)
{
    char*** x=*(char***)a;
    char*** y=*(char***)b;
    int numa=atoi(x[1]);
    int numb=atoi(y[1]);
    return numa-numb;
}
int cmpfood(void* a,void *b)
{
    char** x=*(char**)a;
    char** y=*(char**)b;
    return strcmp(x,y);
}
char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, int* returnSize, int** returnColumnSizes){
    qsort(orders,ordersSize,sizeof(char***),cmpnum);//对orders按餐桌排序
    int hash[501]={0};
    int num[501]={0};
    int count_num=0;
    for(int i=0;i<ordersSize;i++)
    {
        int n=atoi(orders[i][1]);
        hash[n]++;
    }
    for(int i=1;i<=500;i++)//记录共有多少人
        if(hash[i]>0)
            num[count_num++]=i;
    int row=count_num+1;//人数+1为行数
    char*** ans=(char***)malloc(row*sizeof(char**));
    * returnSize=row;
    returnColumnSizes[0]=(int*)calloc(row,sizeof(int));
    char** food=(char**)malloc(500*sizeof(char*));
    int len=strlen(orders[0][2]);
    int count_food=0;
    food[count_food]=(char*)calloc(len+1,sizeof(char));
    strcpy(food[count_food],orders[0][2]);
    food[count_food++][len]='\0';
    for(int i=1;i<ordersSize;i++)//记录共有多少食物
    {
        int flog=0;
        for(int j=0;j<i;j++)
        {
            if(strcmp(orders[i][2],orders[j][2])==0)
            {
                flog=1;
                break;
            }
        }
        if(flog==0)
        {
            len=strlen(orders[i][2]);
            food[count_food]=(char*)calloc(len+1,sizeof(char));
            strcpy(food[count_food],orders[i][2]);
            food[count_food++][len]='\0';
        }
    }
    qsort(food,count_food,sizeof(char**),cmpfood);
    int col=count_food+1;//食物数+1为列数
    for(int i=0;i<row;i++)
    {
        ans[i]=(char**)malloc(col*sizeof(char*));
        returnColumnSizes[0][i]=col;
    }   
    for(int i=0;i<col;i++)//生成第一行
    {
        if(i==0)
            ans[0][i]="Table";
        else
        {
            len=strlen(food[i-1]);
            ans[0][i]=(char*)calloc(len+1,sizeof(char));
            strcpy(ans[0][i],food[i-1]);
            ans[0][i][len]='\0';
        }
    }
    for(int i=1;i<row;i++)//生成第一列
    {
        char s[4];
        sprintf(s,"%d",num[i-1]);
        len=strlen(s);
        ans[i][0]=(char*)calloc(len+1,sizeof(char));
        strcpy(ans[i][0],s);
        ans[i][0][len]='\0';
    }
    int** count=(int**)malloc(count_num*sizeof(int*));
    for(int i=0;i<count_num;i++)
        count[i]=(int*)calloc(count_food,sizeof(int));
    for(int i=0;i<ordersSize;i++)//对每一桌点的菜进行统计，生成点菜表
    {
        int n=atoi(orders[i][1]);
        int x,y;
        for(x=0;x<count_num;x++)
            if(num[x]==n)
                break;
        for(y=0;y<count_food;y++)
            if(strcmp(orders[i][2],food[y])==0)
                break;
        count[x][y]++;
    }
    for(int i=1;i<row;i++)//对照点菜表补充数据
    {
        for(int j=1;j<col;j++)
        {
            char s[4];
            sprintf(s,"%d",count[i-1][j-1]);
            len=strlen(s);
            ans[i][j]=(char*)calloc(len+1,sizeof(char));
            strcpy(ans[i][j],s);
            ans[i][j][len]='\0';
        }
    }
    return ans;
}