#pragma once
#include "Component.h"
#include "SDL.h"
#include "TextureManager.h"

class Player : public Component
{
protected:
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

	SDL_Texture* heartsTexture;
	SDL_Rect heartsRect{};

	SDL_Keycode pressedKey;
	int next;
	bool climbAnim;
	bool isPlatform;
	SDL_Point velocity;
	bool isMoving;
	bool isLadder;
	bool damaged;
	unsigned int lifes;
	bool isGoingRight;
	bool KeyGreen;
	bool KeyRed;
	bool reindeer_saved;
	int extralife;

public:
	Player() = default;
	Player(const char* path, const char* pathForHeads, SDL_Renderer* renderer);
	~Player();
	void setTex(const char* path);
	void setHeartsTex(const char* path);


	void init(void) override;

	void draw(void) override;
	void setdestx(int x);
	void setdesty(int y);
	
	void setNext(void);
	int getNext(void);


	SDL_Texture* getTexture(void)
	{
		return texture;
	}

	SDL_Rect getSrcRect(void)
	{
		return srcRect;
	}

	SDL_Rect getDestRect(void)
	{
		return destRect;
	}

	void setPressedKey(SDL_Keycode pressedKey)
	{
		this->pressedKey = pressedKey;
	}

	void setIsMoving(bool i)
	{
		this->isMoving = i;
	}

	bool IsMoving(void)
	{
		return this->isMoving;
	}

	SDL_Keycode getPressedKey(void)
	{
		return this->pressedKey;
	}

	void setVelocityX(int x);
	void setVelocityY(int y);

	void processPos();

	void Gravity(void);

	SDL_Point getVelocity(void);


	void CheckPlatform(void);


	bool getIsOnPlatform(void)
	{
		return this->isPlatform;
	}


	SDL_Point mapPos(void);

	void setIsOnPlatform(bool s);
	void setIsOnLadder(bool s);
	bool getIsOnLadder(void);

	bool getClimbAnimation(void);
	void setClimbAnimation(void);

	void reset(void);
	

	void checkEnemyCollision(SDL_Point enemyPos[],int nr);

	bool getDamaged(void)
	{
		return this->damaged;
	}

	void setDamaged(bool s)
	{
		this->damaged = s;
	}

	unsigned int getLifes(void)
	{
		return this->lifes;
	}

	void setLifes(unsigned int s)
	{
		this->lifes = s;
	}

	bool checkColision(void);

	void setIsGoingRight(bool s)
	{
		this->isGoingRight = s;
	}

	bool getIsGoingRight(void)
	{
		return isGoingRight;
	}

	SDL_Point mapCentre(void);

	int pickItems(void);
	void Unlockgreen(void);
	void Unlockred(void);
	bool rescued(void);
	void setrescued(bool i);
	bool getIsMoving(void);
};
