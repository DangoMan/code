#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <queue>
#include <iomanip> 
#include "AvlNode.h"

using namespace std;

template <class T>
class AvlTree{
public:
       AvlTree():root(NULL){}
       AvlNode<T>* getRoot() const{return root;}

       bool Insert(T x){ bool taller = false; return Insert(root,x,taller ); }
       bool Delete(T x){ bool shorter = false; return Delete(root,x,shorter); }

       void PrintTree() const{PrintTree(root,0);}
       void PrintTreeLevel() const{PrintTreeLevel(root);}
       void PrintTreePre() const{PrintTreePre(root);}   
       void PrintTreePost() const{PrintTreePost(root);}              
       void PrintTreeIn() const{PrintTreeIn(root);}       
private:
        AvlNode<T> *root;

        bool Insert(AvlNode<T> *& sRoot,T x,bool &taller);
        bool Delete(AvlNode<T> *& sRoot,T x,bool &shorter);

        void RotateLeft(AvlNode<T> * &sRoot);
        void RotateRight(AvlNode<T> * &sRoot);

        void RightBalanceAfterInsert(AvlNode<T> * &sRoot,bool &taller);
        void LeftBalanceAfterInsert(AvlNode<T> * &sRoot,bool &taller);
        void RightBalanceAfterDelete(AvlNode<T> * &sRoot,bool &shorter);
        void LeftBalanceAfterDelete(AvlNode<T> * &sRoot,bool &shorter);

        void PrintTree(AvlNode<T> *t,int layer) const;
        void PrintTreeLevel(AvlNode<T> *t) const;
        void PrintTreePre(AvlNode<T> *t) const;        
        void PrintTreePost(AvlNode<T> *t) const;                
        void PrintTreeIn(AvlNode<T> *t) const;                  
};

template <typename T>
//�������� 
void AvlTree<T>::RotateLeft(AvlNode<T> * &sRoot){
     if( (sRoot == NULL) || (sRoot->right == NULL) ) return;
     
     AvlNode<T> *temp = new AvlNode<T>(sRoot->data);
     if(temp == NULL ) return;
     
     temp->left = sRoot->left;
     sRoot->left = temp;
     temp->right = sRoot->right->left;
     AvlNode<T> *toDelete = sRoot->right;
     sRoot->data = toDelete->data;     
     sRoot->right = toDelete->right;
     
     delete toDelete;
}

template <typename T>
//�������� 
void AvlTree<T>::RotateRight(AvlNode<T> * &sRoot){
     if( (sRoot == NULL) || (sRoot->left == NULL) ) return;
     
     AvlNode<T> *temp = new AvlNode<T>(sRoot->data);
     if(temp == NULL ) return;
     
     temp->right = sRoot->right;
     sRoot->right = temp;
     temp->left = sRoot->left->right;
     AvlNode<T> *toDelete = sRoot->left;
     sRoot->data = toDelete->data;
     sRoot->left = toDelete->left;
     
     delete toDelete;
}

template <typename T>
void AvlTree<T>::RightBalanceAfterInsert(AvlNode<T> *&sRoot,bool &taller){
    //�������ڵ��,sRoot���Ҹ߶���������ƽ�⣬����ô˺�����ʹ������ƽ��
    if( (sRoot == NULL) || (sRoot->right == NULL) ) return;
    AvlNode<T> *rightsub = sRoot->right,*leftsub;
    switch(rightsub->balance){
        case 1:
            sRoot->balance = rightsub->balance = 0;
            RotateLeft(sRoot);
            taller = false; break;
        case 0:
            cout<<"���Ѿ�ƽ�⻯."<<endl; break;
        case -1:
            leftsub = rightsub->left;
            switch(leftsub->balance){
                case 1:
                    sRoot->balance = -1; rightsub->balance = 0; break;
                case 0:
                    sRoot->balance = rightsub->balance = 0; break;
                case -1:
                    sRoot->balance = 0; rightsub->balance = 1; break;
            }
            leftsub->balance = 0;
            RotateRight(rightsub);
            RotateLeft(sRoot);
            taller = false; break;
    }
}

template <typename T>
void AvlTree<T>::LeftBalanceAfterInsert(AvlNode<T> *&sRoot,bool &taller){
    //�������ڵ��,sRoot����߶�����,����ƽ�⣬����ô˺�����ʹ������ƽ��
    AvlNode<T> *leftsub = sRoot->left,*rightsub;
    switch(leftsub->balance){
        case -1:
            sRoot->balance = leftsub->balance = 0;
            RotateRight(sRoot);
            taller = false; break;
        case 0:
            cout<<"���Ѿ�ƽ�⻯."<<endl; break;
        case 1:
            rightsub = leftsub->right;
            switch(rightsub->balance){
                case -1:
                    sRoot->balance = 1; leftsub->balance = 0; break;
                case 0:
                    sRoot->balance = leftsub->balance = 0; break;
                case 1:
                    sRoot->balance = 0; leftsub->balance = -1; break;
            }
            rightsub->balance = 0;
            RotateLeft(leftsub);
            RotateRight(sRoot);
            taller = false; break;
    }
}

template <typename T>
void AvlTree<T>::RightBalanceAfterDelete(AvlNode<T> * &sRoot,bool &shorter){
    //���ɾ���ڵ��sRoot����߶ȼ��٣�����ƽ�⣬����ô˺�����ʹ������ƽ��
    AvlNode<T> *rightsub = sRoot->right,*leftsub;
    switch(rightsub->balance){
        case 1: sRoot->balance = sRoot->balance = 0; RotateLeft(sRoot); break;
        case 0: sRoot->balance = 0; rightsub->balance = -1; RotateLeft(sRoot); break;
        case -1:
            leftsub = rightsub->left;
            switch(leftsub->balance){
                case -1: sRoot->balance = 0; rightsub->balance = 1; break;
                case 0: sRoot->balance = rightsub->balance = 0; break;
                case 1: sRoot->balance = -1; rightsub->balance = 0; break;
            }
            leftsub->balance = 0;
            RotateRight(rightsub);
            RotateLeft(sRoot);
            shorter = false; break;
    }
}

template <typename T>
void AvlTree<T>::LeftBalanceAfterDelete(AvlNode<T> * &sRoot,bool &shorter){
    //���ɾ���ڵ��sRoot���Ҹ߶ȼ��٣�����ƽ�⣬����ô˺�����ʹ������ƽ��
    AvlNode<T> *leftsub = sRoot->left,*rightsub;
    switch(leftsub->balance){
        case 1: sRoot->balance = sRoot->balance = 0; RotateRight(sRoot); break;
        case 0: sRoot->balance = 0; leftsub->balance = -1; RotateRight(sRoot); break;
        case -1:
            rightsub = leftsub->right;
            switch(rightsub->balance){
                case -1: sRoot->balance = 0; leftsub->balance = 1; break;
                case 0: sRoot->balance = leftsub->balance = 0; break;
                case 1: sRoot->balance = -1; leftsub->balance = 0; break;
            }
            rightsub->balance = 0;
            RotateLeft(leftsub);
            RotateRight(sRoot);
            shorter = false; break;
    }
}

template <typename T>
bool AvlTree<T>::Insert(AvlNode<T> *& sRoot,T x,bool &taller){
    //�ݹ麯��,��sRoot�����Ѱ�Һ��ʵ�λ��,����ֵΪx�Ľڵ� 
    bool success;
    if ( sRoot == NULL ) {//�����ĳ���,��Ҷ�ڵ���� 
       sRoot = new AvlNode<T>(x);
       success = sRoot != NULL ? true : false;
       if ( success ) taller = true;
    }
    else if ( x < sRoot->data ) {//���x��ֵС��sRoot��ֵ
        
       //Insert�ĵݹ����,��sRoot��������Ѱ�Һ��ʵ�λ�ò��� 
       success = Insert ( sRoot->left, x, taller );
       if ( taller ){//��������ʹ��sRoot����߶����� 
             switch ( sRoot->balance ) {
                case -1 : LeftBalanceAfterInsert( sRoot, taller ); break;
                case 0 :  sRoot->balance = -1; break;
                case 1 :  sRoot->balance = 0;  taller = false; break;  
            }      
        }
    }
    else if ( x > sRoot->data ) {//���x��ֵ����sRoot��ֵ
    
       //Insert�ĵݹ����,��sRoot��������Ѱ�Һ��ʵ�λ�ò��� 
       success = Insert ( sRoot->right, x, taller );
       
       if ( taller ){//��������ʹ��sRoot���Ҹ߶����� 
          switch ( sRoot->balance ) {              
            case -1 : sRoot->balance = 0; taller = false; break;
            case 0 :  sRoot->balance = 1; break;  
            case 1 :  RightBalanceAfterInsert( sRoot, taller ); break;
        }
     }
    }
    return success;    
}

template <typename T>
bool AvlTree<T>::Delete(AvlNode<T> *& sRoot,T x,bool &shorter){
    //�ݹ麯��,��sRoot�������Ѱ��ֵΪx�Ľڵ㣬��ɾ��֮. 
    bool success = false;
    if(sRoot == NULL) return false; //����������ʧ�� 
    if(x == sRoot->data) {//���sRoot����Ҫɾ���Ľڵ� 
        if(sRoot->left != NULL && sRoot->right != NULL) {//���sRoot�и���Ů
        
            //Ѱ�� sRoot�����������ǰ���ڵ�,��r��ʾ 
            AvlNode<T> *r = sRoot->left;
            while(r->right != NULL) {
                 r = r->right;
            }
            
            //����sRoot��r��ֵ 
            T temp = sRoot->data;
            sRoot->data = r->data;
            r->data = temp;
            
            //�ݹ麯������,��sRoot��������Ѱ��ֵΪx�Ľڵ㣬��ɾ��֮.
            success = Delete(sRoot->left, x, shorter);
            if(shorter) {//���ɾ��������sRoot����߶ȼ���
                switch(sRoot->balance) {
                    case -1: sRoot->balance = 0; break;
                    case 0: sRoot->balance = 1; shorter = 0; break;
                    case 1: RightBalanceAfterDelete(sRoot, shorter);break;
                }
            }
        }
        else {//sRoot���ֻ��һ����Ů,���ǵݹ�ĳ��� 
             AvlNode<T> *p = sRoot;
             sRoot = sRoot->left != NULL ? sRoot->left : sRoot->right;//��sRootָ��������Ů 
             delete p;//�ͷ�ԭ��sRoot��ռ���ڴ�ռ� 
             success = true;
             shorter = true;
        }
    }

    else if(x < sRoot->data) {
        //�ݹ麯������,��sRoot��������Ѱ��ֵΪx�Ľڵ㣬��ɾ��֮.
        success = Delete(sRoot->left, x, shorter);
        if(shorter) {//���ɾ��������sRoot����߶ȼ���
            switch(sRoot->balance) {
                case -1: sRoot->balance = 0; break;
                case 0: sRoot->balance = 1; shorter = 0; break;
                case 1: RightBalanceAfterDelete(sRoot, shorter); break;
            }
        }
    }

    else if(x > sRoot->data) {
        //�ݹ麯������,��sRoot��������Ѱ��ֵΪx�Ľڵ㣬��ɾ��֮.
        success = Delete(sRoot->right, x, shorter);
        if(shorter) {//���ɾ��������sRoot���Ҹ߶ȼ���
            switch(sRoot->balance) {
                case -1: LeftBalanceAfterDelete(sRoot, shorter); break;
                case 0: sRoot->balance = -1; shorter = 0; break;
                case 1: sRoot->balance = 0; break;
            }
        }
    }
    return success;
}


template <typename T>
void AvlTree<T>::PrintTree(AvlNode<T> *t,int layer) const{
    if(t == NULL ) return;
    if(t->right) PrintTree(t->right,layer+1);
    for(int i =0;i<layer;i++) cout<<"    ";
    cout<<t->data<<endl;
    if(t->left) PrintTree(t->left,layer+1);
}
template <typename T>
void AvlTree<T>::PrintTreeLevel(AvlNode<T> *t) const{
     if(t == NULL) return;
     queue<AvlNode<T>*> NodeQueue;
     AvlNode<T> *node;
     NodeQueue.push(t);
     while(!NodeQueue.empty()){
        node = NodeQueue.front();
        NodeQueue.pop();
        cout<<node->data<<",";
        if(node->left != NULL) NodeQueue.push(node->left);
        if(node->right != NULL) NodeQueue.push(node->right);                               
    }
}

template <typename T>
void AvlTree<T>::PrintTreePre(AvlNode<T> *t) const{
     if(t){
          cout<<t->data<<",";
          PrintTreePre(t->left);
          PrintTreePre(t->right);     
     }
}

template <typename T>
void AvlTree<T>::PrintTreePost(AvlNode<T> *t) const{
     if(t){
          PrintTreePost(t->left);
          PrintTreePost(t->right);     
          cout<<t->data<<",";
     }
}

template <typename T>
void AvlTree<T>::PrintTreeIn(AvlNode<T> *t) const{
     if(t){
          PrintTreeIn(t->left);
          cout<<t->data<<",";     
          PrintTreeIn(t->right);     
     }
}
#endif //AVLsRoot_H
