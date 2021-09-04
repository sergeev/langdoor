// Дерево выводится по уровням, корню соответствует 1-й(самый левый) выведенный элемент.
// Ссылки можно не использовать, данном коде их можно просто удалить (кроме процедуры добавления).
#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
#define COUNTNODES 5
#define ROOTLEVEL 0
 
struct Tree{
    int num;
    Tree *left, *right;
};
 
void AddNode(int x, Tree *&MyTree);
void Showtree(Tree *&MyTree, int level);
int countLevel(Tree *MyTree, int N);
void DeleteTree(Tree *&MyTree);
 
int main()
{
    Tree *phead = nullptr;
    int num;
    srand(time(NULL));
    for (int i = 0; i < COUNTNODES; i++){
        num = rand()%100;
        AddNode(num, phead);
    }
    Showtree(phead, ROOTLEVEL);
    int level;
    cout << "Input level : ";
    cin >> level;
    cout << "Number of nodes on level " << level << " = " << countLevel(phead, level) << endl;
    DeleteTree(phead);
    system("pause");
    return 0;
}
 
void AddNode(int x, Tree *&MyTree)
{
    if (MyTree == nullptr){
        MyTree = new Tree;
        MyTree->num = x;
        MyTree->left = MyTree->right = nullptr;
    }
    else{
        if (x < MyTree->num){
            if(MyTree->left != nullptr)
                AddNode(x, MyTree->left);
            else{
                MyTree->left = new Tree;
                MyTree->left->left = MyTree->left->right = nullptr;
                MyTree->left->num = x;
            }
        }
        if (x > MyTree->num){
            if (MyTree->right != nullptr)
                AddNode(x, MyTree->right);
            else{
                MyTree->right = new Tree;
                MyTree->right->left = MyTree->right->right = nullptr;
                MyTree->right->num = x;
            }
        }
    }
}
 
void Showtree(Tree *&MyTree, int level)
{
    if (MyTree){
        Showtree(MyTree->left, level + 1);
        for (int i = 0; i < level; i++)
            cout <<  "    ";
        cout << MyTree->num << endl;
        Showtree(MyTree->right, level + 1);
    }
}
 
int countLevel(Tree *MyTree, int N)
{
    if (MyTree == NULL)
        return 0;
    if (N == 0)
        return 1;
    return countLevel(MyTree->left, N - 1) + countLevel(MyTree->right, N - 1);
}
 
void DeleteTree(Tree *&MyTree)
{
    if(MyTree!=nullptr){
        DeleteTree(MyTree->left);
        DeleteTree(MyTree->right);
        delete MyTree;
        MyTree = nullptr;
    }
}