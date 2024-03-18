
#include <stdio.h>
#include <stdlib.h>
// Começar em 150 o branco, o sensor não capta menos que isso

struct pertSens{ // Pertinencia
    double sE; // Sensor Esquerdo
    double sC; // Sensor Centro
    double sD; // Sensor Direita
};

struct pertSens ptSens;

struct pertVeloMot{
    double mML; // Velocidade Muito Lenta
    double mL; // Velocidade Lenta
    double mM; // Velocidade Média
    double mLR; // Velocidade Levemente Rápida
    double mR; // Velocidade Rápida
    double mMR; // Velocidade Muito Rápido
};

struct pertVeloMot ptVel;

struct pertSaida{
    double levEsq; // Levemente esquerda
    double Esq; // Esquerda
    double Frente; // Frente
    double levDir; // Levemente Direita
    double Dir; // Direita
};

struct pertSaida ptSai;

struct regra{
    double A1;
    double A2;
    double A3;
    double A4;
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
struct regra R14;
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
//1|****           -----             xxxx|
// |   . *        - .  . -         x .   |
// |   .   *    -   .  .   -     x   .   |
// |   .     *-     .  .     - x     .   |
// |   .    -  *    .  .     x -     .   |
//0|___.__-______*__.__.___x_____-___.___|
// 0  P1 P2     P3 P4  P5 P6    P7  P8   1
// P1 = 200
// P2 = 300
// P3 = 400
// P4 = 500
// P5 = 550
// P6 = 600
// P7 = 680
// P8 = 700

void calculaPertinenciaSensor (double valor, double P1, double P2, double P3, double P4, double P5, double P6, double P7, double P8){
    if(valor<P1){
        ptSens.sE=1.0;
    }
    if(valor>=P1 && valor<P3){
        ptSens.sE=(P3-valor) / (P3-P1);
    }
    if(valor>=P3){
        ptSens.sE=0.0;
    }

    if(valor<P2){
        ptSens.sC=0.0;
    }
    if(valor>=P2 && valor<P4){
        ptSens.sC = (valor-P2) / (P4-P2);
    }
    if(valor>=P4 && valor<P5){
        ptSens.sC = 1.0;
    }
    if(valor>=P5 && valor<P7){
        ptSens.sC = (P7-valor)/(P7-P5);
    }
    if(valor>=P7){
        ptSens.sC = 0.0;
    }

    if(valor<P6){
        ptSens.sD = 0.0;
    }
    if(valor>=P6 && valor<P8){
        ptSens.sD = (valor-P6)/(P8-P6);
    }
    if(valor>=P8){
        ptSens.sD = 1.0;
    }
}

void calculaPertinenciaMotor (double valor, double P1, double P2, double P3, double P4, double P5, double P6, double P7, double P8){

}

void avaliaFuzzy (){

}

void calculaSaida(){

}

int main() {

}


