#include "Game.h"
#include"background.h"
#include <iostream>
#include <fstream>
#include"text.h"
#include "Map.h"
#include "Player.h"
#include"Enemy.h"
#include"Menu.h"
#include"Scoreboard.h"
#include"timer.h"
#include"SoundGame.h"



using namespace std;


extern Map* map=nullptr;

Background* back;

Player* player;

Enemy* enemy[5];

Text* gameOver;
Text* gameWin;
Text* endtime;
Menu* menu;

Scoreboard* scoreboard;
Time* timelimit;
SoundGame  se;


Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
	this->difficulty = 3;
}

Game::~Game()
{
	delete player;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr)
		{
			std::cout << "Window created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << endl;
		}
		isRunning = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		isRunning = false;
	}
	menu = new Menu(renderer);

	map = new Map(renderer);
	map->LoadMap();

	back = new Background("assets/Santa.png", renderer);
	back->init();
	player = new Player("assets/idle.png", "assets/heart.png", renderer);
	player->init();
	gameOver = new Text("assets/font.ttf", "Game over! Press r to reload.", renderer, 200, 400, 200, 1500, false, {0,200,0,0 });
	gameOver->init();
	gameWin = new Text("assets/font.ttf", "You win!Press ESC to leave.", renderer, 200, 400, 200, 1500, false, { 0,200,0,0 });
	gameWin->init();
	endtime = new Text("assets/font.ttf", "Time's over! Press r to reload.", renderer, 200, 400, 200, 1500, false, { 0,200,0,0 });
	endtime->init();
	scoreboard = new Scoreboard(renderer);
	timelimit = new Time(renderer);

	
	se.addSound("assets/Audio/mixkit-game-level-completed-2059.wav");
	se.addSound("assets/Audio/mixkit-player-losing-or-failing-2042.wav");
	se.addSound("assets/Audio/mixkit-boxer-getting-hit-2055.wav");
	se.addSound("assets/Audio/mixkit-player-jumping-in-a-video-game-2043.wav");
	se.addSound("assets/Audio/MenuMusic.mp3");
	se.addSound("assets/Audio/GameMusic.mp3");

	ifstream f;
	int x, y;
	char path[] = "levelxenemypos.txt";
	path[5] = map->getLevel() + '0';
	f.open(path);
	for (int i = 0; i < 5; ++i)
	{
		f >> x;
		f >> y;
		if (i != 1 && i != 3)
		{
			enemy[i] = new Enemy("assets/kid.png", renderer, x, y);
			enemy[i]->init();
			enemy[i]->setGen(true);
		}
		else
		{
			enemy[i] = new Enemy("assets/girl.png", renderer, x, y);
			enemy[i]->init();
			enemy[i]->setGen(false);
		}
	}
	f.close();
	isMenu = true;
	se.playSound(4);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	SDL_Point aux = player->mapCentre();

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			if (player->getLifes()!=0)
			{
				player->setVelocityX(8);
				player->setPressedKey(SDLK_RIGHT);
				player->setIsMoving(true);
				
				if (map->getTile(aux.y, aux.x) == 5 || map->getTile(aux.y+1, aux.x) == 5 || map->getTile(aux.y+2, aux.x) == 5)
				{
					player->setIsOnLadder(true);
				}
				else
				{
					player->setIsOnLadder(false);
				}
			}
			player->setIsGoingRight(true);
			break;

		case SDLK_LEFT:
			if (player->getLifes() != 0)
			{
				player->setVelocityX(-8);
				player->setPressedKey(SDLK_LEFT);
				player->setIsMoving(true);

				if (map->getTile(aux.y, aux.x) == 5 || map->getTile(aux.y + 1, aux.x) == 5 || map->getTile(aux.y + 2, aux.x) == 5)
				{
					player->setIsOnLadder(true);
				}
				else
				{
					player->setIsOnLadder(false);
				}
			}
			player->setIsGoingRight(false);
			break;

		case SDLK_UP:
			if (player->getLifes() != 0)
			{
				if (player->getIsOnPlatform() == true || player->getIsOnLadder() == true)
				{
					if (map->getTile(aux.y+1, aux.x) == 5 )
					{
						player->setVelocityY(-8);
						player->setIsOnLadder(true);
						player->setIsOnPlatform(false);

					}
					else
					{

						player->setVelocityY(-30);
						se.playSound(3);
						player->setIsOnPlatform(false);
						player->setIsOnLadder(false);
					}
					player->setPressedKey(SDLK_UP);
					player->setIsMoving(true);
				}
			}
			break;

		case SDLK_DOWN:
			if (player->getLifes() != 0)
			{
				if (map->getTile(aux.y, aux.x) == 5 || map->getTile(aux.y+1, aux.x) == 5 || map->getTile(aux.y+2, aux.x) == 5)
				{
					player->setVelocityY(8);
					player->setIsMoving(true);
					player->setIsOnLadder(true);
				}
				player->setPressedKey(SDLK_DOWN);
			}
			break;

		case SDLK_ESCAPE:
			this->isMenu = true;
			back->setTex("assets/Santa.png");
			se.stopSound(5);
			se.playSound(4);
			player->setrescued( false) ;
			for (int i = 0; i < difficulty; ++i)
			{
				if (difficulty == 3)
					enemy[i]->setVelocityX(1);
				else if (difficulty == 4)
					enemy[i]->setVelocityX(3);
				else enemy[i]->setVelocityX(5);
			}
			//player->setLifes(3);
			player->reset();
			map->LoadMap();
			timelimit->reset(this->difficulty);
			break;

		case SDLK_r:
			player->reset();
			map->LoadMap();
			scoreboard->reset();
			//player->setLifes(3);
			timelimit->reset(this->difficulty);
			break;

		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			player->setVelocityX(0);
			player->setIsMoving(false);
			break;

		case SDLK_LEFT:
			player->setVelocityX(0);
			player->setIsMoving(false);
			break;

		case SDLK_UP:
			player->setVelocityY(0);
			player->setIsMoving(false);
			break;

		case SDLK_DOWN:
			player->setVelocityY(0);
			player->setIsMoving(false);

		}
		break;

	default:
		break;
	}

	SDL_Point impact[5];
	for (int i = 0; i < difficulty; ++i)
	{
		impact[i] = enemy[i]->mapCentre();
	}

	player->checkEnemyCollision(impact,this->difficulty);
	if (player->getLifes() == 0)
	{
		scoreboard->reset();
	}

}


void Game::update() const
{
	char path1[] = "assets/m.png";
	char path2[] = "assets/mb.png";
	char path3[] = "assets/ux.png";

	if (player->getVelocity().x > 0)
	{
		path1[7] = player->getNext() + '0';
		player->setTex(path1);
		player->setNext();
	}

	if (player->getVelocity().x < 0)
	{
		path2[7] = player->getNext() + '0';
		player->setTex(path2);
		player->setNext();
	}

	if ((player->getVelocity().y > 0 && player->getIsOnLadder() == true) || (player->getVelocity().y < 0 && player->getIsOnLadder() == true))
	{
		path3[8] = player->getClimbAnimation() + '0';
		player->setClimbAnimation();
		player->setTex(path3);
		SDL_Delay(45);
	}

	if (player->getDamaged() == true)
	{
		player->setTex("assets/hit.png");
		se.playSound(2);
		player->setDamaged(false);
	}

	if (player->getVelocity().x == 0 && player->getVelocity().y == 0)
	{
		player->setTex("assets/idle.png");
	}

	if (player->getLifes() == 0)
	{
		player->setTex("assets/dead.png");
		player->setVelocityX(0);

	}


	scoreboard->addToScore(player->pickItems());
	scoreboard->convertScore();
	player->Unlockgreen();
	player->Unlockred();

	player->processPos();

	for (int i = 0; i < this->difficulty; ++i)
	{
		enemy[i]->processPos();
	}

	player->Gravity();

}


void Game::render() const
{
	SDL_RenderClear(renderer);

	back->draw();
	map->DrawMap();
	player->draw();
    
	for (int i = 0; i<this->difficulty; ++i)
	{
		enemy[i]->draw();
	}
	timelimit->draw();
	scoreboard->draw();
	

	
	if (player->getLifes() == 0)
	{
		gameOver->draw();
		se.playSound(1); 
	}
	if (timelimit->timeconvert() == 0)
	{
		endtime->draw();
		se.playSound(1);
	}

	
	if(player->rescued() == 1)
	{
		gameWin->draw();
		se.playSound(0);
		for (int i = 0; i < 5; ++i)
		{
			enemy[i]->setVelocityX(0);
		}
		

	}
	SDL_RenderPresent(renderer);
}

bool Game::getIsMenu(void)
{
	return this->isMenu;
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}


void Game::handleAndDrawMenu(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		
		case SDLK_DOWN:
		{
			
			(*menu)++;
			break;
		}

		case SDLK_UP:
		{
			(*menu)--;
			break;
		}

		case SDLK_RETURN:
		{
			if (menu->getIsDiff() == 0)
			{
				if (menu->getSelected() == 0)
				{
					this->isMenu = false;
					se.stopSound(5);
					se.playSound(5);
					back->setTex("assets/back.png");
					timelimit->reset(this->difficulty);
					
				}
				else
				{
					if (menu->getSelected() == 1)
					{
						menu->setIsDiff(1);
						
					}
					else
					{
						isRunning = false;
					}
				}
			}
			else if (menu->getIsDiff() == 1)
			{
				if (menu->getSelected() == 0)
				{
					this->difficulty = 3;
					timelimit->reset(this->difficulty);
					for (int i = 0; i < difficulty; ++i)
					{
						enemy[i]->setVelocityX(1);
					}
					menu->setIsDiff(2);
				}
				else
				{
					if (menu->getSelected() == 1)
					{
						this->difficulty = 4;
						timelimit->reset(this->difficulty);
						for (int i = 0; i < difficulty; ++i)
						{
							enemy[i]->setVelocityX(3);
						}
						menu->setIsDiff(2);
					}
					else
					{
						this->difficulty = 5;
						timelimit->reset(this->difficulty);
						for (int i = 0; i < difficulty; ++i)
						{
							enemy[i]->setVelocityX(5);
						}
						menu->setIsDiff(2);
					}
				}
			}
			else if (menu->getIsDiff() == 2)
			{
				if (menu->getSelected() == 0)
				{
					map->setLevel(1);
					map->LoadMap();
					player->reset();
				}
				else
				{
					if (menu->getSelected() == 1)
					{
						map->setLevel(2);
						map->LoadMap();
						player->reset();

						
					}
					else
					{
						map->setLevel(3);
						map->LoadMap();
						player->reset();
					}
				}
				ifstream f;
				int x, y;
				char pathenemy[] = "levelxenemypos.txt";
				pathenemy[5] = map->getLevel() + '0';
				f.open(pathenemy);
				for (int i = 0; i < 5; ++i)
				{
					f >> x;
					f >> y;
					if (i != 1 && i != 3)
					{
						enemy[i] = new Enemy("assets/kid.png", renderer, x, y);
						enemy[i]->init();
						enemy[i]->setGen(true);
					}
					else
					{
						enemy[i] = new Enemy("assets/girl.png", renderer, x, y);
						enemy[i]->init();
						enemy[i]->setGen(false);
					}
				}
				f.close();
				menu->setIsDiff(0);
				for (int i = 0; i < difficulty; ++i)
				{
					if (difficulty == 3)
						enemy[i]->setVelocityX(1);
					else if (difficulty == 4)
						enemy[i]->setVelocityX(3);
					else enemy[i]->setVelocityX(5);
				}
			}
			break;
		}
		}
	}



	SDL_RenderClear(renderer);

	back->draw();
	menu->draw();
	//se.stopSound(5);
	//se.playSound(4);
	SDL_RenderPresent(renderer);
}

