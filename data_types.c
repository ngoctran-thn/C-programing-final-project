#define _CRT_SECURE_NO_DEPRECATE
#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "data_types.h"
#include <string.h>

WeatherCondition getWeatherCondition(double t, double h, double w) {
	WeatherCondition wc;
	wc.temperature = t;
	wc.humidity = h;
	wc.windy = w;
	return wc;
}

WeatherCondition* readTrainingInputFromFile() {
	FILE* file;
	file = fopen("weather_data_training_input.txt", "r");

	if (file == NULL) {
		printf("Error: can't open weather_data_training_input.txt file.\n");
		exit(EXIT_FAILURE);
	}
	WeatherCondition results[MAX];
	char c[10];
	int i = 0;
	while (fgets(c, 10, file) != NULL) {
		double t = atoi(&c[0]);
		double h = atoi(&c[2]);
		double w = atoi(&c[4]);
		results[i++] = getWeatherCondition(t, h, w);
	}
	fclose(file);

	return results;
}

double* readTrainingOutputFromFile() {
	FILE* file;
	file = fopen("weather_data_training_output.txt", "r");

	if (file == NULL) {
		printf("Error: can't open file.\n");
		exit(EXIT_FAILURE);
	}

	double results[MAX];

	char c[2 * MAX];
	fgets(c, 2 * MAX , file);

	int j = 0;
	for (int i = 0; i < 2*MAX; i++) {
		if (i % 2 == 0) {
			results[j++] = atoi(&c[i]);
		}
	}
	
	fclose(file);
	return results;
}

WeatherCondition ConvertUserData(int x, int y, int z, WeatherCondition convertedUserData) {
	if (x >= 10) {
		convertedUserData.temperature = 1;
	}
	else {
		convertedUserData.temperature = 0;
	}
	if (y >= 50) {
		convertedUserData.humidity = 0;
	}
	else {
		convertedUserData.humidity = 1;
	}
	if (z >= 20) {
		convertedUserData.windy = 0;
	}
	else {
		convertedUserData.windy = 1;
	}
	return convertedUserData;
}
