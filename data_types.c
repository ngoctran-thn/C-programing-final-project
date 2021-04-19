#include "data_types.h"

WeatherCondition getWeatherCondition(double t, double h, double w) {
	WeatherCondition wc;
	wc.temperature = t;
	wc.humidity = h;
	wc.windy = w;
	return wc;
}

WeatherCondition* readDataFromFile() {

}