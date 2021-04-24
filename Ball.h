/******************************************************
file: Ball.h
lab : 11
by : Christian Apostoli
org : FGCU COP 2001, 202001 10409
desc : declaration of a block class object
*******************************************************/
#ifndef BALL_H
#define BALL_H

#include "fgcugl.h"		// OpenGL library
#include "Block.h"		//quad block object

class Ball {
public:
	// global defines
	enum CollisionType {
		None,					//0000
		Vertical,				//0001
		Horizontal			    //0010
	};

	//constructors
	Ball(float x, float y, float velocityX, float velocityY, int size, fgcugl::Color color = fgcugl::Blue);
	
	//accessors
	//getters
	float getXCoordinate();
	float getYCoordinate();
	float getXVelocity();
	float getYVelocity();
	int getSize();
	fgcugl::Color getColor();

	//setters
	void setXCoordinate(float value);
	void setYCoordinate(float value);
	void setXVelocity(float value);
	void setYVelocity(float value);
	void setSize(int value);
	void setColor(fgcugl::Color value);

	//member methods
	int top();
	int bottom();
	int left();
	int right();

	void update(float lag);
	void draw(float lag);

	CollisionType collisionCheck(Block block);
	void doCollision(int collisions);
private:
	float xpos;
	float ypos;
	float velocityX;
	float velocityY;
	int radius;
	fgcugl::Color color;
};

#endif // BALL_H