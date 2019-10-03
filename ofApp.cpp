#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotate(45);

	for (int i = 0; i < 2; i++) {

		for (int len = 50; len < 250; len += 25) {

			vector<glm::vec3> vertices;
			for (int param = 0; param < 100; param++) {

				auto location = glm::vec3(this->make_point(len, param), 0) + glm::vec3(len * 0.5, len * -0.5, 0);
				auto distance = glm::length(location);

				auto angle_y = ofMap(sin(distance * 0.008 + ofGetFrameNum() * 0.02), -1, 1, -PI * 0.2, PI * 0.2);
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(1, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				vertices.push_back(location);
			}

			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}

		ofRotate(180);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}