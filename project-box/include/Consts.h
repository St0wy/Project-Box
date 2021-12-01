#pragma once

constexpr unsigned FRAMERATE = 60;
constexpr char WINDOW_NAME[] = "Labyrinthe de la mort";

constexpr int WINDOW_SCALE = 50;
constexpr int WINDOW_WIDTH = 16 * WINDOW_SCALE;
constexpr int WINDOW_HEIGHT = 9 * WINDOW_SCALE;

constexpr float CAM_SCALE = 1.0f;
constexpr float CAM_WIDTH = 16.0f * CAM_SCALE;
constexpr float CAM_HEIGHT = 9.0f * CAM_SCALE;

constexpr float GRAVITY_STRENGHT = -9.81f;

constexpr float PHYSICS_STEP = 1.0f / static_cast<float>(FRAMERATE);

constexpr int32 POSITION_ITERATIONS = 2;
constexpr int32 VELOCITY_ITERATIONS = 6;