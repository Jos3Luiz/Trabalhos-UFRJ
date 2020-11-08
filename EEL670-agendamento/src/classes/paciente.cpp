#include <string.h>
#include "paciente.h"

using namespace std;

ostream &operator <<(ostream &lhs,Paciente&rhs){
    lhs << rhs.getName();
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
}

Paciente::Paciente(){
    this->name="";
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

string &Paciente_internado::getDisease(){
    return disease;
}