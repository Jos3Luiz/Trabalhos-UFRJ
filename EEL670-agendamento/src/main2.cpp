
#include <iostream>

#include "classes/arvore.h"
#include "classes/paciente.h"

using namespace std;

int main(){
    Paciente p1("carlos");
    Paciente p2("mariana");
    Paciente p3("giovana");
    Cancer p4("igor");
    Anemia p5("jorge");
    Arvore <Paciente> myArvore;
    
    myArvore+=p1;
    myArvore+=p2;
    myArvore+=p3;
    myArvore+=p4;
    myArvore+=p5;

    cout << myArvore;
    cout << "usuario encontrado " << myArvore("igo2r") << endl;
}
