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
        void insertArestas(string word1,string word2);
        Vertice *findVertexByName(string vname);

        //finds the most used single vertex.
        Vertice &mostUsedVertex();

        //finds most used word sequence
        vector<string>    
        getPopularSequence(unsigned size);

    private:

        
        //just a nice interface for __getRecursiveDeepCount
        vector<Vertice *>   
        getRecursiveDeepCount(unsigned deep,Vertice * begin);
        
        //returns occurrence count of a word sequence and its path
        vector<Vertice *>  
         __getRecursiveDeepCount(unsigned,unsigned,vector<Vertice *>);
        
        //hashmap word -> vertex, easy to locate where to put the new node.
        unordered_map<string, Vertice *> allVertex; 



};
//auxiliary function to compute path size
unsigned routeLarge(vector <Vertice *> path);

#endif