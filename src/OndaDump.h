#pragma once

#include "ofMain.h"
#include "colorUtil.h"

class OndaDump
{
	public:
	
		void		setup		( int w, int h, int posY, int intervalos, int gridStep);
		void		draw		( );
		void		drawGrid	( );
		void		update		( );
		void		addForce	( ofPoint p, ofVec2f force );
	
	protected:
		
		ofVec2f		getDampedValue	( ofVec2f oldValue, ofVec2f newValue, float alpha );
		int			getIndexByPos	( ofVec2f pos );

		int width;
		int height;
		int posY;
		int intervalos;
		int gridStep;
		int gridWidth;
		int gridHeight;

		ofVec2f		*grid;
		float		*onda;
		ColorUtil	colorUtil;
};