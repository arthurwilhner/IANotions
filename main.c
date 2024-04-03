
#include <stdio.h>
#include <stdlib.h>
/*
 * T(X1) = {Branco, Cinza e Preto}
 * T(X2) = {Branco, Cinza e Preto}
 * T(X3) = {Branco, Cinza e Preto}
 *
 * T(Y) = {levEsq - levemente Esquerda, Esq - Esquerda, Frente - Frente, levDir - Levemente a Direita e Dir - Direita}
 *
 */

const int analogInPin1 = A0; //Direita
const int analogInPin2 = A1;
const int analogInPin3 = A2;
const int analogInPin4 = A3; //Esquerda

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue23 = 0; // Var para armazenar média dos sensores 2 e 3

// Var dos motores
const int motor1a = 5; // Motor direita
const int motor1b = 6;
const int motor2a = 9; // Motor esquerda
const int motor2b = 10;

struct pertCor{ // Struct de definição das cores captadas pelos sensores
    double Branco;
    double Cinza;
    double Preto;
};

struct pertCor pertcorEsq;
struct pertCor pertcorCent;
struct pertCor pertcorDir;

struct pertSaida{
    double levEsq; // Levemente esquerda
    double Esq; // Esquerda
    double Frente; // Frente
    double levDir; // Levemente Direita
    double Dir; // Direita
};

struct pertSaida ptSai;

double saida;

struct regra{
    double A1;
    double A2;
    double A3;
    double S1; // Saída
};

struct regra R1;
struct regra R2;
struct regra R3;
struct regra R4;
struct regra R5;
struct regra R6;
struct regra R7;
struct regra R8;
struct regra R9;
struct regra R10;
struct regra R11;
struct regra R12;
struct regra R14;
struct regra R13;
struct regra R15;
struct regra R16;
struct regra R17;
struct regra R18;
struct regra R19;
struct regra R20;
struct regra R21;
struct regra R22;
struct regra R23;
struct regra R24;
struct regra R25;
struct regra R26;
struct regra R27;


// Conjuntos Fuzzy
//
// Branco          Cinza             Preto
// 1|****           ----             xxxx|
// |   . *        - .  . -         x .   |
// |   .   *    -   .  .   -     x   .   |
// |   .     *-     .  .     - x     .   |
// |   .    -  *    .  .     x -     .   |
// |___.__-______*__.__.___x_____-___.___|
// 0  P1 P2     P3 P4  P5 P6    P7  P8   1

/*
P1  200
P2  300
P3  400
P4  500
P5  550
P6  600
P7  650
P8  700
*/

void calculaPertinenciaSensorEsquerdo(double valor,
                                      double P1, double P2, double P3, double P4,
                                      double P5, double P6, double P7, double P8){ // Calculo da pertinência de cada cor para o Sensor Esquerdo
    // Branco
    if(valor<P1){
        pertcorEsq.Branco = 1.0;
    }
    if(valor>=P1 && valor<P3){
        pertcorEsq.Branco = (P3-valor)/(P3-P1);
    }
    if(valor>=P3){
        pertcorEsq.Branco = 0.0;
    }
    // Cinza
    if(valor<P2){
        pertcorEsq.Cinza = 0.0;
    }
    if(valor>=P2 && valor <P4){
        pertcorEsq.Cinza = (valor-P2)/(P4-P2);
    }
    if(valor>=P4 && valor<P5){
        pertcorEsq.Cinza = 1.0;
    }
    if(valor >= P5 && valor<P7){
        pertcorEsq.Cinza = (P7-valor)/(P7-P5);
    }
    if(valor>=P7){
        pertcorEsq.Cinza = 0.0;
    }
    // Preto
    if(valor<P6){
        pertcorEsq.Preto = 0.0;
    }
    if(valor>=P6 && valor<P8){
        pertcorEsq.Preto = 1.0;
    }
}

void calculaPertinenciaSensorCentro(double valor,
                                    double P1, double P2, double P3, double P4,
                                    double P5, double P6, double P7, double P8){ // Calculo da pertinência de cada cor para o Sensor do Centro
    // Branco
    if(valor<P1){
        pertcorCent.Branco = 1.0;
    }
    if(valor>=P1 && valor<P3){
        pertcorCent.Branco = (P3-valor)/(P3-P1);
    }
    if(valor>=P3){
        pertcorCent.Branco = 0.0;
    }
    // Cinza
    if(valor<P2){
        pertcorCent.Cinza = 0.0;
    }
    if(valor>=P2 && valor <P4){
        pertcorCent.Cinza = (valor-P2)/(P4-P2);
    }
    if(valor>=P4 && valor<P5){
        pertcorCent.Cinza = 1.0;
    }
    if(valor >= P5 && valor<P7){
        pertcorCent.Cinza = (P7-valor)/(P7-P5);
    }
    if(valor>=P7){
        pertcorCent.Cinza = 0.0;
    }
    // Preto
    if(valor<P6){
        pertcorCent.Preto = 0.0;
    }
    if(valor>=P6 && valor<P8){
        pertcorCent.Preto = 1.0;
    }
}

void calculaPertinenciaSensorDireita(double valor,
                                     double P1, double P2, double P3, double P4,
                                     double P5, double P6, double P7, double P8){ // Calculo da pertinência de cada cor para o Sensor da Direita
    // Branco
    if(valor<P1){
        pertcorDir.Branco = 1.0;
    }
    if(valor>=P1 && valor<P3){
        pertcorDir.Branco = (P3-valor)/(P3-P1);
    }
    if(valor>=P3){
        pertcorDir.Branco = 0.0;
    }
    // Cinza
    if(valor<P2){
        pertcorDir.Cinza = 0.0;
    }
    if(valor>=P2 && valor <P4){
        pertcorDir.Cinza = (valor-P2)/(P4-P2);
    }
    if(valor>=P4 && valor<P5){
        pertcorDir.Cinza = 1.0;
    }
    if(valor >= P5 && valor<P7){
        pertcorDir.Cinza = (P7-valor)/(P7-P5);
    }
    if(valor>=P7){
        pertcorDir.Cinza = 0.0;
    }
    // Preto
    if(valor<P6){
        pertcorDir.Preto = 0.0;
    }
    if(valor>=P6 && valor<P8){
        pertcorDir.Preto = 1.0;
    }
}


void avaliaFuzzy() {
    // Regra 1: PPP -> Reto
    R1.A1 = pertcorEsq.Preto;
    R1.A2 = pertcorCent.Preto;
    R1.A3 = pertcorDir.Preto;
    R1.S1 = R1.A1;
    if(R1.A2 < R1.A1 && R1.A2 < R1.A3){
        R1.S1 = R1.A2;
    }
    if(R1.A3 < R1.A1 && R1.A3 < R1.A2){
        R1.S1 = R1.A3;
    }

    // Regra 2: PPB -> Levemente a Esquerda
    R2.A1 = pertcorEsq.Preto;
    R2.A2 = pertcorCent.Preto;
    R2.A3 = pertcorDir.Branco;
    R2.S1 = R2.A1;
    if(R2.A2 < R2.A1 && R2.A2 <R2.A3){
        R2.S1 = R2.A2;
    }
    if(R2.A3 < R2.A1 != 0){
        R2.S1 = R2.A3;
    }

    // Regra 3: PPC -> Levemente a Esquerda
    R3.A1 = pertcorEsq.Preto;
    R3.A2 = pertcorCent.Preto;
    R3.A3 = pertcorDir.Cinza;
    R3.S1 = R3.A1;
    if(R3.A2 < R3.A1 && R3.A2 <R3.A3){
        R3.S1 = R3.A2;
    }
    if(R3.A3 < R3.A1 != 0){
        R3.S1 = R3.A3;
    }

    // Regra 4: PBP -> Esquerda
    R4.A1 = pertcorEsq.Preto;
    R4.A2 = pertcorCent.Branco;
    R4.A3 = pertcorDir.Preto;
    R4.S1 = R4.A1;
    if(R4.A2 < R4.A1 && R4.A2 <R4.A3){
        R4.S1 = R4.A2;
    }
    if(R4.A3 < R4.A1 != 0){
        R4.S1 = R4.A3;
    }

    // Regra 5: PBB -> Levemente a Esquerda
    R5.A1 = pertcorEsq.Preto;
    R5.A2 = pertcorCent.Branco;
    R5.A3 = pertcorDir.Branco;
    R5.S1 = R5.A1;
    if(R5.A2 < R5.A1 && R5.A2 <R5.A3){
        R5.S1 = R5.A2;
    }
    if(R5.A3 < R5.A1 != 0){
        R5.S1 = R5.A3;
    }

    // Regra 6: PBC -> Esquerda
    R6.A1 = pertcorEsq.Preto;
    R6.A2 = pertcorCent.Branco;
    R6.A3 = pertcorDir.Cinza;
    R6.S1 = R6.A1;
    if(R6.A2 < R6.A1 && R6.A2 <R6.A3){
        R6.S1 = R6.A2;
    }
    if(R6.A3 < R6.A1 != 0){
        R6.S1 = R6.A3;
    }

    // Regra 7: PCP -> Direita
    R7.A1 = pertcorEsq.Preto;
    R7.A2 = pertcorCent.Cinza;
    R7.A3 = pertcorDir.Preto;
    R7.S1 = R6.A1;
    if(R7.A2 < R7.A1 && R7.A2 <R7.A3){
        R7.S1 = R7.A2;
    }
    if(R7.A3 < R7.A1 != 0){
        R7.S1 = R7.A3;
    }

    // Regra 8: PCB -> Esquerda
    R8.A1 = pertcorEsq.Preto;
    R8.A2 = pertcorCent.Cinza;
    R8.A3 = pertcorDir.Branco;
    R8.S1 = R8.A1;
    if(R8.A2 < R8.A1 && R8.A2 < R8.A3){
        R8.S1 = R8.A2;
    }
    if(R8.A3 < R8.A1 != 0){
        R8.S1 = R8.A3;
    }

// Regra 9: PCC -> Levemente a Esquerda
    R9.A1 = pertcorEsq.Preto;
    R9.A2 = pertcorCent.Cinza;
    R9.A3 = pertcorDir.Cinza;
    R9.S1 = R9.A1;
    if(R9.A2 < R9.A1 && R9.A2 < R9.A3){
        R9.S1 = R9.A2;
    }
    if(R9.A3 < R9.A1 != 0){
        R9.S1 = R9.A3;
    }

// Regra 10: BPP -> Levemente a Direita
    R10.A1 = pertcorEsq.Branco;
    R10.A2 = pertcorCent.Preto;
    R10.A3 = pertcorDir.Preto;
    R10.S1 = R10.A1;
    if(R10.A2 < R10.A1 && R10.A2 < R10.A3){
        R10.S1 = R10.A2;
    }
    if(R10.A3 < R10.A1 != 0){
        R10.S1 = R10.A3;
    }

// Regra 11: BPB -> Em Frente
    R11.A1 = pertcorEsq.Branco;
    R11.A2 = pertcorCent.Preto;
    R11.A3 = pertcorDir.Branco;
    R11.S1 = R11.A1;
    if(R11.A2 < R11.A1 && R11.A2 < R11.A3){
        R11.S1 = R11.A2;
    }
    if(R11.A3 < R11.A1 != 0){
        R11.S1 = R11.A3;
    }

// Regra 12: BPC -> Levemente a Direita
    R12.A1 = pertcorEsq.Branco;
    R12.A2 = pertcorCent.Preto;
    R12.A3 = pertcorDir.Cinza;
    R12.S1 = R12.A1;
    if(R12.A2 < R12.A1 && R12.A2 < R12.A3){
        R12.S1 = R12.A2;
    }
    if(R12.A3 < R12.A1 != 0){
        R12.S1 = R12.A3;
    }

// Regra 13: BBP -> Levemente a Direita
    R13.A1 = pertcorEsq.Branco;
    R13.A2 = pertcorCent.Branco;
    R13.A3 = pertcorDir.Preto;
    R13.S1 = R13.A1;
    if(R13.A2 < R13.A1 && R13.A2 < R13.A3){
        R13.S1 = R13.A2;
    }
    if(R13.A3 < R13.A1 != 0){
        R13.S1 = R13.A3;
    }

// Regra 14: BCP -> Levemente a Direita
    R14.A1 = pertcorEsq.Branco;
    R14.A2 = pertcorCent.Cinza;
    R14.A3 = pertcorDir.Preto;
    R14.S1 = R14.A1;
    if(R14.A2 < R14.A1 && R14.A2 < R14.A3){
        R14.S1 = R14.A2;
    }
    if(R14.A3 < R14.A1 != 0){
        R14.S1 = R14.A3;
    }

// Regra 15: CPP -> Direita
    R15.A1 = pertcorEsq.Cinza;
    R15.A2 = pertcorCent.Preto;
    R15.A3 = pertcorDir.Preto;
    R15.S1 = R15.A1;
    if(R15.A2 < R15.A1 && R15.A2 < R15.A3){
        R15.S1 = R15.A2;
    }
    if(R15.A3 < R15.A1 != 0){
        R15.S1 = R15.A3;
    }

// Regra 16: CPC -> Levemente a Direita
    R16.A1 = pertcorEsq.Cinza;
    R16.A2 = pertcorCent.Preto;
    R16.A3 = pertcorDir.Cinza;
    R16.S1 = R16.A1;
    if(R16.A2 < R16.A1 && R16.A2 < R16.A3){
        R16.S1 = R16.A2;
    }
    if(R16.A3 < R16.A1 != 0){
        R16.S1 = R16.A3;
    }

// Regra 17: CBP -> Levemente a Direita
    R17.A1 = pertcorEsq.Cinza;
    R17.A2 = pertcorCent.Branco;
    R17.A3 = pertcorDir.Preto;
    R17.S1 = R17.A1;
    if(R17.A2 < R17.A1 && R17.A2 < R17.A3){
        R17.S1 = R17.A2;
    }
    if(R17.A3 < R17.A1 != 0){
        R17.S1 = R17.A3;
    }

// Regra 18: CPB -> Levemente a Esquerda
    R18.A1 = pertcorEsq.Cinza;
    R18.A2 = pertcorCent.Preto;
    R18.A3 = pertcorDir.Branco;
    R18.S1 = R18.A1;
    if(R18.A2 < R18.A1 && R18.A2 < R18.A3){
        R18.S1 = R18.A2;
    }
    if(R18.A3 < R18.A1 != 0){
        R18.S1 = R18.A3;
    }

// Regra 19: BBB -> Direita
    R19.A1 = pertcorEsq.Branco;
    R19.A2 = pertcorCent.Branco;
    R19.A3 = pertcorDir.Branco;
    R19.S1 = R19.A1;
    if(R19.A2 < R19.A1 && R19.A2 < R19.A3){
        R19.S1 = R19.A2;
    }
    if(R19.A3 < R19.A1 != 0){
        R19.S1 = R19.A3;
    }

    // Regra 20: BBC -> Direita
    R20.A1 = pertcorEsq.Branco;
    R20.A2 = pertcorCent.Branco;
    R20.A3 = pertcorDir.Cinza;
    R20.S1 = R20.A1;
    if(R20.A2 < R20.A1 && R20.A2 < R20.A3){
        R20.S1 = R20.A2;
    }
    if(R20.A3 < R20.A1 != 0){
        R20.S1 = R20.A3;
    }

// Regra 21: BCB -> Direita
    R21.A1 = pertcorEsq.Branco;
    R21.A2 = pertcorCent.Cinza;
    R21.A3 = pertcorDir.Branco;
    R21.S1 = R21.A1;
    if(R21.A2 < R21.A1 && R21.A2 < R21.A3){
        R21.S1 = R21.A2;
    }
    if(R21.A3 < R21.A1 != 0){
        R21.S1 = R21.A3;
    }

// Regra 22: BCC -> Direita
    R22.A1 = pertcorEsq.Branco;
    R22.A2 = pertcorCent.Cinza;
    R22.A3 = pertcorDir.Cinza;
    R22.S1 = R22.A1;
    if(R22.A2 < R22.A1 && R22.A2 < R22.A3){
        R22.S1 = R22.A2;
    }
    if(R22.A3 < R22.A1 != 0){
        R22.S1 = R22.A3;
    }

// Regra 23: CCP -> Esquerda
    R23.A1 = pertcorEsq.Cinza;
    R23.A2 = pertcorCent.Cinza;
    R23.A3 = pertcorDir.Preto;
    R23.S1 = R23.A1;
    if(R23.A2 < R23.A1 && R23.A2 < R23.A3){
        R23.S1 = R23.A2;
    }
    if(R23.A3 < R23.A1 != 0){
        R23.S1 = R23.A3;
    }

// Regra 24: CBB -> Esquerda
    R24.A1 = pertcorEsq.Cinza;
    R24.A2 = pertcorCent.Branco;
    R24.A3 = pertcorDir.Branco;
    R24.S1 = R24.A1;
    if(R24.A2 < R24.A1 && R24.A2 < R24.A3){
        R24.S1 = R24.A2;
    }
    if(R24.A3 < R24.A1 != 0){
        R24.S1 = R24.A3;
    }

// Regra 25: CBC -> Esquerda
    R25.A1 = pertcorEsq.Cinza;
    R25.A2 = pertcorCent.Branco;
    R25.A3 = pertcorDir.Cinza;
    R25.S1 = R25.A1;
    if(R25.A2 < R25.A1 && R25.A2 < R25.A3){
        R25.S1 = R25.A2;
    }
    if(R25.A3 < R25.A1 != 0){
        R25.S1 = R25.A3;
    }

// Regra 26: CCB -> Esquerda
    R26.A1 = pertcorEsq.Cinza;
    R26.A2 = pertcorCent.Cinza;
    R26.A3 = pertcorDir.Branco;
    R26.S1 = R26.A1;
    if(R26.A2 < R26.A1 && R26.A2 < R26.A3){
        R26.S1 = R26.A2;
    }
    if(R26.A3 < R26.A1 != 0){
        R26.S1 = R26.A3;
    }

// Regra 27: CCC -> Esquerda
    R27.A1 = pertcorEsq.Cinza;
    R27.A2 = pertcorCent.Cinza;
    R27.A3 = pertcorDir.Cinza;
    R27.S1 = R27.A1;
    if(R27.A2 < R27.A1 && R27.A2 < R27.A3){
        R27.S1 = R27.A2;
    }
    if(R27.A3 < R27.A1 != 0){
        R27.S1 = R27.A3;
    }

    /*
     * Levemente Esquerda -> 2,3,9,18
     * Esquerda -> 4, 6, 8, 24, 25, 26, 23, 27
     * Reto -> 1, 11
     * Direita -> 7, 15, 19, 20, 21, 22
     * Levemente Direita -> 10, 12, 13, 14, 16, 17
     */

    ptSai.levEsq = R2.S1; // Pertinência de saídas Levemente a Esquerda
    if(ptSai.levEsq < R3.S1){
        ptSai.levEsq = R3.S1;
    }
    if(ptSai.levEsq < R9.S1){
        ptSai.levEsq = R9.S1;
    }
    if(ptSai.levEsq < R18.S1){
        ptSai.levEsq = R18.S1;
    }

    ptSai.Esq = R4.S1; // Pertinência de saídas a Esquerda
    if(ptSai.Esq <R6.S1){
        ptSai.Esq = R6.S1;
    }
    if(ptSai.Esq <R8.S1){
        ptSai.Esq = R8.S1;
    }
    if(ptSai.Esq <R24.S1){
        ptSai.Esq = R24.S1;
    }
    if(ptSai.Esq <R25.S1){
        ptSai.Esq = R25.S1;
    }
    if(ptSai.Esq <R26.S1){
        ptSai.Esq = R26.S1;
    }
    if(ptSai.Esq <R23.S1){
        ptSai.Esq = R23.S1;
    }
    if(ptSai.Esq <R27.S1){
        ptSai.Esq = R27.S1;
    }

    ptSai.Frente = R1.S1; // Pertinência de saídas em Frente
    if(ptSai.Frente < R11.S1){
        ptSai.Esq = R11.S1;
    }

    ptSai.levDir = R10.S1; // Pertinência de saídas levemente a Direita
    if(ptSai.levDir < R12.S1){
        ptSai.levDir = R12.S1;
    }
    if(ptSai.levDir < R13.S1){
        ptSai.levDir = R13.S1;
    }
    if(ptSai.levDir < R14.S1){
        ptSai.levDir = R14.S1;
    }
    if(ptSai.levDir < R16.S1){
        ptSai.levDir = R16.S1;
    }
    if(ptSai.levDir < R17.S1){
        ptSai.levDir = R17.S1;
    }

    ptSai.Dir = R7.S1; // Pertinências de saída à Direita
    if(ptSai.Dir < R15.S1){
        ptSai.Dir = R15.S1;
    }
    if(ptSai.Dir < R19.S1){
        ptSai.Dir = R19.S1;
    }
    if(ptSai.Dir < R20.S1){
        ptSai.Dir = R20.S1;
    }
    if(ptSai.Dir < R21.S1){
        ptSai.Dir = R21.S1;
    }
    if(ptSai.Dir < R22.S1){
        ptSai.Dir = R22.S1;
    }

}

void calculaSaida() {
    // Definindo valores para cada ação
    double valorLevEsq;
    double valorEsq;
    double valorFrente;
    double valorLevDir;
    double valorDir;

    double num = 0.0;
    double den = 0.0;

    valorLevEsq = (0.0+25.0)/2;
    valorEsq = (25.0+45.0)/2;
    valorFrente = (45.0+55.0)/2;
    valorLevDir = (55.0+75.0)/2;
    valorDir = (75.0+100.0)/2;

    if(ptSai.Esq > 0){
        num = num + valorEsq * ptSai.Esq;
        den = den + ptSai.Esq;
    }

    if(ptSai.levEsq > 0){
        num = num + valorLevEsq*ptSai.levEsq;
        den = den + ptSai.levEsq;
    }

    if(ptSai.Frente > 0){
        num = num + valorFrente*ptSai.Frente;
        den = den + ptSai.Frente;
    }

    if(ptSai.Dir > 0){
        num = num + valorDir*ptSai.Dir;
        den = den + ptSai.Dir;
    }

    if(ptSai.levDir > 0){
        num = num + valorLevDir*ptSai.levDir;
        den = den + ptSai.levDir;
    }

    saida = num / den;
}

void setup() {
// configura os pinos de controle dos motores como saída
    pinMode(motor1a, OUTPUT);
    pinMode(motor1b, OUTPUT);
    pinMode(motor2a, OUTPUT);
    pinMode(motor2b, OUTPUT);
// ajusta os motores para andar para frente
    digitalWrite(motor1a, LOW);
    digitalWrite(motor2a, LOW);
}


void loop() {
    // lê os valores dos sensores
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);
    sensorValue3 = analogRead(analogInPin3);
    sensorValue4 = analogRead(analogInPin4);
    //calcula a média dos sensores centrais e soma um offset de 50
    sensorValue23=((sensorValue2+sensorValue3)/2)+50;

    calculaPertinenciaSensorEsquerdo(sensorValue4, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0);
    calculaPertinenciaSensorCentro(sensorValue23, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0);
    calculaPertinenciaSensorDireita(sensorValue1, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0);
    //200.0, 300.0, 400.0, 500.0, 550.0, 600.0, 650.0, 700.0

    avaliaFuzzy();

    calculaSaida();
    /*
    E - ME 0 e MD 255 - FAIXA 0-20
    LE - ME 130 e MD 255 - FAIXA 21-44
    RT - ME 255 e MD 255 - FAIXA 45-55
    LD - ME 255 e MD 130 - FAIXA 46-79
    D - ME 255 e MD 0 - FAIXA 81-100
    */
    analogWrite(motor1b, 150);
    analogWrite(motor2b, 150);

    if(saida<21){
        analogWrite(motor1b, 0);
        analogWrite(motor2b, 255);
    }

    if(saida>20 && saida<45){
        analogWrite(motor1b, 50);
        analogWrite(motor2b, 255);
    }

    if(saida>44 && saida<56){
        analogWrite(motor1b, 255);
        analogWrite(motor2b, 255); ;
    }

    if(saida>55 && saida<80){
        analogWrite(motor1b, 255);
        analogWrite(motor2b, 50);
    }

    if(saida>79){
        analogWrite(motor1b, 255);
        analogWrite(motor2b, 0);
    }
}
/*
int main() {
    /*
    double esq = 350.0;
    double centro = 500.0;
    double dir = 400.0;

    calculaPertinenciaSensorEsquerdo(esq,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0);
    calculaPertinenciaSensorCentro(centro,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0);
    calculaPertinenciaSensorDireita(dir,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0);

    printf("\r\n");
    printf("PertCorEsq.Branco,PertCorEsq.Cinza,PertCorEsq.Preto = %lf %lf %lf\r\n",
           pertcorEsq.Branco, pertcorEsq.Cinza, pertcorEsq.Preto);
    printf(
            "pertcorCent.Branco, pertcorCent.Cinza, pertcorCent.Preto = %lf %lf %lf\r\n",
            pertcorCent.Branco, pertcorCent.Cinza, pertcorCent.Preto);
    printf("pertcorDir.Branco, pertcorDir.Cinza, pertcorDir.Preto = %lf %lf %lf\r\n",
           pertcorDir.Branco, pertcorDir.Cinza, pertcorDir.Preto);
    // Avaliação das Regras
    avaliaFuzzy();
    printf("\r\n");
    printf("R1.A1,R1.A2,R1.A3,R1.S1 = %lf %lf %lf %lf\r\n", R1.A1, R1.A2,
           R1.A3, R1.S1);
    printf("R2.A1,R2.A2,R2.A3,R2.S1 = %lf %lf %lf %lf\r\n", R2.A1, R2.A2,
           R2.A3, R2.S1);
    printf("R3.A1,R3.A2,R3.A3,R3.S1 = %lf %lf %lf %lf\r\n", R3.A1, R3.A2,
           R3.A3, R3.S1);
    printf("R4.A1,R4.A2,R4.A3,R4.S1 = %lf %lf %lf %lf\r\n", R4.A1, R4.A2,
           R4.A3, R4.S1);
    printf("R5.A1,R5.A2,R5.A3,R5.S1 = %lf %lf %lf %lf\r\n", R5.A1, R5.A2,
           R5.A3, R5.S1);
    printf("R6.A1,R6.A2,R6.A3,R6.S1 = %lf %lf %lf %lf\r\n", R6.A1, R6.A2,
           R6.A3, R6.S1);
    printf("R7.A1,R7.A2,R7.A3,R7.S1 = %lf %lf %lf %lf\r\n", R7.A1, R7.A2,
           R7.A3, R7.S1);
    printf("R8.A1,R8.A2,R8.A3,R8.S1 = %lf %lf %lf %lf\r\n", R8.A1, R8.A2,
           R8.A3, R8.S1);
    printf("R9.A1,R9.A2,R9.A3,R9.S1 = %lf %lf %lf %lf\r\n", R9.A1, R9.A2,
           R9.A3, R9.S1);
    printf("R10.A1,R10.A2,R10.A3,R10.S1 = %lf %lf %lf %lf\r\n", R10.A1, R10.A2,
           R10.A3, R10.S1);
    printf("R11.A1,R11.A2,R11.A3,R11.S1 = %lf %lf %lf %lf\r\n", R11.A1, R11.A2,
           R11.A3, R11.S1);
    printf("R12.A1,R12.A2,R12.A3,R12.S1 = %lf %lf %lf %lf\r\n", R12.A1, R12.A2,
           R12.A3, R12.S1);
    printf("R13.A1,R13.A2,R13.A3,R13.S1 = %lf %lf %lf %lf\r\n", R13.A1, R13.A2,
           R13.A3, R13.S1);
    printf("R14.A1,R14.A2,R14.A3,R14.S1 = %lf %lf %lf %lf\r\n", R14.A1, R14.A2,
           R14.A3, R14.S1);
    printf("R15.A1,R15.A2,R15.A3,R15.S1 = %lf %lf %lf %lf\r\n", R15.A1, R15.A2,
           R15.A3, R15.S1);
    printf("R16.A1,R16.A2,R16.A3,R16.S1 = %lf %lf %lf %lf\r\n", R16.A1, R16.A2,
           R16.A3, R16.S1);
    printf("R17.A1,R17.A2,R17.A3,R17.S1 = %lf %lf %lf %lf\r\n", R17.A1, R17.A2,
           R17.A3, R17.S1);
    printf("R18.A1,R18.A2,R18.A3,R18.S1 = %lf %lf %lf %lf\r\n", R18.A1, R18.A2,
           R18.A3, R18.S1);
    printf("R19.A1,R19.A2,R19.A3,R19.S1 = %lf %lf %lf %lf\r\n", R19.A1, R19.A2,
           R19.A3, R19.S1);
    printf("R20.A1,R20.A2,R20.A3,R20.S1 = %lf %lf %lf %lf\r\n", R20.A1, R20.A2,
           R20.A3, R20.S1);
    printf("R21.A1,R21.A2,R21.A3,R21.S1 = %lf %lf %lf %lf\r\n", R21.A1, R21.A2,
           R21.A3, R21.S1);
    printf("R22.A1,R22.A2,R22.A3,R22.S1 = %lf %lf %lf %lf\r\n", R22.A1, R22.A2,
           R22.A3, R22.S1);
    printf("R23.A1,R23.A2,R23.A3,R23.S1 = %lf %lf %lf %lf\r\n", R23.A1, R23.A2,
           R23.A3, R23.S1);
    printf("R24.A1,R24.A2,R24.A3,R24.S1 = %lf %lf %lf %lf\r\n", R24.A1, R24.A2,
           R24.A3, R24.S1);
    printf("R25.A1,R25.A2,R25.A3,R25.S1 = %lf %lf %lf %lf\r\n", R25.A1, R25.A2,
           R25.A3, R25.S1);
    printf("R26.A1,R26.A2,R26.A3,R26.S1 = %lf %lf %lf %lf\r\n", R26.A1, R26.A2,
           R26.A3, R26.S1);
    printf("R27.A1,R27.A2,R27.A3,R27.S1 = %lf %lf %lf %lf\r\n", R27.A1, R27.A2,
           R27.A3, R27.S1);

    printf("\r\n");
    printf("ptSai.levEsq  = %lf\r\n", ptSai.levEsq);
    printf("ptSai.Esq = %lf\r\n", ptSai.Esq);
    printf("ptSai.Frente  = %lf\r\n", ptSai.Frente);
    printf("ptSai.levDir  = %lf\r\n", ptSai.levDir);
    printf("ptSai.Dir = %lf\r\n", ptSai.Dir);

    calculaSaida();
    printf("\r\n");
    printf("Saida = %lf\r\n", saida);

}*/


