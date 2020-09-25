
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
    movingSum=nullptr;
    importData();
}

void Estadual::importData(){

    ifstream file;
	unsigned line;
	string initDate;
	string path="data/"+stateName+".txt";

    
	file.open(path);
	if (!file.is_open()){
		cerr << "Unable to open " << path <<endl;
		throw invalid_argument("File doesent exists");
	}
	else{
		while(file >> line){
			readData.push_back(line);
		}
	}
	file.close();
    dataSize=readData.size();
}

Estadual::~Estadual(){
    deletePtrs();    
}

void Estadual::displayPercentage(){
    cout << "Evolucao percentual de óbitos para o estado: " << stateName << endl;
    genericDisplay(getPercentage(),startTime);
}

void Estadual::displayAcumulated(){
    cout << "Acumulado de óbitos para o estado: " << stateName << endl;
    genericDisplay(getAcumulated(),startTime);
}

void Estadual::displayTendency(bool verbose){
    if (verbose){
        cout << "Tendencia para o estado: " << stateName << endl;
    }
    
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
    if (choosen_N!=new_N){
        choosen_N=new_N;
        //delete old references
        deletePtrs();
    }
}

vector<float> & Estadual::getPercentage(){

    float last,day;
    vector<float> sum = getMovingSum();
    
    
    if (percentage==nullptr){
        percentage=new vector<float>(dataSize,0);

        //computePercentage iterating over own list
        last=0;
        for (unsigned i=0;i<dataSize;i++){
            day=sum[i]/choosen_N;
		    (*percentage)[i]=percentageAtDay(i,day,last);
            last=day;
	    }

    }
    return *percentage;
    
}

vector<float> & Estadual::getAcumulated(){
    float total;
    if (acumulated==nullptr){
        acumulated=new vector<float>(dataSize,0);

        total=0;
        for (unsigned i=0 ; i<dataSize;i++){
            total=total+readData[i];
            (*acumulated)[i]=total;
        }
    }
    
    return *acumulated;
    
}

vector<float> & Estadual::getMovingSum(){
    unsigned today;
	float total;

    
    //compute avg
    if (movingSum==nullptr){
        movingSum=new vector<float>(dataSize,0);
        (*movingSum)[0]=readData[0];

	    for (today=1; today<dataSize;today++){
            //run until N
            if(today<choosen_N){
                total=(*movingSum)[today-1]+readData[today];
            }
            else{
                total=(*movingSum)[today-1]+readData[today]-readData[today-choosen_N];
            }
            (*movingSum)[today]=total;
        }
    }

    return (*movingSum);
}
vector<float> & Estadual::getReadData(){
    return readData;
}

float Estadual::getTendency(){
    return percentageAtDay(dataSize-1);
}


float Estadual::percentageAtDay(unsigned day){

    vector <float> sum=getMovingSum();

    float dayAvg,lastAvg;
    if (day==0){
		lastAvg=0;
	}
	else{
		lastAvg=((float)sum[day-1])/choosen_N;
	}
	dayAvg=((float)sum[day])/choosen_N;

	return computePercentage(dayAvg,lastAvg);
}

float Estadual::percentageAtDay(unsigned day,float dayAvg, float lastAvg){
	return computePercentage(dayAvg,lastAvg);
}

unsigned Estadual::getDataSize(){
    return dataSize;
}


string & Estadual::getName(){
    return stateName;
}

void Estadual::deletePtrs(){
    cout << stateName<<endl;
    if (acumulated != nullptr)
    {
        cout << "erro1" << endl;
        printf("%p\n",acumulated);
        delete acumulated;
        acumulated = nullptr;
    }
    if (percentage != nullptr)
    {
        cout << "erro2" << endl;
        printf("%p\n",percentage);
        delete percentage;
        percentage = nullptr;
    }
    if (movingSum != nullptr)
    {
        cout << "erro3" << endl;
        printf("%p\n",movingSum);
        delete movingSum;
        movingSum = nullptr;
    }
}














