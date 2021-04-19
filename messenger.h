#pragma once

enum weather {
	RAIN, CLOUDY, PARTLY_SUNNY, SUNNY,
};
typedef enum weather WEATHER;

WEATHER mappingOutput(double result);

char* getWeatherName(WEATHER weather);

char* suggestActivity(WEATHER weather);
