#include "Map.h"
#include "TextureManager.h"
#include<iostream>
#include <SDL.h>
#include<fstream>

using namespace std;


Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	brick = TextureManager::LoadTexture("assets/brick.png", renderer);
	block = TextureManager::LoadTexture("assets/block.png", renderer);
	ladder = TextureManager::LoadTexture("assets/ladder_mid.png", renderer);
	spike = TextureManager::LoadTexture("assets/spikes.png", renderer);
	doorGreen = TextureManager::LoadTexture("assets/doorGreen.png",renderer);
	doorRed = TextureManager::LoadTexture("assets/doorRed.png", renderer);
	KeyGreen = TextureManager::LoadTexture("assets/keygreen.png",renderer);
	KeyRed = TextureManager::LoadTexture("assets/keyred.png", renderer);
	cookie= TextureManager::LoadTexture("assets/cookie.png", renderer);
	milk = TextureManager::LoadTexture("assets/Milk.png", renderer);
	reindeer = TextureManager::LoadTexture("assets/moose.png", renderer);
	life = TextureManager::LoadTexture("assets/heart.png", renderer);

	src.x = 0;
	src.y = 0;

	dest.x = 0;
	dest.y = 0;

	dest.w = 32;
	dest.h = 32;

	level = 1;

}

Map::~Map()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(brick);
	SDL_DestroyTexture(block);
	SDL_DestroyTexture(ladder);
	SDL_DestroyTexture(spike);
	SDL_DestroyTexture(doorRed);
	SDL_DestroyTexture(doorGreen);
	SDL_DestroyTexture(KeyRed);
	SDL_DestroyTexture(KeyGreen);
	SDL_DestroyTexture(cookie);
	SDL_DestroyTexture(milk);
	SDL_DestroyTexture(reindeer);
	SDL_DestroyTexture(life);
}

void Map::LoadMap(void)
{
	ifstream f;
	char path[] = "levelx.txt";
	path[5] = this->level + '0';
	f.open(path);

	for (int row = 0; row < 34; row++)
	{
		for (int column = 0; column < 61; column++)
		{
			f>>map[row][column];
			
		}
	}

	f.close();
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 34; row++)
	{
		for (int column = 0; column < 61; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			case 1:
			{
				TextureManager::Draw(block, src, dest, renderer);
				break;
			}
			case 2:
			{
				TextureManager::Draw(brick, src, dest, renderer);
				break;
			}
			case 3:
			{
				TextureManager::Draw(doorGreen, src, dest, renderer);
				break;
			}
			case 4:
			{
				TextureManager::Draw(KeyGreen,src,dest,renderer);
				break;
			}
			case 5:
			{
				TextureManager::Draw(ladder, src, dest, renderer);
				break;
			}
			case 6:
			{
				TextureManager::Draw(milk, src, dest, renderer);
				break;
			}
			case 7:
			{
				TextureManager::Draw(reindeer, src, dest, renderer);
				break;
			}
			case 8:
			{
				TextureManager::Draw(KeyRed, src, dest, renderer);
				break;
			}
			case 9:
			{
				TextureManager::Draw(doorRed, src, dest, renderer);
				break;
			}
			
			case 10:
			{
				TextureManager::Draw(spike, src, dest, renderer);
				break;
			}
			case 11:
			{
				TextureManager::Draw(life, src, dest, renderer);
				break;
			}

			case 20:
			{
				TextureManager::Draw(cookie, src, dest, renderer);
				break;
			}

			default:
				break;
			}
		}
	}
}



int Map::getTile(int i, int j)
{
	return map[i][j];
}


void Map::setTile(int i, int j, int val)
{
	this->map[i][j] = val;
}

int Map:: getLevel(void)
{
	return level;
}

void Map::setLevel(int s)
{
	this->level = s;
}