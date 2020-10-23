#ifndef CATALOGO_H
#define CATALOGO_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map> 

using namespace std;

typedef struct Movie
{
    string movieName;
    string producerName;
    double rating;

} Movie;

bool operator==(Movie const& lhs, Movie const& rhs);
bool operator>(Movie const& lhs, Movie const& rhs);
bool operator<(Movie const& lhs, Movie const& rhs);
ostream &operator<<(ostream & lhs, Movie &rhs);


class Catalogo{
    friend ostream &operator<< (ostream & lhs, const Catalogo &rhs);
    friend istream &operator>> (istream & lhs, Catalogo &rhs);
    public:
    
        Catalogo();
        ~Catalogo();

        //insert movie
        vector<Movie> & operator+= (Movie &toAdd);
        //insert movie list
        vector<Movie> & operator+= (vector<Movie> &toAdd);
        //delete a movie
        vector<Movie> & operator-= (Movie &toRemove);


        //search for movie
        Movie * operator() (string name);
        //edit producer
        Movie * operator() (string name,string producer);
        //edit rate
        Movie * operator() (string name,double rate);

        //search for movies
        //impossible to override >  and < operators. Already in use.
        Movie *searchPerRating();
        

        
    private:
        vector<Movie> movieList;

};


#endif