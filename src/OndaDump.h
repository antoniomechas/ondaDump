#pragma once

#include "ofMain.h"
#include "colorUtil.h"
#include "ofxBox2d.h"
#include "ofxGui.h"

class OndaDump
{
	public:
					OndaDump	();
		void		setup		( int w, int h, int posY, int intervalos, int gridStep);
		void		draw		( );
		void		drawGrid	( );
		void		update		( );
		void		addForce	( ofPoint p, ofVec2f force );
	
		ofxFloatSlider	paramSpring;
		ofxFloatSlider	paramAttractionForce;

	protected:
		
		void		setupBox2d		( );
		ofVec2f		getDampedValue	( ofVec2f oldValue, ofVec2f newValue, float alpha );
		int			getIndexByPos	( ofVec2f pos );
		int			getColByPos		( ofVec2f pos );
		void		drawBox2d		( );

		int width;
		int height;
		int posY;
		int intervalos;
		int gridStep;
		int gridWidth;
		int gridHeight;
		
		float intervaloWidth;

		ofVec2f							*grid;
		float							*onda;
		ColorUtil						colorUtil;
		ofxBox2d						box2d;			  //	the box2d world
		ofxBox2dCircle					anchor1, anchor2;  //	fixed anchor
		vector<ofPtr<ofxBox2dCircle>>	circles;		  //	default box2d circles
		vector<ofPtr<ofxBox2dJoint> >	joints;			  //	joints

		bool							bInited;
		float							seed;
};