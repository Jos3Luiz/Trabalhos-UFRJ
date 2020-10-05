#include <iostream>

#include "classes/grafo.h"
#include "classes/nodes.h"

using namespace std;

int main(){
    cout << "hello wordl" << endl;
    Grafo my_g;
    //my_g.insertArestas("ola","mundo");
    //my_g.insertArestas("novo","mundo");
    //my_g.insertArestas("velho","mundo");
    //my_g.insertArestas("velho","coisa");
    //my_g.insertArestas("velho","objeto");
    my_g.insertArestas("velho","pedra");
    my_g.insertArestas("pedra","galho");
    //cout << "hello wordl" << endl;
    //cout << "Resposta: " << my_g.mostUsedVertex().getName() << endl ;
    //cout << "hello wordl" << endl;

    my_g.mostUsedSequence(3).printRoute();
    
}

