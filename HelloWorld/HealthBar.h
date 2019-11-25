#pragma once
#include "JSON.h"
class HealthBar
{
public:
	//Creates the health bar
	HealthBar();

	//Creates the health bar with this amount of health
	HealthBar(float health);

	//Destroys the health bar
	~HealthBar();

	//Display the current health
	void DisplayHealth();

	//Getters
	float GetHealth() const;

	void SetHealth(float health);
private:
	//100% health
	float m_health = 1.f;
};

//Sends Healthbar TO json file
inline void to_json(nlohmann::json& j, const HealthBar& bar)
{
	j["Health"] = bar.GetHealth();
}

//Sends Healthbar TO json file
inline void from_json(nlohmann::json& j, HealthBar& bar)
{
	bar.SetHealth(j["Health"]);
}