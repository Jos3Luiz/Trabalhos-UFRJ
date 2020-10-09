
#include <vector>
#include <string>
#include <iostream>
#include <limits>

#include "grafo.h"
#include "nodes.h"
using namespace std;

Grafo::~Grafo(){
    //clear up all the objects because new is used for instantiating
    for (auto x : allVertex) 
      delete x.second; 
}


void Grafo::insertArestas(string word1,string word2){

    Vertice *start;
    Vertice *end;
    unordered_map<string,Vertice *>::const_iterator got;

    got = allVertex.find(word1);
    //if word is in graph
    if (got!= allVertex.end()){
        start = got->second;
    }
    else{
        start = new Vertice(word1);
        allVertex[word1] = start;
    }

    //check if word2 is already in graph
    got = allVertex.find(word2);
    if (got!= allVertex.end()){
        end = got->second;
    }
    else{
        end = new Vertice(word2);
        allVertex[word2] = end;
    }

    //join or increment both nodes
    start->InsertSentAresta(end);
    
}

//just querys the hashmap in O(1)
Vertice *Grafo::findVertexByName(string vname){

    unordered_map<string,Vertice *>::const_iterator got;
    Vertice * result= nullptr;
    got = allVertex.find(vname);
    if (got!= allVertex.end()){
        result = got->second;
    }
    return result;

}


Vertice &Grafo::mostUsedVertex(unsigned *res){
    unsigned max=0;
    unsigned current=0;
    Vertice *choosen;

    if (allVertex.size()<1){
        throw invalid_argument("O grafo esta vazio!");
    }
    for (auto x : allVertex){
        //search everyone pointing to that node
        current=x.second->getVerticeBackward();
        
        if (current > max){
            max = current;
            choosen = x.second;
        }
    }
    *res=max;
    return *choosen;

}

//just a nice interface for __getRecursiveDeepCount
vector<Vertice *> 
Grafo::getRecursiveDeepCount(unsigned deep,Vertice * begin){

    vector<Vertice *> start;
    start.push_back(begin);

    return __getRecursiveDeepCount(deep,deep,start);
     
}

//just a auxliary function to compute the weight of a path.
unsigned routeLarge(vector <Vertice *> path){

    unsigned totalSize=0;
    if (path.size()<=1){
        totalSize=0;
    }
    else{
        totalSize=path[0]->getWeightByVertex(path[1]);
        for (unsigned i=1;i<path.size()-1;i++){
            totalSize=min(path[i]->getWeightByVertex(path[i+1]),totalSize);
        }
    }
    
    return totalSize;
}

//search recursively in depth on the graph
vector<Vertice *> 
Grafo::__getRecursiveDeepCount(unsigned initialDeep,unsigned deep,vector<Vertice *> path){

    //recursive search
    vector<Vertice *> bestPath;

    //for unpacking the result
    vector<Vertice *> currentPath;
    vector<Vertice *> newPath;

    Vertice *vertexPtr=path.back();
    
    //reached the end
    if ( deep == 1 ){
        return path;
    }
    //reached a node with no more children
    else if (vertexPtr->getSentConnections().size()==0){
        return vector<Vertice *>();
    }
    
    else{
        for(Aresta *x : vertexPtr->getSentConnections() ){
            newPath=path;
            newPath.push_back(x->getDst());
            currentPath=__getRecursiveDeepCount(initialDeep,deep-1 ,newPath);
            //checking if the path found is better than the previous
            if(currentPath.size()>1){
                if (routeLarge(bestPath) < routeLarge(currentPath)){
                    bestPath=currentPath;
                }
            }    
        }
    }
    return bestPath;
     
}



//wraper for all in depth search. called for each node and then checked whats the best node. returns empty vector if no sequence matches the desired lenght
vector<string>  Grafo::getPopularSequence(unsigned size,unsigned *res){
    vector<Vertice *>best,current;
    vector<string>result;
    for (auto x : allVertex){

        current=getRecursiveDeepCount(size,x.second);
        if (routeLarge(current) > routeLarge(best)){
            best=current;
        }
    }
    for (Vertice *x : best){
        result.push_back(x->getName());
    }
    *res=routeLarge(best);
    return result;

}