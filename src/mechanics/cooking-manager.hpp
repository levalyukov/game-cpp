#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdint.h>

#include "items.hpp"

class CookingManager {
	public:
		CookingManager(
			Items& items_container
		) : items(items_container) {
			addRecipe("borsch", 1);
		};

		std::map<std::string, Items::CookRecipe> availableRecipes;
		inline void addRecipe(const std::string recipe_name, uint16_t id) {
			if (items.hasRecipe(id)) {
				std::string lower_name = recipe_name;
				std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
					[](unsigned char c) {return std::tolower(c); });
				availableRecipes.emplace(lower_name, *items.getRecipeInfo(id));
			};
		};

		inline Items::CookRecipe* getRecipe(const std::string recipe_name) {
			std::string lower_name = recipe_name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = availableRecipes.find(lower_name);
			return (item != availableRecipes.end()) ? &item->second : nullptr;
		};

		inline void startCookProcess(const std::string recipe_name) {
			std::string lower_name = recipe_name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			recipeTime = getRecipe(lower_name)->cook_time;
			cookTimer = 0.f;
			cookedFlag = false;
			cookingFlag = true;
			recipeName = lower_name;
		};

		inline void cookingProcess(const float delta) {
			if (cookingFlag) {
				cookTimer += delta;
				std::cout << cookTimer << std::endl;
				if (cookTimer >= recipeTime) {
					cookingFlag = false;
					cookedFlag = true;
					cookTimer = 0.f;
					recipeTime = 0.f;
				};
			};
		};

		inline void resetCookeedFlag() { cookedFlag = false; recipeName.clear(); };
		inline bool getCookingFlag() const { return cookingFlag; };
		inline bool getCookeedFlag() const { return cookedFlag; };
		inline std::string getCookingRecipeName() const { return recipeName; }

	private:
		Items& items;
		std::string recipeName;
		bool cookingFlag = false;
		bool cookedFlag = false;
		float cookTimer = 0.f;
		float recipeTime = 0.f;
};