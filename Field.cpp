#include <hge.h>								
#include <hgesprite.h>	

#include "Field.h"
#include "Figure_.h"

Field::Field(){
	hge = hgeCreate(HGE_VERSION);
	for(int i=1;i<15;i++){
		for(int j=0;j<21;j++){
			data[i][j]=0;
		}
	}
	for(int i=0;i<15;i++){
		data[i][20]=1;
	}
	for(int i=0;i<21;i++){
		data[0][i]=1;
		data[15][i]=1;
	}
}

void Field::Sdvig(int y){
	for(int i=14;i>=1;i--){
		for(int j=21;j>=0;j--){
			data[i][j]=data[i][j-1];
			data[7][y]=0;
		}
	}
}

bool Field::ProverkaNaSdvig(){
	int count=0;
	int sdvig=0;
	for(int j=1;j<20;j++){
		bool fool = true;
		for(int i = 0; i < 15; i++){
			if (data[i][j] != 1){
				fool = false;
				break;
			}
		}
		if (fool){
			Sdvig(j);
			return true;
		}
	}
	return false;
}

void Field::FigMove(Figure &x,float dt){

	int fx=x.getX()/30 + 1;
	int fy=x.getY()/30;
	switch(x.getFigureType()){
	case 1:
		for (int i = 0; i < 4; i++){
			data[fx][fy+i] = 0;
		}
		if(data[fx][fy+4]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	case 2:
		data[fx][fy]=0;
		data[fx+1][fy]=0;
		data[fx][fy+1]=0;
		data[fx+1][fy+1]=0;
		if(data[fx][fy+2]==true||data[fx+1][fy+2]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	case 3:
		data[fx+1][fy]=0;
		data[fx+1][fy+1]=0;
		data[fx][fy+1]=0;
		data[fx][fy+2]=0;
		if(data[fx][fy+3]==true||data[fx+1][fy+2]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	case 4:
		data[fx][fy]=0;
		data[fx][fy+1]=0;
		data[fx+1][fy+1]=0;
		data[fx+1][fy+2]=0;
		if(data[fx][fy+2]==true||data[fx+1][fy+3]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	case 5:
		data[fx][fy+1]=0;
		data[fx+1][fy]=0;
		data[fx+1][fy+1]=0;
		data[fx+2][fy+1]=0;
		if(data[fx][fy+2]==true||data[fx+1][fy+2]==true||data[fx+2][fy+2]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	case 6:
		data[fx][fy]=0;
		data[fx][fy+1]=0;
		data[fx][fy+2]=0;
		data[fx+1][fy+2]=0;
		if(data[fx][fy+3]==true||data[fx+1][fy+3]==true){
			x.setStop(1);
			break;
		}
		else x.Move(dt);
		Control(x);
		break;
	}
	fx=x.getX()/30 + 1;
	fy=x.getY()/30;	
	switch(x.getFigureType()){
	case 1:
		for (int i = 0; i < 4; i++){
			data[fx][fy+i] = 1;
		}
		break;
	case 2:
		data[fx][fy]=1;
		data[fx+1][fy]=1;
		data[fx][fy+1]=1;
		data[fx+1][fy+1]=1;
		break;
	case 3:
		data[fx+1][fy]=1;
		data[fx+1][fy+1]=1;
		data[fx][fy+1]=1;
		data[fx][fy+2]=1;
		break;
	case 4:
		data[fx][fy]=1;
		data[fx][fy+1]=1;
		data[fx+1][fy+1]=1;
		data[fx+1][fy+2]=1;
		break;
	case 5:
		data[fx][fy+1]=1;
		data[fx+1][fy]=1;
		data[fx+1][fy+1]=1;
		data[fx+2][fy+1]=1;
		break;
	case 6:
		data[fx][fy]=1;
		data[fx][fy+1]=1;
		data[fx][fy+2]=1;
		data[fx+1][fy+2]=1;
		break;
	}
}

void Field::Control(Figure& x){
	if (hge->Input_GetKeyState (HGEK_LEFT) && hge->Input_GetKey()) {
		int fx=x.getX()/30 + 1;
		int fy=x.getY()/30;
		for (int i = 0; i < 4; i++){
			data[fx][fy+i] = 0;
		}
		if(data[fx-1][fy]==true){
			x.setX(x.getX());
		}
		else x.setX(x.getX()-30);	
	}
	if (hge->Input_GetKeyState(HGEK_RIGHT) && hge->Input_GetKey()){
		int fx=x.getX()/30 + 1;
		int fy=x.getY()/30;
		switch(x.getFigureType()){
		case 1:
			for (int i = 0; i < 4; i++){
				data[fx][fy+i] = 0;
			}
			if(data[fx+1][fy]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		case 2:
			data[fx][fy]=0;
			data[fx+1][fy]=0;
			data[fx][fy+1]=0;
			data[fx+1][fy+1]=0;
			if(data[fx+2][fy]==true||data[fx+2][fy+1]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		case 3:
			data[fx+1][fy]=0;
			data[fx+1][fy+1]=0;
			data[fx][fy+1]=0;
			data[fx][fy+2]=0;
			if(data[fx+2][fy]==true||data[fx+2][fy+1]==true||data[fx+1][fy+2]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		case 4:
			data[fx][fy]=0;
			data[fx][fy+1]=0;
			data[fx+1][fy+1]=0;
			data[fx+1][fy+2]=0;
			if(data[fx+1][fy]==true||data[fx+2][fy+1]||data[fx+2][fx+2]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		case 5:
			data[fx][fy+1]=0;
			data[fx+1][fy]=0;
			data[fx+1][fy+1]=0;
			data[fx+2][fy+1]=0;
			if(data[fx+2][fy]==true||data[fx+3][fy+1]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		case 6:
			data[fx][fy]=0;
			data[fx][fy+1]=0;
			data[fx][fy+2]=0;
			data[fx+1][fy+2]=0;
			if(data[fx+1][fy]==true||data[fx+1][fy+1]==true||data[fx+2][fy+2]==true){
				x.setX(x.getX());
			}
			else x.setX(x.getX()+30);
			break;
		}
	}
	if (hge->Input_GetKeyState(HGEK_DOWN) && hge->Input_GetKey()){
		int fx=x.getX()/30 + 1;
		int fy=x.getY()/30;
		switch(x.getFigureType()){
		case 1:
			for (int i = 0; i < 4; i++){
				data[fx][fy+i] = 0;
			}
			if(data[fx][fy+4]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		case 2:
			data[fx][fy]=0;
			data[fx+1][fy]=0;
			data[fx][fy+1]=0;
			data[fx+1][fy+1]=0;
			if(data[fx][fy+2]==true||data[fx+1][fy+2]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		case 3:
			data[fx+1][fy]=0;
			data[fx+1][fy+1]=0;
			data[fx][fy+1]=0;
			data[fx][fy+2]=0;
			if(data[fx][fy+3]==true||data[fx+1][fy+2]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		case 4:
			data[fx][fy]=0;
			data[fx][fy+1]=0;
			data[fx+1][fy+1]=0;
			data[fx+1][fy+2]=0;
			if(data[fx][fy+2]==true||data[fx+1][fy+3]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		case 5:
			data[fx][fy+1]=0;
			data[fx+1][fy]=0;
			data[fx+1][fy+1]=0;
			data[fx+2][fy+1]=0;
			if(data[fx][fy+2]==true||data[fx+1][fy+2]==true||data[fx+2][fy+2]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		case 6:
			data[fx][fy]=0;
			data[fx][fy+1]=0;
			data[fx][fy+2]=0;
			data[fx+1][fy+2]=0;
			if(data[fx][fy+3]==true||data[fx+1][fy+3]==true){
				x.setStop(1);
				break;
			}
			else 		x.setY(x.getY()+30);
			break;
		}
	}
}
