#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

class Cooking {
	public:
		Cooking() {
			addRecipe("ramen", { "Ramen", 50 });
			addRecipe("solyanka", { "Solyanka", 100 });
			addRecipe("borsch", { "Borsch", 150 });
			addRecipe("miso-soup", { "Miso soup", 1350 });
		};
		~Cooking() {};
		Cooking(Cooking& const) = delete;
		Cooking& operator=(Cooking& const) = delete;

		struct Recipe { std::string title; int price; };
		std::map<std::string, Recipe> recipes;

		inline static Cooking& instance() {
			static Cooking c;
			return c;
		};

		inline void addRecipe(std::string name_recipe, Recipe new_recipe) {
			std::transform(name_recipe.begin(), name_recipe.end(), name_recipe.begin(), [](unsigned char c) {return std::tolower(c); });
			recipes.emplace(name_recipe, new_recipe);
		};

		inline Recipe getRecipe(std::string name_recipe) {
			std::transform(name_recipe.begin(), name_recipe.end(), name_recipe.begin(), [](unsigned char c) {return std::tolower(c); });
			auto recipe = recipes.find(name_recipe);
			if (recipe != recipes.end()) return recipe->second;
		};

		inline void removeRecipe(std::string name_recipe) {
			std::transform(name_recipe.begin(), name_recipe.end(), name_recipe.begin(), [](unsigned char c) {return std::tolower(c); });
			if (recipes.find(name_recipe) != recipes.end()) {
				recipes.erase(name_recipe);
			}
		};
};