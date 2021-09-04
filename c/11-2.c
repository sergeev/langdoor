// Матрица в graph.txt

// 1 0 0 0 0 -1 -1 0
// -1 1 0 -1 0 0 0 0
// 0 0 -1 1 -1 0 0 0
// 0 -1 1 0 0 0 1 1
// 0 0 0 0 1 1 0 -1

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <malloc.h>
#define n 100
#include <locale.h>
/*Структура вершины графа, представленного списком смежно-
сти*/
typedef struct ListNode_
{
    int info;
    ListNode_ *next;
} ListNode;
bool flag[n] = { false };
ListNode *BEGIN[n];
/*Набор процедур, реализующих обход в ширину BFS*/
struct QueneNode
{
    int info;
    QueneNode *next;
};
QueneNode *BeginQuene;
QueneNode *EndQuene;
void InitQuene()
{
    BeginQuene = NULL;
    EndQuene = NULL;
}
void EnQuene(int x)//занесение в очередь
{
    QueneNode *p;
    p = (QueneNode *)malloc(sizeof(QueneNode));
    p->info = x;
    p->next = NULL;
    if (BeginQuene == NULL)
        BeginQuene = p;
    else EndQuene->next = p;
    EndQuene = p;
}
int DeQuene()
{
    int val;
    QueneNode *p;
    p = (QueneNode *)malloc(sizeof(QueneNode));
    p = BeginQuene;
    val = BeginQuene->info;
    BeginQuene = p->next;
    if (BeginQuene == NULL)
        EndQuene = NULL;
    free(p);
    return val;
}
bool IsEmptyQuene()
{
    if (EndQuene == NULL)
        return true;
    else return false;
}
void BFS(int cur, int end)
{
    EnQuene(cur);
    flag[cur] = true;
    while (IsEmptyQuene() != true)
    {
        cur = DeQuene();
        ListNode *List = BEGIN[cur];
        while (List != NULL)
        {
            if (flag[List->info] == false)
            {
                EnQuene(List->info);
                flag[List->info] = true;
                printf("%d-%d\n", cur + 1, List->info + 1);
            }
            List = List->next;
        }
    }
}
int main()
{
    int i, j;
    FILE *f = fopen("graph.txt", "r");
    for (i = 0; !feof(f); i++)
    {
        int n1;
        fscanf(f, "%d", &n1);/*считываем количество вершин,
                             смежных с i-й вершиной*/
        for (j = 0; j < n1; j++)
        {
            int a;
 
            fscanf(f, "%d", &a);/*считываем номер очередной j-й
                                вершины, смежной с вершиной i */
            ListNode *cuz = (ListNode*)malloc(
                sizeof(ListNode));
            cuz->info = a - 1;/*заносим в поле info списка значе-
                              ние номера j-й смежной вершины на 1 меньше ее реального номера,
                              так как в массиве вершин нумерация элементов начинается с 0, а не
                              с 1, как нумеруются вершины графа */
            cuz->next = BEGIN[i];
            BEGIN[i] = cuz;
        }
    }
    fclose(f);
    int FST;
    int end;
    SetConsoleTitleW(L"Lab2");
    setlocale(LC_ALL, "russian");
    printf("Введите номер вершины, с которой будет начат обход графа в ширину:\n");
    scanf("%d", &FST);
    printf("Введите номер вершины, на которой будет закончен обход графа в ширину:\n");
    scanf("%d", &end);
    /*Подготовка массива flag к использованию для поиска в
    ширину*/
    printf("\nОбход в ширину BFS\n");
    for (i = 0; i < n; i++) flag[i] = false;
    /*Реализация поиска в ширину*/
    InitQuene();
    BFS(FST - 1, end);
    getch();
    for (i = 0; i < n; i++)
    {
        ListNode *cuz, *tmp;
        cuz = BEGIN[i];
        while (cuz != NULL)
        {
            tmp = cuz;
            cuz = cuz->next;
            free(tmp);
        }
    }
    return 0;
}