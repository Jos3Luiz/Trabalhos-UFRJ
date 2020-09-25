#include <iostream>
#include <string>

#include "estadual.h"
#include "nacional.h"


int main(){
    vector <string>stateList = {"AC","AL","AM","AP","BA","CE","DA","DA","DF","ES","GO","MA","MG","MS"
                                ,"MT","PA","PB","PE","PI","PR","RJ","RN","RO","RR","RS","SC","SE","SP","TO"};

    Estadual rio("RJ",7,0);
    cout << "Ola mundo! " << endl;
    //rio.displayAcumulated();
    //rio.displayPercentage();
    //rio.displayTendency();

    Nacional br("Brasil",7,stateList);
    br.displayAcumulated();
    br.displayGroup();
    br.displayPercentage();
    br.displayTendency();
    br.displayStateAcumulated("RJ");

}