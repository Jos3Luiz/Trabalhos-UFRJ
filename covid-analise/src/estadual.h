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
        void setChoosen_N(unsigned new_N);

        vector<float> &getPercentage();
        vector<float> &getAcumulated();
        vector<float> &getReadData();
        vector<float> &getMovingSum();
        float getTendency();

        //display stuff
        void displayPercentage();
        void displayAcumulated();
        void displayTendency(bool verbose=true);

        //info
        unsigned getDataSize();
        string &getName();

    private:
        void importData();
        float percentageAtDay(unsigned day);
        float percentageAtDay(unsigned day,float dayAvg, float lastAvg);

        void deletePtrs();
        
        unsigned choosen_N;
        time_t startTime;
        string stateName;
        float dataSize;

        vector<float> readData;

        vector<float> *acumulated=nullptr;
        vector<float> *percentage=nullptr;
        vector<float> *movingSum=nullptr;

       

};

#endif