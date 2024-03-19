
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

double saida;

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

void calculaPertinenciaSensor(double valor, char sensor, double P1, double P2, double P3, double P4, double P5, double P6, double P7, double P8) {
    if(sensor == 'E') {
        if(valor < P1) {
            ptSens.sE = 1.0;
        } else if(valor >= P1 && valor < P3) {
            ptSens.sE = (P3 - valor) / (P3 - P1);
        } else {
            ptSens.sE = 0.0;
        }
    } else if(sensor == 'C') {
        if(valor < P2) {
            ptSens.sC = 0.0;
        } else if(valor >= P2 && valor < P4) {
            ptSens.sC = (valor - P2) / (P4 - P2);
        } else if(valor >= P4 && valor < P5) {
            ptSens.sC = 1.0;
        } else if(valor >= P5 && valor < P7) {
            ptSens.sC = (P7 - valor) / (P7 - P5);
        } else {
            ptSens.sC = 0.0;
        }
    } else if(sensor == 'D') {
        if(valor < P6) {
            ptSens.sD = 0.0;
        } else if(valor >= P6 && valor < P8) {
            ptSens.sD = (valor - P6) / (P8 - P6);
        } else {
            ptSens.sD = 1.0;
        }
    }
}

void calculaPertinenciaMotor(double valor, double P1, double P2, double P3, double P4, double P5, double P6) {
    // Reset valores de pertinência
    ptVel.mML = ptVel.mL = ptVel.mM = ptVel.mLR = ptVel.mR = ptVel.mMR = 0.0;

    // Muito Lenta [0, P1]
    if (valor <= P1) {
        ptVel.mML = 1.0;
    }

    // Lenta [P1, P2]
    if (valor > P1 && valor < P2) {
        ptVel.mL = (valor - P1) / (P2 - P1);
    } else if (valor >= P2 && valor <= P3) {
        ptVel.mL = (P3 - valor) / (P3 - P2);
    }

    // Média [P2, P4]
    if (valor > P2 && valor < P4) {
        ptVel.mM = (valor - P2) / (P4 - P2);
    } else if (valor >= P4 && valor <= P5) {
        ptVel.mM = (P5 - valor) / (P5 - P4);
    }

    // Levemente Rápida [P4, P6]
    if (valor > P4 && valor < P6) {
        ptVel.mLR = (valor - P4) / (P6 - P4);
    }

}

void avaliaFuzzy() {
    // Resetando a saída fuzzy para todas as direções
    ptSai.levEsq = ptSai.Esq = ptSai.Frente = ptSai.levDir = ptSai.Dir = 0.0;

    // Regra 1: PPP
    if (ptSens.sC > 0.8) {
        ptSai.Frente = 1.0; // Siga em frente
    }

    // Regra 2: PPB
    if (ptSens.sE > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 3: PPC
    if (ptSens.sD > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 4: PBP
    if (ptSens.sD > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 5: PBB
    if (ptSens.sD > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 6: PBC
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 7: PCP
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 8: PCB
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 9: PCC
    if (ptSens.sD > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 10: BPP
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 11: BPB
    if (ptSens.sC > 0.8) {
        ptSai.Frente = 1.0; // Siga em frente
    }

    // Regra 12: BPC
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 13: BBP
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 14: BCP
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 15: CPP
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 16: CPC
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 17: CBP
    if (ptSens.sD > 0.8) {
        ptSai.levDir = 0.5; // Ajuste leve para a direita
    }

    // Regra 18: CPB
    if (ptSens.sD > 0.8) {
        ptSai.levEsq = 0.5; // Ajuste leve para a esquerda
    }

    // Regra 19: BBB
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 20: BBC
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 21: BCB
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 22: BCC
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 23: CCP
    if (ptSens.sD > 0.8) {
        ptSai.Dir = 0.5; // Ajuste para a Direita
    }

    // Regra 24: CBB
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 25: CBC
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 26: CCB
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.5; // Ajuste para a esquerda
    }

    // Regra 27: CCC
    if (ptSens.sD > 0.8) {
        ptSai.Esq = 0.7; // Ajuste para a esquerda
    }

}



void calculaSaida() {
    // Definindo valores para cada ação
    double valorLevEsq;
    double valorEsq;
    double valorFrente;
    double valorLevDir;
    double valorDir;

    double num = 0;
    double den = 0;

    valorLevEsq = (0+50)/2;
    valorEsq = (50+100)/2;
    valorFrente = (100+150)/2;
    valorLevDir = (150+200)/2;
    valorDir = (200+250)/2;

    if(ptSai.Esq){
        num += valorEsq*ptSai.Esq;
        den += ptSai.Esq;
    }

    if(ptSai.levEsq){
        num += valorLevEsq*ptSai.levEsq;
        den += ptSai.levEsq;
    }

    if(ptSai.Frente){
        num += valorFrente*ptSai.Frente;
        den += ptSai.Frente;
    }

    if(ptSai.Dir){
        num += valorDir*ptSai.Dir;
        den += ptSai.Dir;
    }

    if(ptSai.levDir){
        num += valorLevDir*ptSai.levDir;
        den += ptSai.levDir;
    }

    saida = num / den;
}


int main() {

}


