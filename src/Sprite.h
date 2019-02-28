#pragma once

//  	
//	Alex Frank
//	San Jose State University
//	CS134: Computer Game Design
//
//	Code modified from source code provided by 
//	CS134 Professor Kevinn Smith (c) 2019
//

#include "ofMain.h"

class BaseObject {
	public:
		BaseObject();

		ofVec2f trans, scale;
		float	rot;				
		bool	bSelected;

		void setPosition(ofVec3f);
};

class Sprite : public BaseObject {

public:
	Sprite();

	ofVec3f velocity;	// pixels/sec
	float speed;		// screenspace coordinates per second (pixels)
	ofImage image;
	float birthtime;	// elapsed time in ms
	float lifespan;		// time in ms
	string name;
	bool haveImage;
	float width, height;

	void draw();
	float age();
	void setImage(ofImage);
};
