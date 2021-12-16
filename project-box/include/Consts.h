#pragma once

constexpr unsigned FRAMERATE = 60;
constexpr char WINDOW_NAME[] = "Project Box";

constexpr int WINDOW_SCALE = 100;
constexpr int WINDOW_WIDTH = 16 * WINDOW_SCALE;
constexpr int WINDOW_HEIGHT = 9 * WINDOW_SCALE;

constexpr float CAM_SCALE = 2.0f;
constexpr float CAM_WIDTH = 16.0f * CAM_SCALE;
constexpr float CAM_HEIGHT = 9.0f * CAM_SCALE;

constexpr float SCALE_FACTOR = 2.0f / 16.0f;

constexpr float GRAVITY_STRENGHT = -9.81f;

constexpr float PHYSICS_STEP = 1.0f / static_cast<float>(FRAMERATE);

constexpr int POSITION_ITERATIONS = 2;
constexpr int VELOCITY_ITERATIONS = 6;

constexpr char SPRITESHEET_PATH[] = "./data/sprites/char_spritesheet.png";
constexpr char BLOCK_SPRITE_PATH[] = "./data/sprites/block.png";
constexpr char FONT_PATH[] = "./data/fonts/upheaval.ttf";

constexpr char JUMP_SOUND_PATH[] = "./data/sounds/jump.wav";

const sf::Vector2u SPRITE_SIZE(16u, 16u);