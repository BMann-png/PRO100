#pragma once
#include "Component/Component.h"
#include <string>

class Card : public pbls::Component
{
public:
	enum class eType
	{
		Damage,
		Defense,
		Heal
	};

	struct Ability
	{
		int value;
		eType type;
		std::string name;
	};

public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<Card>(*this); }

	~Card() {};
	Card() {}
	Card(std::string name, int value = 0, int type = 0);

	void RandomAbility();
	//void UseAbility(Actor* other);

	void Create() override;
	virtual void Update() override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

	std::string toString();

private:
	Ability ability;

	std::string abilities[9] = { "Shadowslash", "Flamearrow", "Manabullet", 
								"Stonewall", "Heroic Shield", "Smoke Bomb",
								"Firey Embers", "Heal", "Maiden's Grace" };

	
};

