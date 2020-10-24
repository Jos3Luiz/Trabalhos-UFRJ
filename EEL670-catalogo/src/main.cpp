
#include <iostream>
#include <string>
#include "classes/catalogo.h"

#define OK 0
#define ERROR 1

using namespace std;

void showHelp(){
    cout << "Uso: ./catalogo  <comando> " << endl
    << "Parametros adicionais serão passados de forma interativa." << endl
    << "Obs: O nome do filme deve ser constituido de apenas um nome sem espacos" << endl
    << "Comandos:" << endl
    <<"[help]                  -> Mostra o display de ajuda."<< endl 
	<<"[inserir]              -> parametros: <nome> <nomeProdutora> <notaFilme> Insere o filme no catalogo"<<endl
	<<"[remover]              -> parametros: <nome> Remove o filme do catalogo."<<endl
    <<"[edicaoProdutora]      -> parametros: <nome> <novaProdutora> altera o nome da produtora do filme"<<endl
    <<"[edicaoNota]           -> parametros: <nome> <novaNota> altera a nota do filme"<<endl
    <<"[exibir]               -> Exibe todo o catalogo."<<endl
    <<"[buscaPorNota]         -> Exibe o filme mais bem avaliado."<<endl
    <<"[buscaPorNome]         -> Retorna os dados daquele filme."<<endl;
    exit(OK);
}

void checkArgc(int argc,int desired){
    if(argc<desired){
        cout << "Quantidade de arguementos insuficiente" << endl;
        showHelp();
    }
}
double getRate(char *string){
    size_t sz;
    double result;
    result=stod(string,&sz);
    return result;

}
int main(int argc,char **argv){

    Catalogo my_catalogo;
    Movie new_movie;
    string command;
    Movie *movie_ptr;

    string movie_name;
    string producer_name;
    double rating;


    if (argc<2){
		cerr << "Quantidade de Argumentos invalida" << endl;
		showHelp();
	}

    command=argv[1];


    
	if (command=="help"){
        showHelp();
	}
	else if(command=="inserir"){
        cout << "insira os dados do filme no formato <nome> <produtora> <nota>" << endl;
        cin >> new_movie;
        my_catalogo+=new_movie;
	}
    else if(command=="remover"){
        cout << "insira o nome do filme" << endl;
        cin >> movie_name;
        if(not (my_catalogo-=movie_name)){
            cout << "Nome inexistente" << endl;
        }
	}
    else if(command=="edicaoProdutora"){
        cout << "insira o nome do filme"<< endl;
        cin >> movie_name;
        cout << "insira o nome da produtora"<< endl;
        cin >> producer_name;
        if(!my_catalogo(movie_name,producer_name)){
            cout << "Nome inexistente" << endl;
        }
	}
    else if(command=="edicaoNota"){
        cout << "insira o nome do filme"<< endl;
        cin >> movie_name;
        cout << "insira a nota do filme"<< endl;
        cin >> rating;
        if(!my_catalogo(movie_name,rating)){
            cout << "Nome inexistente" << endl;
        }
    }
    else if(command=="exibir"){
        cout << my_catalogo;
	}
    else if(command=="buscaPorNota"){
        if((movie_ptr=my_catalogo.searchPerRating())){
            cout << *movie_ptr;
        }
       
	}
    else if(command=="buscaPorNome"){
        cout << "insira o nome do filme"<< endl;
        cin >> movie_name;
        if((movie_ptr=my_catalogo(movie_name))){
            cout << *movie_ptr;
        }
       
	}
	else{
		cout << "Comando Invalido." << endl;
		showHelp();
	}

}
