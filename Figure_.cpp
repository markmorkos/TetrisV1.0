#include <hge.h>								
#include <hgesprite.h>							
												
#include "Figure_.h"

Figure::Figure(){
	hge = hgeCreate(HGE_VERSION);
	x=180;
	y=0;
	stop=0;
}

void Figure::Move(float dt){
	if(dt>=1)setY(getY()+30);
}

void Figure::Stop(int y){
	setY(y);
}

