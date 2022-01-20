#pragma once
#include"SDL.h"
#include "Component.h"
#include "text.h"
#include "SDL_ttf.h"
#include"TextureManager.h"

class Menu :public Component {
	
	SDL_Renderer *renderer;
	Text* start, * quit, *difficulty,*easy,*medium,*hard,*level1,*level2,*level3;

	int nrElem;
	int selected;
	int isDiff;

public:

	Menu(SDL_Renderer *renderer);

	void draw();
	void init();

	void operator ++(int);
	void operator --(int);

	int getSelected(void);
	void setIsDiff(int s)
	{
		this->isDiff = s;
	}

	int getIsDiff(void)
	{
		return isDiff;
	}
};