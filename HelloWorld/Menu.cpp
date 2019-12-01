#include "Menu.h"


Menu::Menu(std::string name)
	: Scene(name)
{
}

void Menu::InitScene(float windowWidth, float windowHeight)
{

	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Camera Entity
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

	//Menu
	{
		//Creates Main Menu
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

	}


}
