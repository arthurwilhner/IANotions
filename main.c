
#include <stdio.h>
#include <stdlib.h>

struct pertSens{ // Pertinencia
    double sE; // Sensor Esquerdo
    double sC; // Sensor Centro
    double sD; // Sensor Direita
};

struct pertVeloMot{
    double mML; // Velocidade Muito Lenta
    double mL; // Velcidade Lenta
    double mM; // Velocidade Média
    double mLR; // Velocidade Levemente Rápida
    double mR; // Velocidade Rápida
    double mMR; // Velocidade Muito Rápido
};

struct pertSaida{
    double ;
    double ;
    double ;
    double ;
    double ;
};

struct regra{
    struct A1;
    struct A2;
    struct A3;
    struct A4;
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
// Branco          Cinza             Pretp
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


int main() {
    printf("Hello, World!\n");
    return 0;
}


