#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "estadual.h"
#include "nacional.h"

#define OK 0
#define ERROR 1

void showHelp(){
    cout << "Uso: ./covid <comando> [estado] [-n=tamanho]" << endl
    << "Comandos:" << endl
    <<"[help]                        -> Mostra o display de ajuda."<< endl 
	<<"[porcentagemEstado]           -> Calcula a série histórica da porcentagem em relação ao valor de obitos no estado pedido."<<endl
	<<"[porcentagemNacao]            -> Calcula a série histórica da porcentagem em relação ao valor de obitos no país."<<endl
	<<"[categoriaEstado]             -> Informa uma lista de estados com suas respectivas situações: queda, estavel ou crescente."<<endl
	<<"[categoriaNacao]              -> Informa se o país está em queda, estável em crescente."<<endl
	<<"[extremos]                    -> Informa o estado que está com maior crescimento e maior queda"<< endl
	<<"[acumuladoEstado]             -> Calcula a série histórica dos valor acumulados do estado pedido."<<endl
	<<"[acumuladoNacao]              -> Calcula a série histórica dos valor acumulados da nação." <<endl
    <<"[listarDisponiveis]           -> Mostra a Lista dos estados disponiveis para consulta." << endl
    <<"A opcao [-n=tamanho] irá configurar o paramêtro N para o cálculo da média móvel (padrão=7)." << endl
    <<"Código fonte disponível em : https://github.com/Jos3Luiz/Trabalhos-UFRJ/tree/master/covid-analise/src " << endl; 
    exit(OK);
}

string getEstado(int argc , char **argv){
    string response="";
	if (argc<=2){
		cerr << "E necessario passar o nome do estado"<< endl;
        showHelp();
	}
	else{
		response=string(argv[2]);
	}
    return response;
}

void printBanner(){
    ifstream file;
    string line;
    file.open("banner.txt");
    if (!file.is_open()){
		cerr << "Unable to open banner.txt" <<endl;
		throw invalid_argument("File doesent exists");
	}
    while(getline(file, line)){
        cout << line << endl;
    }

}

int main(int argc,char **argv){
    

    vector <string>stateList = {"AC","AL","AM","AP","BA","CE","DA","DA","DF","ES","GO","MA","MG","MS"
                                ,"MT","PA","PB","PE","PI","PR","RJ","RN","RO","RR","RS","SC","SE","SP","TO"};

    string parameter;
    unsigned n_option=7;

    if (argc==1){
        printBanner();
    }
    

	for (int i=0;i<argc;i++){	
		parameter=argv[i];	
		if (parameter=="help"){
			showHelp();
		}
		if (parameter.substr(0,3)=="-n="){
			n_option=stoi(parameter.substr(3));
			if (n_option<=0){
				cerr<< "O valor de N deve ser positivo" << endl;
				exit(ERROR);
			}
		}
	}

    Nacional brasil("Brasil",n_option,stateList);
	if (argc<=1){
		cerr << "Quantidade de Argumentos invalida" << endl;
		showHelp();
	}
	
	parameter=argv[1];
	if (parameter=="porcentagemEstado"){
		string estado=getEstado(argc,argv);
		brasil.displayStatePercentage(estado);
	}
	else if(parameter=="porcentagemNacao"){
		brasil.displayPercentage();
	}
	else if(parameter=="categoriaEstado"){
		brasil.displayGroup();
	}
	else if(parameter=="categoriaNacao"){
		brasil.displayTendency();
	}
	else if(parameter=="extremos"){
		brasil.displayExtremes();
	}
	else if(parameter=="acumuladoEstado"){
		string estado=getEstado(argc,argv);
		brasil.displayStateAcumulated(estado);
	}
	else if(parameter=="acumuladoNacao"){
		brasil.displayAcumulated();
	}
    else if(parameter=="listarDisponiveis"){
        cout << "Lista dos estados disponíveis: " << endl;
		for(string &s : stateList){
            cout << s << endl;
        }
	}
	else{
		cout << "Comando Invalido." << endl;
		showHelp();
	}

}