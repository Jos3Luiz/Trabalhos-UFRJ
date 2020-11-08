#ifndef paciente_h
#define paciente_h
#include <string>

using namespace std;

class Paciente{

    friend ostream &operator <<(ostream &lhs,Paciente&rhs);

    private:
        string name;
    public:
        Paciente(string init_name);
        Paciente();
        Paciente(const Paciente &paciente);
        string &getName();

        bool operator>(Paciente const& other);
        bool operator<(Paciente const& other); 
        bool operator==(Paciente const& other); 

};

class Paciente_internado : Paciente{
    friend ostream &operator <<(ostream &lhs,Paciente_internado&rhs);

    private:
        string disease;
    public:
        string &getDisease();

};



#endif