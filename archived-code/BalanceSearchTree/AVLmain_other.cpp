#include <iostream>
#include <stdlib.h>
#include "AvlTree.h"
//#include "BTree.h"
//#include "BSTree.h"
using namespace std;
int main(){
    AvlTree<int> l;
    for(int i = 1 ; i <= 15 ; i++){
        l.Insert(i);
    }
    l.PrintTree();
    while(true){
        int toDelete;
        cout<<"������Ҫɾ���ڵ��ֵ:"<<endl;
        cin>>toDelete;
        l.Delete(toDelete);
        cout<<"ɾ�������Ϊ:"<<endl;
        l.PrintTree();
    }
    return 0;
    system("PAUSE");
}
