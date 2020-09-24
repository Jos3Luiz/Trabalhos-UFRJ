
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "utils.h"
#include "estadual.h"

using namespace std;


Estadual::Estadual(string name,unsigned N,time_t begin){
    stateName=name;
    choosen_N=N;
    startTime=begin;
    acumulated=nullptr;
    percentage=nullptr;
    readData=nullptr;
    importData();
}

void Estadual::importData(){

    ifstream file;
	unsigned line;
	string initDate;
	string path="dados/estados/"+stateName+".txt";

    readData = new vector<float>();
    
	file.open(path);
	if (!file.is_open()){
		cerr << "Unable to open " << path <<endl;
		throw invalid_argument("File doesent exists");
	}
	else{
		while(file >> line){
			readData->push_back(line);
		}
	}
	file.close();
    dataSize=readData->size();
}

Estadual::~Estadual(){
    delete acumulated;
    delete percentage;
    delete readData;
    delete movingSum;
}

void Estadual::displayPercentage(){
    cout << "Evolucao percentual de óbitos para o estado: " << stateName << endl;
    genericDisplay(getPercentage(),startTime);
}

void Estadual::displayAcumulated(){
    cout << "Acumulado de óbitos para o estado: " << stateName << endl;
    genericDisplay(getAcumulated(),startTime);
}

void Estadual::displayTendency(){
    cout << "Tendencia para o estado: " << stateName << endl;
    float tendency;
    tendency=getTendency();
    printEntryLine(
        {
            to_string(tendency),
            evaluateTendency(tendency)
        });
}

void Estadual::setChoosen_N(unsigned new_N)
{
        vector<float> *acumulated;
        vector<float> *percentage;
        vector<float> *readData;
        vector<float> *movingSum;
    
    if (choosen_N!=new_N){
        choosen_N=new_N;

        //delete old references
        if (acumulated!=nullptr){ 
            delete acumulated; 
            acumulated=nullptr;
        }
        if (percentage!=nullptr){ 
            delete percentage; 
            percentage=nullptr;
        }
        if (readData!=nullptr){ 
            delete readData; 
            readData=nullptr;
        }
        if (movingSum!=nullptr){ 
            delete movingSum; 
            movingSum=nullptr;
        }
    }
}

vector<float> & Estadual::getPercentage(){


    if (percentage==nullptr){
        percentage=new vector<float>(dataSize,0);
        //computePercentage
        for (unsigned i=0;i<dataSize;i++){
		    (*percentage)[i]=percentageAtDay(i);
	    }

    }
    return *percentage;
    
}

vector<float> & Estadual::getAcumulated(){
    float total;
    if (acumulated==nullptr){
        acumulated=new vector<float>(dataSize,0);
        total=0;
        for (float &i : *readData){
            total=total+i;
            (*acumulated)[i]=total;
        }
        
    }
    
    return *acumulated;
    
}

vector<float> & Estadual::getData(){
    return *readData;
}

float Estadual::getTendency(){
    return percentageAtDay(dataSize-1);
}

vector<float> & Estadual::getMovingSum(){
    unsigned today;
	float total;
    vector <float> &movingSumRef=*movingSum;
    vector <float> &readDataRef=*readData;
    
    //compute avg
    if (movingSum==nullptr){
        
        movingSum=new vector<float>(dataSize,0);
        movingSumRef[0]=readDataRef[0];

	    for (today=1; today<dataSize;today++){
            //run until N
            if(today<choosen_N){
                total=movingSumRef[today-1]+readDataRef[today];
            }
            else{
                total=movingSumRef[today-1]+readDataRef[today]-readDataRef[today-choosen_N];
            }
            movingSumRef[today]=total;
        }
    }

    return movingSumRef;
}



float Estadual::percentageAtDay(unsigned day){
    vector <float> movingSum=getMovingSum();
    float dayAvg,lastAvg;
    if (day==0){
		lastAvg=0;
	}
	else{
		lastAvg=((float)movingSum[day-1])/choosen_N;
	}
	dayAvg=((float)movingSum[day])/choosen_N;

	return computePercentage<float>(dayAvg,lastAvg);
}
















