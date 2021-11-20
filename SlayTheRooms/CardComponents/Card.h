#pragma once
#include "Component/Component.h"
#include "CardAbilites.h"

namespace pbls
{
	class Card : public Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<Card>(*this); }

		~Card() {};
		Card() {}
		Card(const Ability &ability) : ability{ability} {}

		void RandomAbility();
		//void UseAbility(Actor* other);

		void Create() override;
		virtual void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Ability ability = Ability("default");
	private:
		//int maxDeckSize = 10; or something like that
		

		Ability ability1 = Ability("Shadowslash", 3);
		Ability ability2 = Ability("Flamearrow", 4);
		Ability ability3 = Ability("Manabullet", 2);

		Ability ability4 = Ability("Stonewall", 0, 4);
		Ability ability5 = Ability("Heroic Shield", 0, 3);
		Ability ability6 = Ability("Smoke Bomb", 0, 2);

		Ability ability7 = Ability("Firey Embers", 0, 0, 3);
		Ability ability8 = Ability("Heal", 0, 0, 2);
		Ability ability9 = Ability("Maiden's Grace", 0, 0, 4);
	
		Ability abilities[9] = { ability1, ability2, ability3, ability4, ability5, ability6, ability7,  ability9 };

		
	};
}

