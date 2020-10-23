
#include <iostream>
#include <fstream>
#include <algorithm>
#include "catalogo.h"

using namespace  std;



bool operator==( Movie const& lhs, Movie const& rhs ){
    return lhs.movieName == lhs.movieName;
}

bool operator>( Movie const& lhs, Movie const& rhs ){
    return lhs.movieName < lhs.movieName;
}

bool operator<( Movie const& lhs, Movie const& rhs ){
    return lhs.movieName > lhs.movieName;
}

ostream &operator<<(ostream & output, Movie &rhs){
    /*output  << left << setfill(' ') 
    << setw(20) << rhs.movieName 
    << setw(20) << rhs.producerName 
    << setw(20) << rhs.rating 
    << endl;
    */
    output <<  rhs.movieName << " " <<  rhs.producerName << " " << rhs.rating << endl;
    return output;
}

istream &operator>>(istream & input, Movie &rhs){
    /*output  << left << setfill(' ') 
    << setw(20) << rhs.movieName 
    << setw(20) << rhs.producerName 
    << setw(20) << rhs.rating 
    << endl;
    */
    input >>  rhs.movieName >> rhs.producerName >> rhs.rating;
    return input;
}


Catalogo::Catalogo(){
    ifstream inputFile;
    string line;
    inputFile.open("data.txt");
    if (!inputFile.is_open()){
		cerr << "Nao foi possivel abir o arquivo com o catalogo existente. O catalogo comecara vazio" <<endl;
	}
    else
    {
        while(inputFile >> *this){ }
        cout << "Catalogo carregado." << " Tamanho do catalogo: " << movieList.size()<<endl;
    }
    
}

Catalogo::~Catalogo(){
    ofstream output;
    output.open("data.txt", ios::out);
    if (!output.is_open()){
		cerr << "Nao foi possivel abir o arquivo para salvar o catalogo." <<endl;
	}
    else
    {

        output << *this;
        cout << "Catalogo salvo." << " Tamanho do catalogo: " << movieList.size()<<endl;
    }
    
}

ostream &operator<< (ostream & output, const Catalogo &rhs){
/*    output << "|" << left << setfill(' ') 
    << setw(20) << "Nome" << "|"
    << setw(20) << "Produtor" << "|"
    << setw(20) << "Avaliacao" << "|"
    << endl;*/
    for(auto i : rhs.movieList){
        output << i;
    }
    return output;
}

istream &operator>> (istream & input, Catalogo &rhs){
    
    Movie m;
    if (input >> m){
        rhs.operator+=(m); 
    }
    return input;

}


vector<Movie> & Catalogo::operator+= (Movie &toAdd){
    movieList.push_back(toAdd);
    sort (movieList.begin(), movieList.begin());
    return movieList;
}

vector<Movie> & Catalogo::operator+= (vector<Movie> &toAdd){
    movieList.insert(movieList.end(),toAdd.begin(),toAdd.end());
    sort (movieList.begin(), movieList.begin());
    return movieList;
}

vector<Movie> & Catalogo::operator-= (Movie &toRemove){
    
    movieList.erase(find(movieList.begin(),movieList.end(),toRemove));
    return movieList;
}

Movie * Catalogo::operator() (string name){
    Movie *result=nullptr;
    for (Movie &i : movieList){
        if (i.movieName==name){
            result=&i;
            break;
        }
    }
    return result;
}

Movie * Catalogo::operator() (string name,string producer){
    Movie *result=this->operator()(name);
    if (!result){
        result->producerName=producer;
    }
    return result;
}

Movie * Catalogo::operator() (string name,double rate){
    Movie *result=this->operator()(name);
    if (!result){
        result->rating=rate;
    }
    return result;
}

Movie * Catalogo::searchPerRating(){
    double best=0;
    Movie *result=nullptr;

    for (Movie &m : movieList){
        if (m.rating > best){
            best=m.rating;
            result=&m;
        }
    }
    return result;
}
