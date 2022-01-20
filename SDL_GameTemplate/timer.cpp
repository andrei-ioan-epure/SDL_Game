#include "timer.h"
#include<math.h>
#include "Player.h"
#include"SoundGame.h"
#include "Scoreboard.h"
//void Time::Timer( int m, int s) {
//    for (;;)
//    {
//      
//
//        if (s == 0 && m == 0)
//        {
//            break;
//        }
//        if (s == 0)
//        {
//            s = 60;
//            m--;
//        }
//        system("cls");
//        cout << m << " : " << s--;
//        Sleep(1000);
//    }
//
//}



Time::Time(SDL_Renderer* renderer) : renderer(renderer)
{
	/*this->m = 20;
	this->s = 30;
    this->ss = 00;*/
	for (int i = 0; i < 8; ++i)
	{
		this->texture[i] = TextureManager::LoadTexture("assets/hud_0.png", renderer);
		if(i==2||i==5)
		this->texture[i] = TextureManager::LoadTexture("assets/Puncte.png", renderer);
	}

	this->init();
}
//Time::~Time()
//{
//    //SDL_DestroyTexture(texture[8]);
//    SDL_DestroyRenderer(renderer);
//}
 SoundGame sound;
void Time::init(void)
{
   
    sound.addSound("assets/Audio/Countdown.mp3");
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 900;
	destRect.y = 32;
	destRect.w = 30;
	destRect.h = 30;
    this->m = 0;
    this->s = 20;
    this->ss = 00;
}

void Time::draw(void)
{
	int a = 0;
	int aux = destRect.x;
	for (unsigned int i = 0; i < 8; ++i)
	{
		destRect.x = aux + a;
		TextureManager::Draw(texture[i], srcRect, destRect, renderer);
		a = a - 30;
	}
	destRect.x = aux;
    this->timeconvert();
}
bool Time::timeconvert(void)
{

    char path[] = "assets/hud_0.png";
   
    if (m > 9)
    {
        int rest = m % 10;
        int cat = m / 10;
        path[11] = rest + '0';
        texture[6] = TextureManager::LoadTexture(path, renderer);
        path[11] = cat + '0';
        texture[7] = TextureManager::LoadTexture(path, renderer);
    }
    else
    {
        path[11] = m + '0';
        texture[6] = TextureManager::LoadTexture(path, renderer);
        path[11] = 0 + '0';
        texture[7] = TextureManager::LoadTexture(path, renderer);
    }
    if (s > 9)
    {
        int rest = s % 10;
        int cat = s / 10;
        path[11] = rest + '0';
        texture[3] = TextureManager::LoadTexture(path, renderer);
        path[11] = cat + '0';
        texture[4] = TextureManager::LoadTexture(path, renderer);
    }
    else
    {
        path[11] = s + '0';
        texture[3] = TextureManager::LoadTexture(path, renderer);
        path[11] = 0 + '0';
        texture[4] = TextureManager::LoadTexture(path, renderer);
    }
    if (ss > 9)
    {
        int rest = ss % 10;
        int cat = ss / 10;
        path[11] = rest + '0';
        texture[0] = TextureManager::LoadTexture(path, renderer);
        path[11] = cat + '0';
        texture[1] = TextureManager::LoadTexture(path, renderer);
    }
    else
    {
        path[11] = ss + '0';
        texture[0] = TextureManager::LoadTexture(path, renderer);
        path[11] = 0 + '0';
        texture[1] = TextureManager::LoadTexture(path, renderer);
    }
    if (m == 0 )
    {
        if(s==10||s==9|| s == 8 || s == 7 || s == 6 || s == 5 || s == 4 || s == 3 || s == 2 || s == 1)
        sound.playSound(0);
        
    }
    
    if (ss == 0) {

        if (s != 0)
        {
            this->s--;
            this->ss += 60;
        }
        else {
            if (m != 0)
            {
                this->m--;
                this->s += 60;
             }
            else {
                return 0;
            }
        }
    }

    this->ss -= 0.00000000000001;
  
    return 1;
}

void Time::reset(int diff) {
    switch (diff)
    {
        case 3:
        {
            this->m= 3;
            this->s = 0;
            this->ss = 0;
            break;

        }
        case 4:
        {
            this->m = 2;
            this->s = 0;
            this->ss = 0;
            break;
        }
        case 5:
        {
            this->m = 1;
            this->s = 30;
            this->ss = 0;
            break;
        }
        default:
        {
            this->m = 3;
            this->s = 0;
            this->ss = 0;
            break;
        }
    }
}
