#include "Player.h"
#include "map.h"
#include "TextureManager.h"
#include<iostream>
#include <math.h>
#include <fstream>
#include "Game.h"
#include"SoundGame.h"
#include"Scoreboard.h"

using namespace std;

extern Map* map;

SoundGame s;


int a;

Player::Player(const char* path, const char* pathForHearts, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
	setHeartsTex(pathForHearts);
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(heartsTexture);
}
void Player::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Player::setHeartsTex(const char* path)
{
	heartsTexture = TextureManager::LoadTexture(path, renderer);
}


void Player::init()
{
	
	s.addSound("assets/Audio/Chewing-food.mp3");
	s.addSound("assets/Audio/mixkit-wallowing-drink-quickly-161.wav");
	s.addSound("assets/Audio/extralife.mp3");
	s.addSound("assets/Audio/getkey.mp3");
	s.addSound("assets/Audio/unlocked.mp3");

	extralife = 0;
	a = 2000;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 0;
	srcRect.w = 0;

	destRect.x = 50;
	destRect.y = 898;

	destRect.w = 80;//100;
	destRect.h = 90;//90;

	velocity.x = 0;
	velocity.y = 0;



	isMoving = false;
	lifes = 3;
	isGoingRight = false;
	pressedKey = 0;
	next = 1;
	climbAnim = false;
	isPlatform = true;
	isLadder = false;
	damaged = false;
	KeyGreen=false;
	KeyRed = false;
	reindeer_saved = false;
	extralife = 0;
	heartsRect.x = 1350;
	heartsRect.y = 20;
	heartsRect.w = 64;
	heartsRect.h = 64;
}
void Player::setdestx(int x)
{
	this->destRect.x = x;
}
void Player::setdesty(int y)
{
	this->destRect.y = y;
}

void Player::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
	int a = 0;
	int aux = heartsRect.x;
	for (int i = 0; i < lifes; ++i)
	{
		heartsRect.x = aux + a;
		TextureManager::Draw(heartsTexture, srcRect, heartsRect, renderer);
		a = a + 80;

	}
	
	heartsRect.x = 1350;
	
	
}

int Player::getNext(void)
{
	return this->next;
}

void Player::setNext(void)
{
	if (next == 8)
	{
		next = 1;
	}
	else
	{
		next++;
	}
}

void Player::setVelocityX(int x)
{
	this->velocity.x = x;
}
void Player::setVelocityY(int y)
{
	this->velocity.y = y;
}

void Player::processPos(void)
{
	this->destRect.x = this->destRect.x + this->velocity.x;

	if (this->destRect.x < -40 || this->checkColision() == true)
	{
		this->destRect.x = this->destRect.x - this->velocity.x;
	}

	this->destRect.y = this->destRect.y + this->velocity.y;

	SDL_Point aux = this->mapPos();

	if ((this->destRect.y > 1080 || this->destRect.y < 0 || this->checkColision() == true))
	{
		this->destRect.y = this->destRect.y - this->velocity.y;
	}
	else
	{
		if ((map->getTile(aux.y + 3, aux.x) == 1 && this->isLadder == false)|| (map->getTile(aux.y + 3, aux.x) == 5 && map->getTile(aux.y + 2, aux.x) != 5))
		{
			this->destRect.y = (aux.y * 32)+5;
		}
	}

}

void Player::Gravity(void)
{
	this->CheckPlatform();
	if (this->isLadder==false && this->isPlatform == false )
	{
		if(this->velocity.y<35)
			this->velocity.y +=5;
	}
	else
	{
		if(this->isLadder==false)
			this->velocity.y = 0;
	}
}

void Player::reset(void)
{
	{
		if (map->getLevel() == 1)
		{
			destRect.x = 50;
			destRect.y = 892;// 864;
		}
		if (map->getLevel() == 2)
		{
			destRect.x = 1800;
			destRect.y = 622;//594;
		}
		else if(map->getLevel()==3) {
			destRect.x = 1200;
			destRect.y = 892;//864;

		}
		lifes = 3;
		extralife = 0;
		a = 2000;
	}
}

SDL_Point Player::getVelocity(void)
{
	return this->velocity;
}


SDL_Point Player::mapPos(void)
{
	SDL_Point ret;

	if (this->isGoingRight == false)
	{
		ret.x = (int)(this->getDestRect().x + 25) / 32;
	}
	else
	{
		ret.x = (int)(this->getDestRect().x + 60) / 32;
	}

	ret.y = (int)(this->getDestRect().y + 20) / 32;

	//cout << "Map pos: " << ret.x << " " << ret.y << endl;
	return ret;
}

SDL_Point Player::mapCentre(void)
{
	SDL_Point ret;
	ret.x = (int)(this->getDestRect().x + 40) / 32;
	ret.y = (int)(this->getDestRect().y + 45) / 32;
	//cout << "Map centre: " << ret.x << " " << ret.y << endl;
	return ret;

}


void Player::CheckPlatform(void)
{
	SDL_Point aux = this->mapPos();

	if (map->getTile(aux.y + 3, aux.x) == 1)
	{
		this->isPlatform = true;
		return;
	}

	if (map->getTile(aux.y + 3, aux.x) == 5)
	{
		this->isPlatform = true;
		return;
	}

	if (map->getTile(aux.y + 3, aux.x-1) == 1 && this->isGoingRight == true)
	{
		this->isPlatform = true;
		return;
	}

	if (map->getTile(aux.y + 3, aux.x+1) == 1 && this->isGoingRight == false)
	{
		this->isPlatform = true;
		return;
	}

	if (map->getTile(aux.y + 3, aux.x) == 2)
	{
		this->isPlatform = true;
		return;
	}
	

	this->isPlatform = false;

}



void Player::setIsOnPlatform(bool ok)
{
	this->isPlatform = ok;
}

void Player::setIsOnLadder(bool ok)
{
	this->isLadder = ok;
}
bool Player::getIsOnLadder(void)
{
	return this->isLadder;
}

bool Player::getClimbAnimation(void)
{
	return this->climbAnim;
}

void Player::setClimbAnimation(void)
{
	this->climbAnim = not this->climbAnim;
}

void Player::checkEnemyCollision(SDL_Point enemyPos[],int nr)
{
	if (this->damaged == false)
	{
		SDL_Point aux = this->mapCentre();
		for(int i=0;i<nr;++i)
		{
			if( (aux.x == enemyPos[i].x && aux.y + 1 == enemyPos[i].y) || (aux.x==enemyPos[i].x && aux.y+1==enemyPos[i].y-1) || (aux.x == enemyPos[i].x && aux.y == enemyPos[i].y - 1))
			{
				if (lifes > 1)
				{
					if (this->pressedKey == SDLK_LEFT)
					{
						this->destRect.x += 80;
					}
					else
					{
						this->destRect.x += -80;
					}
				}

				if (lifes != 0)
				{
					lifes--;
				}
				else
				{
					lifes = 0;
				}

				this->damaged = true;
			}
		}

		if (map->getTile(aux.y + 1, aux.x) == 10)
		{
			if (lifes > 1)
			{
				if (this->pressedKey == SDLK_LEFT)
				{
					if(map->getTile(aux.y+1,aux.x+1)==0|| map->getTile(aux.y , aux.x + 1) == 0)
					this->destRect.x += 80;
				}
				else
				{
					if(map->getTile(aux.y + 1, aux.x - 1) == 0 || map->getTile(aux.y, aux.x + 1) == 0)
					this->destRect.x += -80;
				}
			}

			if (lifes != 0)
			{
				lifes--;
			}
			else
			{
				lifes = 0;
			}

			this->damaged = true;
		}
	}
}

bool Player::checkColision(void)
{
	SDL_Point aux = mapPos();

	if (map->getTile(aux.y+1, aux.x) == 1)
	{
		return true;
	}

	if (map->getTile(aux.y + 2, aux.x) == 1)
	{
		return true;
	}
	return false;
}

int Player::pickItems(void)
{
	SDL_Point aux = mapCentre();
	//s.addSound("assets/Audio/mixkit-player-jumping-in-a-video-game-2043.wav");
	

	if (map->getTile(aux.y + 1, aux.x) == 6)
	{
		s.playSound(1);
		map->setTile(aux.y + 1, aux.x, 0);
		extralife += 200;
		return 200;
	}
	else if (map->getTile(aux.y, aux.x) == 6)
	{
		s.playSound(1);
		map->setTile(aux.y , aux.x, 0);
		extralife += 200;
		return 200;
	}
	else if (map->getTile(aux.y-1, aux.x) == 6)
	{
		s.playSound(1);
		map->setTile(aux.y-1, aux.x, 0);
		extralife += 200;
		return 200;
	}

	if (map->getTile(aux.y + 1, aux.x) == 20)
	{
		map->setTile(aux.y + 1, aux.x, 0);
		s.playSound(0);
		extralife += 100;
		return 100;
	}
	else if (map->getTile(aux.y, aux.x) == 20)
	{
		s.playSound(0);
		map->setTile(aux.y, aux.x, 0);
		extralife += 100;
		return 100;
	}
	else if (map->getTile(aux.y - 1, aux.x) == 20)
	{
		s.playSound(0);
		map->setTile(aux.y - 1, aux.x, 0);
		extralife += 100;
		return 100;
	}


	if (map->getTile(aux.y + 1, aux.x) == 4 )
	{
		map->setTile(aux.y + 1, aux.x, 0);
		this->KeyGreen = true;
		s.playSound(3);
		extralife += 500;
		return 500;
	}
	else if (map->getTile(aux.y, aux.x) == 4)
	{
		s.playSound(3);
		this->KeyGreen = true;
		map->setTile(aux.y, aux.x, 0);
		extralife += 500;
		return 500;
	}
	else if (map->getTile(aux.y - 1, aux.x) == 4)
	{
		this->KeyGreen = true;
		s.playSound(3);
		map->setTile(aux.y - 1, aux.x, 0);
		extralife += 500;
		return 500;
	}

	if (map->getTile(aux.y + 1, aux.x) == 8)
	{
		map->setTile(aux.y + 1, aux.x, 0);
		this->KeyRed = true;
		s.playSound(3);
		extralife += 500;
		return 500;
	}
	else if (map->getTile(aux.y, aux.x) == 8)
	{
		s.playSound(3);
		this->KeyRed = true;
		map->setTile(aux.y, aux.x, 0);
		extralife += 500;
		return 500;
	}
	else if (map->getTile(aux.y - 1, aux.x) == 8)
	{
		this->KeyRed = true;
		s.playSound(3);
		map->setTile(aux.y - 1, aux.x, 0);
		extralife += 500;
		return 500;
	}


	if (map->getTile(aux.y + 1, aux.x) == 7)
	{
		map->setTile(aux.y + 1, aux.x, 0);
		this->reindeer_saved = true;
		extralife += 1000;
		return 1000;
	}
	else {
		if (map->getTile(aux.y, aux.x) == 7) {
			map->setTile(aux.y , aux.x, 0);
			this->reindeer_saved = true;
			extralife += 1000;
			return 1000;
		}
		else if (map->getTile(aux.y - 1, aux.x) == 7)
		{
			map->setTile(aux.y-1, aux.x, 0);
			this->reindeer_saved = true;
			extralife += 1000;
			return 1000;
		}
	}


	if (map->getTile(aux.y + 1, aux.x ) == 11)
	{
		map->setTile(aux.y + 1, aux.x, 0);
		lifes = lifes + 1;
		s.playSound(2);
		extralife += 500;
		return 500;
	}
	


	if (extralife >= a )
	{
		lifes = lifes + 1;
		s.playSound(2);
		a += 2000;
	}
	
	
	return 0;
}

void Player::Unlockgreen(void)
{
	SDL_Point aux = mapCentre();
	//28,3
	
	if (map->getTile(aux.y, aux.x-1) == 3 && this->KeyGreen==true)
	{
		map->setTile(aux.y, aux.x-1, 0);
		map->setTile(aux.y + 1, aux.x-1, 0);
		map->setTile(aux.y - 1, aux.x-1, 0);
		s.playSound(4);
		
	}
	if (map->getTile(aux.y, aux.x + 1) == 3 && this->KeyGreen == true)
	{
		map->setTile(aux.y, aux.x + 1, 0);
		map->setTile(aux.y + 1, aux.x + 1, 0);
		map->setTile(aux.y - 1, aux.x + 1, 0);
		s.playSound(4);
	}

}
void Player::Unlockred(void)
{
	SDL_Point aux = mapCentre();
	//  40 13
	if (map->getTile(aux.y, aux.x - 1) == 9 && this->KeyRed == true)
	{
		map->setTile(aux.y, aux.x - 1, 0);
		map->setTile(aux.y + 1, aux.x - 1, 0);
		map->setTile(aux.y - 1, aux.x - 1, 0);
		s.playSound(4);

	}

	if (map->getTile(aux.y, aux.x + 1) == 9 && this->KeyRed == true)
	{
		map->setTile(aux.y, aux.x + 1, 0);
		map->setTile(aux.y + 1, aux.x + 1, 0);
		map->setTile(aux.y - 1, aux.x + 1, 0);
		s.playSound(4);
	}

}
bool Player::rescued(void)
{
	return this->reindeer_saved;
}
void Player::setrescued(bool i)
{
	this->reindeer_saved = i;
}
bool Player::getIsMoving(void)
{
	return this->isMoving;
}
