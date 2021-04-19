#pragma once

enum weather {
	RAIN, CLOUDY, PARTLY_SUNNY, SUNNY,
};
typedef enum weather WEATHER;

/*
Map the output number to a weather:
  1: sunny
  0.75: partly sunny
  0.5: cloudy
  0.25: light rain
  0: rain
*/
WEATHER mappingOutput(double result);

char* getWeatherName(WEATHER weather);

char* suggestActivity(WEATHER weather);
