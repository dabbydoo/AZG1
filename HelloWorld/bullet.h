#pragma once

struct Bullet
{
	int bulletID;
	int xPos, yPos, zPos;
	int xDir, yDir;
};

struct Explosion
{
	int explosionID;
	int xPos, yPos, zPos;
	clock_t beginTime;
};


