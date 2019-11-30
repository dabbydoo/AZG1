#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "HelloWorld.h"
#include "bullet.h"

#include"Enemy_Class.h"

//Our main class for running our game
class Game
{
public:
	//Empty constructor
	Game() { };
	//Deconstructor for game
	//*Unloads window
	~Game();

	//Initiaiizes game
	//*Seeds random
	//*Initializes SDL
	//*Creates Window
	//*Initializes GLEW
	//*Create Main Camera Entity
	//*Creates all other entities and adds them to register
	void InitGame();

	//Runs the game
	//*While window is open
	//*Clear window
	//*Update 
	//*Draw
	//*Poll events
	//*Flip window
	//*Accept input
	bool Run();
	
	//Updates the game
	//*Update timer
	//*Update the rendering system
	//*Update the animation system
	void Update();

	//Runs the GUI
	//*Uses ImGUI for this
	void GUI();

	//Check events
	//*Checks the results of the events that have been polled
	void CheckEvents();

	/*Input Functions*/
	void AcceptInput();
	void KeyboardHold();
	void KeyboardDown();
	void KeyboardUp();

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt);
	void MouseClick(SDL_MouseButtonEvent evnt);
	void MouseWheel(SDL_MouseWheelEvent evnt);

	//Set background
	void setBackground(int background);

	//Border
	void CloseTop();
	void CloseLeft();
	void CloseRight();
	void CloseBottom();
	void OpenTop();
	void OpenLeft();
	void OpenRight();
	void OpenBottom();

	//Create Bullet
	void CreateBullet(int xDir, int yDir);
	void UpdateBullet();

	//Create Explosion
	void CreateExplosion(int xPos, int yPos);
	void UpdateExplosion();

	//Bullet collision to border
	bool isHitBorder(Bullet bullet);

	void CreateBeetle();

	void UpdateBeetle();

	void CreateBoss();

	void ShadowEffect();

	bool player_in_room();

private:
	//The window
	Window *m_window = nullptr;

	//Scene name
	std::string m_name;
	//Clear color for when we clear the window
	vec4 m_clearColor;
	
	//The main register for our ECS
	entt::registry* m_register;

	//Scenes
	Scene* m_activeScene;
	std::vector<Scene*> m_scenes;
	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	bool enemy = true;

	//Bullet
	std::vector<Bullet> m_bulletList;
	std::vector<Enemy>m_Bettle_spawn;

	//Bullet fire rate
	int m_fireRate = 25;
	int m_rateCounter = 0;
	int m_FiringDir = 0;

	//Fireball
	std::vector<Explosion> m_fireballList;

	//Room coord
	int m_xMap = 3;
	int m_yMap = 3;

};



#endif // !__GAME_H__

