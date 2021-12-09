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
	Card(std::string name, int index, int value = 0, int type = 0);

	int GetValue() { return ability.value; }
	eType GetType() { return ability.type; }
	std::string GetTypeString();
	std::string GetName() { return ability.name; }
	int GetTexture() { return texture; }

	void RandomAbility(int index, int CardBonus = 0);
	//void UseAbility(Actor* other);

	void Create() override;
	virtual void Update() override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

	std::string toString();

public:
	int index = 0;

private:
	Ability ability;

	std::string abilities[9] = { "Shadowslash", "Flamearrow", "Manabullet",
								"Stonewall", "Heroic Shield", "Smoke Bomb",
								"Firey Embers", "Heal", "Maiden's Grace" };

	int texture = 10;
};