#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class Line {
	private:
		ofVec3f start;
		ofVec3f end;
		double width;
	public:
		void setStart(ofVec3f Start);
		void setEnd(ofVec3f End);
		void setWidth(double Width);
		ofVec3f getStart();
		void draw();

};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void updateLines();
		void draw();

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

		ofEasyCam cam;

		ofxPanel gui;
		ofxFloatSlider length;
		ofxFloatSlider radius;
		int Num = 300;
		ofxIntSlider rotation;
		ofxFloatSlider linewidth;
		ofxIntSlider alpha;
		
		ofSpherePrimitive sphere;

		ofVec2f target; 

		int times[4];
		double radiuses[3] = {0,120,200};//ライト配置の半径、球の半径、球の移動半径

		int mode = 0;
		int mouse = 0;

		vector <Line> lines;
};
