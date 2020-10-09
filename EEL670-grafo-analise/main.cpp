#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include "classes/grafo.h"
#include "classes/nodes.h"

#define OK 0
#define ERROR 1

using namespace std;

vector<string> split (string &target, string delimiters,unsigned occurences=1);

//simple one character split. recives suport for multiple splits chars in delimiters parameter.
vector<string> split (string &target, string delimiters,unsigned occurences) {

    std::string token;
    vector<string>result;
    const char *content=target.c_str();

    unsigned j=0;
    unsigned events=0;
    for (unsigned i=0; content[i]!='\0';i++) {
        //if found...
        if (delimiters.find(content[i])!=std::string::npos){
            events++;
            if(events==occurences){
                token = target.substr(j+1, i-j-1);
                j=i;
                result.push_back(token);
                events=0;
            }

        }
    }
    return result;
}


//recives a file name and makes the imputs to the graph. SizeNode parameter enables the option for using 'super arestas'
unsigned buildGraph(string fname,Grafo &my_g,unsigned sizeNode){
    string line;
    string text;
    ifstream myfile(fname, ios::out);
    vector<string> palavras;
    unsigned inserted=0;

    if (!myfile.is_open()){
		cerr << "Não foi possivel abrir o arquivo "<< fname <<"." <<endl;
        exit(ERROR);
	}

    //since the scope of the project is only for small texts, there's no problem on put everything on a single string
    while(getline(myfile, line)){
        text+=line;
    }

    
    for (auto frase : split(text,".")){
        palavras=split(frase," ",sizeNode);

        //only include if the sentence has 2 or more words. its nonsense include a vertex that no one points to it, it has no weight.
        if (palavras.size()>2){
            for (unsigned i=0;i<palavras.size()-1;i++ ){
                my_g.insertArestas(palavras[i],palavras[i+1]);
                inserted++;
            }
        }

    }
    return inserted;
    


}


void showHelp(){
    cout << "Uso: ./analise <comando> [nome do arquivo] [-n=tamanho] " << endl
    << "Comandos:" << endl
    <<"[help]                        -> Mostra o display de ajuda."<< endl 
	<<"[palavra]                     -> Calcula a palavra mais utilizada no texto."<<endl
	<<"[sequencia]                   -> Calcula sequencia de tamanho -n=tamanho mais utilizada no texto usando o método de grafos simples."<<endl
    <<"[sequencia2]                   -> Calcula sequencia de tamanho -n=tamanho mais utilizada no texto usando o método de super arestas."<<endl
    <<"A opcao [-n=tamanho] irá configurar o paramêtro N para o cálculo da melhor sequencia de palavras (padrão=3)." << endl
    <<"A opcao obrigatória [nome do arquivo] deve ser o caminho com um arquivo de texto para ser analizada. " << endl; 
    exit(OK);
}

void printList(vector<string> &list){
    unsigned i;
    for (i=0;i<list.size();i++){
        cout << list[i] << "->";
    }
    cout << endl;
}

int main(int argc,char **argv){

    Grafo my_grafo;
    string command;
    string filename;
    string option;
    unsigned res;
    int n_option=3;
    vector<string> result;

    if (argc<3){
		cerr << "Quantidade de Argumentos invalida" << endl;
		showHelp();
	}

    command=argv[1];
    filename=argv[2];


    if (argc>3){
		option=argv[3];
        if (option.substr(0,3)=="-n="){
			n_option=stoi(option.substr(3));
			if (n_option<=0){
				cerr<< "O valor de N deve ser positivo." << endl;
				showHelp();
			}
		}
        
	}

    
	if (command=="help"){
        showHelp();
	}
	else if(command=="palavra"){
        if (!buildGraph(filename,my_grafo,1)){
            cout <<"Não foi possivel criar o grafo. Revise o texto." << endl;
            exit(ERROR);
        }
        cout << "A palavra mais utilizada é: " << my_grafo.mostUsedVertex(&res).getName() << endl;
        cout << "Ocorrencias: " << res << endl;

	}
    else if(command=="sequencia"){
        if (!buildGraph(filename,my_grafo,1)){
            cout <<"Não foi possivel criar o grafo. Revise o texto." << endl;
            exit(ERROR);
        }

        if ((result=my_grafo.getPopularSequence(n_option,&res)).size()>0){
            cout << "A sequencia de palavras mais utilizada é: " <<endl;
            printList (result);
            cout << "Ocorrencias: " << res << endl;
        }
        else{
            cout << "Nao foi possivel encontrar uma sequencia com o tamanho especificado. " <<endl;
        }
	}
    else if(command=="sequencia2"){
        if (!buildGraph(filename,my_grafo,n_option)){
            cout <<"Não foi possivel criar o grafo. Revise o valor de N passado para esta técnica." << endl;
            exit(ERROR);
        }
        cout << "A sequencia mais utilizada é: " <<my_grafo.mostUsedVertex(&res).getName() << endl;
        cout << "Ocorrencias: " << res << endl;
	}
	else{
		cout << "Comando Invalido." << endl;
		showHelp();
	}

}

