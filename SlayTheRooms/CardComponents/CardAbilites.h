#pragma once
#include <string>

namespace pbls
{
	class Ability
	{
	public:
		Ability() {};
		Ability(const std::string &name, int damage = 0, int defense = 0, int heal = 0) : name{ name }, damage{ damage }, defense{ defense }, heal{ heal } {}

		int damage = 0;
		int defense = 0;
		int heal = 0;
		std::string name;
	};

	class shadowslash : public Ability
	{
	public:
		int damage = 3;
		std::string name = "Shadowslash";
	};
	class flamearrow : public Ability {
	public:
		int damage = 4;
		std::string name = "Flamearrow";
	};
	 
	class manabullet : public Ability {
	public:
		int damage = 2;
		std::string name = "Manabullet";
	};
	 
	class stonewall : public Ability {
	public:
		int defense = 4;
		std::string name = "Stonewall";
	};
	class heroicshield : public Ability {
	public:
		int defense = 3;
		std::string name = "Heroic Shield";
	};
	class smokebomb : public Ability {
	public:
		int defense = 2;
		std::string name = "Smoke Bomb";
	};
	class fireyembers : public Ability {
	public:
		int heal = 3;
		std::string name = "Firey Embers";
	};
	/*class heal : public Ability {
	public:
		int heal = 2;
		std::string name = "Heal";
	};*/
	class maidensgrace : public Ability {
	public:
		int heal = 4;
		std::string name = "Maiden's Grace";
	};

}