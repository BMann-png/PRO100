#include "Card.h"
#include "Engine.h"

namespace pbls
{
	
	void Card::RandomAbility()
	{
		/*NumOfAbilities = sizeof(cardAbility array);
		index = rand() % numOfAbilities;
		ability = cardAbility array[ rand() % numOfAbilities ];*/
		int index = RandomInt(8);
		ability = abilities[index];		
	}

	void Card::Create()
	{
	}

	void Card::Update()
	{
	}

	bool Card::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Card::Read(const rapidjson::Value& value)
	{
		return false;
	}
	
}