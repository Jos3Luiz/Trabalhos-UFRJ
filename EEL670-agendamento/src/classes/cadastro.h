#ifndef cadastro_h
#define cadastro_h

#include <string>

#include "arvore.h"
#include "paciente.h"

using namespace std;

class notFound : public exception
{
    public:
    const char *what() const throw()
    {
        return "Item nao encontrado\n";
    }

};

class alreadyInserted : public exception
{
    public:
    const char *what() const throw()
    {
        return "Item ja inserido\n";
    }

};

class Cadastro{
    //friend class Arvore;

    friend ostream &operator<<(ostream &output, Cadastro &cadastro);

    private:
        Arvore<Paciente> myArvore;
    public:
        Cadastro();
        void insere(Paciente p);
        Paciente &consulta(string nome);





};


#endif