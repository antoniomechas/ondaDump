#pragma once

#ifndef __ColorUtil__
#define __ColorUtil__

#include "ofMain.h"

#define NUM_PALETA_COLORS 1000

class ColorUtil
{
	public:
		
		ColorUtil(){};
		
		void		setup();
		ofColor		getRandomColor			( );
		ofColor		getRandomBrightColor	( );
		ofColor		getNoiseColor			( float seedValue );
		ofColor		getNoiseColor2			( float seedValue );
		ofColor		getContinuoColor		( int step = 1 );
		
		ofColor		getNoiseAround			( ofColor c, float radius, float seedValue );			// Devuelve un color alrededor del especificado
		ofColor		getNoiseAroundMin		( ofColor c, float radius );							// Devuelve el color minimo que puede mostrar con este  valor de radio
		ofColor		getNoiseAroundMax		( ofColor c, float radius );							// Devuelve el color maximo que puede mostrar con este  valor de radio

		float		getDampedValue			( float oldValue, float newValue, float alpha );		// Devuelve el valor con un factor de damping
		ofPoint		getDampedValue			( ofPoint oldValue, ofPoint newValue, float alpha );	// Devuelve el valor con un factor de damping

	protected:

		ofColor		paleta[NUM_PALETA_COLORS];
		ofColor		*paletaCompleta;
		int			size;
		float		width;
		float		height;
		int			iContinuo;
};

#endif