#pragma once

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
WeatherCondition* readDataFromFile();