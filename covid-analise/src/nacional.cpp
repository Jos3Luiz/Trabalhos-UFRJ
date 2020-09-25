#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <map>

#include "Nacional.h"
#include "estadual.h"
#include "utils.h"


bool compareTendency(Estadual a, Estadual b){
	float t1,t2;
	t1=a.getTendency();
	t2=b.getTendency();
	return (t1 > t2);
}


Nacional::Nacional(string name, unsigned N, vector<string> stateNames){
    
    unsigned c=0;
    startTime=loadTime();
    countryName=name;
    choosen_N=N;
    
    for (string &s: stateNames){
        
        states.push_back(Estadual(s,choosen_N,startTime));
        if (c>0){
            if(states[c].getDataSize()!=states[c-1].getDataSize()){
                invalid_argument("A lista contendo os dados de cada estado deve possuir o mesmo tamanho");
            }
        }
        c++;

    }
    dataSize=states[0].getDataSize();
    if (dataSize<choosen_N){
        cerr << "CUIDADO! PARAMETRO N ESCOLHIDO E SUPERIOR AO TAMANHO DO DATASET!" << endl;
    }

}

time_t Nacional::loadTime(){
    
    ifstream file;
	time_t initDate;

	file.open("data/DATE.txt");
	if (!file.is_open()){
		cerr << "Unable to open DATE.txt to load begin date." <<endl;
		throw invalid_argument("File doesent exists");
	}
	file >> initDate;
	file.close();

    return initDate;
}

//not Thread Safe, beware!!!!
void Nacional::setChoosen_N(unsigned new_N)
{
    if (choosen_N!=new_N){
        choosen_N=new_N;
        //delete old data
        acumulated.clear();
        percentage.clear();
        movingSum.clear();
    }
    for(Estadual &e : states){
        e.setChoosen_N(new_N);
    }
}

void Nacional::displayPercentage(){
    cout << "Evolucao percentual de óbitos para : " << countryName << endl;
    genericDisplay(getPercentage(),startTime);
}

void Nacional::displayAcumulated(){
    cout << "Evolucao do acumulado de óbitos para : " << countryName << endl;
    genericDisplay(getAcumulated(),startTime);
}

void Nacional::displayTendency(){
    float tendency=getTendency();

    cout << "Tendencia para : " << countryName << endl;
    printEntryLine(
        {
            to_string(tendency),
            evaluateTendency(tendency)
        });
}

void Nacional::displayGroup(){

    sortStates();
    cout << "Tendencia dos estados agrupada : " << countryName << endl;
    for(Estadual &e: states){
        e.displayTendency(false);
    }
}

void Nacional::displayExtremes(){
    sortStates();
    cout << "Extremos dos estados: " << countryName << endl;
    states[0].displayTendency();
    states[dataSize-1].displayTendency();
    
}

void Nacional::displayStatePercentage(string stateName){
    Estadual *e;
    e=findState(stateName);
    if (e!=nullptr){
        e->displayPercentage();
    }
}

void Nacional::displayStateAcumulated(string stateName){
    Estadual *e;
    e=findState(stateName);
    if (e!=nullptr){
        e->displayAcumulated();
    }
}

Estadual * Nacional::findState(string stateName){
    Estadual *statePtr=nullptr;
    for(Estadual &e: states){
        if (e.getName()==stateName){
            statePtr = &e;
        }
    }
    return statePtr;
    
}

vector<float> &Nacional::getPercentage(){

    float last,day;
    vector<float> sum = getMovingSum();
    
    if (percentage.size()==0){
        percentage= vector<float>(dataSize,0);

        //computePercentage iterating over own list
        last=0;
        for (unsigned i=0;i<dataSize;i++){
            day=sum[i]/choosen_N;
		    percentage[i]=computePercentage(day,last);
            last=day;
	    }

    }
    return percentage;

}

vector<float> & Nacional::getMovingSum(){

    vector<float> iter;
    if (movingSum.size()==0){

        movingSum=vector<float>(dataSize,0);
        for(Estadual &e : states){
            iter=e.getMovingSum();
            for (unsigned i=0;i<dataSize;i++){
                movingSum[i]=movingSum[i] + iter[i];
            }
        }
    }
    return movingSum;
}

vector<float> & Nacional::getAcumulated(){

    
    vector<float> iter;
    if (acumulated.size()){        
        acumulated=vector<float>(dataSize,0);
        for(Estadual &e : states){
            iter=e.getAcumulated();
            for (unsigned i=0;i<dataSize;i++){
                acumulated[i]=acumulated[i] + iter[i];
            }
        }
    }
    return acumulated;
}

float Nacional::getTendency(){

    return computePercentage(
        getMovingSum()[dataSize-1],
        getMovingSum()[dataSize-2]
        );
}

void Nacional::sortStates(){
    sort(states.begin(),states.end(),compareTendency);
}