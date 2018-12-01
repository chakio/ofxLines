#include "ofApp.h"

void Line::setStart(ofVec3f Start)
{
	start = Start;
}
void Line::setEnd(ofVec3f End)
{
	end = End;
}
void Line::setWidth(double Width)
{
	width = Width;
}
ofVec3f Line::getStart()
{
	return start;
}
void Line::draw()
{
	ofSetLineWidth(width);
	ofDrawLine(start,end);
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	ofSetFrameRate(60);

	gui.setup("panel");
	gui.setPosition(ofGetWidth() / 2 - ofGetWidth() / 3, ofGetHeight() / 2 - ofGetHeight() / 3);
	gui.add(length.setup("length", 500, 0, 1000));
	gui.add(radius.setup("radius", 500, 0, 1000));
	gui.add(rotation.setup("rotation",500, 0, 1000));
	gui.add(linewidth.setup("linewidth", 1, 0, 2));
	gui.add(alpha.setup("alpha", 100, 0, 255));
	sphere.set(2, 4);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	lines.resize(Num);
}

//--------------------------------------------------------------
void ofApp::update(){

	radiuses[0] = radius;

	times[0] = (int)(ofGetElapsedTimef() * 60) % (Num + 1);
	times[1] = (int)(ofGetElapsedTimef() * rotation) % (Num + 1);
	times[2] = (int)(ofGetElapsedTimef() * 100) % (Num + 1);
	times[3] = (int)(ofGetElapsedTimef() * 30) % (16*(Num + 1));
	
	updateLines();	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//gui.draw();
	ofEnableDepthTest();
	cam.begin();
	double r = radius;

	for (int i = 0; i < lines.size(); i++)
	{
		ofSetColor(255, 255, 255, alpha);
		lines[i].draw();

		ofSetLineWidth(1);
		ofSetColor(255, 0, 0);
		sphere.setPosition(lines[i].getStart());
		sphere.drawWireframe();
	}

	cam.end();
	ofDisableDepthTest();
}

void ofApp::updateLines()
{
	double resolution =40;
	for (int t = 0; t < Num; t++)
	{
		ofVec3f start,end;
		start.x = radiuses[0]*sin((double)t / resolution * 2 * PI);
		start.y = (double)(t - Num)*(length / Num) + length / 2;
		start.z = radiuses[0]*cos((double)t / resolution * 2 * PI);
		lines[t].setStart(start);

		ofVec3f center;//円。級の中心
		center.x = radiuses[2]*sin((double)times[2] / Num * 2 * PI);
		center.y = -(double)(length)*(sin(2 * PI*((double)times[0] / (double)Num))) / 2;
		center.z = radiuses[2]*cos((double)times[2] / Num * 2 * PI);
		if (mode == 0)//円の場合
		{
			double r = sqrt(pow(start.x - center.x, 2) + pow(start.z - center.z, 2));

			if (radiuses[2] < r)
			{
				end.x = center.x - radiuses[1]*cos(atan2(start.z - center.z, start.x - center.x) + PI + (double)acos(radiuses[2] / r)*sin(2 * PI*(double)times[1] / (double)Num + t));
				end.z = center.z - radiuses[1]*sin(atan2(start.z - center.z, start.x - center.x) + PI + (double)acos(radiuses[2] / r)*sin(2 * PI*(double)times[1] / (double)Num + t));
			}
			else
			{
				end.x = center.x - radiuses[1]*cos(atan2(start.z - center.z, start.x - center.x) + PI + (double)acos(r / radiuses[2])*sin(2 * PI*(double)times[1] / (double)Num + t));
				end.z = center.z - radiuses[1]*sin(atan2(start.z - center.z, start.x - center.x) + PI + (double)acos(r / radiuses[2])*sin(2 * PI*(double)times[1] / (double)Num + t));
			}
			end.y =center.y;
		}
		else if (mode == 1)
		{
			ofVec3f v1;
			v1 = start - center;

			double theta1;//xy���ʂɑ΂���p�x�̌v�Z
			theta1 = atan2(v1.z, v1.x);

			ofVec3f v2;//v1��xy���ʏ�ɗ���悤�ɉ�]�����x�N�g��
			v2 = v1.getRotatedRad(theta1, ofVec3f(0, 1, 0));

			ofVec3f v3;//v2��xy���ʂ�90�x��]�����x�N�g�� ������radius2
			v3 = v2.getRotatedRad(PI / 2, ofVec3f(0, 0, 1));
			v3 = v3.getNormalized();

			ofVec3f v4;//�ړ_����v1�ɐ���������Ƃ���̌�_�Ƌ��̒��S�܂ł̃x�N�g��
			v4 = (v2.length() - (pow(v2.length(), 2) - pow(radiuses[1], 2)) / v2.length())*v2.getNormalized();

			ofVec3f v5;//���߂��������x�N�g��
			v5 = v4 + v3*sqrt(pow(radiuses[1], 2) - pow(v4.length(), 2));

			v5 = v5.getRotatedRad(2 * PI*(((double)times[1] + (double)t) / (double)Num), v1);//���Ԃɉ����ĉ�

			v5 = v5.getRotatedRad(theta1, ofVec3f(0, -1, 0));//���̕����ɖ߂�
			v5 = v5 + center;//���̈ʒu�ɖ߂�;

			end = v5;
		}
		lines[t].setEnd(end);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mode = (mode + 1) % 2;
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
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}