#ifndef NODES_H
#define NODES_H

#include <vector>
#include <string>


using namespace std;

class Aresta;
class Vertice;
class Caminho;

class Aresta{
    public:
        Aresta(Vertice *src,Vertice *dst);
        void incrementCount();
        Vertice *getDst();
        Vertice *getSrc();
        unsigned getCount();

    private:
        Vertice *src;
        Vertice *dst;
        unsigned count;
};


class Vertice{
    public:
        Vertice(string word);
        ~Vertice();
        void InsertSentAresta(Vertice *dst);
        string &getName();

        vector<Aresta *> & getSentConnections();
        vector<Aresta *> & getRecvConnections();
        unsigned getVerticeUses();
        unsigned getVerticeForward();
        unsigned getVerticeBackward();
        unsigned getWeightByVertex(Vertice *v);
        

        
    private:
        void InsertRecivedAresta(Aresta *a);
        
        //what's
        string word;

        //who am i pointing to?
        vector<Aresta *>sentConnections;
        //who is pointing to me?
        vector<Aresta *>recvConnections;
        
};



class Caminho{
    public:
        Caminho();
        Caminho(vector<Vertice *>copy);
        void insertNode(Vertice *node);
        vector<Vertice *> & getRoute();
        unsigned getSize();
        void printRoute();
    private:
        vector<Vertice *>route;
        
        
};
#endif