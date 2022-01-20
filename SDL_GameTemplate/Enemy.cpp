#include"Enemy.h"
#include"Map.h"
#include"Game.h"

extern Map* map;

Enemy::Enemy(const char* path, SDL_Renderer* renderer,int posX, int posY)
{
	this->renderer = renderer;
	setTex(path);
	destRect.x = posX;
	destRect.y = posY;
}

void Enemy::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Enemy::draw(void)
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}

void Enemy::init(void)
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 0;
	srcRect.w = 0;

	//destRect.w = 50;
	//destRect.h = 70;
	destRect.w = 60;
	destRect.h = 73;
	this->next = false;
	
	velocity.x = 1;
	velocity.y = 0;
	
}

SDL_Point Enemy::mapCentre(void)
{
	SDL_Point ret;



	if (this->isGoingRight == false)
	{
		ret.x = (int)(this->getDestRect().x ) / 32;
	}
	else
	{
		ret.x = (int)(this->getDestRect().x + 60) / 32;
	}
	ret.y = (int)(this->destRect.y + 45) / 32;

	return ret;
}

void Enemy::processPos(void)
{
	SDL_Point r = mapCentre();

	if( map->getTile(r.y,r.x) == 1 || map->getTile(r.y, r.x)  == 10 || map->getTile(r.y+1, r.x+1) ==0 || map->getTile(r.y+1, r.x-1) == 0)
	{
		this->isGoingRight = not this->isGoingRight;
	}
	if (gen == 1) {
		if (isGoingRight == 1)
		{
			char path[] = "assets/mx.png";
			path[8] = this->next + '0';
			this->next = not this->next;
			this->setTex(path);
			this->destRect.x += this->velocity.x;
		}
		else
		{
			char path[] = "assets/mxb.png";
			path[8] = this->next + '0';
			this->next = not this->next;
			this->setTex(path);
			this->destRect.x += -this->velocity.x;
		}
	}
	else {
		if (isGoingRight == 1)
		{
			char path[] = "assets/fx.png";
			path[8] = this->next + '0';
			this->next = not this->next;
			this->setTex(path);
			this->destRect.x += this->velocity.x;
		}
		else
		{
			char path[] = "assets/fxb.png";
			path[8] = this->next + '0';
			this->next = not this->next;
			this->setTex(path);
			this->destRect.x += -this->velocity.x;
		}
	}
}

void Enemy::setGen(bool g)
{
	gen = g;
}