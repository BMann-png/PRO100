#pragma once
#include "document.h"
#include <SDL_image.h>
#include <string>
#include <vector>

#define JSON_READ(value, data) pbls::json::Get(value, #data, data)

namespace pbls
{
	class Vector2;

	class Color;

	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);
		bool Get(const rapidjson::Value& value, const std::string& name, int& key);

		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
		bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data);

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);
	}
}