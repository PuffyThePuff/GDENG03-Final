#pragma once

class GlobalProperties
{
public:
	static void setActiveCubes(bool flag);
	static void setEnabledCubes(bool flag);
	static void setBackgroundColor(float red, float green, float blue);

	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;

	static bool IS_CUBE_MOVEMENT_ON;
	static bool ARE_CUBES_ACTIVE;

	static float BACKGROUND_COLOR[3];
	static float TRANSLATION_SPEED;
	static float ROTATION_SPEED;
	static float SCALE_SPEED;
};