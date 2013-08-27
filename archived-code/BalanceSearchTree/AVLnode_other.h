#ifndef AVLNODE_H
#define AVLNODE_H
#include <iostream>
using namespace std;

template  <class T> class AvlTree; //����AvlTree��

template <class T>
class AvlNode{
public:
       friend class AvlTree<T>;//��Ԫ��
        
      //���캯��
      AvlNode():left(NULL),right(NULL),balance(0){};
      AvlNode(const T& e,AvlNode<T> *lt = NULL,AvlNode<T> *rt = NULL):data(e),left(lt),right(rt),balance(0){};

      int getBalance() const{return balance;}
      AvlNode<T>* getLeft() const{return left;}
      AvlNode<T>* getRight() const{return right;}
      T getData() const{return data;}
private:
      T data;    //�ڵ��ֵ
      AvlNode *left;    //����
      AvlNode *right;    //�к���
      int balance;        //ƽ������,�������ĸ߶ȼ�ȥ�������ĸ߶�
};
#endif //AVLNODE_H
