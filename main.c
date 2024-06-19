#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define num_ind 10 // número de indivíduos na população
#define taxa_mutacao 20 // taxa de mutação em %
#define limitePeso 20 // capacidade máxima de peso da mochila
#define disponibilidade_1 10 // quantidade disponível do item 1
#define disponibilidade_2 12 // quantidade disponível do item 2
#define disponibilidade_3 11 // quantidade disponível do item 3
#define disponibilidade_4 8  // quantidade disponível do item 4
#define disponibilidade_5 7  // quantidade disponível do item 5

int populacao[num_ind][5]; //[tipo 1] [tipo 2] [tipo 3] [tipo 4] [tipo 5]
int novaPopulacao[num_ind][5]; // armazena a geração seguinte durante a reprodução
int fitness[num_ind]; // armazena o fitness de cada indivíduo da população
int fitnessTotal; // armazena a soma de todos os fitness da população para usar na seleção
int melhor[5]; // armazena o melhor indivíduo

double aleatorio() {
    return ((double)rand() / RAND_MAX);
}

int inteiroAleatorio(int maximo) {
    return (rand() % (maximo + 1));
}

void calculaFitness() {
    int cont;
    fitnessTotal = 0;
    for (cont = 0; cont < num_ind; cont++) {
        fitness[cont] = (populacao[cont][0] * 40) + (populacao[cont][1] * 100) + (populacao[cont][2] * 50) + (populacao[cont][3] * 60) + (populacao[cont][4] * 110);
        fitnessTotal = fitnessTotal + fitness[cont];
    }
}

int calculaPeso(int ind) {
    return ((populacao[ind][0] * 3) + (populacao[ind][1] * 5) + (populacao[ind][2] * 2) + (populacao[ind][3] * 4) + (populacao[ind][4] * 6));
}

void inicializaPopulacao() {
    int cont = 0;
    while (cont < num_ind) {
        populacao[cont][0] = inteiroAleatorio(disponibilidade_1);
        populacao[cont][1] = inteiroAleatorio(disponibilidade_2);
        populacao[cont][2] = inteiroAleatorio(disponibilidade_3);
        populacao[cont][3] = inteiroAleatorio(disponibilidade_4);
        populacao[cont][4] = inteiroAleatorio(disponibilidade_5);
        if (calculaPeso(cont) <= limitePeso)
            cont++;
    }
}

int selecionaTorneio() {
    int indiv1, indiv2;
    indiv1 = inteiroAleatorio(num_ind);
    indiv2 = inteiroAleatorio(num_ind);
    if (fitness[indiv1] > fitness[indiv2]) {
        return (indiv1);
    }
    else {
        return (indiv2);
    }
}

int selecionaRoleta() {
    int cont = 0;
    double roleta = aleatorio() * fitnessTotal;
    double somatorioFitness = fitness[0];
    while (somatorioFitness < roleta) {
        cont++;
        somatorioFitness = somatorioFitness + fitness[cont];
    }
    return (cont);
}

void reproducao() {
    int cont = 0;
    int pai, mae;
    int pesoFilho1, pesoFilho2;
    while (cont < num_ind) {
        pesoFilho1 = limitePeso + 1;
        pesoFilho2 = limitePeso + 1;
        while (pesoFilho1 > limitePeso || pesoFilho2 > limitePeso) {
            pai = selecionaRoleta();
            mae = selecionaRoleta();
            while (pai == mae) {
                mae = selecionaRoleta();
            }
            if (aleatorio() < 0.5) {
                novaPopulacao[cont][0] = populacao[pai][0];
                novaPopulacao[cont][1] = populacao[mae][1];
                novaPopulacao[cont][2] = populacao[mae][2];
                novaPopulacao[cont][3] = populacao[pai][3];
                novaPopulacao[cont][4] = populacao[pai][4];
                novaPopulacao[cont + 1][0] = populacao[mae][0];
                novaPopulacao[cont + 1][1] = populacao[pai][1];
                novaPopulacao[cont + 1][2] = populacao[pai][2];
                novaPopulacao[cont + 1][3] = populacao[mae][3];
                novaPopulacao[cont + 1][4] = populacao[mae][4];
            }
            else {
                novaPopulacao[cont][0] = populacao[pai][0];
                novaPopulacao[cont][1] = populacao[pai][1];
                novaPopulacao[cont][2] = populacao[mae][2];
                novaPopulacao[cont][3] = populacao[pai][3];
                novaPopulacao[cont][4] = populacao[mae][4];
                novaPopulacao[cont + 1][0] = populacao[mae][0];
                novaPopulacao[cont + 1][1] = populacao[mae][1];
                novaPopulacao[cont + 1][2] = populacao[mae][2];
                novaPopulacao[cont + 1][3] = populacao[mae][3];
                novaPopulacao[cont + 1][4] = populacao[pai][4];
            }
            pesoFilho1 = (novaPopulacao[cont][0] * 3) + (novaPopulacao[cont][1] * 5) + (novaPopulacao[cont][2] * 2) + (novaPopulacao[cont][3] * 4) + (novaPopulacao[cont][4] * 6);
            pesoFilho2 = (novaPopulacao[cont + 1][0] * 3) + (novaPopulacao[cont + 1][1] * 5) + (novaPopulacao[cont + 1][2] * 2) + (novaPopulacao[cont + 1][3] * 4) + (novaPopulacao[cont + 1][4] * 6);
        }
        cont

                = cont + 2;
    }
    for (cont = 0; cont < num_ind; cont++) {
        populacao[cont][0] = novaPopulacao[cont][0];
        populacao[cont][1] = novaPopulacao[cont][1];
        populacao[cont][2] = novaPopulacao[cont][2];
        populacao[cont][3] = novaPopulacao[cont][3];
        populacao[cont][4] = novaPopulacao[cont][4];
    }
}

int encontraMelhor() {
    int cont;
    int melhorIndividuo;
    int melhorFitness = 0;
    for (cont = 0; cont < num_ind; cont++) {
        if (fitness[cont] > melhorFitness) {
            melhorFitness = fitness[cont];
            melhorIndividuo = cont;
        }
    }
    melhor[0] = populacao[melhorIndividuo][0];
    melhor[1] = populacao[melhorIndividuo][1];
    melhor[2] = populacao[melhorIndividuo][2];
    melhor[3] = populacao[melhorIndividuo][3];
    melhor[4] = populacao[melhorIndividuo][4];
    return (melhorIndividuo);
}

void mutacao() {
    int cont;
    int temp;
    int individuoMutante[5];
    for (cont = 0; cont < num_ind; cont++) {
        if ((aleatorio() * 100) < taxa_mutacao) {
            individuoMutante[0] = populacao[cont][0];
            individuoMutante[1] = populacao[cont][1];
            individuoMutante[2] = populacao[cont][2];
            individuoMutante[3] = populacao[cont][3];
            individuoMutante[4] = populacao[cont][4];
            temp = inteiroAleatorio(4);
            if (temp == 0) individuoMutante[0] = inteiroAleatorio(disponibilidade_1);
            if (temp == 1) individuoMutante[1] = inteiroAleatorio(disponibilidade_2);
            if (temp == 2) individuoMutante[2] = inteiroAleatorio(disponibilidade_3);
            if (temp == 3) individuoMutante[3] = inteiroAleatorio(disponibilidade_4);
            if (temp == 4) individuoMutante[4] = inteiroAleatorio(disponibilidade_5);
            if (((individuoMutante[0] * 3) + (individuoMutante[1] * 5) + (individuoMutante[2] * 2) + (individuoMutante[3] * 4) + (individuoMutante[4] * 6)) <= limitePeso) {
                populacao[cont][0] = individuoMutante[0];
                populacao[cont][1] = individuoMutante[1];
                populacao[cont][2] = individuoMutante[2];
                populacao[cont][3] = individuoMutante[3];
                populacao[cont][4] = individuoMutante[4];
            }
        }
    }
}

void elitismo() {
    int elemento;
    elemento = aleatorio() * num_ind;
    populacao[elemento][0] = melhor[0];
    populacao[elemento][1] = melhor[1];
    populacao[elemento][2] = melhor[2];
    populacao[elemento][3] = melhor[3];
    populacao[elemento][4] = melhor[4];
    calculaFitness();
}

int main() {
    srand((unsigned)time(NULL));
    int i;
    int cont;
    int contGeracao = 0;
    inicializaPopulacao();
    calculaFitness();
    printf("Geracao %d \n", contGeracao);
    for (i = 0; i < num_ind; i++) {
        printf("%d:-> %d %d %d %d %d (%d Kg)(R$%d)\n", i, populacao[i][0], populacao[i][1], populacao[i][2], populacao[i][3], populacao[i][4], calculaPeso(i), fitness[i]);
    }
    i = encontraMelhor();
    printf("Melhor individuo %d Fitness = R$%d\n", i, fitness[i]);
    printf("Fitness total %d\n----------------------------------------------\n", fitnessTotal);
    getchar();
    while (contGeracao < 100) {
        contGeracao++;
        reproducao();
        mutacao();
        calculaFitness();
        elitismo();
        i = encontraMelhor();
        printf("Geracao %d \n", contGeracao);
        for (cont = 0; cont < num_ind; cont++) {
            printf("%d:-> %d %d %d %d %d (%d Kg)(R$%d)\n", cont, populacao[cont][0], populacao[cont][1], populacao[cont][2], populacao[cont][3], populacao[cont][4], calculaPeso(cont), fitness[cont]);
        }
        printf("Melhor individuo %d Fitness = R$%d\n", i, fitness[i]);
        printf("Fitness total %d\n---------------------------------------------\n", fitnessTotal);
        getchar();
    }
}