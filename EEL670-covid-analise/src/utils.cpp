
#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
#include <iomanip>
#include <string>

#include "utils.h"

using namespace std;

void printEntryLine(vector <string> strList){

    cout << "|" << left << setfill(' ') ;
    for (auto& value :strList){
        cout << setw(20) << value << "|";
    }
    cout << endl;
}



void genericDisplay(vector<float> &data,time_t start){
    
    tm *date;
    string dateStr;

    for (auto& value :data){
        date=localtime(&start);
        dateStr = to_string(date->tm_mday) + "/" + to_string(date->tm_mon+1) + "/" + to_string(date->tm_year+1900);

        printEntryLine(
            {   dateStr,
                to_string(value)
            });
        start=start+(60*60*24);
        /*
        cout << "|" << left << setfill(' ') << setw(20)<< 
        dateStr << "|"<<
        setw(20) << value << "|" << endl;
        */

        //next day
        
    }
}

string evaluateTendency(float tendency){
    string output;
    if (tendency > 15){
        output="Alta";
    }
    else if (tendency<-15){
        output="Baixa";
    }
    else
    {
        output="Estável";
    }
    return output;   

}

/*
template <class T> 
T computePercentage(T a,T b){
		T res;
		if (b==0){
			//handle 0 division
			res=std::numeric_limits<T>::infinity();
		}
		else{
			res=((a-b)/b)*100;
		}
		return res;
}
*/
float computePercentage(float a,float b){
		float res;
		if (b==0){
			//handle 0 division
			res=numeric_limits<float>::infinity();
		}
		else{
			res=((a-b)/b)*100;
		}
		return res;
}

