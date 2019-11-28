#include "Game.h"
#include <Windows.h>
#include <mmsystem.h>

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	/*bool menu = true;
	
	if (menu = true) {
		
	}*/


	//Scene names and clear colors
	m_name = "Risk of Rain 2D";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Grabs the initialized window, whenever making a new scene
	m_scenes.push_back(new HelloWorld("Hello World"));
	m_scenes.push_back(new Scene("First Loaded Scene"));

	//Sets active scene reference to our HelloWorld scene
	//m_activeScene = m_scenes[0]; //Load the HelloWorld basic scene
	m_activeScene = m_scenes[0]; //Load the first scene
	
	//Inititalizes the scene, //Save, uncomment to save and comment the load
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	
	//Load uncomment to load and comment the save
	//*m_activeScene = File::LoadJSON("Hello World.json"); //Hello World Sprite
	//*m_activeScene = File::LoadJSON("Hello Anime World.json"); //Load the saved scene

	
	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		

		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();
		
		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
		
	}
	
	return true;
}

void Game::Update()
{

	int mapArray[5][5];
	vec3 playerPos = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	//walls	
	//CloseTop();
	//CloseRight();
	//CloseLeft();
	//CloseBottom();
	//OpenTop();
	//OpenBottom();
	//OpenLeft();
	//OpenRight();

	//Update bullet position
	UpdateBullet();
	
	auto& animControllerr = ECS::GetComponent<AnimationController>(1);

	//Moving to the next room
	if (playerPos.x > 190) {
		
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((playerPos.x = -190));
		m_xMap += 1;
	}
	if (playerPos.y > 100) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((playerPos.y = -100));
		m_yMap -= 1;
	}
	if (playerPos.x < -190) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((playerPos.x = 190));
		m_xMap -= 1;
	}
	if (playerPos.y < -100) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((playerPos.y = 100));
		m_yMap += 1;

	}


	//Col 1
	if (m_xMap == 1 && m_yMap == 1) {
		//Load TopLeft
		animControllerr.SetActiveAnim(0);
		CloseTop();
		CloseLeft();
		OpenBottom();
		OpenRight();
	}
	if (m_xMap == 1 && m_yMap == 2 || m_xMap == 1 && m_yMap == 3 || m_xMap == 1 && m_yMap == 4) {
		//Load MiddleLeft
		animControllerr.SetActiveAnim(3);
		CloseLeft();
		OpenTop();
		OpenBottom();
		OpenRight();
	}
	if (m_xMap == 1 && m_yMap == 5) {
		//Load BottomLeft
		animControllerr.SetActiveAnim(6);
		CloseLeft();
		CloseBottom();
		OpenTop();
		OpenRight();
	}

	//Col 5
	if (m_xMap == 5 && m_yMap == 1) {
		//Load TopRight
		animControllerr.SetActiveAnim(2);
		CloseTop();
		CloseRight();
		OpenBottom();
		OpenLeft();
	}
	if (m_xMap == 5 && m_yMap == 2 || m_xMap == 5 && m_yMap == 3 || m_xMap == 5 && m_yMap == 4) {
		//Load MiddleRight
		animControllerr.SetActiveAnim(5);
		CloseRight();
		OpenTop();
		OpenBottom();
		OpenLeft();
	}
	if (m_xMap == 5 && m_yMap == 5) {
		//Load BottomRight
		animControllerr.SetActiveAnim(8);
		CloseRight();
		CloseBottom();
		OpenTop();
		OpenLeft();
	}

	//Top middle
	if (m_xMap == 2 && m_yMap == 1 || m_xMap == 3 && m_yMap == 1|| m_xMap == 4 && m_yMap == 1) {
		//Load TopMiddle
		animControllerr.SetActiveAnim(1);
		CloseTop();
		OpenBottom();
		OpenLeft();
		OpenRight();
	}

	//Middle Middle
	if (m_xMap == 2 && m_yMap == 2 || m_xMap == 2 && m_yMap == 3 || m_xMap == 2 && m_yMap == 4 || m_xMap == 3 && m_yMap == 2 || m_xMap == 3 && m_yMap == 3 || m_xMap == 3 && m_yMap == 4 || m_xMap == 4 && m_yMap == 2 || m_xMap == 4 && m_yMap == 3 || m_xMap == 4 && m_yMap == 4) {
		//Load Middle
		animControllerr.SetActiveAnim(4);
		OpenTop();
		OpenBottom();
		OpenLeft();
		OpenRight();
	}

	//Bottom Middle
	if (m_xMap == 2 && m_yMap == 5 || m_xMap == 3 && m_yMap == 5 || m_xMap == 4 && m_yMap == 5) {
		//Load BottomMiddle
		animControllerr.SetActiveAnim(7);
		CloseBottom();
		OpenTop();
		OpenLeft();
		OpenRight();
	}




	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
	
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{

	bool animationtest = true;

	HelloWorld* scene = (HelloWorld*)m_activeScene;
	auto entity = scene->Beetle();
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	static float try2 = 0.35;

	vec3 Beetleposition = m_register->get<Transform>(entity).GetPosition();

	animController.SetActiveAnim(0);
	auto& anim = animController.GetAnimation(0);

	if (Beetleposition.x <= 135 && Beetleposition.y == -25) {
		m_register->get<Transform>(entity).SetPositionX(Beetleposition.x + try2);
	}

	if (Beetleposition.x > 135) {
		m_register->get<Transform>(entity).SetPositionY(Beetleposition.y = -24.75);
	}

	if (Beetleposition.y == -24.75) {
		
		m_register->get<Transform>(entity).SetPositionX(Beetleposition.x - try2);
	}

	if (Beetleposition.x < -137) {
		m_register->get<Transform>(entity).SetPositionY(Beetleposition.y = -25);
	}
	

	
	

	
	




	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	//Just calls all the other input functions 
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

//Keys being press continuely
void Game::KeyboardHold()
{
	//Keyboard button held
	if (Input::GetKey(Key::F3))
	{
		
	}
	if (Input::GetKey(Key::F4)){
		printf("F4 Key Held\n");
	}

	auto& animControllerr = ECS::GetComponent<AnimationController>(2);
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	float speed = 30.f;
	//Keyboard button held
	if (Input::GetKey(Key::W)) {
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(++position.y + (speed * Timer::deltaTime));
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y+0.25f) + (speed * Timer::deltaTime));
	
	}
	if (Input::GetKey(Key::S)) {
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(--position.y - (speed * Timer::deltaTime));
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y - 0.25f) - (speed * Timer::deltaTime));
		
	}
	if (Input::GetKey(Key::A)) {
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(--position.x - (speed * Timer::deltaTime));
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x - 0.25f) - (speed * Timer::deltaTime));
	
	}
	if (Input::GetKey(Key::D)) {
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(++position.x + (speed * Timer::deltaTime));
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x + 0.25f) + (speed * Timer::deltaTime));
		
		/*
		HelloWorld* scene = (HelloWorld*)m_activeScene;
		auto entitySpaceRanger = scene->SpaceRanger();
		auto& animControllerr = ECS::GetComponent<AnimationController>(entitySpaceRanger);
		animControllerr.SetActiveAnim(3);
		auto& anim = animControllerr.GetAnimation(3);
		*/
	}
	if ((Input::GetKey(Key::UpArrow)) && (m_FiringDir == 1)) {
		m_rateCounter++;
		
		animControllerr.SetActiveAnim(1);

		if (m_rateCounter > m_fireRate)
		{
			CreateBullet(0, 1);
			m_rateCounter = 0;
		}
	
	}

	if ((Input::GetKey(Key::RightArrow)) && (m_FiringDir == 2)) {
		m_rateCounter++;
		
		animControllerr.SetActiveAnim(3);
		if (m_rateCounter > m_fireRate)
		{
			CreateBullet(1, 0);
			m_rateCounter = 0;
		}
	}

	if ((Input::GetKey(Key::DownArrow)) && (m_FiringDir == 3)) {
		m_rateCounter++;
		animControllerr.SetActiveAnim(0);
		if (m_rateCounter > m_fireRate)
		{
			CreateBullet(0, -1);
			m_rateCounter = 0;
		}
		
	}

	if ((Input::GetKey(Key::LeftArrow)) && (m_FiringDir == 4)) {
		m_rateCounter++;
		animControllerr.SetActiveAnim(2);
		if (m_rateCounter > m_fireRate)
		{
			CreateBullet(-1, 0);
			m_rateCounter = 0;
		}		
	}
	//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x);
	

	

}

//Keys being pressed once
void Game::KeyboardDown()
{
	//Keyboard button down
	/*if (Input::GetKeyDown(Key::UpArrow))
	{
		HelloWorld* scene = (HelloWorld*)m_activeScene;
		auto entitySpaceRanger = scene->bullet();
		auto& animControllerr = ECS::GetComponent<AnimationController>(entitySpaceRanger);

		vec3 bulletposition = m_register->get<Transform>(entitySpaceRanger).GetPosition();
		m_register->get<Transform>(entitySpaceRanger).SetPosition(bulletposition);
	}*/

	if (Input::GetKeyDown(Key::F4))
	{
		printf("F4 Key Down\n");
	}

	
	auto& animControllerr = ECS::GetComponent<AnimationController>(2);

	if (Input::GetKeyDown(Key::A))
	{
		
		printf("A Key Down\n");
		//animControllerr.SetActiveAnim(2);
		
	}
	
	if (Input::GetKeyDown(Key::W))
	{
		printf("W Key Down\n");
		//animControllerr.SetActiveAnim(1);

	}if (Input::GetKeyDown(Key::S))
	{
		printf("S Key Down\n");
		//animControllerr.SetActiveAnim(0);
	}
	if (Input::GetKeyDown(Key::D))
	{
		printf("D Key Down\n");
		//animControllerr.SetActiveAnim(3);
	}

	//Bullet
	if (Input::GetKeyDown(Key::UpArrow))
	{
			m_FiringDir = 1;
	}

	if (Input::GetKeyDown(Key::RightArrow))
	{
			m_FiringDir = 2;
	}

	if (Input::GetKeyDown(Key::DownArrow))
	{
			m_FiringDir = 3;
	}

	if (Input::GetKeyDown(Key::LeftArrow))
	{
			m_FiringDir = 4;
	}


	
}
//Keys after being press once
void Game::KeyboardUp()
{
	//Keyboard button up
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}

	
	if (Input::GetKeyUp(Key::UpArrow))
	{
		
	}

	if (Input::GetKeyUp(Key::RightArrow))
	{
		
	}

	if (Input::GetKeyUp(Key::DownArrow))
	{
		
	}

	if (Input::GetKeyUp(Key::LeftArrow))
	{
		
	}

}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	printf("Mouse Moved (%f, %f)\n", float(evnt.x), float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;	
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
	{
		printf("Left Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		printf("Right Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		printf("Middle Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("Mouse Scroll %f\n", float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}

void Game::setBackground(int background)
{

}

void Game::CloseTop()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if ((position.y >= 75)) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = 75));
	}
}

void Game::CloseLeft()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (position.x <= -143) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = -143));

	}
}

void Game::CloseRight()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (position.x >= 142) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = 142));

	}
}

void Game::CloseBottom()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (position.y <= -62) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = -62));

	}
}

void Game::OpenTop()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (((position.y >= 75)&& (position.y <= 77)) && ((position.x >= -144) && (position.x <= -10)) || ((position.y >= 75) && (position.y <= 77)) && ((position.x <= 143) && (position.x >= 6))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = 75));
	}

	if ((position.y >= 76) && ((position.x <= -10)&& (position.x >= -11))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = -10));
	}

	if ((position.y >= 76) && ((position.x <= 7) && (position.x >= 6))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = 6));
	}
}

void Game::OpenLeft()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (((position.y <= 77) && (position.y >= 15)) && ((position.x <= -143) && (position.x >= -144)) || ((position.y <= -1) && (position.y >= -65)) && ((position.x <= -143)&&(position.x >= -144))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = -143));
	}

	if ((position.x <= -143) && ((position.y >= 14) && (position.y <= 15))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = 14));
	}

	if ((position.x <= -143) && ((position.y <= -1) && (position.y >= -3))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = -1));
	}
}

void Game::OpenRight()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (((position.y <= 77) && (position.y >= 15)) && ((position.x >= 142) && (position.x <= 144)) || ((position.y <= -1) && (position.y >= -65)) && ((position.x >= 142) && (position.x <= 144))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = 142));
	}

	if ((position.x >= 143) && ((position.y >= 14) && (position.y <= 15))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = 14));
	}

	if ((position.x >= 143) && ((position.y <= -1) && (position.y >= -3))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = -1));
	}
}

void Game::OpenBottom()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (((position.y >= -64) && (position.y <= -62)) && ((position.x >= -145) && (position.x <= -10)) || ((position.y >= -64) && (position.y <= -62)) && ((position.x <= 143) && (position.x >= 6))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY((position.y = -62));
	}

	if ((position.y <= -62) && ((position.x <= -10) && (position.x >= -11))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = -10));
	}

	if ((position.y <= -62) && ((position.x <= 7) && (position.x >= 6))) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX((position.x = 6));
	}
}

void Game::CreateBullet(int xDir, int yDir)
{
	Bullet bullet;
	//Power up animataion file
	auto bulletSprite = File::LoadJSON("Bullet.json");
	 
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Set up components
	std::string fileName = "Green.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(fileName);
	//Adds first animation
	animController.AddAnimation(bulletSprite["Green"]);

	//Sets active animation
	animController.SetActiveAnim(0);

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 5, 5, true, &animController);
	ECS::GetComponent<Sprite>(entity).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));

	//Set bullet initial position based on current player position
	ECS::GetComponent<Transform>(entity).SetPositionX(ECS::GetComponent<Transform>(2).GetPosition().x);
	ECS::GetComponent<Transform>(entity).SetPositionY(ECS::GetComponent<Transform>(2).GetPosition().y);
	ECS::GetComponent<Transform>(entity).SetPositionZ(ECS::GetComponent<Transform>(2).GetPosition().z);

	//Record bullet ID
	bullet.bulletID = entity;

	//Record initial bullet position in vector
	bullet.xInitPos = ECS::GetComponent<Transform>(entity).GetPositionX();
	bullet.yInitPos = ECS::GetComponent<Transform>(entity).GetPositionY();
	bullet.zInitPos = ECS::GetComponent<Transform>(entity).GetPositionZ();
	bullet.xPos = bullet.xInitPos;
	bullet.yPos = bullet.yInitPos;
	bullet.zPos = bullet.zInitPos;
	bullet.xDir = xDir;
	bullet.yDir = yDir;
	m_bulletList.push_back(bullet);

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Bullet");
}

void Game::UpdateBullet()
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		//Update Vector
		m_bulletList[i].xPos = m_bulletList[i].xPos + m_bulletList[i].xDir;
		m_bulletList[i].yPos = m_bulletList[i].yPos + m_bulletList[i].yDir;
		
		//Update bullet position on screen
		
		ECS::GetComponent<Transform>(m_bulletList[i].bulletID).SetPositionX(m_bulletList[i].xPos);
		ECS::GetComponent<Transform>(m_bulletList[i].bulletID).SetPositionY(m_bulletList[i].yPos);
		
		if (isHitBorder(m_bulletList[i]))
		{
			ECS::DestroyEntity(m_bulletList[i].bulletID);
			m_bulletList.erase(m_bulletList.begin() + i);
			
		}
	}
}

bool Game::isHitBorder(Bullet bullet)
{
	if (bullet.xPos > 145 || bullet.xPos < -148 || bullet.yPos > 70 || bullet.yPos < -71)
	{
		return true;
	}
	else
		return false;
}
