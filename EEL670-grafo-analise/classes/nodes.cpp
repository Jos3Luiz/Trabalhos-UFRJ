
#include <vector>
#include <iostream>
#include "nodes.h"

using namespace std;


Aresta::Aresta(Vertice *src,Vertice *dst){
    this->src=src;
    this->dst=dst;
    this->count=1;
}

inline void Aresta::incrementCount(){       
    count++;            
}

unsigned Aresta::getCount(){               
    return count;       
}

Vertice *Aresta::getDst(){                  
    return dst;         
}

Vertice *Aresta::getSrc(){                  
    return src;         
}



Vertice::Vertice(string word){
    this->word=word;
}

Vertice::~Vertice(){
    //clear up all the objects because new is used for instantiating
    for (Aresta *x: sentConnections){
        delete x;
    }
}

void Vertice::InsertSentAresta(Vertice *dst){
    Aresta *n_ptr;

    //find our Aresta if it exists
    for (Aresta *x: sentConnections){
        if (x->getDst()==dst){
            //increment existing conection
            x->incrementCount();
            return;
        }
    }
    //create new connection if it doesnt
    n_ptr= new Aresta(this,dst);
    sentConnections.push_back(n_ptr);

    //let destination be aware that someone is pointing to them
    dst->InsertRecivedAresta(n_ptr);

}

void Vertice::InsertRecivedAresta(Aresta *a){
    recvConnections.push_back(a);
}

string & Vertice::getName(){
    return word;
}


vector<Aresta *> & Vertice::getSentConnections(){
    return sentConnections;
}

vector<Aresta *> & Vertice::getRecvConnections(){
    return recvConnections;
}


unsigned Vertice::getVerticeUses(){
    return getVerticeForward()+getVerticeBackward();
}

unsigned Vertice::getVerticeForward(){

    unsigned total=0;
    //get both ocurrence when im the first or second word
    for(Aresta * a : sentConnections){
        total=total+a->getCount();
    }
    return total;
}

unsigned Vertice::getVerticeBackward(){

    unsigned total=0;
    //get both ocurrence when im the first or second word
    for(Aresta * a : recvConnections){
        total=total+a->getCount();
    }
    return total;
}

unsigned Vertice::getWeightByVertex(Vertice *v){
    for(auto x: sentConnections){
        if (x->getDst()==v){
            return x->getCount();
        }
    }
    cout << "Unable to find desired vertex" << endl;
    throw 1;
}
