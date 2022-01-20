#pragma once
#include <SDL_image.h>
#include<fstream>
#include<iostream>

using namespace std;


class Map
{
private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* brick;
	SDL_Texture* block;
	SDL_Texture* water;
	SDL_Texture* ladder;
	SDL_Texture* spike;
	SDL_Texture* doorGreen;
	SDL_Texture* doorRed;
	SDL_Texture* KeyGreen;
	SDL_Texture* KeyRed;
	SDL_Texture* cookie;
	SDL_Texture* milk;
	SDL_Texture* reindeer;
	SDL_Texture* life;

	int map[35][61] = { 0 };
	int level;

public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap();
	void DrawMap(void);
	int getTile(int i, int j);
	void setTile(int i, int j, int val);
	int getLevel(void);
	void setLevel(int s);


};

