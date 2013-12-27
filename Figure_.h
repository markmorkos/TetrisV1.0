#ifndef FIGURE__H
#define FIGURE__H

#include <hge.h>
#include <hgesprite.h>

class Figure{
	int x,y;
	int type;
	bool stop;
public:
	Figure();
	~Figure(){};
	virtual void RenderFigure(){};
	void Move(float dt);
	void Stop(int y);
	void setStop(bool st){stop=st;};
	void setX(int x){this->x=x;};
	void setY(int y){this->y=y;};
	bool getStop(){return stop;}
	int getX(){return x;};
	int getY(){return y;};
	virtual int getFigureType(){return type;};
	virtual void TextureLoad(){};
	HGE* hge;
};

class Figure1:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure1():Figure(){
		hge = hgeCreate(HGE_VERSION);
		type=1;
	};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("1.png");
		g_sFig=new hgeSprite(g_tFig,0,0,30,120);
	}
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

class Figure2:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure2():Figure(){hge = hgeCreate(HGE_VERSION);type=2;};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("2.png");
		g_sFig=new hgeSprite(g_tFig,0,0,60,60);
	};
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

class Figure3:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure3():Figure(){hge = hgeCreate(HGE_VERSION);type=3;};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("3.png");
		g_sFig=new hgeSprite(g_tFig,0,0,60,90);
	};
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

class Figure4:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure4():Figure(){hge = hgeCreate(HGE_VERSION);type=4;};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("4.png");
		g_sFig=new hgeSprite(g_tFig,0,0,60,90);
	};
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

class Figure5:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure5():Figure(){hge = hgeCreate(HGE_VERSION);type=5;};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("5.png");
		g_sFig=new hgeSprite(g_tFig,0,0,90,60);
	};
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

class Figure6:public Figure{
	HTEXTURE g_tFig;
	hgeSprite* g_sFig;
	int type;
public:
	Figure6():Figure(){hge = hgeCreate(HGE_VERSION);type=6;};
	virtual void TextureLoad(){
		g_tFig=hge->Texture_Load("6.png");
		g_sFig=new hgeSprite(g_tFig,0,0,60,90);
	};
	virtual void RenderFigure(){
		this->g_sFig->Render(getX(),getY());
	};
	void setFigureType(int type){this->type=type;};
	virtual int getFigureType(){return type;};
};

#endif
