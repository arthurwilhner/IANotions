// Exercício Redes Neurais
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NEURONS 4
#define HIDDEN_NEURONS 5
#define OUTPUT_NEURONS 3
#define LEARNING_RATE 0.1
#define EPOCHS 10000

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of sigmoid
double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Random double between -1.0 and 1.0 for weight initialization
double random_weight() {
    return 2.0 * ((double)rand() / RAND_MAX) - 1.0;
}

// Neural network structure
typedef struct {
    double input[INPUT_NEURONS];
    double hidden[HIDDEN_NEURONS];
    double output[OUTPUT_NEURONS];
    double weights_ih[INPUT_NEURONS][HIDDEN_NEURONS];
    double weights_ho[HIDDEN_NEURONS][OUTPUT_NEURONS];
} NeuralNetwork;

// Initialize the neural network weights
void initialize_network(NeuralNetwork *nn) {
    for (int i = 0; i < INPUT_NEURONS; i++) {
        for (int j = 0; j < HIDDEN_NEURONS; j++) {
            nn->weights_ih[i][j] = random_weight();
        }
    }
    for (int j = 0; j < HIDDEN_NEURONS; j++) {
        for (int k = 0; k < OUTPUT_NEURONS; k++) {
            nn->weights_ho[j][k] = random_weight();
        }
    }
}

// Feedforward operation
void feedforward(NeuralNetwork *nn) {
    for (int j = 0; j < HIDDEN_NEURONS; j++) {
        nn->hidden[j] = 0;
        for (int i = 0; i < INPUT_NEURONS; i++) {
            nn->hidden[j] += nn->input[i] * nn->weights_ih[i][j];
        }
        nn->hidden[j] = sigmoid(nn->hidden[j]);
    }

    for (int k = 0; k < OUTPUT_NEURONS; k++) {
        nn->output[k] = 0;
        for (int j = 0; j < HIDDEN_NEURONS; j++) {
            nn->output[k] += nn->hidden[j] * nn->weights_ho[j][k];
        }
        nn->output[k] = sigmoid(nn->output[k]);
    }
}

int main() {
    NeuralNetwork nn;
    initialize_network(&nn);

    // Example of setting inputs and running the network
    nn.input[0] = 1;
    nn.input[1] = 0;
    nn.input[2] = 1;
    nn.input[3] = 1;
    feedforward(&nn);
    printf("Output X: %f\n", nn.output[0]);
    printf("Output Y: %f\n", nn.output[1]);
    printf("Output Z: %f\n", nn.output[2]);

    return 0;
}
