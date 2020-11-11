#include <string.h>
#include <iostream>
#include "paciente.h"

using namespace std;

/*---------------- Paciente_base------------------*/


ostream &operator <<(ostream &output,Paciente& p){
    output << " Nome: " << p.getName() <<" detalhes: "<< p.details << endl ;
    return output;

}
istream &operator >>(istream &lhs,Paciente&rhs){
    string nome;
    lhs >> nome;
    rhs.name=nome;
    return lhs;

}

Paciente::Paciente(string init_name){
    name=init_name;
}

string &Paciente::getName(){
    return name;
}

Paciente::Paciente(const Paciente &paciente){
    this->name=paciente.name;
    this->details=paciente.details;
}

Paciente::Paciente(){
    setDetails();
}


bool Paciente::operator>(Paciente const& other){
    return this->name > other.name;
}

bool Paciente::operator<(Paciente const& other){
    return this->name < other.name;
}

bool Paciente::operator==(Paciente const& other){
    return this->name == other.name;
}

void Paciente::setDetails(){
    details= "Paciente base,não há detalhes adicionais";
}


/*---------------- Paciente_derivados------------------*/

void Paciente_Doente::setDetails(){
    details= "Paciente doente, gravidade="+to_string(gravidade);
}

void Paciente_Internado::setDetails(){
    details= "Paciente internado, dias internado="+to_string(diasInternados);
}

double Paciente_Doente::getGravidade(){
    return gravidade;
}

//binded in compilation time so another constructor is needed
Paciente_Doente::Paciente_Doente(){
    setDetails();
}

Paciente_Internado::Paciente_Internado(){
    setDetails();
}
