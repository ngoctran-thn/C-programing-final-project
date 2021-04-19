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
	double x, y, z;
	
	printf(" The program will be based on your data ( temperature, humidity and windy)\n");
	printf(" In order to give you some suggestion of activities\n");
	printf("Please enter the temperature ( 1 if more than 10 C degree, 0 otherwise ): ");
	scanf_s("%lf", &x);

	printf("Please enter the humidity ( 1 if more than 50 %, 0 otherwise ): ");
	scanf_s("%lf", &y);

	printf("Please enter the windy ( 1 if more than 20 km/h, 0 otherwise ): ");
	scanf_s("%lf", &z);
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
	
	double userInput[3];
	userInput[0] = x;
	userInput[1] = y;
	userInput[2] = z;

	
	double forecastResult = analyze(userInput);
	printf("The analyze result is %lf\n", forecastResult);
	WEATHER weather = mappingOutput(forecastResult);
	printf("Temperature: %.0f\nHumidity: %.0f\nWindy: %.0f\n", userInput[0], userInput[1], userInput[2]);
	printf("The weather is: %s. You can %s.\n", getWeatherName(weather), suggestActivity(weather));
	
	return 0;
}











