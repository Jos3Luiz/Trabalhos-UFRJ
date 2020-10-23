
#include <iostream>
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
    output << "|" << left << setfill(' ') 
    << setw(20) << rhs.movieName << "|"
    << setw(20) << rhs.producerName << "|"
    << setw(20) << rhs.rating << "|"
    << endl;
    return output;
}


Catalogo::Catalogo(){
    cout << "Build catalogo" << endl;
}

Catalogo::~Catalogo(){
    cout << "deleting catalogo" << endl;
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

ostream &operator<< (ostream & output, const Catalogo &rhs){
    output << "|" << left << setfill(' ') 
    << setw(20) << "Nome" << "|"
    << setw(20) << "Produtor" << "|"
    << setw(20) << "Avaliacao" << "|"
    << endl;
    for(auto i : rhs.movieList){
        output << i;
    }
    return output;
}

istream &operator>> (istream & input, Catalogo &rhs){
    Movie m;
    cin >> m.movieName >> m.producerName >> m.rating;
    rhs.operator+=(m);
    return input;

}
