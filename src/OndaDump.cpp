#include "OndaDump.h"
#include "ofxBox2d.h"

OndaDump::OndaDump()
{
	bInited = false;
}

void OndaDump::setup ( int w, int h, int posY, int intervalos, int gridStep)
{
	width = w;
	height = h;
	this->posY = posY;
	this->intervalos = intervalos;
	this->gridStep = width / intervalos;

	intervaloWidth = (float)width / (float)intervalos;

	if (bInited)
	{
		delete [] onda;
		delete [] grid;
	}

	onda = new float[intervalos];
	for (int i = 0 ; i < intervalos ; i++)
		onda[i] = 0;
	
	//gridWidth = width / gridStep;
	//gridHeight = height / gridStep;
	gridWidth = intervalos;
	gridHeight = 1;
	grid = new ofVec2f[gridHeight * gridWidth];
	memset(grid, 0, gridHeight * gridWidth * sizeof(ofVec2f));

	setupBox2d();
	bInited = true;

	seed = ofRandom(1,1000);
}

void OndaDump::setupBox2d()
{
	if (!bInited)
	{
		box2d.init();
		box2d.setGravity(0, 0);
		box2d.setFPS(30.0);
		box2d.registerGrabbing();
		box2d.createBounds();
		box2d.createGround();
	}

	if (bInited)
	{
		for (int i = 0 ; i < joints.size() ; i++)
			joints[i].get()->destroy();
		for (int i = 0 ; i < circles.size() ; i++)
			circles[i].get()->destroy();
		circles.clear();
		joints.clear();
	}
	//anchor1.setup(box2d.getWorld(), 0, posX, 20);
	//anchor1.setPhysics(3.0, 0.53, 0.1);

	//anchor2.setup(box2d.getWorld(), width, , 20);
	//anchor2.setPhysics(3.0, 0.53, 0.1);

	for (int i=0; i<intervalos; i++) 
	{
		ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		if ( i != 0 && i != intervalos-1 )
			circle.get()->setPhysics(3.0, 0.53, 0.1);
		circle.get()->setup(box2d.getWorld(), i * intervaloWidth, posY, 4);
		circles.push_back(circle);
	}
	
	//primer y ultimo circle son inamovibles
	//circles[0].get()->setPhysics(1000.0, 0.53, 0.1);
	//circles[circles.size()-1].get()->setPhysics(1000.0, 0.53, 0.1);

	// now connect each circle with a joint
	// The greater the number, the more springy
	//float springiness = 1;
	for (int i=0; i<circles.size() - 1; i++) {
		
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
		
		b2Vec2 v1, v2;
		joint.get()->setup(box2d.getWorld(), circles[i].get()->body, circles[i+1].get()->body);
		v1 = circles[i].get()->body->GetPosition() ;
		v2 = circles[i+1].get()->body->GetPosition();

		ofVec2f vv1 (v1.x, v1.y);
		ofVec2f vv2 (v2.x, v2.y);
		float dist = vv1.distance(vv2) * 20.0;

		joint.get()->setFrequency(paramSpring);
		joint.get()->setLength(dist);
		joints.push_back(joint);

	}

}


void OndaDump::drawBox2d()
{
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x01b1f2);
		circles[i].get()->draw();
	}

	ofPolyline poly;
	//poly.addVertex(ofPoint(joints[0].get()->joint->GetAnchorA().x, joints[0].get()->joint->GetAnchorA().y) * OFX_BOX2D_SCALE);
	//for(int i=0; i<joints.size(); i++) {
	//	poly.curveTo(ofPoint(joints[i].get()->joint->GetAnchorB().x, joints[0].get()->joint->GetAnchorB().y) * OFX_BOX2D_SCALE);
	//}
	poly.addVertex(circles[0].get()->getPosition());
	poly.curveTo(circles[0].get()->getPosition());
	ofCircle(circles[0].get()->getPosition(),3);
	for(int i=1; i<circles.size(); i++) {
		poly.curveTo(circles[i].get()->getPosition());
		ofCircle(circles[i].get()->getPosition(),3);
	}
	//poly.curveTo(circles[0].get()->getPosition());
	//poly.curveTo(circles[0].get()->getPosition());
	//poly.close();
	ofSetColor(255,0,0);
	poly.draw();
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}


void OndaDump::draw ( )
{

	//drawBox2d();
	//return;

	drawGrid();
	
	ofSetColor(255,255,255);

	ofPolyline pol;
	pol.addVertex(0, posY - onda[0]);
	pol.curveTo(0, posY - onda[0]);
	
	float step = (float)width / (float)intervalos;
	//cout << "Intervalos: " << intervalos << ", gridWidth: " << gridWidth << endl;

	for (int i = 1 ; i < intervalos ; i++)
	{
		float v = 0;
		for (int k = 0 ; k < gridHeight ; k++)
			v = v + grid[k * gridWidth + i].y;
		
		onda[i] = v * 1.;
		//onda[i] = onda[i] * 0.99;
		//pol.curveTo(i * step, posY + (-.0 + sin(ofNoise(seed + (float)i + ofGetElapsedTimeMillis()) * 10. + ofGetElapsedTimeMillis() * .001f)) * onda[i]);
		pol.curveTo(i * step, posY + (sin( ofNoise(i, ofGetElapsedTimeMillis() * .001f) + ofGetElapsedTimeMillis() * .01f)) * onda[i]);
		//if (onda[i]>0) 
		//	cout << onda[i] << " ->sin = " << sin(onda[i]) << " # " ;
		//ofCircle(i * step, posY + onda[i],10);
	}

	pol.curveTo(width, posY);
	pol.curveTo(width, posY);
	pol.draw();

}

void OndaDump::drawGrid()
{
	for (int x = 0 ; x < gridWidth ; x++)
		for (int y = 0 ; y < gridHeight ; y++)
		{
			ofSetColor(grid[y * gridWidth + x].x, grid[y * gridWidth + x].y,0);
			ofFill();
			ofRect(x * gridStep,y * gridStep, gridStep, gridStep);
		}

}

void OndaDump::update ( )
{
	for(int i=0; i<circles.size(); i++)
	{
		circles[i].get()->addAttractionPoint(ofVec2f(i * intervaloWidth, posY), paramAttractionForce);
	}
	box2d.update();
	float damp = .996f;
	
	//ofVec2f *gridCols = new ofVec2f[gridWidth];
	//for (int i = 0 ; i < gridWidth ; i++)
	//{
	//	float v = 0;
	//	for (int k = 0 ; k < gridHeight ; k++)
	//		v = v + grid[k * gridWidth + i].y;
	//	gridCols[i].y = v;
	//}

	//float amount = 0.001f;
	//grid[0].y += gridCols[1].y * amount;
	//grid[gridWidth-1].y += gridCols[gridWidth-2].y * amount;

	//for (int i = 1 ; i < gridWidth -1; i++)
	//	grid[i].y += gridCols[i-1].y * amount + gridCols[i+1].y * amount;

	//for (int i = 0 ; i < gridHeight * gridWidth ; i++)
	//{
	//	grid[i] = grid[i] * damp;
	//	if (grid[i].y < 0.01)
	//		grid[i].y = 0;
	//	if (grid[i].x < 0.01)
	//		grid[i].x = 0;
	//}
	for (int i = 0 ; i < gridHeight * gridWidth ; i++)
		grid[i] = grid[i] * damp;

}

void OndaDump::addForce	( ofPoint p, ofVec2f force )
{
	//int index = getIndexByPos(p);
	int index = getColByPos(p);
	
	grid[index] = grid[index] + force;
	//if (index > 0)
	//	grid[index-1] = grid[index-1] + force * .8f;
	//if (index < intervalos)
	//	grid[index+1] = grid[index+1] + force * .8f;

}

ofVec2f OndaDump::getDampedValue ( ofVec2f oldValue, ofVec2f newValue, float alpha )
{
	return (alpha * newValue) + (1.0 - alpha) * oldValue;
}

int OndaDump::getIndexByPos ( ofVec2f pos )
{
	int x = floor(pos.x / gridStep); 
	int y = floor(pos.y / gridStep);
	return (y * gridWidth + x);
}

int OndaDump::getColByPos ( ofVec2f pos )
{
	int x = floor(pos.x / gridStep); 
	return (x);
}

