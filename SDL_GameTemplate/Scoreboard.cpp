#pragma once
#include "Scoreboard.h"
#include"Player.h"

Scoreboard::Scoreboard(SDL_Renderer *renderer) : renderer(renderer)
{
	this->score = 0;
	for (int i = 0; i < 6; ++i)
	{
		this->texture[i] = TextureManager::LoadTexture("assets/hud_0.png", renderer);
	}

	this->init();
}
Scoreboard::~Scoreboard()
{
	SDL_DestroyTexture(texture[5]);
	SDL_DestroyRenderer(renderer);
}
void Scoreboard::init(void)
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 180;
	destRect.y = 32;
	destRect.w = 30;
	destRect.h = 30;
	
}

void Scoreboard::draw(void)
{
	int a = 0;
	int aux = destRect.x;
	for (unsigned int i = 0; i < 6; ++i)
	{
		destRect.x = aux + a;
		TextureManager::Draw(texture[i], srcRect, destRect, renderer);
		a = a - 30;
	}
	destRect.x = aux;
}

void Scoreboard::convertScore(void)
{
	int r, c = score, i = 0;
	char path[] = "assets/hud_0.png";

	if (score != 0)
	{
		do
		{
			r = c % 10;
			c = c / 10;
			path[11] = r + '0';
			texture[i] = TextureManager::LoadTexture(path, renderer);
			i++;

		} while (c != 0);
	}
	else
	{
		for (int i = 0; i<6;++i)
		{
			texture[i] = TextureManager::LoadTexture("assets/hud_0.png", renderer);
		}
	}
	
	
} 
int Scoreboard::getscore(void)
{
	return score;
}
void Scoreboard::addToScore(int val)
{
	this->score += val;
}

void Scoreboard::reset(void)
{
	this->score = 0;
}