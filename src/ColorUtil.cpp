
#include "ColorUtil.h"

//--------------------------------------------------------------
void ColorUtil::setup()
{
	ofImage p;
	p.loadImage("images/paleta.png");
	
	width = p.width;
	height = p.height;
	size = width * height;

	paletaCompleta = new ofColor[size];

	unsigned char *pi = p.getPixels();
	int pos;

	for (int t=0; t < NUM_PALETA_COLORS ; t++)
	{
		pos = ofRandom( size ) * 3;
		paleta[t].r = pi[pos];
		paleta[t].g = pi[pos+1];
		paleta[t].b = pi[pos+2];
	}
	pos = 0;
	for (int t=0; t < size * 3 ; t = t + 3)
	{
		paletaCompleta[pos].r = pi[t];
		paletaCompleta[pos].g = pi[t+1];
		paletaCompleta[pos].b = pi[t+2];
		pos++;
	}
	
	iContinuo = ofRandom(size);

}

//--------------------------------------------------------------
ofColor ColorUtil::getContinuoColor(int step)
{
	iContinuo = iContinuo + step;
	if (iContinuo > size)
		iContinuo = 0;
	
	return(paletaCompleta[iContinuo]);
}


//--------------------------------------------------------------
ofColor ColorUtil::getRandomColor()
{
	return getRandomBrightColor();
	//return(paleta[(int)ofRandom(0, NUM_PALETA_COLORS - 1)]);
}

//--------------------------------------------------------------
ofColor ColorUtil::getRandomBrightColor()
{
	ofColor c;
	c.setHsb(ofRandom(255), ofRandom(200,255), ofRandom(200,255));

	return( c );
}
	

//--------------------------------------------------------------
ofColor	ColorUtil::getNoiseColor(float seedValue)
{
	//float scaleX = 0.007; //1.0 / scaleX is coherence in x
	//float scaleY = 0.008; //1.0 / scaleY is coherence in y
	//float posX0 = 593.2;
	//float posY0 = 43.7;
	//float value = ofNoise( x*scaleX+posX0, y*scaleY+posY0 );
	
	int pos = ofNoise(seedValue) * (float)(size-1);
	
	return(paletaCompleta[pos]);

}

//--------------------------------------------------------------
ofColor	ColorUtil::getNoiseColor2(float seedValue)
{
	//float scaleX = 0.007; //1.0 / scaleX is coherence in x
	//float scaleY = 0.008; //1.0 / scaleY is coherence in y
	//float posX0 = 593.2;
	//float posY0 = 43.7;
	//float value = ofNoise( x*scaleX+posX0, y*scaleY+posY0 );
	
	int posX = ofNoise(seedValue) * width;
	int posY = ofNoise(seedValue) * height;
	
	return(paletaCompleta[(int)(posY * width + posX)]);

}


//--------------------------------------------------------------
ofColor ColorUtil::getNoiseAround( ofColor c, float radius, float seedValue )
{
	float hue, saturation, brightness;
	
	c.getHsb(hue, saturation, brightness);

	float noise = (ofNoise(seedValue) * (radius * 2)) - radius;
	hue = hue + noise;
	if (hue < 0) 
		hue = 255.0f + hue;
	if (hue > 255.0) 
		hue = hue - 255.0f;
	
	c.setHsb(hue, saturation, brightness);

	return (c);
}

//--------------------------------------------------------------
ofColor ColorUtil::getNoiseAroundMin( ofColor c, float radius )
{

	float hue, saturation, brightness;
	
	c.getHsb(hue, saturation, brightness);

	hue = hue - radius;
	if (hue < 0) 
		hue = 255.0f + hue;
	if (hue > 255.0) 
		hue = hue - 255.0f;
	
	c.setHsb(hue, saturation, brightness);

	return (c);

}

//--------------------------------------------------------------
ofColor ColorUtil::getNoiseAroundMax( ofColor c, float radius )
{

	float hue, saturation, brightness;
	
	c.getHsb(hue, saturation, brightness);

	hue = hue + radius;
	if (hue < 0) 
		hue = 255.0f + hue;
	if (hue > 255.0) 
		hue = hue - 255.0f;
	
	c.setHsb(hue, saturation, brightness);

	return (c);

}


float ColorUtil::getDampedValue ( float oldValue, float newValue, float alpha ) 
{
	return (alpha * newValue) + (1.0 - alpha) * oldValue;
}

ofPoint ColorUtil::getDampedValue ( ofPoint oldValue, ofPoint newValue, float alpha )
{
	return (alpha * newValue) + (1.0 - alpha) * oldValue;
}
