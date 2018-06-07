#pragma once

#include <QVector2D>
#include <limits>
#include <functional>
#include <QMouseEvent>
#include <memory>
#include <type_traits>
#include <iostream>

/* filename of the config file */
constexpr char config_path[] = "config.json";
constexpr char collideSound_path[] = "../Poolgame/sound/collide.wav";
constexpr char pocketSound_path[] = "../Poolgame/sound/pocket.wav";

constexpr int animFrameMS = 16;
constexpr int drawFrameMS = 16;

constexpr double DOUBLEINF = std::numeric_limits<double>::max();

constexpr double flashLightRadius = 100.0;
