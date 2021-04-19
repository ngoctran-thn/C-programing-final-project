#include <stdio.h>
#include <stdint.h>

#include <stdlib.h>

#include "sigmoid.h"
#include "helpers.h"
#include "messenger.h"

#define MAX 10
static double synaptic_weights[3];

double analyze(double input[]){
	double result = dot(input, synaptic_weights, 3);
	result = sigmoid(result);
	return result;
}

void think_train(double input[][3], double output[]){
		double results[MAX];
		for (int i = 0; i < MAX; i++){
			results[i] = dot(&input[i][0], synaptic_weights, 3);
			output[i] = sigmoid(results[i]);
		}
}

void train(double training_set_inputs[][3], double training_set_outputs[], uint32_t n){
	
	for(uint32_t i = 0; i < n; i++){
		
		double error[MAX];
		double output[MAX];
		
		think_train(training_set_inputs, output);
		for (int j = 0; j < MAX; j++) {
			error[j] = training_set_outputs[j] - output[j];

			error[j] *= sigmoid_derivative(output[j]);
		}

		double transpose[3][MAX];
		for (int j = 0; j < MAX; j++) {
			transpose[0][j] = training_set_inputs[j][0];
			transpose[1][j] = training_set_inputs[j][1];
			transpose[2][j] = training_set_inputs[j][2];
		}

		double adjustments[3];
		
		adjustments[0] = dot(error, &transpose[0][0], MAX);
		adjustments[1] = dot(error, &transpose[1][0], MAX);
		adjustments[2] = dot(error, &transpose[2][0], MAX);
		
		synaptic_weights[0] += adjustments[0];
		synaptic_weights[1] += adjustments[1];
		synaptic_weights[2] += adjustments[2];
	}
	
}

int main(int argc, char *argv[]){

	// {temperature, humidity, wind}
	double training_set_inputs[MAX][3] = { 
										 {1, 1, 1},
										 {1, 1, 1},
										 {1, 1, 1},
										 {0, 0, 0},
										 {0, 0, 0},
										 {0, 0, 0},
										 {0, 0, 0},
										 {0, 0, 0},
										 {0, 1, 1},
										 {0, 1, 1},
									   };

	// weather: 1 sunny, 0.75: partly sunny, 0.5: cloudy, 0.25: light rain, 0: rain
	double training_set_outputs[MAX] = { 1, 1 , 1 , 1, 0, 0, 0, 0, 1, 1};

	srand(1);
	
	synaptic_weights[0] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[1] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[2] = 2 * ((double)rand()/RAND_MAX) - 1;
	
	train(training_set_inputs, training_set_outputs, 10000);
	
	double test_1[3] = { 0, 1, 1 };	// expect ~1
	
	double result1 = analyze(test_1);
	printf("Result %lf \n", result1);
	printf("Result %d \n", mappingOutput(result1));
	
	double test_2[3] = { 0, 0, 0 };	// expect ~0
	
	printf("Result %lf \n", analyze(test_2));
	
	return 0;
}











