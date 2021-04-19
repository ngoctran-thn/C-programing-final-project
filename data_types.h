#pragma once

#define MAX 10

struct WeatherCondition {
	double temperature;
	double humidity;
	double windy;
};
typedef struct WeatherCondition WeatherCondition;

/*
Returns a WeatherCondition based on the inputting temperature, humidity and windy

\param t The temperature
\param h The humidity
\param w The windy

\return The WeatherCondition instance
*/
WeatherCondition getWeatherCondition(double t, double h, double w);

/*
Read the weather dataset from resource file.

\return An pointer to the array of WeatherCondition(s)
*/
WeatherCondition* readTrainingInputFromFile();

/*
Read the weather training output dataset from resource file.

The output dataset must contain the same number of samples (records) to the input dataset.
*/
double* readTrainingOutputFromFile();
