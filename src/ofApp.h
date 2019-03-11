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
#include "ofxGui.h"
#include "Emitter.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void checkCollisions();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Sprite-specific methods
		void updateSprite();
		void moveSprite(MoveDir);
		void stopSprite();
		void startAccel();
		void stopAccel();
		float modulateAccel(float);
		
		// Initializations
		Sprite sprite;
		Emitter *enemyEmitter1, *enemyEmitter2, *gun;
		ofVec3f start_point;
		ofVec3f finish_point;
		float start_time;
		float finish_time;
		ofVec3f mouse_last;
		MoveDir moveDir;
		bool accel;
		ofVec3f startAccelPoint;
		float currentRate;

		// Images for player and projectiles
		ofImage playerImage;
		ofImage bulletImage;
		ofImage enemyImage;

		// Slider setup
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;

		// GUI variables
		ofxPanel gui;
		bool bToggleGUI;

		// Flag for game start
		bool bGameStarted;
		
		// Sounds
		ofSoundPlayer shot;

		int score;
};
