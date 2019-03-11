//  	
//	Alex Frank
//	San Jose State University
//	CS134: Computer Game Design
//
//	Code modified from source code provided by 
//	CS134 Professor Kevin Smith (c) 2019
//

#include "ofApp.h"

void ofApp::setup(){

	// Console message to show idle mode
	cout << "Press space to start game..." << endl;

	// Window setup
	ofSetWindowTitle("Arcade Shooter");
	ofSetVerticalSync(true);
	bToggleGUI = false;
	bGameStarted = false;
	currentRate = 0;

	// Load sounds
	shot.load("sounds/shot.wav");
	
	// Set up player sprite
	if (playerImage.loadImage("images/ship.png")) {
		sprite.setImage(playerImage);
	}
	start_point = ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0);
	finish_point = ofVec3f(650, 500);
	sprite.trans.set(start_point);
	sprite.speed = 240;   // in pixels per second (screenspace 1 unit = 1 pixel)
	moveDir = MoveStop;

	// Set up bullet emitter
	gun = new Emitter(new SpriteSystem());
	if (bulletImage.loadImage("images/bullet.png")) {
		gun->setChildImage(bulletImage);
	}
	gun->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 - 60, 0));
	gun->start();

	// Set up enemy emitters
	enemyEmitter1 = new Emitter(new SpriteSystem());
	if (enemyImage.loadImage("images/enemy1.png")) {
		enemyImage.resize(50, 50);
		enemyEmitter1->setChildImage(enemyImage);
	}
	enemyEmitter1->setPosition(ofVec3f(100, 10, 0));
	enemyEmitter1->velocity.set(0, 300, 0);
	enemyEmitter1->setLifespan(5000);
	enemyEmitter1->setRate(1);
	enemyEmitter1->setChildSize(50, 50);
	enemyEmitter1->start();

	enemyEmitter2 = new Emitter(new SpriteSystem());
	if (enemyImage.loadImage("images/enemy1.png")) {
		enemyImage.resize(50, 50);
		enemyEmitter2->setChildImage(enemyImage);
	}
	enemyEmitter2->setPosition(ofVec3f(ofGetWindowWidth() - 100, 10, 0));
	enemyEmitter2->velocity.set(0, 300, 0);
	enemyEmitter2->setLifespan(5000);
	enemyEmitter2->setRate(1);
	enemyEmitter2->setChildSize(50, 50);
	enemyEmitter2->start();



	//GUI setup
	gui.setup();
	gui.add(rate.setup("rate", 2, 1, 10));
	gui.add(life.setup("life", 2, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -500, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
}

//--------------------------------------------------------------
void ofApp::update() {
	updateSprite();
	gun->setRate(currentRate);
	gun->setLifespan(life * 1000);  
	gun->setVelocity(ofVec3f(velocity));
	gun->update();
	enemyEmitter1->update();
	enemyEmitter2->update();
	checkCollisions();

	// Vary initial enemy velocity
	ofVec3f v1 = enemyEmitter1->velocity;
	enemyEmitter1->setVelocity(ofVec3f(ofRandom(-v1.y / 2, v1.y / 2), v1.y, v1.z));

	ofVec3f v2 = enemyEmitter1->velocity;
	enemyEmitter2->setVelocity(ofVec3f(ofRandom(-v2.y / 2, v2.y / 2), v2.y, v2.z));

}

//  This is a simple O(M x N) collision check
//  For each missle check to see which invaders you hit and remove them
//
void ofApp::checkCollisions() {

	// find the distance at which the two sprites (missles and invaders) will collide
	// detect a collision when we are within that distance.
	//
	float collisionDist = gun->childHeight / 2 + enemyEmitter1->childHeight / 2;

	// Loop through all the missiles, then remove any invaders that are within
	// "collisionDist" of the missiles.  the removeNear() function returns the
	// number of missiles removed.
	//
	for (int i = 0; i < gun->sys->sprites.size(); i++) {
		score += enemyEmitter1->sys->removeNear(gun->sys->sprites[i].trans, collisionDist);
		score += enemyEmitter2->sys->removeNear(gun->sys->sprites[i].trans, collisionDist);
	}
}

// Given a distance return a modulated value between 1-10 based on 
// sin wave shape from 0 to PI
float ofApp::modulateAccel(float dist) {
	return sin(dist * PI) * 5.0 + 1.0;
}

void ofApp::updateSprite() {

	// Calculate distance to travel for this update
	float dist = sprite.speed * 1 / ofGetFrameRate();
	ofVec3f dir;
	ofRectangle r = ofGetWindowRect();
	
	//  If the accelerator modifer key is pressed, accelerate and
	//  deacclerate sprite from starting position to window edge
	if (accel) {
		switch (moveDir) {
			case MoveUp:
			{
				float totalDist = startAccelPoint.y;
				float frac = sprite.trans.y / totalDist;
				dir = ofVec3f(0, -dist * modulateAccel(frac), 0);
			}
			break;
			case MoveDown:
			{
				float totalDist = r.getMaxY() - startAccelPoint.y;
				float frac = sprite.trans.y / totalDist;
				dir = ofVec3f(0, dist * modulateAccel(frac), 0);
			}
			break;
			case MoveLeft:
			{
				float totalDist = startAccelPoint.x;
				float frac = sprite.trans.x / totalDist;
				dir = ofVec3f(-dist * modulateAccel(frac), 0, 0);
			}
			break;
			case MoveRight:
			{
				float totalDist = r.getMaxX() - startAccelPoint.x;
				float frac = sprite.trans.x / totalDist;
				dir = ofVec3f(dist * modulateAccel(frac), 0, 0);
				break;
			}
		}
	} else {
		switch (moveDir) {
		case MoveUp:
			dir = ofVec3f(0, -dist, 0);
			break;
		case MoveDown:
			dir = ofVec3f(0, dist, 0);
			break;
		case MoveLeft:
			dir = ofVec3f(-dist, 0, 0);
			break;
		case MoveRight:
			dir = ofVec3f(dist, 0, 0);
			break;
		}
	}

	// Translate sprite and bullet emitter together
	sprite.trans += dir;
	gun->trans += dir;
}

// Start sprite helper methods -------------------------------
void ofApp::moveSprite(MoveDir dir) {
	moveDir = dir;
}

void ofApp::stopSprite() {
	moveDir = MoveStop;
}

void ofApp::startAccel() {
	startAccelPoint = sprite.trans;
	accel = true;
}

void ofApp::stopAccel() {
	accel = false;
}
// End sprite helper methods ---------------------------------


//--------------------------------------------------------------
void ofApp::draw(){

	// Set background gradient
	ofColor colorOne(0, 0, 0);
	ofColor colorTwo(15, 32, 39);
	ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

	// Draw player and bullets
	sprite.draw();
	gun->draw();
	enemyEmitter1->draw();
	enemyEmitter2->draw();

	// Draw user interface
	if (!bToggleGUI) {
		gui.draw();
	}

	// Draw current score
	string scoreText;
	scoreText += "Score: " + std::to_string(score);
	ofDrawBitmapString(scoreText, ofPoint(10, 20));


}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	// If the game hasn't started, don't allow user to move
	if (!bGameStarted) return;

	// Move player + emitter pair according to mouse drag
	ofPoint mouse_cur = ofPoint(x, y);
	ofVec3f delta = mouse_cur - mouse_last;
	sprite.trans += delta;
	gun->trans += delta;
	mouse_last = mouse_cur;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	// If the game hasn't started, don't allow user to move
    if (!bGameStarted) return;

	mouse_last = ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// If the game hasn't started, don't allow user to move
	if (!bGameStarted) {
		switch (key) {
			case ' ':
				// Start the game on space bar press
				cout << "Game started!" << endl;
				bGameStarted = true;
				break;
			}
		return;
	}

	switch (key) {
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
			bToggleGUI = !bToggleGUI;
			break;
		case ' ':
			// Scale shot noise speed w/ rate of fire
			shot.setSpeed(rate / 3.5);
			shot.setLoop(true);
			if (!shot.isPlaying()) shot.play();
			// Set current rate to slider rate
			currentRate = rate; 
			break;
		case '.':
			sprite.speed += 30;
			break;
		case ',':
			sprite.speed -= 100;
			break;
		case OF_KEY_RIGHT:
		case 'd':
		case 'D':
			moveSprite(MoveRight);
			break;
		case OF_KEY_LEFT:
		case 'a':
		case 'A':
			moveSprite(MoveLeft);
			break;
		case OF_KEY_UP:
		case 'w':
		case 'W':
			moveSprite(MoveUp);
			break;
		case OF_KEY_DOWN:
		case 's':
		case 'S':
			moveSprite(MoveDown);
			break;
		case OF_KEY_CONTROL:
			startAccel();
			break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
		case ' ':
			shot.setLoop(false);
			currentRate = 0;
			break;
		case 'w':
		case 'W':
		case 'a':
		case 'A':
		case 's':
		case 'S':
		case 'd':
		case 'D':
		case OF_KEY_LEFT:
		case OF_KEY_RIGHT:
		case OF_KEY_UP:
		case OF_KEY_DOWN:
			stopSprite();
			stopAccel();
			break;
		case OF_KEY_CONTROL:
			stopAccel();
			break;
		}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

