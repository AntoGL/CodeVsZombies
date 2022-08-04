#pragma once
#include "Point.h"

constexpr int WIDTH = 16000;
constexpr int HEIGHT = 9000;

constexpr Point LEFT_TOP_POINT = Point(0, 0);
constexpr Point RIGHT_BOTTOM_POINT = Point(WIDTH, HEIGHT);

constexpr int ASH_ID = -1;
constexpr double ASH_SPEED = 1000;
constexpr double ASH_ATTACK_RANGE = 2000;

constexpr double ZOMBIE_SPEED = 400;
constexpr double ZOMBIE_ATTACK_RANGE = 400;