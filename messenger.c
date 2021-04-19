#include "messenger.h"

WEATHER mappingOutput(double result) {
	if (result < 0.25)
		return RAIN;
	if (result < 0.5)
		return CLOUDY;
	if (result < 0.75)
		return PARTLY_SUNNY;
	return SUNNY;
}

char* getWeatherName(WEATHER weather) {
	switch (weather) {
	case RAIN:
		return "rain";
		break;
	case CLOUDY:
		return "cloudy";
		break;
	case PARTLY_SUNNY:
		return "partly sunny";
		break;
	default:
		return "sunny";
		break;
	}
}