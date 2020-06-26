#include "alu.h"

alu::alu()
{

}

vector<unsigned int> alu::pasarBinario(unsigned int num, int j)
{
    vector<unsigned int> binario;
    int k;
    int n = num;
    int i = j;
    for (k = i - 1; k >= 0; k--) {
        unsigned int h = (((n >> k) & 1) ? 1 : 0);
        binario.push_back(h);

    }
    return binario;
}

unsigned int alu::pasarDecimal(vector<unsigned int> binario)
{
    unsigned int retorno = 0;
    unsigned int exp = (int)binario.size()-1;

    for(int i = 0; i < (int)binario.size(); i++)
    {
        retorno = retorno + binario[i]*pow(2, exp);

        exp--;
    }

    return retorno;
}

double alu::pasarAEscalar(unsigned int binario)
{
    double retorno = 0.0;
    unsigned int exp = 1;

    for(int i = 22; i >= 0; i--)
    {
        retorno = retorno + (((binario >> i) & 1) * (1/pow(2, exp)));

        exp++;
    }

    return (1 + retorno);
}

void alu::multiplicacionBinariaSinSigno(unsigned int *A, unsigned int B, unsigned int *P)
{

    unsigned int c = 0;
    vector<unsigned int> prueba1;
    vector<unsigned int> prueba2;

    for(int i = 0; i < 24; i++)
    {
        if(((*A >> 0) & 1) == 1)
        {
            *P = *P + B;
            c = *P >> 24;
        }
        else
        {
            *P = *P + 0;
        }

        *A = *A >> 1;

        if(((*P >> 0) & 1) == 1)
        {
            *A = *A + pow(2, 23);
        }

        *P = *P >> 1;

        if(c == 1)
        {
            *P = *P + pow(2, 31);
        }

        c = c >> 1;
    }
}

/***************SUMA***************/

union Code alu::suma(union Code A, union Code B)
{
    /*Paso 1*/

    vector<unsigned int> P;
    unsigned int  g, r, st = 0;
    unsigned int n = 24;
    unsigned int d = 0;
    unsigned int c1 = 0;
    bool Operandos_intercambiados = false;
    bool Complementado_P = false;

    union Code partesNumA;
    partesNumA = A;



    /*Mantisa de A*/

    union Code partesNumB;
    partesNumB = B;

    vector<unsigned int> manABinario;

    if(partesNumA.IEEE754.expo == 0)
    {
        manABinario = pasarBinario(partesNumA.IEEE754.partFrac, 23);
        reverse(manABinario.begin(), manABinario.end());
        manABinario.push_back(0);
        reverse(manABinario.begin(), manABinario.end());
        partesNumA.IEEE754.expo = 1;
    }
    else
    {
        manABinario = pasarBinario(partesNumA.IEEE754.partFrac, 23);
        reverse(manABinario.begin(), manABinario.end());
        manABinario.push_back(1);
        reverse(manABinario.begin(), manABinario.end());
    }

    /*Mantisa de B*/
    vector<unsigned int> manBBinario;

    if(partesNumB.IEEE754.expo == 0)
    {

        manBBinario = pasarBinario(partesNumB.IEEE754.partFrac, 23);
        reverse(manBBinario.begin(), manBBinario.end());
        manBBinario.push_back(0);
        reverse(manBBinario.begin(), manBBinario.end());
        partesNumB.IEEE754.expo = 1;

    }
    else
    {
        manBBinario = pasarBinario(partesNumB.IEEE754.partFrac, 23);
        reverse(manBBinario.begin(), manBBinario.end());
        manBBinario.push_back(1);
        reverse(manBBinario.begin(), manBBinario.end());

    }

    union Code partesNumRes;


    /*EXCEPCION*/

    if(partesNumA.IEEE754.expo == partesNumB.IEEE754.expo && partesNumA.IEEE754.partFrac == partesNumB.IEEE754.partFrac && partesNumA.IEEE754.signo != partesNumB.IEEE754.signo)
    {
        partesNumRes.numero = 0;
        return partesNumRes;
    }




    /*Paso 2*/

    if(partesNumA.IEEE754.expo < partesNumB.IEEE754.expo)
    {
        /* Intercambio de las uniones*/

        union Code aux;
        aux = partesNumA;
        partesNumA = partesNumB;
        partesNumB = aux;

        /* Actualizacion de las variables iniciales */

        vector<unsigned int> mantAux;
        mantAux = manABinario;
        manABinario = manBBinario;
        manBBinario = mantAux;

        /* Cambiar testigo */

        Operandos_intercambiados = true;

    }

    /*Paso 3*/

    partesNumRes.IEEE754.expo = partesNumA.IEEE754.expo;
    if(partesNumRes.IEEE754.expo == 255)
    {
        infinito = true;
        return partesNumRes;
    }

    d = partesNumA.IEEE754.expo - partesNumB.IEEE754.expo;
    /*Paso 4*/

    if(partesNumA.IEEE754.signo != partesNumB.IEEE754.signo)
    {
        unsigned int manBDecimal = pasarDecimal(manBBinario);
        manBDecimal = (~(manBDecimal)) + 1;
        manBBinario = pasarBinario(manBDecimal, 24);
    }

    /*Paso 5*/

    P = manBBinario;

    /*Paso 6*/

    reverse(P.begin(), P.end()); //Se voltea el vector para acceder a los índices menos significativos

    if(d >= 1)
    {

        g = P[d-1];

    }

    if(d >= 2)
    {

        r = P[d-2];


    }

    if(d >= 3)
    {
        unsigned int i = 3;
        unsigned int ORING = 0;
        while(i <= d)
        {
            ORING = P[d-i];
            st = st | ORING;
            i++;
        }


    }

    reverse(P.begin(), P.end()); //se restaura el orden del vector


    /*Paso 7*/

    vector<unsigned int> aux;
    if(partesNumA.IEEE754.signo != partesNumB.IEEE754.signo)
    {
        for(unsigned int i = 0; i < d; i++)
        {
            aux.push_back(1);
        }

        for(int j = d; j < (int)P.size(); j++)
        {
            aux.push_back(P[j-d]);
        }

        P = aux;
    }
    else
    {
        for(unsigned int i = 0; i < d; i++)
        {
            aux.push_back(0);
        }

        for(int j = d; j < (int)P.size(); j++)
        {
            aux.push_back(P[j-d]);
        }

        P = aux;
    }

    /*Paso 8*/
    unsigned int P_decimal = 0;
    P_decimal = pasarDecimal(manABinario) + pasarDecimal(P);
    c1 = P_decimal >> 24;



    /*Paso 9*/
    P = pasarBinario(P_decimal, 24);

    if(partesNumA.IEEE754.signo != partesNumB.IEEE754.signo && P[n-1] == 1 &&  c1 == 0)
    {
        for(int i = 0; i < (int)P.size(); i++)
        {
            if(P[i] == 1)
            {
                P[i] = 0; //cambio de los 1 por 0 y viceversa
            }
            else
            {
                P[i] = 1;
            }

            if(i == (int)P.size()-1)
            {
                P[i] = P[i] ^ 1; //se le suma una al ultimo bit
            }
        }
        Complementado_P = true;
    }


    /*Paso 10*/
    if(partesNumA.IEEE754.signo == partesNumB.IEEE754.signo && c1 == 1)
    {
        st = g | r | st;
        r = P[23];
        vector<unsigned int> aux;
        aux.push_back(c1);
        for(int i = 0; i < (int)P.size()-1; i++)
        {
            aux.push_back(P[i]);
        }
        P = aux;

        partesNumRes.IEEE754.expo = partesNumRes.IEEE754.expo + 1;
    }
    else
    {
        unsigned int k = 0;
        while(P[0] != 1 && k < 24)
        {
            for(int i = 1; i < (int)P.size(); i++)
            {
                P[i-1] = P[i];
            }
            P[23] = g;
            k++;
        }

        if(k == 0)
        {
            st = r | st;
            r = g;
        }

        if(k > 1)
        {
            r = 0;
            st = 0;
        }

        unsigned int suma = partesNumRes.IEEE754.expo - k;

        if((int) suma <= 0)
        {
            partesNumRes.IEEE754.expo = 1;
        }
        else
        {
            partesNumRes.IEEE754.expo = suma;
        }

    }
    /*Paso 11*/
    if ((r == 1 && st == 1) || (r == 1 && st == 0 && P[23]))
    {
        unsigned int P_decimal = pasarDecimal(P);
        P_decimal = P_decimal + 1;
        unsigned int c2 = P_decimal >> 24;
        P = pasarBinario(P_decimal, 24);

        if(c2 == 1)
        {
            for(int i = 1; i < (int)P.size(); i++)
            {
                P[i-1] = P[i];
            }
            P[23] = c2;
            partesNumRes.IEEE754.expo = partesNumRes.IEEE754.expo + 1;
        }
    }


    partesNumRes.IEEE754.partFrac = pasarDecimal(P);
    /*Paso 12*/
    if(Operandos_intercambiados == false &&   Complementado_P == true)
    {
        partesNumRes.IEEE754.signo = partesNumB.IEEE754.signo;
    }
    else
    {
        partesNumRes.IEEE754.signo = partesNumA.IEEE754.signo;

    }
    /*Paso 13*/

    return partesNumRes;

}

/***************MULIPLICACION***************/

union Code alu::producto(union Code A, union Code B)
{
    union Code partesNumA = A;
    union Code partesNumB = B;
    union Code partesNumRes;
    unsigned int n = 24;
    unsigned int P = 0;
    unsigned int r = 0;
    unsigned int st = 0;
    unsigned int t = 0;

    /*EXCEPCIONES*/

    if(partesNumA.numero == 0.0)
    {
        if(partesNumB.IEEE754.expo == 255 && partesNumB.IEEE754.partFrac == 0)
        {
            nan = true;
            return partesNumRes;
        }
        else
        {
            partesNumRes.numero = 0;
            return partesNumRes;
        }


    }
    else if(partesNumB.numero == 0.0)
    {

        if(partesNumA.IEEE754.expo == 255 && partesNumA.IEEE754.partFrac == 0)
        {
            nan = true;
            return partesNumRes;
        }
        else
        {
            partesNumRes.numero = 0;
            return partesNumRes;
        }

    }

    //PASO 1

    partesNumRes.IEEE754.signo = partesNumA.IEEE754.signo ^ partesNumB.IEEE754.signo;

    //PASO 2

    unsigned int expA = partesNumA.IEEE754.expo - 127;
    unsigned int expB = partesNumB.IEEE754.expo - 127;

    unsigned int suma = (int)expA + (int)expB + 127;

    if(suma > 255)
    {
        partesNumRes.IEEE754.expo = 255;
    }
    else
    {
        partesNumRes.IEEE754.expo = suma;
    }


    //PASO 3

    vector<unsigned int> manABinario = pasarBinario(partesNumA.IEEE754.partFrac, 23);
    reverse(manABinario.begin(), manABinario.end());
    manABinario.push_back(1);
    reverse(manABinario.begin(), manABinario.end());

    vector<unsigned int> manBBinario = pasarBinario(partesNumB.IEEE754.partFrac, 23);
    reverse(manBBinario.begin(), manBBinario.end());
    manBBinario.push_back(1);
    reverse(manBBinario.begin(), manBBinario.end());
    //convertimos las mantisas a decimal una vez anexado el 1 para tener los 24
    unsigned int manADecimal = pasarDecimal(manABinario);
    unsigned int manBDecimal = pasarDecimal(manBBinario);


    multiplicacionBinariaSinSigno(&manADecimal, manBDecimal, &P);
    //vector<unsigned int> PVector = pasarBinario(P, 24);



    if(((P >> (n-1)) & 1) == 0)
    {

        P = P << 1;

        if(((manADecimal >> (n - 1)) & 1) == 1) //si el primoero por la izquierda de A es un 1, hay que insertar un uno en la derecha de P
        {
            P = P + pow(2,0);  // p = (p << 1) + 1
        }

        manADecimal = manADecimal << 1;




    }
    else
    {
        //sumar uno al exp del producto

        partesNumRes.IEEE754.expo = partesNumRes.IEEE754.expo + 1;
        suma = suma + 1;

    }

    r = ((manADecimal >> (n-1)) & 1); //grabamos el resultado del and, si el 23 es 1, 1 y si es 0, 0


    for(int i = n - 2; i >= 0; i --)
    {
        st = st | ((manADecimal >> (i)) & 1);
    }

    if((r == 1 && st == 1) || (r == 1 && st == 0 && (((P >> 0) & 1) == 1)))
    {
        P = P + 1;
    }

    /*DESBORDAMIENTOS*/

    if((int)suma >= 255) //overflow y nos da un infinito
    {
        infinito = true;
        return partesNumRes;
    }
    else if((int)suma < 1) //underflow (expo < 1 que es el minimo representable 2^0)
    {
        //t = 1 - partesNumRes.IEEE754.expo;
        t = 1 - suma;
        if(t >= n) //underflow no hay bits sufiecientes para poder representar el numero, se desplazaria tanto la mantisa que se pierden todos los bits
        {
            //pintamos que es not a number (mantisa se queda sin bits)
            nan = true;
            return partesNumRes;
        }
        else //va a ser un denormal del que pintaremos la aproximacion
        {
            manADecimal = manADecimal >> t;

            for(int i = 0; i < (int)t; i++){

                if(((P >> i) & 1) == 0){

                    manADecimal = manADecimal >> 1;
                }else{
                    manADecimal = manADecimal >> 1;
                    manADecimal = manADecimal + pow(2, 23);
                }
            }
            P = P >> t;


            partesNumRes.IEEE754.expo = 1; //para representar la aproximacion del denormal porque si 0 no se puede representar


        }
    }

    /*CASOS DENORMALES*/

    if(partesNumA.IEEE754.expo == 0 || partesNumB.IEEE754.expo == 0)
    {

        if(partesNumRes.IEEE754.expo > 1)
        {

            unsigned int t1 = partesNumRes.IEEE754.expo - 1;
            unsigned int t2 = 0;
            int i = 23;
            while(((P >> i) & 1) == 1)
            {
                t2++;
            }

            t = min(t1, t2);
            partesNumRes.IEEE754.expo = partesNumRes.IEEE754.expo - t;

            for(int i = 23; i > (23-(int)t); i--){

                if(((manADecimal >> i) & 1) == 0){

                    P = P << 1;
                }else{
                    P = P << 1;
                    P = P + pow(2, 0);
                }
            }

            manADecimal = manADecimal << t;

            partesNumRes.IEEE754.partFrac = P;
            return partesNumRes;

        }
        else
        {
            partesNumRes.IEEE754.partFrac = P;
            denormal = true;
            return partesNumRes;
        }


    }
    else
    {
        partesNumRes.IEEE754.partFrac = P;
        return partesNumRes;
    }
}

/***************DIVISION***************/

union Code alu::division(union Code A, union Code B)
{
    union Code partesNumA = A;
    union Code partesNumB = B;
    union Code partesNumRes;
    union Code xUnion, yUnion, rUnion, aUnion, bUnion, bpUnion, xiUnion, aux;
    float a, b, bp;

    /*EXCEPCIONES*/

    if(partesNumA.numero == 0.0)
    {

        partesNumRes.numero = 0.0;
        return partesNumRes;


    }
    else if(partesNumB.numero == 0.0)
    {
        nan = true;
        return partesNumRes;

    }
    else if(partesNumA.IEEE754.expo == 255 || partesNumA.IEEE754.expo == 255)
    {

        infinito = true;
        return partesNumRes;

    }

    if(partesNumA.IEEE754.expo == partesNumB.IEEE754.expo && partesNumA.IEEE754.partFrac == partesNumB.IEEE754.partFrac)
    {
        if(partesNumA.IEEE754.signo == partesNumB.IEEE754.signo)
        {
            partesNumRes.numero = 1;
            return partesNumRes;
        }
        else
        {
            partesNumRes.numero = -1;
            return partesNumRes;
        }
    }

    a = pasarAEscalar(partesNumA.IEEE754.partFrac);
    b = pasarAEscalar(partesNumB.IEEE754.partFrac);

    if(b >= 1 && b < 1.25){
        bp = 1;
    }else if(b >= 1.25 && b < 2){
        bp = 0.8;
    }

    aUnion.numero = a;
    bUnion.numero = b;
    bpUnion.numero = bp;

    xUnion = producto(aUnion, bpUnion);
    yUnion = producto(bUnion, bpUnion);

    union Code dos;
    union Code menosUno;
    dos.numero = 2;
    menosUno.numero = -1;

    do{
        aux = xUnion;
        rUnion = suma(dos, producto(yUnion, menosUno));
        yUnion = producto(yUnion, rUnion);
        xiUnion = producto(xUnion, rUnion);
        xUnion = xiUnion;

    }while(suma(xiUnion, producto(aux, menosUno)).numero > 10e-4);

    //se cumple ya la cond de finalizacion

    //xi es considerado aprox de A*1/B
    //lo pasamos a IEEE754 (ya viene en el xiUnion)

    /*Paso 5*/

    partesNumRes.IEEE754.signo =  partesNumA.IEEE754.signo ^ partesNumB.IEEE754.signo;

    /*Paso 6*/

    unsigned int suma = (partesNumA.IEEE754.expo - partesNumB.IEEE754.expo) + xiUnion.IEEE754.expo;
    if(suma >= 255){
        infinito = true;
        return partesNumRes;
    }

    partesNumRes.IEEE754.expo = (partesNumA.IEEE754.expo - partesNumB.IEEE754.expo) + xiUnion.IEEE754.expo;

    partesNumRes.IEEE754.partFrac = xiUnion.IEEE754.partFrac;

    return partesNumRes;

}
