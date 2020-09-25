#ifndef NACIONAL_H
#define NACIONAL_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "estadual.h"

using namespace std;

bool compareTendency(Estadual a, Estadual b);

class Nacional{
    public:

        Nacional(string name, unsigned N, vector<string> stateNames);
        ~Nacional();
        
        //brasil only
        void displayPercentage();
        void displayAcumulated();
        void displayTendency();

        //all states
        void displayGroup();
        void displayExtremes();

        //wraper for calling state.data
        void displayStatePercentage(string stateName);
        void displayStateAcumulated(string stateName);
        
        void setChoosen_N(unsigned new_N);



    private:
        time_t loadTime();

        vector<float> &getPercentage();
        vector<float> &getAcumulated();
        vector<float> &getMovingSum();
        float getTendency();

        //aux
        Estadual * findState(string stateName);
        void deletePtrs();
        void sortStates();

        string countryName;
        time_t startTime;
        unsigned choosen_N;
        unsigned dataSize;
        vector<Estadual> states;


        vector<float> *acumulated=nullptr;
        vector<float> *percentage=nullptr;
        vector<float> *movingSum=nullptr;


};


#endif