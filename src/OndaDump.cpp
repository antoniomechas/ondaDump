#include "OndaDump.h"


void OndaDump::setup ( int w, int h, int posY, int intervalos, int gridStep)
{
	width = w;
	height = h;
	this->posY = posY;
	this->intervalos = intervalos;
	this->gridStep = width / intervalos;

	onda = new float[intervalos];
	for (int i = 0 ; i < intervalos ; i++)
		onda[i] = 0;
	
	gridWidth = width / gridStep;
	gridHeight = height / gridStep;
	grid = new ofVec2f[gridHeight * gridWidth];
	memset(grid, 0, gridHeight * gridWidth * sizeof(ofVec2f));

}

void OndaDump::draw ( )
{
	drawGrid();
	
	ofSetColor(255,255,255);

	ofPolyline pol;
	pol.addVertex(0, posY - onda[0]);
	pol.curveTo(0, posY - onda[0]);
	
	float step = (float)width / (float)intervalos;

	for (int i = 1 ; i < intervalos ; i++)
	{
		float v = 0;
		for (int k = 0 ; k < gridHeight ; k++)
			v = v + grid[k * gridWidth + i].y;
		onda[i] = v;
		pol.curveTo(i * step, posY + onda[i]);
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
	float damp = .996f;
	for (int i = 0 ; i < gridHeight * gridWidth ; i++)
		grid[i] = grid[i] * damp;
}

void OndaDump::addForce	( ofPoint p, ofVec2f force )
{
	int index = getIndexByPos(p);
	
	grid[index] = grid[index] + force;

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

