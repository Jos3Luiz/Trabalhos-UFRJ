
#include <vector>
#include <string>
#include <iostream>
#include <limits>

#include "grafo.h"
#include "nodes.h"
using namespace std;

void printList(vector<Vertice *> list){
    for (auto i : list){
        cout << i->getName() <<"\t";
    }
    cout << endl;

}
Grafo::~Grafo(){
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

Vertice &Grafo::mostUsedVertex(){
    unsigned max=0;
    unsigned current=0;
    Vertice *choosen;
    //cout << "Starting..." << endl;


    for (auto x : allVertex){
        current=x.second->getVerticeUses();
        
        if (current > max){
            max = current;
            choosen = x.second;
        }
    }
    return *choosen;

}


Caminho Grafo::mostUsedSequence(unsigned N){

    //iterating checking
    Caminho bestPath;

    //for unpacking
    Caminho currentPath;

    //return
    vector <string> sequence;

    Vertice *node;
    
    //for each entry node..
    bool firstTime=true;

    for (auto v: allVertex){
        node = v.second;
        
        currentPath=getRecursiveDeepCount( Caminho({node}), N );

        if (firstTime){
             firstTime=false;
             bestPath=currentPath;
        }
        //cout << "recursiving to " << node->getName() << " Returned size "<< current<<currentPath.size() << endl<<"\t";
        //printList(currentPath);
        //cout << endl;
        

        if (bestPath.getSize() < currentPath.getSize() && currentPath.getRoute().size()==N){
            bestPath = currentPath;
        }
    }
    cout << "ocurrencies : " << bestPath.getSize() << endl;
    

    cout << "Best matches" << endl; 
    for (string  v: sequence){
        cout << v << endl;
    }
    cout << "endseq" << endl;

    return bestPath;

}

Caminho
Grafo::getRecursiveDeepCount(Caminho path,unsigned deep){

    //recursive downhill
    Caminho bestPath;

    //for unpacking
    Caminho currentPath;
    Caminho newPath;

    Vertice *vertexPtr;
    //cout << "\taccessing to " << vertexPtr->getName() <<deep << endl;
    vertexPtr=path.getRoute().back();

    if ( deep == 1 or vertexPtr->getSentConnections().size()==0 ){
        return path;
    }
    else{

        bestPath=Caminho(path);
        bestPath.insertNode(vertexPtr->getSentConnections()[0]->getDst());

        for(Aresta *x : vertexPtr->getSentConnections() ){
            newPath=path;
            newPath.insertNode(x->getDst());
            currentPath=
                getRecursiveDeepCount(
                    newPath,
                    deep-1 );

            if(bestPath.getSize() < currentPath.getSize()){
                bestPath=currentPath;
            }    
        }
    }
    return bestPath;
     
}



