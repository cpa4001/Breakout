/******************************************************
file: Paddle.h
lab:  11
by:   Christian Apostoli
org:  FGCU COP 2001, 202001 10409
desc: implementation of a Player Paddle class object
*******************************************************/
#include <math.h>	//velocity checking
#include "Paddle.h"

const float ACCEL_SPEED = 6.0;
const float MAX_SPEED = 300.0;

// constructors
//-------------------------------------------------------------
/**
	default constructor - intialize empty block
*/
Paddle::Paddle()
{ 
	paddle = Block();
	currentX = 0.0;
	currentY = 0.0;
	velocity = 0.0;
}

/**
	default constructor - intialize to parameter values
*/
Paddle::Paddle(int x, int y, int width, int height, fgcugl::Color color)
{ 
	paddle = Block(x, y, width, height, color);
	currentX = x;
	currentY = y;
	velocity = 0.0;
}

//accessors
//-------------------------------------------------------------
//getters
Block Paddle::getPaddle() { return paddle; } 		//READ ONLY
float Paddle::getXCoordinate() { return currentX; }
float Paddle::getYCoordinate() { return currentY; }
int Paddle::getWidth() { return paddle.getWidth(); }
int Paddle::getHeight() { return paddle.getHeight(); }
fgcugl::Color Paddle::getColor() { return getColor(); }
float Paddle::getVelocity() { return velocity; }

//setters
void Paddle::setXCoordinate(float value)
{ 
	currentX = value;
	paddle.setXCoordinate(value);
}
void Paddle::setYCoordinate(float value)
{ 
	currentY = value;
	paddle.setYCoordinate(value);
}
void Paddle::setWidth(int value) { paddle.setWidth(value); }
void Paddle::setHeight(int value) { paddle.setHeight(value); }
void Paddle::setColor(fgcugl::Color value) { paddle.setColor(value); }
void Paddle::setVelocity(float value) { velocity = value; }

// member methods
//-------------------------------------------------------------
int Paddle::top() { return paddle.top(); }
int Paddle::bottom() { return paddle.bottom(); }
int Paddle::left() { return paddle.left(); }
int Paddle::right() { return paddle.right(); }

/**
	return true if block is empty (width + height is 0)
*/
bool Paddle::isEmpty() { return paddle.isEmpty(); }

/**
	determine current paddle movement direction from 
	its velocity (None = 0, Left = neg, Right = pos)
	Returns:
	PaddleDirection		direction paddle is moving
*/
Paddle::PaddleDirection Paddle::currentDirection() 
{
	PaddleDirection direction = None;

	if (fpclassify(velocity) == FP_ZERO)
	{
		direction = None;
	}
	else if (signbit(velocity))
	{
		direction = Left;
	}
	else
	{
		direction = Right;
	}

	return direction;
}

/**
	update location of paddle each frame relative to lag and perform
	collision checking with left and right walls
	Parameters:
	next		user keyboard input
	leftWall	location of left wall
	rightWall	location of right wall
	lag			current frame lag
*/
void Paddle::update(PaddleDirection next, Block leftWall, Block rightWall, float lag)
{
	PaddleDirection curDir = currentDirection();

	// is palyer not holding a direction key
	if (next == None)
	{
		// if paddle is moving
		if (curDir != None)
		{
			//slow paddle to a stop
			if (curDir == Left)
			{
				velocity += ACCEL_SPEED;
			}
			else
			{
				velocity -= ACCEL_SPEED;
			}
		} // paddle is moving
	}
	// player is holding direction key
	else
	{
		// accelerate paddle in user direction
		if (next == Left)
		{
			velocity -= ACCEL_SPEED;
		}
		else
		{
			velocity += ACCEL_SPEED;
		} //accel

		// keep speed at or below max
		if (abs(velocity) > MAX_SPEED)
		{
			if (next == Left)
			{
				velocity = -MAX_SPEED;
			}
			else
			{
				velocity = MAX_SPEED;
			} //accel
		}// max speed

	} // holding direction key

	//adjust paddle position
	currentX += velocity * lag;
	paddle.setXCoordinate(currentX);

	// check for collision with walls
	if (left() < leftWall.right())
	{
		velocity = 0.0;
		setXCoordinate(leftWall.right() + 1);
	}
	else if (right() > rightWall.left())
	{
		velocity = 0.0;
		setXCoordinate(rightWall.left() - getWidth());
	}

}// update


/**
	draw paddle objects on the Opengl window relative to
	current x/y with lag
	Paramters:
	lag		time between current time and rendering
*/
void Paddle::draw(float lag)
{ 
	float x = currentX + velocity * lag;
	Block currentPos(paddle);
	currentPos.setXCoordinate(x);
	currentPos.draw();
}

/**
draw the paddle with a broder by drawing the block passed on top
of a background block

Parameters :
borderColor		color of the border block
borderSize		size of border in pizels
*/
void Paddle::drawWithBorder(float lag, fgcugl::Color borderColor, int borderSize)
{ 
	float x = currentX + velocity * lag;
	float y = currentY;
	int width = paddle.getWidth();
	int height = paddle.getHeight();
	fgcugl::Color color = paddle.getColor();

	//draw background block
	Block background = Block(x, y, width, height, borderColor);
	background.draw();
	// draw inner block
	Block foreground = Block(x + borderSize, y + borderSize,
		width - 2 * borderSize, height - 2 * borderSize,
		color);
	foreground.draw();
}
