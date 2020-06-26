#ifndef ALU_H
#define ALU_H

#include <QMainWindow>
#include <QWidget>
#include "cmath"

using namespace std;

union Code
{

    struct IEEE754
    {
        unsigned int partFrac : 23; //un float internamente se almacena como 4 bytes = 32 bits, entonces aqui estoy definiendo unos bytes que suman 32 y que en realidad al compartirse la memoria (mi float en binario) es accesible por estos campos pero solamente cada uno de ellos cogería el numero de bits que tiene estipulado del total de 32 que ocupa mi float
        unsigned int expo : 8; //es realmente para hacernos una idea el cuadrito de la division de estandar IEEE 754
        unsigned int signo : 1;
    }IEEE754;

    float numero; //almacena el numero original o a devolver
};

class alu
{
public:
    alu();
    union Code suma(union Code A, union Code B);
    union Code producto(union Code A, union Code B);
    union Code division(union Code A, union Code B);
    bool infinito;
    bool nan;
    bool denormal;

private:
    vector<unsigned int> pasarBinario(unsigned int num, int j);
    static unsigned int pasarDecimal(vector<unsigned int> binario);
    static double pasarAEscalar(unsigned int binario);
    void multiplicacionBinariaSinSigno(unsigned int *A, unsigned int B, unsigned int *P);


};

#endif // ALU_H
