#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>

#include "paciente.h"

//each node of the tree
template <typename type_data>
struct Node
{
    type_data data;
    Node *right;
    Node *left;
    Node();
};
//just bc new operator is used, a constructor is necessary. Also some QOL bc starts ptrs as null.
template <typename type_data>
Node<type_data>::Node() : right(nullptr), left(nullptr){};

template <typename T>
class Arvore
{

    template <typename tipoArvore>
    friend ostream &operator<<(ostream &output, Arvore<T> &arvore);

public:
    Arvore();
    ~Arvore();
    T *operator+=(const T &toAdd);
    T *operator()(const string &name);
    void display(ostream &output);

private:
    void recursivePrint(Node<T> *begin, ostream &output);           //used to display
    void recursiveDelete(Node<T> *begin);                           //used in destructor
    Node<T> *recursiveInsert(Node<T> *begin, const T &toAdd);       

    template <typename type_data>
    Node<T> *recursiveSearch(Node<T> *begin, const type_data &name);

    Node<T> *start = nullptr;
};


template <typename T>
Arvore<T>::Arvore(){}

template <typename T>
Arvore<T>::~Arvore(){
    if (start!=nullptr){
        recursiveDelete(start);
    }
}

template <typename T>
T *Arvore<T>::operator+=(const T &toAdd)
{

    //if first time...
    if (start == nullptr)
    {
        start = new Node<T>;
        start->data = toAdd;
        return &(start->data);
    }
    else
    {
        return &(recursiveInsert(start, toAdd)->data);
    }
}

template <typename T>
ostream &operator<<(ostream &output, Arvore<T> &arvore)
{
    arvore.display(output);
    return output;
}

template <typename T>
void Arvore<T>::display(ostream &output)
{
    if (start)
    {
        recursivePrint(start, output);
    }
    else
    {
        output << "A arvore esta vazia!" << endl;
    }
}

template <typename T>
void Arvore<T>::recursivePrint(Node<T> *begin, ostream &output)
{
    if (begin->right)
    {
        recursivePrint(begin->right, output);
    }
    //to acess in alphabetic order all nodes on the right should be accessed first.
    output << begin->data << endl;
    if (begin->left)
    {
        recursivePrint(begin->left, output);
    }
}

template <typename T>
void Arvore<T>::recursiveDelete(Node<T> *begin)
{
    if (begin->right)
    {
        recursiveDelete(begin->right);
    }
    if (begin->left)
    {
        recursiveDelete(begin->left);
    }
    //access the farest and delete their content
    delete begin;
}

template <typename T>
Node<T> *Arvore<T>::recursiveInsert(Node<T> *begin, const T &toAdd)
{
    //fail
    if (begin->data == toAdd)
    {
        return nullptr;
    }
    //left
    if (begin->data < toAdd)
    {
        if (begin->left == nullptr)
        {
            begin->left = new Node<T>;
            begin->left->data = toAdd;
            return begin->left;
        }
        else
        {
            return recursiveInsert(begin->left, toAdd);
        }
    }
    //right
    else
    {
        if (begin->right == nullptr)
        {
            begin->right = new Node<T>;
            begin->right->data = toAdd;
            return begin->right;
        }
        else
        {
            return recursiveInsert(begin->right, toAdd);
        }
    }
}

//wraper for recursive search
template <typename T>
T *Arvore<T>::operator()(const string &name)
{
    return &(recursiveSearch(start, name)->data);
}

template <typename T>
template <typename type_data>
Node<T> *Arvore<T>::recursiveSearch(Node<T> *begin, const type_data &value)
{
    //if not found
    if (begin == nullptr)
    {
        return nullptr;
    }
    else if (begin->data == value)
    {
        return begin;
    }
    //if greater
    else if (begin->data < value)
    {
        return recursiveSearch(begin->left, value);
    }
    //if less
    else
    {
        return recursiveSearch(begin->right, value);
    }
}

#endif