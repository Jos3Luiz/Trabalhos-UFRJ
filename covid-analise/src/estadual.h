#ifndef ESTADUAL_H
#define ESTADUAL_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Estadual{
    public:
        Estadual(string Name,unsigned N,time_t begin);
        ~Estadual();

        //unused
        void setChoosen_N(unsigned new_N);

        vector<float> &getPercentage();
        vector<float> &getAcumulated();
        vector<float> &getData();
        vector<float> &getMovingSum();
        float getTendency();

        //display stuff
        void displayPercentage();
        void displayAcumulated();
        void displayTendency();

    private:
        void importData();
        float percentageAtDay(unsigned day);
        
        unsigned choosen_N;
        time_t startTime;
        string stateName;
        float dataSize;

        vector<float> *acumulated;
        vector<float> *percentage;
        vector<float> *readData;
        vector<float> *movingSum;

};

#endif