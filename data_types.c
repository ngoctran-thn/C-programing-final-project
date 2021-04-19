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

WeatherCondition* readDataFromFile() {
	FILE* file;
	file = fopen("weather_data.txt", "r");

	if (file == NULL) {
		printf("Error: can't open file.\n");
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