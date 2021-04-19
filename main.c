#include <stdio.h>
#include <stdint.h>

#include <stdlib.h>

#include "sigmoid.h"
#include "helpers.h"
#include "messenger.h"
#include "data_types.h"

static double synaptic_weights[3];

double analyze(double input[]){
	double result = dot(input, synaptic_weights, 3);
	result = sigmoid(result);
	return result;
}

void think_train(WeatherCondition input[], double output[]){
		double results[MAX];
		for (int i = 0; i < MAX; i++){
			double currentRow[3] = {input[i].temperature, input[i].humidity, input[i].windy};
			results[i] = dot(&currentRow[0], synaptic_weights, 3);
			output[i] = sigmoid(results[i]);
		}
}

void train(WeatherCondition training_set_inputs[], double training_set_outputs[], uint32_t n){
	
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
			transpose[0][j] = training_set_inputs[j].temperature;
			transpose[1][j] = training_set_inputs[j].humidity;
			transpose[2][j] = training_set_inputs[j].windy;
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
	WeatherCondition* data = readTrainingInputFromFile();
	WeatherCondition training_set_inputs_weather[MAX];

	double* outputData = readTrainingOutputFromFile();
	double training_set_outputs[MAX];

	for (int i = 0; i < MAX; i++) {
		training_set_inputs_weather[i] = data[i];
		training_set_outputs[i] = outputData[i];
	}

	srand(1);
	
	synaptic_weights[0] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[1] = 2 * ((double)rand()/RAND_MAX) - 1;
	synaptic_weights[2] = 2 * ((double)rand()/RAND_MAX) - 1;
	
	train(training_set_inputs_weather, training_set_outputs, 10000);
	
	double test_1[3] = { 0, 1, 1 };	// expect ~1
	
	double result1 = analyze(test_1);
	printf("Result %lf \n", result1);

	WEATHER weather1 = mappingOutput(result1);
	printf("Result %d \n", weather1);
	printf("The weather is: %s. You can %s.\n", getWeatherName(weather1), suggestActivity(weather1));

	
	double test_2[3] = { 0, 0, 0 };	// expect ~0
	
	printf("Result %lf \n", analyze(test_2));
	
	return 0;
}











