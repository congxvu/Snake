// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */
 
void draw_nothing(int u, int v);
void draw_plant(int u, int v);
void draw_wall(int u, int v);
void draw_goodie(int u, int v);
void draw_snake_body(int u, int v);
void draw_snake_head_down(int u, int v);
void draw_snake_head_up(int u, int v);
void draw_snake_head_right(int u, int v);
void draw_neg(int u,int v);
void draw_neg_status();
void draw_snake_head_left(int u, int v);
void draw_snake_tail(int u, int v);
void draw_snake(int u, int v);
void draw_poison(int u, int v);
void draw_cure(int u, int v);
void draw_frozen(int u, int v);
void draw_gate(int u, int v);
void draw_key(int u, int v);
void draw_poison_status();
void draw_shield(int u, int v);
void draw_shield_status();
void draw_life(int u, int v);
void draw_cross(int u, int v);
void draw_cross_status();
void draw_frozen_status();
void draw_two(int u, int v);
void draw_two_status();
void draw_ez(int u, int v);
void draw_ez_status();
void draw_key_status();
void draw_spike(int u, int v);
#endif // GRAPHICS_H