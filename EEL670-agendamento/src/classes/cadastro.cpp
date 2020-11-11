
#include <exception>

#include "cadastro.h"


//avoid compilation error when Cadastro::Cadastro() not found
Cadastro::Cadastro(){}


ostream &operator<<(ostream &output, Cadastro &cadastro)
{
    output << cadastro.myArvore;
    return output;
}

void Cadastro::insere(Paciente p)
{
    if ((myArvore += p)==nullptr){
        throw alreadyInserted();
    }
}

Paciente &Cadastro::consulta(string nome)
{
    Paciente *result = myArvore(nome);
    if (result == nullptr)
    {
        throw notFound();
    }
    return *result;
}