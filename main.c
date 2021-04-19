#include <stdio.h>
#include <stdint.h>

#include <stdlib.h>

#include "sigmoid.h"
#include "helpers.h"

static double synaptic_weights[3];

double analyze(double input[]){
	double result = dot(input,synaptic_weights,3);
	result = sigmoid(result);
	return result;
}

void think_train(double input[][3], double output[]){
		double result1, result2, result3, result4;
		
		result1 = dot(&input[0][0],synaptic_weights,3);
		result2 = dot(&input[1][0],synaptic_weights,3);
		result3 = dot(&input[2][0],synaptic_weights,3);
		result4 = dot(&input[3][0],synaptic_weights,3);
		
		output[0] = sigmoid(result1);
		output[1] = sigmoid(result2);
		output[2] = sigmoid(result3);
		output[3] = sigmoid(result4);
}

void train(double training_set_inputs[][3], double training_set_outputs[], uint32_t n){
	
	for(uint32_t i = 0; i < n; i++){
		
		double error[4];
		double output[4];
		
		think_train(training_set_inputs, output);
		
		error[0] = training_set_outputs[0] - output[0];
		error[1] = training_set_outputs[1] - output[1];
		error[2] = training_set_outputs[2] - output[2];
		error[3] = training_set_outputs[3] - output[3];
		
		error[0] *= sigmoid_derivative(output[0]);
		error[1] *= sigmoid_derivative(output[1]);
		error[2] *= sigmoid_derivative(output[2]);
		error[3] *= sigmoid_derivative(output[3]);
		
		double transpose[3][4];
		
		transpose[0][0] = training_set_inputs[0][0];
		transpose[0][1] = training_set_inputs[1][0];
		transpose[0][2] = training_set_inputs[2][0];
		transpose[0][3] = training_set_inputs[3][0];
		
		transpose[1][0] = training_set_inputs[0][1];
		transpose[1][1] = training_set_inputs[1][1];
		transpose[1][2] = training_set_inputs[2][1];
		transpose[1][3] = training_set_inputs[3][1];
		
		transpose[2][0] = training_set_inputs[0][2];
		transpose[2][1] = training_set_inputs[1][2];
		transpose[2][2] = training_set_inputs[2][2];
		transpose[2][3] = training_set_inputs[3][2];
		
		double adjustments[3];
		
		adjustments[0] = dot(error, &transpose[0][0], 4);
		adjustments[1] = dot(error, &transpose[1][0], 4);
		adjustments[2] = dot(error, &transpose[2][0], 4);
		
		synaptic_weights[0] += adjustments[0];
		synaptic_weights[1] += adjustments[1];
		synaptic_weights[2] += adjustments[2];
	}
	
}

int main(int argc, char *argv[]){

	double training_set_inputs[4][3] = { {0, 0, 0},
										 {1, 1, 1},
										 {1, 0, 1},
										 {0, 1, 1}
									   };
									   
	double training_set_outputs[4] = {0,1,1,0};

	srand(1);
	
	synaptic_weights[0] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[1] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[2] = 2 * ((double)rand()/RAND_MAX) - 1;
	
	train(training_set_inputs, training_set_outputs, 10000);
	
	double test_1[3] = {0,0,1};
	
	printf("Result %lf \n", analyze(test_1));
	
	double test_2[3] = {1,0,0};
	
	printf("Result %lf \n", analyze(test_2));
	
	return 0;
}











