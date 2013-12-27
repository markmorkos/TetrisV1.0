#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <hgeparticle.h>
#include <hgegui.h>
#include <hgeguictrls.h>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#pragma once

using namespace std;

#include "Field.h"

HGE* hge = NULL;
int score=0;

list<Figure*> List;
vector<int> score_list;
Field field;

HTEXTURE g_tBackground=0;
hgeSprite* g_sBackground=NULL;
hgeFont *fnt;
hgeFont *fnt2;
hgeFont *fntpause;
hgeFont *fntrecords;
hgeSprite *g_spause=NULL;
HEFFECT snd;
HEFFECT back;
hgeSprite *cursor;
hgeGUI *gui;
hgeGUIButton* start=0;
hgeGUIButton* records=0;
HTEXTURE tstart=0;
HTEXTURE trecords=0;
HTEXTURE cur=0;

ofstream out("records.txt");

float time_s=0;
int flag=0;
bool checker_menu=true;
bool MenuUpgrade(float time);
void fun_pause();
bool pause=0;

void CreateFigure(){
	int a=hge->Random_Int(1,6);
	switch(a){
	case 1:
		List.push_back(new Figure1());
		break;
	case 2:
		List.push_back(new Figure2());
		break;
	case 3:
		List.push_back(new Figure3());
		break;
	case 4:
		List.push_back(new Figure4());
		break;
	case 5:
		List.push_back(new Figure5());
		break;
	case 6:
		List.push_back(new Figure6());
		break;
	}
}

vector <int> merge(vector <int> c, vector <int> b){
	vector<int> a(c.size() + b.size());
	int versh_b, versh_c;
	versh_b = 0;
	versh_c = 0;
	for (int i = 0; i < a.size(); i++){
		if (versh_c == c.size()){
			a[i] = b[versh_b];
			versh_b++;
			continue;
		}
		if (versh_b == b.size()){
			a[i] = c[versh_c];
			versh_c++;
			continue;
		}
		if (c[versh_c] <= b[versh_b]){
			a[i] = c[versh_c];
			versh_c++;
		}
		else{
			a[i] = b[versh_b];
			versh_b++;
		}
	}
	return a;
}

vector <int> merge_sort(vector <int> a){
	if (a.size() <= 1)
		return a;
	vector<int> b, c;
	b.assign(a.begin(), a.end() - (a.size() / 2));
	c.assign(a.end() - (a.size() / 2), a.end());
	return merge(merge_sort(b), merge_sort(c));
}

bool FrameFunc()
{
	snd = hge->Effect_PlayEx(back,50,0,14.0,true);
	time_s+=hge->Timer_GetDelta();
	if(checker_menu){
		gui->Update(time_s);
		if(MenuUpgrade(time_s))return true;
	}
	else{
		if(List.back()->getStop()==1) CreateFigure();
		if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
		if (hge->Input_GetKeyState(HGEK_SPACE))pause=1;
		if (hge->Input_GetKeyState(HGEK_ENTER))pause=0;
		if(!pause){
			field.FigMove(*List.back(), time_s);
			if(field.ProverkaNaSdvig()==true){
				score+=200;
				for(list<Figure*>::iterator it=List.begin();it!=List.end();++it){
					(*it)->setY((*it)->getY()+30);
					(*it)->setStop(1);
				}
			}
			if(List.back()->getStop()==1)score+=100;
			if(List.back()->getStop()==1&&(List.back()->getY()==0||List.back()->getY()==30||List.back()->getY()==60)){MessageBox(NULL,"You loose :(","You loose!", MB_OK);hge->System_Shutdown();out<<score<<' ';out.close();}
			if (time_s >= 1) time_s = 0;
		}
	}
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	g_sBackground->Render(0,0);
	if(checker_menu){
		gui->Render();
		fnt2->SetColor(ARGB(255,255,255,255));
		fnt2->printf(435,20,HGETEXT_LEFT,"Press DOWN\nto move down\n\nPress LEFT\nto move left\n\nPress RIGHT\nto move right\n\nOne figure\n= 100\n\nOne line\n= 200");
	}
	else{
		fnt->SetColor(ARGB(255,255,255,255));
		fnt->printf(455,20,HGETEXT_LEFT,"Your Score:\n%i\n\nPress Space \nto pause\n\nPress Enter\n to resume",score);
		if(pause==1){
			fntpause->SetColor(ARGB(255,255,55,55));
			fntpause->printf(200,120,HGETEXT_CENTER,"PAUSE");
		}
		else{
		for(list<Figure*>::iterator it = List.begin(); it != List.end(); ++it){
			(*it)->TextureLoad();
			(*it)->RenderFigure();
		}
		}
	}
	hge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);//music
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);//timer
	hge->System_SetState(HGE_TITLE, "Tetris");

	hge->System_SetState(HGE_SCREENWIDTH,600);
	hge->System_SetState(HGE_SCREENHEIGHT,600);
	if(hge->System_Initiate())
	{
		tstart=hge->Texture_Load("start.png");
		//trecords=hge->Texture_Load("records.png");

		cur=hge->Texture_Load("cursor.png");
		cursor=new hgeSprite(cur,0,0,32,32);
		
		start = new hgeGUIButton(1,70,150,295,295,tstart,0,0);
		//records = new hgeGUIButton(1,170,500,100,29,trecords,0,0);
		
		g_tBackground = hge->Texture_Load("fon.jpg");
		g_sBackground = new hgeSprite(g_tBackground,0,0,420,600);
		fnt=new hgeFont("font1.fnt");
		fnt2=new hgeFont("font1.fnt");
		fntpause=new hgeFont("font1.fnt");
		//fntrecords=new hgeFont("font1.fnt");
		
		gui=new hgeGUI();

		gui->AddCtrl(start);
		//gui->AddCtrl(records);

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(cursor);
		gui->SetFocus(1);
		gui->Enter();

		back=hge->Effect_Load("tetris.mp3");

		CreateFigure();
		
		hge->System_Start();
		
		hge->Texture_Free(tstart);
		hge->Texture_Free(g_tBackground);
		
		delete gui;
		delete fnt;
		delete fnt2;
		delete fntpause;
		//delete fntrecords;
		delete g_sBackground;
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	hge->System_Shutdown();
	hge->Release();

	return 0;
}

bool MenuUpgrade(float time){
	gui->Update(time);
	if(start->GetState()||hge->Input_GetKeyState(HGEK_ENTER))checker_menu=false;
	//if(records->GetState()){
	//	fntrecords->SetColor(ARGB(255,255,255,255));
	//	vector<int>::iterator it;
	//	fstream input("records.txt");
	//	copy(istream_iterator<int>(input), istream_iterator<int>(), back_inserter(score_list));
	//	input.close();
	//	score_list=merge_sort(score_list);
	//	for(it=score_list.begin();it!=score_list.end();++it){
	//		fnt->printf(200,200,HGETEXT_CENTER,"%i\n",(*it));
	//	}
	//}
	return false;
}
