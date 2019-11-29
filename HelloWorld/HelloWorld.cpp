#include "HelloWorld.h"
#include "Framebuffer.h"

//#include "EntityIdentifier.cpp"
//#include "Game.cpp"

HelloWorld::HelloWorld(std::string name)
 :Scene(name)
{
	
}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	Framebuffer::InitFullscreenQuad();

	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);
	float aspectRatio = windowWidth / windowHeight;
	{
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}


	//Setup new Entity Health Bar
	/*
	{
		//Creates entity
		auto entity = ECS::CreateEntity();


		//Creates new orthographic camera
		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	}

*/

	
	{
		
		//Power up animataion file
		auto mapLayout = File::LoadJSON("MapLayout.json");

		//Creates entity
		auto globalMap = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(globalMap);
		ECS::AttachComponent<Transform>(globalMap);
		ECS::AttachComponent<AnimationController>(globalMap);

		//Set up components
		std::string globalMapFile = "fullMap2.png";
		auto& mapAnim = ECS::GetComponent<AnimationController>(globalMap);
		mapAnim.InitUVs(globalMapFile);

		//Adds first animation
		mapAnim.AddAnimation(mapLayout["TopLeft"]);			//0
		mapAnim.AddAnimation(mapLayout["TopMiddle"]);		//1
		mapAnim.AddAnimation(mapLayout["TopRight"]);		//2
		mapAnim.AddAnimation(mapLayout["MiddleLeft"]);		//3
		mapAnim.AddAnimation(mapLayout["MiddleMiddle"]);	//4
		mapAnim.AddAnimation(mapLayout["MiddleRight"]);		//5
		mapAnim.AddAnimation(mapLayout["BottomLeft"]);		//6
		mapAnim.AddAnimation(mapLayout["MiddleBottom"]);	//7
		mapAnim.AddAnimation(mapLayout["BottomRight"]);		//8

		//Sets active animation
		mapAnim.SetActiveAnim(4);
		//Gets first animation

		ECS::GetComponent<Sprite>(globalMap).LoadSprite(globalMapFile, 380, 200, true, &mapAnim);
		ECS::GetComponent<Sprite>(globalMap).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));
		ECS::GetComponent<Transform>(globalMap).SetPosition(vec3(0.f, 0.f, 13.f));

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(globalMap, bitHolder, "Global Map");
		
		/*//Creates entity Map
		auto entityBack = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entityBack);
		ECS::AttachComponent<Transform>(entityBack);

		//Sets up components
		std::string BackGround = "Middle.png"; //400, 200
		ECS::GetComponent<Sprite>(entityBack).LoadSprite(BackGround, 380, 200);
		ECS::GetComponent<Transform>(entityBack).SetPosition(vec3(0.f, 0.f, 13.f));
		
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entityBack, bitHolder, "Temp Entity");
		*/
	}

	

	/*{
		//Creates entity Map
		auto entityLoad = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entityLoad);
		ECS::AttachComponent<Transform>(entityLoad);

		//Sets up components
		std::string MenuScreen = "TitleScreen.jpg"; //400, 200
		ECS::GetComponent<Sprite>(entityLoad).LoadSprite(MenuScreen, 380, 200);

		ECS::GetComponent<Transform>(entityLoad).SetPosition(vec3(0.f, 0.f, 50.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entityLoad, bitHolder, "Loading Menu");

		m_entityMenu = entityLoad;
	}*/
	
	/*
	{
		//Map1
		auto Moving = File::LoadJSON("NewSpaceRanger.json");
		
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string Map = "FullMap1.0.png";
		auto& animControllerr = ECS::GetComponent<AnimationController>(entity);
		animControllerr.InitUVs(Map);

		//Adds first Animation
		animControllerr.AddAnimation(Map1["TopLeft"]);
		animControllerr.GetAnimation(0).SetRepeating(true);
		animControllerr.AddAnimation(Map1["MiddleLeft"]);
		animControllerr.GetAnimation(1).SetRepeating(true);
		animControllerr.AddAnimation(Map1["BottomLeft"]);
		animControllerr.GetAnimation(2).SetRepeating(true);
		animControllerr.AddAnimation(Map1["TopMiddle"]);
		animControllerr.GetAnimation(3).SetRepeating(true);
		animControllerr.AddAnimation(Map1["MiddleMiddle"]);
		animControllerr.GetAnimation(4).SetRepeating(true);
		animControllerr.AddAnimation(Map1["BottomMiddle"]);
		animControllerr.GetAnimation(5).SetRepeating(true);
		animControllerr.AddAnimation(Map1["TopRight"]);
		animControllerr.GetAnimation(6).SetRepeating(true);
		animControllerr.AddAnimation(Map1["MiddleRight"]);
		animControllerr.GetAnimation(7).SetRepeating(true);
		animControllerr.AddAnimation(Map1["BottomRight"]);
		animControllerr.GetAnimation(8).SetRepeating(true);

		animControllerr.AddAnimation(Moving["MovingDown"]);
		//animControllerr.GetAnimation(0).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingUp"]);
		//animControllerr.GetAnimation(1).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingLeft"]);
		//animControllerr.GetAnimation(2).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingRight"]);
		//animControllerr.GetAnimation(3).SetRepeating(true);
		animControllerr.AddAnimation(Moving["Red"]);
		animControllerr.AddAnimation(Moving["Idle"]);
		

		//Set first anitmation
		animControllerr.SetActiveAnim(0);

		//gets first animation
		auto& anim = animControllerr.GetAnimation(4);

		//Makes it repeat
		anim.SetRepeating(true);

		//Sets the time between frames
		anim.SetSecPerFrame(0.1667f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(Map, 380, 200, true, &animControllerr);
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 14.f));

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Map Entity");

	}

	*/

	//Setup new Entity, SpaceRanger
	{
		//Our attack animation file
		auto Moving = File::LoadJSON("NewSpaceRanger.json");
		//auto Moving = File::LoadJSON("Main_Character1.json");

		//Creates entity
		auto entitySpaceRanger = ECS::CreateEntity();

		//Main Player
		EntityIdentifier::MainPlayer(entitySpaceRanger);

		//Add components
		ECS::AttachComponent<Sprite>(entitySpaceRanger);
		ECS::AttachComponent<Transform>(entitySpaceRanger);
		ECS::AttachComponent<AnimationController>(entitySpaceRanger);

		//Sets up components
		//std::string SpaceRanger = "Space Rager 2.png";
		std::string SpaceRanger = "Space.png";
		//std::string SpaceRanger = "Main_Character.png";
		auto& animControllerr = ECS::GetComponent<AnimationController>(entitySpaceRanger);
		animControllerr.InitUVs(SpaceRanger);

		//Adds first Animation
		//animControllerr.AddAnimation(Animation());
										//Calling the name of the animation
		
		animControllerr.AddAnimation(Moving["MovingDown"]);
		//animControllerr.GetAnimation(0).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingUp"]);
		//animControllerr.GetAnimation(1).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingLeft"]);
		//animControllerr.GetAnimation(2).SetRepeating(true);
		animControllerr.AddAnimation(Moving["MovingRight"]);
		//animControllerr.GetAnimation(3).SetRepeating(true);
		animControllerr.AddAnimation(Moving["Red"]);
		animControllerr.AddAnimation(Moving["Idle"]);

		/* //Farhan Json
		animControllerr.AddAnimation(Moving["walking_straight"]);
		animControllerr.AddAnimation(Moving["back_facing"]);
		animControllerr.AddAnimation(Moving["walking_left"]);
		animControllerr.AddAnimation(Moving["walking_right"]);
		animControllerr.AddAnimation(Moving["Regular_Stance"]);
		*/

		//Set first anitmation
		animControllerr.SetActiveAnim(0);

		//gets first animation
		auto& anim = animControllerr.GetAnimation(0);

		//Makes it repeat
		anim.SetRepeating(true);

		//Sets the time between frames
		anim.SetSecPerFrame(0.1667f);
		//485 547
		ECS::GetComponent<Sprite>(entitySpaceRanger).LoadSprite(SpaceRanger, 485 / 30, 547 / 30, true, &animControllerr);
		ECS::GetComponent<Sprite>(entitySpaceRanger).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));
		//30, -25, 20
		ECS::GetComponent<Transform>(entitySpaceRanger).SetPosition(vec3(0.f, 0.f, 50.f));

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entitySpaceRanger, bitHolder, "SpaceRanger Entity");

	}
	
	{
		/*//Bullets
		auto Moving = File::LoadJSON("Bullet.json");

		//Creates entity
		auto entitySpaceRanger = ECS::CreateEntity();
		
		//Add components
		ECS::AttachComponent<Sprite>(entitySpaceRanger);
		ECS::AttachComponent<Transform>(entitySpaceRanger);
		ECS::AttachComponent<AnimationController>(entitySpaceRanger);

		//Sets up components
		std::string SpaceRanger = "Green.png";
		auto& animControllerr = ECS::GetComponent<AnimationController>(entitySpaceRanger);
		animControllerr.InitUVs(SpaceRanger);

		//Adds first Animation
		//animControllerr.AddAnimation(Animation());
										//Calling the name of the animation

		animControllerr.AddAnimation(Moving["Green"]);
		animControllerr.GetAnimation(0).SetRepeating(true);



		//Set first anitmation
		animControllerr.SetActiveAnim(0);

		//gets first animation
		auto& anim = animControllerr.GetAnimation(0);

			
		ECS::GetComponent<Sprite>(entitySpaceRanger).LoadSprite(SpaceRanger, 18 / 3, 18 / 3, true, &animControllerr);
		//ECS::GetComponent<Sprite>(entitySpaceRanger).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));
		//ECS::GetComponent<Transform>(entitySpaceRanger).SetPosition(vec3(-25.f, -25.f, 25.f));
		
		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entitySpaceRanger, bitHolder, "GreenBullet");

		//ECS::SetIsMainPlayer(Moving, true);

		//m_entitybullet = Moving;
		*/
	}
	
	/*
	
	{
		//Beetle animation file
		auto Moving = File::LoadJSON("Insect.json");
		
		//Creates entity Beetle
		auto entityB = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entityB);
		ECS::AttachComponent<Transform>(entityB);
		ECS::AttachComponent<AnimationController>(entityB);

		//Sets up components
		std::string Beetle = "Beetle.png";
		auto& animController = ECS::GetComponent<AnimationController>(entityB);
		animController.InitUVs(Beetle);

		//Adds first Animation
		animController.AddAnimation(Moving["move"]);
		animController.AddAnimation(Moving["still"]);

		//Set first anitmation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim = animController.GetAnimation(0);

		ECS::GetComponent<Sprite>(entityB).LoadSprite(Beetle, 86 / 4, 87 / 4, true, &animController);
		ECS::GetComponent<Sprite>(entityB).SetUVs(vec2(81.f, 88.f), vec2(163.f, 1.f));
		ECS::GetComponent<Transform>(entityB).SetPosition(vec3(-115.f, -25.f, 20.f));

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entityB, bitHolder, "Beetle Entity");

		m_BeetleEntity = entityB;

	}
	*/
	{
		//Lizard animation file
		auto Moving = File::LoadJSON("Lizard.json");

		//Creates entity Lizard
		auto entityL = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entityL);
		ECS::AttachComponent<Transform>(entityL);
		ECS::AttachComponent<AnimationController>(entityL);

		//Sets up components
		std::string Lizard = "Lizard.png";
		auto& animController = ECS::GetComponent<AnimationController>(entityL);
		animController.InitUVs(Lizard);

		//Adds first Animation
		animController.AddAnimation(Moving["left_walk"]);
		animController.AddAnimation(Moving["left_still"]);
		animController.AddAnimation(Moving["right_walk"]);
		animController.AddAnimation(Moving["right_still"]);

		//Set first anitmation
		animController.SetActiveAnim(2);

		//gets first animation
		auto& anim = animController.GetAnimation(0);

		ECS::GetComponent<Sprite>(entityL).LoadSprite(Lizard, 60/3,49/3, true, &animController);
		ECS::GetComponent<Sprite>(entityL).SetUVs(vec2(1.f, 50.f), vec2(59.f, 1.f));
		ECS::GetComponent<Transform>(entityL).SetPosition(vec3(-70.f, 50.f, 21.f));

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entityL, bitHolder, "Lizard Entity");
	} 


	{
		//Boss animation file
		auto Moving = File::LoadJSON("bossSprite.json");

		//Creates entity Boss
		auto entityBo = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entityBo);
		ECS::AttachComponent<Transform>(entityBo);
		ECS::AttachComponent<AnimationController>(entityBo);

		//Sets up components
		std::string Boss = "Boss.png";
		auto& animController = ECS::GetComponent<AnimationController>(entityBo);
		animController.InitUVs(Boss);

		//Adds first Animation
		animController.AddAnimation(Moving["bossLeft"]);
		animController.AddAnimation(Moving["bossRight"]);

		//Set first anitmation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim = animController.GetAnimation(0);

		ECS::GetComponent<Sprite>(entityBo).LoadSprite(Boss, 108/2, 151/2,true, &animController);
		ECS::GetComponent<Sprite>(entityBo).SetUVs(vec2(1.f, 152.f), vec2(113.f, 1.f));
		ECS::GetComponent<Transform>(entityBo).SetPosition(vec3(100.f, -30.f, 22.f));

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entityBo, bitHolder, "Boss Entity");
	}
}



int HelloWorld::SpaceRanger()
{
	return m_entitySpaceRanger;
}

int HelloWorld::bullet()
{
	return m_entitybullet;
}
int HelloWorld::Beetle()
{
	return m_BeetleEntity;
}
int HelloWorld::Menu()
{
	return m_entityMenu;
}
void function()
{
}
