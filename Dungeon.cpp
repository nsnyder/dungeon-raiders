#include "Dungeon.h"

//=============================================================================
// Constructor
//=============================================================================
Dungeon::Dungeon() {
	
}

//=============================================================================
// Destructor
//=============================================================================
Dungeon::~Dungeon()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Dungeon::initialize(HWND hwnd)
{
	SFXon = true;
	activeMenu = false;
	timeInState = 0.0;
	gameStates = SPLASH_SCREEN;

    Game::initialize(hwnd); // throws GameError

	/*
	for (int i = 0; i < nTextures; i++) {
		if (!textures[i].initialize(graphics, images[i].c_str())) 
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	}

	for (int i = 0; i < nImages; i++) {
		if (!staticImages[i].initialize(graphics, 0, 0, 0, &textures[loadImages[i]]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Images"));
	}
	*/
	

	// Menu
	activeMenu = false;
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input, NULL);

	mainMenu->setMenuHeading("Stick Fight");

	std::vector<std::string> menuItems;
	menuItems.push_back("New Game >");	// Menu 1
	menuItems.push_back("Sound FX >");	// Menu 2
	menuItems.push_back("Cheats >");	// Menu 3
	menuItems.push_back("I'm Feeling Lucky");
	mainMenu->setMenuItems(menuItems);

	std::vector<Menu*> children = mainMenu->getChildren();

	// menu1
	Menu* menu1 = new Menu();
	menu1->initialize(graphics, input, mainMenu);
	menuItems.resize(2);
	menuItems[0] = "1 Player";	// Index 11
	menuItems[1] = "2 Player";	// Index 12
	children[0] = menu1;

	menu1->setMenuItems(menuItems);
	menu1->setMenuHeading("Choose Amount of Players");

	// menu2
	Menu* menu2 = new Menu();
	menu2->initialize(graphics, input, mainMenu);
	menuItems.resize(2);
	menuItems[0] = "On";	// Index 21
	menuItems[1] = "Off";	// Index 22
	children[1] = menu2;

	menu2->setMenuItems(menuItems);
	menu2->setMenuHeading("Effects");

	// menu3
	Menu* menu3 = new Menu();
	menu3->initialize(graphics, input, mainMenu);
	menuItems.resize(2);
	menuItems[0] = "On";	// Index 21
	menuItems[1] = "Off";	// Index 22
	children[2] = menu3;

	menu3->setMenuItems(menuItems);
	menu3->setMenuHeading("Cheats");
	

	mainMenu->setChildren(children);
	
}

//=============================================================================
// Update all game items
//=============================================================================
void Dungeon::update()
{
	gameStateUpdate();

	
	if(gameStates == MENU || (activeMenu && gameStates != CHARACTER_SELECT)) {
		mainMenu->getActiveMenu()->update();
		if(mainMenu->getMenuState() == SFX_OFF) { SFXon = false; audio->stopCue(BACKGROUND); }
		if(mainMenu->getMenuState() == SFX_ON) { SFXon = true;  audio->playCue(BACKGROUND); }
		//if(mainMenu->getMenuState() == MODE_1_PLAYER) { gameStates = CHARACTER_SELECT; multiplayer = false; activeMenu = false; }
		//if(mainMenu->getMenuState() == MODE_2_PLAYER) { gameStates = CHARACTER_SELECT; multiplayer = true; activeMenu = false; }
	} /*
	if (gameStates == CHARACTER_SELECT) {
		if (input->wasKeyPressed(VK_LEFT)) { if (oneChar < 1) oneChar++; else oneChar = 0; }
		if (input->wasKeyPressed(VK_RIGHT)) { if (oneChar > 0) oneChar--; else oneChar = 1; }
		if (input->wasKeyPressed(0x44)) if (twoChar < 1) twoChar++; else twoChar = 0;
		if (input->wasKeyPressed(0x41)) if (twoChar > 0) twoChar--; else twoChar = 1;
		if (input->wasKeyPressed(VK_SPACE) || input->wasKeyPressed(VK_RETURN)) {
			one[oneChar]->setX(200 - one[oneChar]->getWidth() / 2);
			one[oneChar]->setY(300 - one[oneChar]->getHeight() / 2);
			one[oneChar]->setScale(0.5);
			one[0]->setHealth(100.0f);
			one[1]->setHealth(100.0f);
			two[twoChar]->setX(400 - two[twoChar]->getWidth() / 2);
			two[twoChar]->setY(300 - two[twoChar]->getHeight() / 2);
			two[twoChar]->setScale(0.5);
			two[0]->setHealth(100.0f);
			two[1]->setHealth(100.0f);
			timeInState = 0.0;
			if(multiplayer) {
				gameStates = INSTRUCTIONS_MULTI;
			} else {
				gameStates = INSTRUCTIONS_SINGLE;
			}
		}
	}
	if (gameStates == LEVEL1 && !activeMenu) {
		one[oneChar]->readInput(false);
		one[oneChar]->update(frameTime);
		if (multiplayer) two[twoChar]->readInput(true);
		two[twoChar]->update(frameTime);
		for (int i = 0; i < nWalls; i++) walls[i].update(frameTime);

		oneHealth.setScaleX(one[oneChar]->getHealth() * 2);
		twoHealth.setScaleX(two[twoChar]->getHealth() * 2);
		twoHealth.setX(GAME_WIDTH - twoHealth.getScaleX());
	}
	if(input->wasKeyPressed(VK_ESCAPE)) {
		activeMenu = !activeMenu;
		mainMenu->setActiveMenu(mainMenu);
	}
	*/
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Dungeon::ai()
{
	/*
	if (gameStates != LEVEL1) return;
	if (!multiplayer) 
		two[twoChar]->Ai(one[oneChar]);
	*/
}

//=============================================================================
// Handle collisions
//=============================================================================
void Dungeon::collisions()
{
	/*
	if (gameStates != LEVEL1) return;
	one[oneChar]->collisions(walls, nWalls);
	two[twoChar]->collisions(walls, nWalls);

	VECTOR2 cv;
	Entity* hb = one[oneChar]->getHitbox();
	if (hb != 0 && two[twoChar]->collidesWith(*hb, cv) && two[twoChar]->getInvincible() == 0) {
		if (one[oneChar]->getCenterX() > two[twoChar]->getCenterX())
			two[twoChar]->setVelocity(VECTOR2(-5, 0.5));
		else
			two[twoChar]->setVelocity(VECTOR2(5, 0.5));
		two[twoChar]->damage(10);
		two[twoChar]->stunned = 100;
		if(two[twoChar]->getHealth() <= 0) {
			// DIE
			if(SFXon) audio->playCue(DEATH);
		} else
			if(SFXon) one[oneChar]->soundHit(audio);
	}  else if(hb != 0) {
		// Firing too often
		// if(SFXon) one[oneChar]->soundMiss(audio);
	}
	hb = two[twoChar]->getHitbox();
	if (hb != 0 && one[oneChar]->collidesWith(*hb, cv) && one[oneChar]->getInvincible() == 0) {
		if (one[oneChar]->getCenterX() > two[twoChar]->getCenterX())
			one[oneChar]->setVelocity(VECTOR2(5, 0.5));
		else
			one[oneChar]->setVelocity(VECTOR2(-5, 0.5));
		one[oneChar]->damage(10);
		one[oneChar]->stunned = 100;
		if(one[oneChar]->getHealth() <= 0) {
			// DIE
			if(SFXon) audio->playCue(DEATH);
		} else
			if(SFXon) two[twoChar]->soundHit(audio);
	} else if(hb != 0) {
		// Firing too often
		// if(SFXon) two[twoChar]->soundMiss(audio);
	}
	*/
}

//=============================================================================
// Render game items
//=============================================================================
void Dungeon::render()
{
	graphics->spriteBegin();
	if(activeMenu) {
		staticImages[0].draw();
		mainMenu->getActiveMenu()->displayMenu(frameTime);
	} else {
		switch(gameStates) {
		case SPLASH_SCREEN:
			/*
			staticImages[0].draw();
			text.print(		"Heroes and Villians of the Ages", GAME_WIDTH / 2 - 175, GAME_HEIGHT / 2 - 120);
			if (timeInState > 2) {
				text.print(	"Meeting for Epic Battle", GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2 - 80);
			}
			if (timeInState > 4) {
				text.print(	"In the Arenas of the Ancients", GAME_WIDTH / 2 - 160, GAME_HEIGHT / 2 - 40);
			}
			if (timeInState > 6) {
				text.print(	"Ohh, and They are Stick Figures", GAME_WIDTH / 2 - 175, GAME_HEIGHT / 2);
			}
			if (timeInState > 8) {
				timeInState = 0.0;
				audio->playCue(BACKGROUND);
				gameStates = MENU;
			}
			*/
			break;
		case MENU:
			// Render menu
			// staticImages[0].draw(); Black screen
			mainMenu->getActiveMenu()->displayMenu(frameTime);
			break;
		case INSTRUCTIONS_MULTI:
			// staticImages[0].draw();
			// text.print("PLAYER 1: ARROW KEYS to move, SPACE to attack", 10, GAME_HEIGHT / 2 - 120);
			// text.print("PLAYER 2: WASD to move, TAB to attack", 10, GAME_HEIGHT / 2);
			// if(timeInState>2) gameStates = LEVEL1;
			break;
		case INSTRUCTIONS_SINGLE:
			// staticImages[0].draw();
			// text.print("PLAYER 1: ARROW KEYS to move, SPACE to attack", 10, GAME_HEIGHT / 2 - 120);
			// if(timeInState>2) gameStates = LEVEL1;
			break;
		case CHARACTER_SELECT:
			// staticImages[0].draw();
			// 
			// text.print("Choose your character", 100, 10);
			// 
			// staticImages[1].setX(50);
			// staticImages[1].setY(70);
			// staticImages[1].setScaleX(200);
			// staticImages[1].setScaleY(300);
			// staticImages[1].draw();
			// 
			// text.print("Player 1", 50, 40);
			// 
			// one[0]->setX(60);
			// one[0]->setY(80);
			// one[0]->setScale(1.0);
			// one[0]->setCurrentFrame(6);
			// one[1]->setX(-60);
			// one[1]->setY(-40);
			// one[1]->setScale(1.0);
			// one[1]->setCurrentFrame(0);
			// one[oneChar]->draw();
			// 
			// if (multiplayer) {
			// 	staticImages[1].setX(300);
			// 	staticImages[1].setY(70);
			// 	staticImages[1].setScaleX(200);
			// 	staticImages[1].setScaleY(300);
			// 	staticImages[1].draw();
			// 
			// 	text.print("Player 2", 290, 40);
			// 
			// 	two[0]->setX(310);
			// 	two[0]->setY(80);
			// 	two[0]->setScale(1.0);
			// 	two[0]->setCurrentFrame(6);
			// 	two[1]->setX(180);
			// 	two[1]->setY(-40);
			// 	two[1]->setScale(1.0);
			// 	two[1]->setCurrentFrame(0);
			// 	two[twoChar]->draw();
			// }
			break;
		case LEVEL1:
			// staticImages[2].draw();
			// if (one[oneChar]->getInvincible() > 0)
			// 	one[oneChar]->draw(SETCOLOR_ARGB(100, 255, 255, 255));
			// else
			// 	one[oneChar]->draw();
			// 
			// if (two[twoChar]->getInvincible() > 0)
			// 	two[twoChar]->draw(SETCOLOR_ARGB(100, 255, 255, 255));
			// else
			// 	two[twoChar]->draw();
			// 
			// oneHealth.draw();
			// twoHealth.draw();
			// 
			// if(one[oneChar]->getHealth()<=0) {
			// 	gameStates = WIN2;
			// 	timeInState = 0;
			// }
			// if(two[twoChar]->getHealth()<=0) {
			// 	gameStates = WIN1;
			// 	timeInState = 0;
			// }
			// 
			break;
		case WIN1:
			// staticImages[0].draw();
			// text.print("PLAYER 1 WINS!", 10, GAME_HEIGHT / 2 - 120);
			// if(timeInState>2) {
			// 	resetAll();
			// 	gameStates = MENU;
			// }
			break;
		case WIN2:
			// staticImages[0].draw();
			// text.print("PLAYER 2 WINS!", 10, GAME_HEIGHT / 2 - 120);
			// if(timeInState>2) {
			// 	resetAll();
			// 	gameStates = MENU;
			// }
			break;
		}
	}
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Dungeon::releaseAll()
{
    Game::releaseAll();
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Dungeon::resetAll()
{
    Game::resetAll();
	mainMenu->getActiveMenu()->update();
}

//=============================================================================
// Update all game items
//=============================================================================

void Dungeon::gameStateUpdate()
{
	timeInState += frameTime;
	if (gameStates==SPLASH_SCREEN && input->wasKeyPressed(VK_SPACE))
	{
		gameStates = MENU;
		audio->playCue(BACKGROUND);
		timeInState = 0;
	}
	if (gameStates==MENU) {
		if(mainMenu->getMenuState() == MODE_1_PLAYER) {
			multiplayer = false;
			gameStates = CHARACTER_SELECT;
			timeInState = 0;
		}
		if(mainMenu->getMenuState() == MODE_2_PLAYER) {
			multiplayer = true;
			gameStates = CHARACTER_SELECT;
			timeInState = 0;
		}
	}
	if (gameStates==LEVEL1)
	{
		timeInState = 0;
	}
}
