#ifndef cadastro_h
#define cadastro_h

#include <string>

#include "arvore.h"
#include "paciente.h"

using namespace std;


//some exceptions to use when not found in tree
class notFound : public exception
{
    public:
    const char *what() const throw()
    {
        return "Item nao encontrado\n";
    }

};
//if already in the tree 
class alreadyInserted : public exception
{
    public:
    const char *what() const throw()
    {
        return "Item ja inserido\n";
    }

};

//mostly a wraper to Arvore object
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