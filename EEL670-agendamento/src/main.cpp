
#include <iostream>
#include <string>
#include <stdlib.h>

#include "classes/cadastro.h"
#include "classes/paciente.h"

using namespace std;
typedef enum opcao{op_exibir,op_inserir,op_buscar,op_ajuda,op_sair} options;


//for read option
istream& operator>>( istream& is, options& i )
{
    int tmp ;
    if ( is >> tmp ){
        tmp--;
        i = static_cast<options>( tmp ) ;
    }
        
    if (i>op_sair || i <op_exibir){
        cout << "Opcao invalida!!";
        i=op_sair;
    }
    return is ;
}

options getOpt(){
    options result;
    cout 
    << "1. Exibir Pacientes" << endl
    << "2. Inserir Paciente" << endl
    << "3. Buscar Paciente" << endl
    << "4. Ajuda" << endl
    << "5. Sair" << endl;
    cout <<"Escolha um numero: ";
    cin >> result;
    return result;
}

void exibir(Cadastro &myCadastro){
    cout << "Exibindo Toda a lista de cadastrados:"<<endl;
    cout << myCadastro ; 
}

void inserir(Cadastro &myCadastro){
    char result;
    Paciente *p;

    cout 
    << "1. Paciente generico" << endl
    << "2. Paciente doente" << endl
    << "3. Paciente internado" << endl
    << "Escolha um tipo de paciente: ";
    cin >> result;
    cout << "Insira o nome do paciente: ";
    switch (result)
    {
    case '1':
        p = new Paciente;
        break;
    case '2':
        p = new Paciente_Doente;
        break;
    case '3':
        p = new Paciente_Internado;
        break;  
    default:
        cout << "tipo de paciente inexistente." << endl;
        return;
        break;


    }
    cin >> *p;
    try{
        myCadastro.insere(*p);
    }
    catch(const alreadyInserted &e){
        cout << "Uma exceção ocorreu mas foi tratada!: "<< endl;
        cerr<< e.what();

    }
    delete p;

}

void buscar(Cadastro &myCadastro){
    string nome;
    cout << "Insira o nome do paciente: ";
    cin >> nome; 
    cout << "Exibindo detalhes do paciente:"<< endl;

    try{
        cout << myCadastro.consulta(nome);
    }
    catch(const notFound &e){
        cout << "Uma exceção ocorreu mas foi tratada!: "<< endl;
        cerr<< e.what();

    }

}

void ajuda(){
    cout << "Exibindo menu de ajuda" << endl;
}

int main(){
    Cadastro myCadastro;
    opcao escolha;
    bool isRunning=true;
    while (isRunning){
        escolha=getOpt();
        
        switch (escolha)
        {
        case op_exibir:
            exibir(myCadastro);
            break;
        case op_inserir:
            inserir(myCadastro);
            break;
        case op_buscar:
            buscar(myCadastro);
            break;
        case op_ajuda:
            ajuda();
            break;
        case op_sair:
            cout << "Saindo..." << endl;
            isRunning=false;
            break;
        
        
        default:
            cout << "Opção invalida!"<< endl;
            break;
        }
        cout << endl;

    }


    return 0;

    
    
}
