#include"GlobalProperties.h"

int GlobalProperties::WINDOW_WIDTH = 1440;
int GlobalProperties::WINDOW_HEIGHT = 900;
bool GlobalProperties::IS_CUBE_MOVEMENT_ON = true;
bool GlobalProperties::ARE_CUBES_ACTIVE = true;
float GlobalProperties::BACKGROUND_COLOR[3] = {
	154.f / 255.f,
	216.f / 255.f,
	216.f / 255.f
};
float GlobalProperties::TRANSLATION_SPEED = 5.f;
float GlobalProperties::ROTATION_SPEED = 1.f;
float GlobalProperties::SCALE_SPEED = 1.f;

void GlobalProperties::setActiveCubes(bool flag) {
	IS_CUBE_MOVEMENT_ON = flag;
}

void GlobalProperties::setEnabledCubes(bool flag) {
	ARE_CUBES_ACTIVE = flag;
}

void GlobalProperties::setBackgroundColor(float red, float green, float blue) {
	BACKGROUND_COLOR[0] = red;
	BACKGROUND_COLOR[1] = green;
	BACKGROUND_COLOR[2] = blue;
}