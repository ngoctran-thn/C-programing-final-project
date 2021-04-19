#pragma once

struct WeatherCondition {
	double temperature;
	double humidity;
	double windy;
};
typedef struct WeatherCondition WeatherCondition;

WeatherCondition getWeatherCondition(double t, double h, double w);
