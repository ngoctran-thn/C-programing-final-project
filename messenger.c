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

