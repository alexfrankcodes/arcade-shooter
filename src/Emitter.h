#pragma once
//  	
//	Alex Frank
//	San Jose State University
//	CS134: Computer Game Design
//
//	Code modified from source code provided by 
//	CS134 Professor Kevin Smith (c) 2019
//

#include "SpriteSystem.h"

//  General purpose Emitter class for emitting sprites
class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem *);

	SpriteSystem *sys;
	float rate;
	float speed;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	float width, height;
	float childWidth, childHeight;
	
	void draw();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
	void setImage(ofImage);
	void setRate(float);
	float maxDistPerFrame();
	void update();
	
};
