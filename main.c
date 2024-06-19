// Exercício Redes Neurais
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NEURONIOS_ENTRADA 4
#define NEURONIOS_OCULTOS 5
#define NEURONIOS_SAIDA 3

// Função de ativação sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivada da função sigmoid
double derivada_sigmoid(double x) {
    return x * (1 - x);
}

// Função que retorna um número aleatório entre -1.0 e 1.0 para inicialização dos pesos
double peso_aleatorio() {
    return 2.0 * ((double)rand() / RAND_MAX) - 1.0;
}

// Estrutura da rede neural
typedef struct {
    double entrada[NEURONIOS_ENTRADA];
    double oculto[NEURONIOS_OCULTOS];
    double saida[NEURONIOS_SAIDA];
    double pesos_eo[NEURONIOS_ENTRADA][NEURONIOS_OCULTOS];
    double pesos_os[NEURONIOS_OCULTOS][NEURONIOS_SAIDA];
} RedeNeural;

// Inicializa os pesos da rede neural
void inicializa_rede(RedeNeural *rn) {
    for (int i = 0; i < NEURONIOS_ENTRADA; i++) {
        for (int j = 0; j < NEURONIOS_OCULTOS; j++) {
            rn->pesos_eo[i][j] = peso_aleatorio();
        }
    }
    for (int j = 0; j < NEURONIOS_OCULTOS; j++) {
        for (int k = 0; k < NEURONIOS_SAIDA; k++) {
            rn->pesos_os[j][k] = peso_aleatorio();
        }
    }
}

// Operação de feedforward
void feedforward(RedeNeural *rn) {
    for (int j = 0; j < NEURONIOS_OCULTOS; j++) {
        rn->oculto[j] = 0;
        for (int i = 0; i < NEURONIOS_ENTRADA; i++) {
            rn->oculto[j] += rn->entrada[i] * rn->pesos_eo[i][j];
        }
        rn->oculto[j] = sigmoid(rn->oculto[j]);
    }

    for (int k = 0; k < NEURONIOS_SAIDA; k++) {
        rn->saida[k] = 0;
        for (int j = 0; j < NEURONIOS_OCULTOS; j++) {
            rn->saida[k] += rn->oculto[j] * rn->pesos_os[j][k];
        }
        rn->saida[k] = sigmoid(rn->saida[k]);
    }
}

int main() {
    RedeNeural rn;
    inicializa_rede(&rn);

    // Exemplo de definição de entradas e execução da rede
    rn.entrada[0] = 1;
    rn.entrada[1] = 0;
    rn.entrada[2] = 1;
    rn.entrada[3] = 1;
    feedforward(&rn);
    printf("Saida X: %f\n", rn.saida[0]);
    printf("Saida Y: %f\n", rn.saida[1]);
    printf("Saida Z: %f\n", rn.saida[2]);

    return 0;
}
