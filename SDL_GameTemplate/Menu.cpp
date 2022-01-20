#include"Menu.h"

Menu::Menu(SDL_Renderer *renderer):renderer(renderer)
{
	SDL_Color c = {0,200,0};//{255, 206, 68};
	this->start = new Text("assets/font.ttf", "Start", renderer,150,500,80,200,true,c);
	this->difficulty= new Text("assets/font.ttf", "Difficulty", renderer,150,650,80,200,false, c);
	this->quit= new Text("assets/font.ttf", "Quit", renderer,150,800,80,200,false, c);
	
	this->easy = new Text("assets/font.ttf", "Easy", renderer, 150, 500, 80, 200, true, c);
	this->medium = new Text("assets/font.ttf", "Medium", renderer, 150, 650, 80, 200, false, c);
	this->hard = new Text("assets/font.ttf", "Hard", renderer,150,800,80,200,false, c);

	this->level1 = new Text("assets/font.ttf", "Level 1", renderer, 150, 500, 80, 200, true, c);
	this->level2 = new Text("assets/font.ttf", "Level 2", renderer, 150, 650, 80, 200, false, c);
	this->level3 = new Text("assets/font.ttf", "Level 3", renderer, 150, 800, 80, 200, false, c);

	//SDL_RenderFillRect(renderer, &destRect);

	nrElem = 3;
	selected = 0;
	isDiff = 0;
}

void Menu::init(void)
{

}

void Menu::draw(void)
{
	if (this->isDiff == 2)
	{
		switch (this->selected)
		{
		case 0:
		{
		
			this->level1->setIsHighlight(true);
			this->level2->setIsHighlight(false);
			this->level3->setIsHighlight(false);

			break;
		}
		case 1:
		{
			this->level1->setIsHighlight(false);
			this->level2->setIsHighlight(true);
			this->level3->setIsHighlight(false);

			break;
		}
		case 2:
		{
			this->level1->setIsHighlight(false);
			this->level2->setIsHighlight(false);
			this->level3->setIsHighlight(true);

			break;
		}

		}
		this->level1->draw();
		this->level2->draw();
		this->level3->draw();

	}
	else

		if (this->isDiff == 1)
		{
			switch (this->selected)
			{
			case 0:
			{
				this->easy->setIsHighlight(true);
				this->medium->setIsHighlight(false);

			this->hard->setIsHighlight(false);

				break;
			}
			case 1:
			{
				this->easy->setIsHighlight(false);
				this->medium->setIsHighlight(true);
				this->hard->setIsHighlight(false);

				break;
			}
			case 2:
			{
				this->easy->setIsHighlight(false);
				this->medium->setIsHighlight(false);
				this->hard->setIsHighlight(true);

				break;
			}

			}
			this->easy->draw();
			this->medium->draw();
			this->hard->draw();

		}
		else
		{
			switch (this->selected)
			{
			case 0:
			{
				this->start->setIsHighlight(true);
				this->difficulty->setIsHighlight(false);
				this->quit->setIsHighlight(false);

				break;
			}
			case 1:
			{
				this->start->setIsHighlight(false);
				this->difficulty->setIsHighlight(true);
				this->quit->setIsHighlight(false);

				break;
			}
			case 2:
			{
				this->start->setIsHighlight(false);
				this->difficulty->setIsHighlight(false);
				this->quit->setIsHighlight(true);

				break;
			}

			}

			this->start->draw();
			this->difficulty->draw();
			this->quit->draw();
		}

}

int Menu::getSelected(void)
{
	return selected;
}

void Menu::operator ++(int)
{
	if (selected < 2)
	{
		selected++;
	}
}

void Menu::operator --(int)
{
	if (selected > 0)
	{
		selected--;
	}
}

