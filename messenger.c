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
	}
}

char* suggestActivity(WEATHER weather) {
	char* sunnyActivities[] = { "go swimming", "go camping", "go rowing" };
	char* partlySunnyActivities[] = { "take photography", "go cycling", "go climbing" };
	char* cloudyActivities[] = { "go jogging", "do planning trees", "hang out with dogs" };
	char* rainnyActivities[] = { "go to cinema", "go to library", "go sleeping" };

	int randNumber = time(0) % 3;
	switch (weather) {
	case RAIN:
		return rainnyActivities[randNumber];
		break;
	case CLOUDY:
		return cloudyActivities[randNumber];
		break;
	case PARTLY_SUNNY:
		return partlySunnyActivities[randNumber];
		break;

	default:
		return  sunnyActivities[randNumber];
	}
}