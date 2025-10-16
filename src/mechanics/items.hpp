#pragma once

#include <map>
#include <string>

class Items {
	public:
		struct Item {
			std::string icon;
			unsigned int price;
		};

		struct CookRecipe {
			std::string title;
			std::string description;
			std::string icon_path;
			unsigned int output_item = 0;
			float cooking_time = 0.f;

			CookRecipe() = default;
			CookRecipe(
				const std::string item_title,
				const std::string item_description,
				const std::string item_icon_path,
				const unsigned int output,
				const float cook_time
			) : title(item_title),
				description(item_description),
				output_item(output),
				icon_path(item_icon_path),
				cooking_time(cook_time) {};
		};

		inline bool hasRecipe(const unsigned __int16 id) {
			return (recipes.find(id) != recipes.end()) ? true : false;
		};

		inline CookRecipe* getRecipeInfo(const unsigned __int16 id) {
			auto item = recipes.find(id);
			return (item != recipes.end()) ? &item->second : nullptr;
		};

		inline Item* getItemInfo(const unsigned __int16 id) {
			auto item = items.find(id);
			return (item != items.end()) ? &item->second : nullptr;
		};

		inline size_t getItemsSize() const { return items.size(); };
		inline size_t getRecipesSize() const { return recipes.size(); };

	private:
		std::map<unsigned __int16, Item> items = {
			{1, {"../../../assets/textures/ui/icons/soup-1.png", 100}},
			{2, {"../../../assets/textures/ui/icons/soup-2.png", 100}},
			{3, {"../../../assets/textures/ui/icons/soup-3.png", 100}},
			{4, {"../../../assets/textures/ui/icons/soup-4.png", 100}},
		};

		std::map<unsigned __int16, CookRecipe> recipes = {
			{1, {"Borsch", "Recipe Description", "../../../assets/textures/ui/icons/soup-1.png", 1, 5.f}},
			{2, {"Chicken soup", "Recipe Description", "../../../assets/textures/ui/icons/soup-2.png", 2, 5.f}},
			{3, {"Vegan Soup", "Recipe Description", "../../../assets/textures/ui/icons/soup-3.png", 3, 5.f}},
			{4, {"Ramen", "Recipe Description", "../../../assets/textures/ui/icons/soup-4.png", 4, 5.f}},
		};
};
