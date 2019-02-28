#include "Sprite.h"

//  	
//	Alex Frank
//	San Jose State University
//	CS134: Computer Game Design
//
//	Code modified from source code provided by 
//	CS134 Professor Kevin Smith (c) 2019
//

BaseObject::BaseObject() {
	trans = ofVec3f(0, 0, 0);
	scale = ofVec3f(1, 1, 1);
	rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
	trans = pos;
}

// Basic Sprite Object
Sprite::Sprite() {
	speed = 0;
	velocity = ofVec3f(0, 0, 0);
	lifespan = -1;      // lifespan of -1 => immortal 
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 20;
	height = 20;
}

// Return a sprite's age in milliseconds
float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite
void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

//  Render the sprite
void Sprite::draw() {

	// Draw image centered and add in translation amount
	if (haveImage) {
		image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
	}
	else {
		// In case no image is supplied, draw something.
		ofNoFill();
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
	}
}
