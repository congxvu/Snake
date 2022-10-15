//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "snake.h"
#include <math.h>
#include<stdio.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))




int immortal = 0;
int pause = 0;
int start = 0;
int delta = 1;
int delta_score = 1;
  

// Helper function declarations
void playSound(char* wav);

/**
 * The main game state. Must include snake locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
Snake snake;

// Function prototypes

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 */
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8
#define LENGTH 10
#define WIN 12


// Get Actions from User (push buttons & accelerometer)
// Based on push button and accelerometer inputs, determine which action
// needs to be performed (may be no action).
int get_action(GameInputs inputs)
{
    if (!inputs.b1) immortal = !immortal;
    if (!inputs.b2) pause = !pause;
    if (!inputs.b3) start = !start;
    if ((snake.life == 0 && !immortal && snake.cross == 0) || snake.length >= LENGTH || snake.score >= WIN) return GAME_OVER;  
    if (inputs.ay >= 0.5 && pause == 0 && snake.frozen == 0 ) return GO_UP;
    if (inputs.ay < -0.5 && pause == 0 && snake.frozen == 0) return GO_DOWN;
    if (inputs.ax < -0.5 && pause == 0 && snake.frozen == 0) return GO_LEFT;
    if (inputs.ax >= 0.5 && pause == 0 && snake.frozen == 0 ) return GO_RIGHT;
    else return NO_ACTION;
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the snake position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the snake has not moved.
 */
int update_game(int action)

        //snake buffs, debuffs conditions 
{      if(snake.two == 1 && snake.poisoned == 0)
        {delta_score = 2;}
       if(snake.poisoned == 1)
        {delta_score = 0;}
       if(snake.poisoned == 0 && snake.two == 0)
       {delta_score = 1;}
       if(snake.neg == 1)
       {
            for(int i = snake.length - 1 ; i >=0; i--)
            {   add_nothing(snake.locations[i].x, snake.locations[i].y);}
       }
       if(snake.neg == 0)
            
    
        
         
       if(((snake.timer%2) == 0) && snake.ez == 1) // EZ MOVE, move the snake every 2 cycles.
                  {
                  return NO_RESULT;}
         
        if(snake.health == 0)
            {
                snake.life -=1;
                snake.health = 3;
                snake.score = 0;
                
                for(int i = snake.length-1 ; i > 1; i--)
                {add_nothing(snake.locations[i].x, snake.locations[i].y);
                }
                snake.length = 3; 
                                
                add_snake_body(snake.locations[1].x,snake.locations[1].y);
                    
                add_snake_tail(snake.locations[snake.length-1].x,snake.locations[snake.length-1].y);
                
                
            }
       if(snake.key != 0)
            {   draw_key_status();
              }
        if(snake.key == 0)
            {   uLCD.locate(8,15);
                
               uLCD.color(CLEAR);
               uLCD.printf("K");
                snake.key = 0;}
        
        if(snake.ez_timer !=0 && snake.ez != 0)
            {   draw_ez_status();
                snake.ez_timer = snake.ez_timer - 1;}
        if(snake.ez_timer == 0)
            {   uLCD.locate(16,15);
                uLCD.color(CLEAR);
                uLCD.printf("E");
                snake.ez = 0;}
                
        if(snake.frozen_timer !=0 && snake.frozen != 0)
            {   draw_frozen_status();
                snake.frozen_timer = snake.frozen_timer - 1;}
        if(snake.frozen_timer == 0)
            {   uLCD.locate(13,15);
                uLCD.color(CLEAR);
                uLCD.printf("F");
                snake.frozen = 0;}
        
        if(snake.neg !=0 && snake.neg_timer != 0)
            {   draw_neg_status();
                snake.neg_timer = snake.neg_timer - 1;}
        if(snake.neg_timer == 0)
            {   uLCD.locate(7,15);
                uLCD.color(CLEAR);
                uLCD.printf("N");
                snake.neg = 0;}
                
        if(snake.two_timer !=0 && snake.two != 0)
            {   draw_two_status();
                snake.two_timer = snake.two_timer - 1;}
        if(snake.two_timer == 0)
            {   uLCD.locate(10,15);
                uLCD.color(CLEAR);
                uLCD.printf("2x");
                snake.two = 0;}
                
        if(snake.poison_timer !=0 && snake.poisoned != 0)
            {   draw_poison_status();
                snake.poison_timer = snake.poison_timer - 1;}
        if(snake.poison_timer == 0)
            {   uLCD.locate(9,15);
                uLCD.color(CLEAR);
                uLCD.printf("P");
                snake.poisoned = 0;}
                
        if(snake.cross_timer !=0 && snake.cross != 0)
            {   draw_cross_status();
                snake.cross_timer = snake.cross_timer - 1;}
        if(snake.cross_timer == 0)
            {   uLCD.locate(16,0);
                uLCD.color(CLEAR);
                uLCD.printf("I");
                snake.cross = 0;}
               
        if(snake.shield_timer !=0 && snake.shielded != 0)
            {   
                draw_shield_status();
                snake.shield_timer = snake.shield_timer - 1;}
        if(snake.shield_timer == 0)
            {   uLCD.locate(12,15);
                uLCD.color(CLEAR);
                uLCD.printf("S");
                snake.shielded = 0;}
                
            if (pause == 1)
                {uLCD.locate(15,15);
                uLCD.color(RED);
                uLCD.printf("P");
                }
            if(pause == 0)
                {uLCD.locate(15,15);
                uLCD.color(CLEAR);
                uLCD.printf("P");
                }
        
    
    switch(action) {
        case GAME_OVER: // game over screen
            
            {uLCD.color(RED);
            uLCD.cls();
            uLCD.text_width(3);
            uLCD.text_height(3);
            uLCD.printf("GAME\nOVER");
            uLCD.color(GREEN);
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.printf("\n\n\n\n\nScore %d", snake.score);
            uLCD.color(BLUE);
            uLCD.text_width(1);
            uLCD.text_height(1);
            if (snake.score >= WIN)
            {   
                uLCD.printf("\nYou win!");
                //uLCD.printf("\n\n\n\nWant a cookie bro?");
                playSound("/sd/start.wav");
            }
            else
            {
            uLCD.printf("\nBetter luck");
            uLCD.printf("\nnext time fam :(.");
            playSound("/sd/lose.wav");}
            }

            while(1);

            
                // Snake movement functions
        case GO_UP:
        if(get_north(snake.head_x, snake.head_y)->type == NEG)
        {snake.neg_timer = 50; snake.neg = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == KEY)
        {snake.key = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == EZ)
        {snake.ez_timer = 50; snake.ez = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == TWO)
        {snake.two_timer = 50; snake.two = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == FROZEN)
        {snake.frozen_timer = 50; snake.frozen = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == CROSS)
        {snake.cross_timer = 50; snake.cross = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == POISON)
        {snake.poison_timer = 50; snake.poisoned = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == SHIELD)
        {snake.shield_timer = 50; snake.shielded = 1;}
        if(get_north(snake.head_x, snake.head_y)->type == LIFE)
        {snake.health = snake.health + 1;}
        if(get_north(snake.head_x, snake.head_y)->type == ENEMY && snake.shielded == 0)
        {
                snake.health = snake.health - 1;
        
        
                
         }
                
        
        
         if(get_north(snake.head_x, snake.head_y)->walkable != false || get_north(snake.head_x, snake.head_y) == NULL)
            {
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y; 
        if(get_north(snake.head_x, snake.head_y)->type == GOODIE)
         { 
         
           
            snake.score  += delta_score;
            snake.length +=1;
            /*
                if(snake.two == 1)
                    {snake.score +=2;}
        
            
        else if(snake.poisoned == 0 && snake.neg == 1)
           snake.score  -=1;
            snake.length +=1;
            if(snake.two == 1)
            {snake.score -=2;}*/
            
        
        
        
            
                 for (int i = snake.length-1; i > 0 ; i--)
            {   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_y -=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0)
                    {add_snake_head_up(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);}
               break;     
        }
        
              add_nothing(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y);
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_y -=1;
                    snake.locations[0].x = snake.head_x;
                    snake.locations[0].y = snake.head_y;
                    if(snake.neg == 0){
                    add_snake_head_up(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);
                    
                    add_snake_tail(snake.locations[snake.length-1].x,snake.locations[snake.length-1].y);}
                    if(get_north(snake.head_x, snake.head_y)->type == WALL  && !immortal)
        {snake.life = 0;}
        if(get_north(snake.head_x, snake.head_y)->type == SNAKE_BODY  && !immortal)
        {snake.life = 0;}
                    if(get_north(snake.head_x, snake.head_y)->type == DOOR  && !immortal && snake.key == 0)
                    {snake.life = 0;}
                    if(get_north(snake.head_x, snake.head_y)->type == DOOR  && snake.key == 1)
                    {snake.key = 0;
                    add_nothing(35,10);
                    add_nothing(30,5);}
                    break;}break;
            
        case GO_LEFT:
        if(get_west(snake.head_x, snake.head_y)->type == NEG)
        {snake.neg_timer = 50; snake.neg = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == KEY)
        {snake.key = 1;}
        
        if(get_west(snake.head_x, snake.head_y)->type == EZ)
        {snake.ez_timer = 50; snake.ez = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == TWO)
        {snake.two_timer = 50; snake.two = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == FROZEN)
        {snake.frozen_timer = 50; snake.frozen = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == CROSS)
        {snake.cross_timer = 50; snake.cross = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == POISON)
        {snake.poison_timer = 50; snake.poisoned = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == SHIELD)
        {snake.shield_timer = 50; snake.shielded = 1;}
        if(get_west(snake.head_x, snake.head_y)->type == LIFE)
        {snake.health = snake.health + 1;}
        if(get_west(snake.head_x, snake.head_y)->type == ENEMY && snake.shielded == 0)
        {
                snake.health = snake.health - 1;
        
                
         }
        
        
        
        if(get_west(snake.head_x, snake.head_y)->walkable != false || get_west(snake.head_x, snake.head_y) == NULL)
            {
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y; 
        if(get_west(snake.head_x, snake.head_y)->type == GOODIE)
         { 
                
                    
                    snake.score  += delta_score;
                    snake.length +=1;
               
                
            
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_x -=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0)
                    {add_snake_head_left(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);}
               break;     
        }
        
              add_nothing(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y);
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_x -=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0)
                    {add_snake_head_left(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);
                    
                    add_snake_tail(snake.locations[snake.length-1].x,snake.locations[snake.length-1].y);}
                    if(get_west(snake.head_x, snake.head_y)->type == WALL  && !immortal)
        {snake.life = 0;}
        if(get_west(snake.head_x, snake.head_y)->type == SNAKE_BODY  && !immortal)
        {snake.life = 0;}
                    break;}break;
 
        case GO_DOWN:
        
        if(get_south(snake.head_x, snake.head_y)->type == NEG)
        {snake.neg_timer = 50; snake.neg = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == KEY)
        {snake.key = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == EZ)
        {snake.ez_timer = 50; snake.ez = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == TWO)
        {snake.two_timer = 50; snake.two = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == FROZEN)
        {snake.frozen_timer = 50; snake.frozen = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == CROSS)
        {snake.cross_timer = 50; snake.cross = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == POISON)
        {snake.poison_timer = 50; snake.poisoned = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == SHIELD)
        {snake.shield_timer = 50; snake.shielded = 1;}
        if(get_south(snake.head_x, snake.head_y)->type == LIFE)
        {snake.health = snake.health + 1;}
        if(get_south(snake.head_x, snake.head_y)->type == ENEMY && snake.shielded == 0)
        {
                snake.health = snake.health - 1;
            
                
         }
        
        
        if(get_south(snake.head_x, snake.head_y)->walkable != false || get_south(snake.head_x, snake.head_y) == NULL)
            {
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y; 
        if(get_south(snake.head_x, snake.head_y)->type == GOODIE)
         { 
         
            
            snake.score  += delta_score;
            snake.length +=1;
               
            
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_y +=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0){
                    add_snake_head_down(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);}
               break;     
        }
        
              add_nothing(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y);
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                    
                 
                    snake.head_y += 1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0){
                    add_snake_head_down(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);
                    
                    add_snake_tail(snake.locations[snake.length-1].x,snake.locations[snake.length-1].y);}
                    if(get_south(snake.head_x, snake.head_y)->type == WALL  && !immortal)
        {snake.life = 0;}
        if(get_south(snake.head_x, snake.head_y )->type == SNAKE_BODY  && !immortal)
        {snake.life = 0;}
                    break;}
                    
                //if(get_south(snake.head_x, snake.head_y)->type == CUT)
        //    {
                 //for (int i = 2; i < snake.length; i++)
               //  {add_nothing(snake.locations[i].x, snake.locations[i].y);}
              //   snake.length = 3;}
               break;
                    
                    
           
        case GO_RIGHT:
        if(get_east(snake.head_x, snake.head_y)->type == NEG)
        {snake.neg_timer = 50; snake.neg = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == KEY)
        {snake.key = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == EZ)
        {snake.ez_timer = 50; snake.ez = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == TWO)
        {snake.two_timer = 50; snake.two = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == FROZEN)
        {snake.frozen_timer = 50; snake.frozen = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == CROSS)
        {snake.cross_timer = 50; snake.cross = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == POISON)
        {snake.poison_timer = 50; snake.poisoned = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == SHIELD)
        {snake.shield_timer = 50; snake.shielded = 1;}
        if(get_east(snake.head_x, snake.head_y)->type == LIFE)
        {snake.health = snake.health + 1;}
        if(get_east(snake.head_x, snake.head_y)->type == ENEMY && snake.shielded == 0)
        {
                snake.health = snake.health - 1;
            
                
                
        }
        
        
        if(get_east(snake.head_x, snake.head_y)->walkable != false || get_east(snake.head_x, snake.head_y) == NULL)
            {
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y; 
        if(get_east(snake.head_x, snake.head_y)->type == GOODIE)
         { 
         
            
            snake.score  += delta_score;
            snake.length += 1;
                
                
            
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                
                  snake.head_x +=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0){
                    add_snake_head_left(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);}
                  
               break;     
        }
        
              add_nothing(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y);
                 for (int i = snake.length-1; i > 0 ; i--){   
                snake.locations[i].x = snake.locations[i-1].x;
                snake.locations[i].y =   snake.locations[i-1].y;     
                }          
                  snake.head_x +=1;
                   snake.locations[0].x = snake.head_x;
                   snake.locations[0].y = snake.head_y;
                   
                   if(snake.neg == 0){
                    add_snake_head_left(snake.locations[0].x, snake.locations[0].y);                  
                    add_snake_body(snake.locations[1].x,snake.locations[1].y);
                    
                    add_snake_tail(snake.locations[snake.length-1].x,snake.locations[snake.length-1].y);}
                    if(get_east(snake.head_x, snake.head_y)->type == WALL  && !immortal )
        {snake.life = 0;}
        if(get_east(snake.head_x, snake.head_y)->type == SNAKE_BODY  && !immortal)
        {snake.life = 0;}
                    break;} break;
       }
        
    return NO_RESULT;
    
}

    

/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    //Coordinates
    uLCD.color(0x0D3572);
    uLCD.locate(1,0);
    uLCD.printf("(%d ",snake.head_x);
    uLCD.color(0x0D3572);
    uLCD.locate(5,0);
    uLCD.printf("%d)",snake.head_y);
    //Health
    uLCD.color(RED);
    uLCD.locate(8,0);
    uLCD.printf("H:%d",snake.health);
    // Life
    uLCD.color(WHITE);
    uLCD.locate(12,0);
    uLCD.printf("L:%d",snake.life);
}


    
/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    //uLCD.line(0, 118, 127, 118, GREEN);
    uLCD.locate(0,15);
    uLCD.color(GREEN);
    uLCD.printf("Pts: %d",snake.score);
    
}
/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int draw_option)
{
    // Draw game border first
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        int u = 58;
        int v = 59;
        draw_snake_head_right(u, v);
        draw_snake_body(u-11, v);
        draw_snake_tail(u-22, v);
        return;
    }
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + snake.head_px;
            int py = j + snake.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{   int i;
    srand(time(0));
    rand() % 55 + 1;
    Map* map = set_active_map(0);
    for (i = 1; i < 60; i++)
        {add_goodie(rand() % 55 + 1,rand() % 55 + 1);}
    
    pc.printf("plants\r\n")
    ;
    
    for (i = 1; i < 25; i++)
        {add_poison(rand() % 55 + 1 ,rand() % 55 + 1);}
    for (i = 1; i < 60; i++)
        {add_spike(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 5; i++)
        {add_life(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 3; i++)
        {add_cross(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 9; i++)
        {add_frozen(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 10; i++)
        {add_two(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 3; i++)
        {add_ez(rand() % 55 + 1,rand() % 55 + 1);}
    for (i = 1; i < 6; i++)
        {add_shield(rand() % 55 + 1,rand() % 55 + 1);}
        for (i = 1; i < 8; i++)
        {add_neg(rand() % 55 + 1,rand() % 55 + 1);}
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    add_snake_head_right(snake.locations[0].x, snake.locations[0].y);
    add_snake_body(snake.locations[1].x, snake.locations[1].y);
    add_snake_tail(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");
    add_gate(35,10);
    add_key(  rand()% 55 ,10 + rand()% 30);
    add_life(33,5);
    add_life(34,5);
    add_life(35,5);
    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

//    profile_hashtable();
    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function or all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    snake_init(&snake);
    // 0. Initialize the maps -- implement this function:
    maps_init();
    init_main_map();
    
    
     //playSound("/sd/wavfiles/eat.wav");

    // Initialize game state
    set_active_map(0);
   // snake.head_px = snake.head_x = 5 ;
   // snake.head_py = snake.head_y = 5 ;
    // Initial drawing
            uLCD.color(RED);
            
           uLCD.text_width(2);
           uLCD.text_height(2);
            uLCD.printf("A Snek\n Game");
            uLCD.color(0xFFFF00);
            
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.printf("\n\n\n\n\n\n by Khoa Nguyen");
            
            uLCD.color(0x0112FF);
            
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.printf("\npls gif xtra creds");
            uLCD.color(GREEN);
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.printf("\n\n\n\n Press b3 to start");
            uLCD.color(GREEN);
            //playSound("/sd/lightweight.wav");
            GameInputs i = read_inputs();
            
            while(!start){get_action(i); i = read_inputs();}
    uLCD.cls();
    draw_game(FULL_DRAW);
    // Main game loop
    while(1) {
        // Timer to measure game update speed
        Timer t;
        t.start();
   
        
        
        
        if(snake.timer > 1) 
        {
        snake.timer = snake.timer + delta;
        delta = -delta;}
        
        

        // 1. Read inputs -- implement this function:
        GameInputs inputs = read_inputs();
        
        // 2. Determine action (move, act, menu, etc.) -- implement this function:
        int action = get_action(inputs);
        
        // 3. Update game -- implement this function:
        int result = update_game(action);
        
        // 3b. Check for game over based on result
        // and if so, handle game over -- implement this.
                
        // 4. Draw screen -- provided:
        draw_game(result);
        
        // Compute update time
        t.stop();
        int dt = t.read_ms();

        // Display and wait
        // NOTE: Text is 8 pixels tall
        if (dt < 100) wait_ms(100 - dt);
    }
}

// Plays a wavfile

void playSound(char* wav) 
{
FILE *wave_file;
    wave_file=fopen(wav,"r");

    // play wav file
    waver.play(wave_file);

    // close wav file
    fclose(wave_file);
}