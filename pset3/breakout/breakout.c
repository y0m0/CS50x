//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle size
#define PADDLE_HEIGHT 12 
#define PADDLE_WIDTH 60

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard
    GLabel label = initScoreboard(window);
    sendToBack(label);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
 
    // ball speed
    double xSpeed;
    double ySpeed = 0.5;
    
    //random xSpeed either positive or negative
    double check = drand48();
    do
    {
        xSpeed = drand48();
    } 
    while(xSpeed <= 0.5);
    
    if (check <= 0.5)
    {
        xSpeed = -xSpeed;
    }
    
    // wait click to start
    waitForClick();
        
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // move the paddle with the mouse
        GEvent paddle_movement = getNextEvent(MOUSE_EVENT);
 
        // check for paddle events
        if (paddle_movement != NULL)
        {
            //check for paddle_movement
            if (getEventType(paddle_movement) == MOUSE_MOVED)
            {
                double x = getX(paddle_movement) - getWidth(paddle) / 2;
                if(x <= 0)
                {
                    x = 0;
                }
                else if (x + getWidth(paddle) >= WIDTH)
                {
                    x = WIDTH - getWidth(paddle);
                }
                setLocation(paddle, x, HEIGHT - 50);
            }
        }
        // move ball        
        move(ball, xSpeed, ySpeed);
        
        //detect if ball touches edges of the window     
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            xSpeed = -xSpeed;
        }
        else if (getX(ball) <= 0)
        {
            xSpeed = -xSpeed;
        }
        else if (getY(ball) <= 0)
        {
            ySpeed = -ySpeed;
        }
        // detect if ball touched the bottom
        else if (getY(ball) + getWidth(ball) >= HEIGHT)
        {
            lives--;
            waitForClick();
            removeGWindow(window, ball);
            ball = initBall(window);
            
            
        }
        
        // detect ball collision with objects
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // check if ball touches the paddle 
            if (object == paddle)  
            {
                // if ball moving down change Y direction
                if(ySpeed >= 0) 
                { 
                    // if ball hit the side of the paddle change X direction
                    if (getY(ball) + getWidth(ball) > getY(paddle))
                    {
                        if (getX(paddle) <= getX(ball) + getWidth(ball) || 
                            getX(paddle) + getWidth(paddle) >= getX(ball))
                        {
                            xSpeed = -xSpeed;
                            ySpeed = -ySpeed;
                        }
                    }    
                    else
                    {
                        ySpeed = -ySpeed;
                    }
                }
            }   
                
            // check if ball touches a brick
            else if (strcmp(getType(object), "GRect") == 0)
            {
                // change ball direction
                ySpeed = -ySpeed;
                // check if the ball hit the side of a brick
                if (getX(object) <= getX(ball) + getWidth(ball) || 
                    getX(object) + getWidth(object) >= getX(ball))
                {
                    if (getY(ball) < getY(object) &&
                        getY(ball) + getWidth(ball) > getY(object))
                    {
                        xSpeed = -xSpeed;
                        ySpeed = -ySpeed;
                    }
                    else if (getY(ball) < getY(object) + getHeight(object) &&
                             getY(ball) + getWidth(ball) > getY(object) + getHeight(object))
                    {
                        xSpeed = -xSpeed;
                        ySpeed = -ySpeed;
                    }                                             
                }
                // remove the touched brick
                removeGWindow(window, object);
                // decrease brick count
                bricks--;
                // increase score
                points++;
                // update scoreboard
                updateScoreboard(window, label, points);
            }
        }
        // add some pause to the while loop to make it playable
        pause(2);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int x = 2; // x-axis start point
    int y = 50; //y-axis start point
    int brick_width = 36;
    int brick_height = 10;
    
    char * color[5] = {"BLUE", "MAGENTA", "ORANGE", "GREEN", "CYAN"}; 
    int i = 0; // colors iterator

    for (int j = 0; j < ROWS; j++)
    {
        for (int k = 0; k < COLS; k++)
        {
            GRect brick = newGRect(x, y, brick_width, brick_height);
            setFilled(brick, true);
            setColor(brick, color[i]); 
            add(window, brick);
            x = x + 40;
        }
        i++;
        x = 2; // reset x-axys start point
        y = y + 15; // move y down to make a new row
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2 - RADIUS, HEIGHT/2, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "RED");
    add(window, ball);
    return ball;
    
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH - PADDLE_WIDTH) / 2, HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "DARK_GRAY");
    add(window, paddle);
    return paddle;

}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // create points board
    GLabel label = newGLabel("");
    setColor(label, "ORANGE");
    setFont(label, "Dialog-*-30");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
