#pragma once

//  	
//	Alex Frank
//	San Jose State University
//	CS134: Computer Game Design
//
//	Code modified from source code provided by 
//	CS134 Professor Kevin Smith (c) 2019
//

#include "ofMain.h"
#include "Sprite.h"

//  Manages all Sprites in a system.  You can create multiple systems.
class SpriteSystem {
	public:
		SpriteSystem();

		void add(Sprite);
		void remove(int);
		void update();
		int removeNear(ofVec3f point, float dist);
		void draw();
		vector<Sprite> sprites;
};
