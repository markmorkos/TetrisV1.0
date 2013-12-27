#ifndef FIELD_H
#define FIELD_H

#include <hge.h>
#include <hgesprite.h>
#include "Figure_.h"

class Field{
	bool data[16][22];
public:
	Field();
	~Field(){};
	void Sdvig(int y);
	bool ProverkaNaSdvig();
	void Control(Figure& x);
	void FigMove(Figure &x, float dt);
	HGE* hge;
};

#endif
