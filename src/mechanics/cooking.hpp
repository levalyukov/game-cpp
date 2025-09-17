#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

class CookingManager {
	public:
		struct Recipe {
			std::string title;
			std::string description;
			unsigned __int16 price = 0;
			float cookTime = 0.f;
		};
		std::map<std::string, Recipe> recipes;

		CookingManager() {
			addRecipe("ramen", { "Ramen","Description for ramen",50,5.f });
		};

		inline void addRecipe(std::string nameRecipe, const Recipe newRecipe) {
			if (recipes.size() <= 4 ) {
				std::transform(nameRecipe.begin(), nameRecipe.end(), nameRecipe.begin(), [](unsigned char c) {return std::tolower(c); });
				recipes.emplace(nameRecipe, newRecipe);
			}
		};

		inline Recipe getRecipe(std::string nameRecipe) {
			std::transform(nameRecipe.begin(), nameRecipe.end(), nameRecipe.begin(), [](unsigned char c) {return std::tolower(c); });
			auto recipe = recipes.find(nameRecipe);
			if (recipe != recipes.end()) return recipe->second;
		};

		inline void removeRecipe(std::string nameRecipe) {
			std::transform(nameRecipe.begin(), nameRecipe.end(), nameRecipe.begin(), [](unsigned char c) {return std::tolower(c); });
			if (recipes.find(nameRecipe) != recipes.end()) {
				recipes.erase(nameRecipe);
			}
		};
};