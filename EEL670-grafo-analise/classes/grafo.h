#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include <unordered_map> 

#include "nodes.h"

using namespace std;

class Grafo{
    public:
        ~Grafo();
        Vertice &mostUsedVertex();
        Caminho mostUsedSequence(unsigned N);
        void insertArestas(string word1,string word2);

    private:
        //hashmap word -> vertex, easy to locate where to put the new node.
        unordered_map<string, Vertice *> allVertex; 

        //returns occurrence count of a word sequence and its path
        Caminho  getRecursiveDeepCount(Caminho path,unsigned deep);

};

#endif