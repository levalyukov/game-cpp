#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "items.hpp"

class CookingManager {
	public:

		CookingManager(Items& items_container) : items(items_container) {
			addRecipe("borsch", 1);
			addRecipe("chicken", 2);
			addRecipe("vegan", 3);
			addRecipe("recipe", 4);
		};

		std::map<std::string, Items::CookRecipe> availableRecipes;
		inline void addRecipe(const std::string name, unsigned __int16 id) {
			if (items.hasRecipe(id)) {
				std::string lower_name = name;
				std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
					[](unsigned char c) {return std::tolower(c); });
				availableRecipes.emplace(lower_name, *items.getRecipeInfo(id));
			};
		};

		inline Items::CookRecipe* getRecipe(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = availableRecipes.find(lower_name);
			return (item != availableRecipes.end()) ? &item->second : nullptr;
		};

		inline void startCookProcess(const std::string nameRecipe) {
			recipeTime = getRecipe(nameRecipe)->cooking_time;
			cookTimer = 0.f;
			cookedFlag = false;
			cookingFlag = true;
		};

		inline void cookingProcess(const float delta) {
			if (cookingFlag) {
				cookTimer += delta;
				if (cookTimer >= recipeTime) {
					cookingFlag = false;
					cookedFlag = true;
					cookTimer = 0.f;
					recipeTime = 0.f;
				};
			};
		};

		inline void resetCookeedFlag() { cookedFlag = false; };
		inline bool getCookingFlag() const { return cookingFlag; };
		inline bool getCookeedFlag() const { return cookedFlag; };

	private:
		Items& items;
		bool cookingFlag = false;
		bool cookedFlag = false;
		float cookTimer = 0.f;
		float recipeTime = 0.f;
};