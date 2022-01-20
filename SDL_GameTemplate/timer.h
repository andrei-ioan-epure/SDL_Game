#pragma once
#include"Component.h"
#include"text.h"
#include"TextureManager.h"
#include<Windows.h>
#include<iostream>


class Time:public Component
{
	SDL_Texture* texture[8];
	SDL_Renderer* renderer;
	SDL_Rect srcRect{}, destRect{};
	int m, s,ss;
public:
	Time(SDL_Renderer* renderer);
	//~Time();
	void init(void);
	void draw(void);
	bool timeconvert(void);
	void reset(int diff);
};
