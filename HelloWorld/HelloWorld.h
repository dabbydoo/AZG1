#pragma once
#include "Scene.h"

class HelloWorld : public Scene
{
public:
	HelloWorld(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	int m_entitySpaceRanger;
	int m_entitybullet;
	int m_BeetleEntity;
	int SpaceRanger();
	int bullet();
	int Beetle();
};
