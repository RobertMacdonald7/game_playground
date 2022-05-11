#pragma once

constexpr int unit_size_pixels = 10;
constexpr int game_width_pixels = 800;
constexpr int game_height_pixels = 600;

constexpr int game_area_pixels = game_width_pixels * game_height_pixels;

constexpr int game_width_units = game_width_pixels / unit_size_pixels;
constexpr int game_height_units = game_height_pixels / unit_size_pixels;
