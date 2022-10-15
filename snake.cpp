// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "snake.h"

void snake_init (Snake * s)
{
    
    
    s->head_px = 4 ;
    s->head_py = 4;
    s->head_x = 5;
    s->head_y = 5;
    s->length = 3; 
    s->locations[0].x = 5;
    s->locations[0].y = 5;
    s->locations[1].x = 4;
    s->locations[1].y = 5;
    s->locations[2].x = 3;
    s->locations[2].y = 5;
    s->score = 0; //Current score of the snake
    
    // Buff variables and their respective timer
    s->poison_timer = 0;
    s->shield_timer = 0;
    s->cross_timer = 0;
    s->frozen_timer = 0;
    s->two_timer = 0;
    s->two = 0;
    s->timer = 2;
    s->ez = 0;
    s->ez_timer = 0;
    s->cross = 0;
    s->poisoned = 0;
    s->frozen = 0;
    s->shielded = 0;
    s->life = 3;
    s->health = 3;
    s->neg = 0;
    s->neg_timer = 0;
    s->key = 0;
    
}
