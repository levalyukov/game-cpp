#pragma once

#include <map>
#include <string>

class Items {
	public:
		struct Item {
			uint8_t id;
			std::string icon;
			unsigned int price;
		};

		struct CookRecipe {
			uint8_t id;
			std::string title;
			std::string description;
			std::string icon_path;
			unsigned int output = 0;
			float cook_time = 0.f;
			float customer_wait = 0.f;

			CookRecipe() = default;
			CookRecipe(
				const uint8_t _id,
				const std::string _title,
				const std::string _description,
				const std::string _icon_path,
				const unsigned int _output,
				const float _cook_time,
				const float _customer_wait
			) : id(_id),
				title(_title),
				description(_description),
				output(_output),
				icon_path(_icon_path),
				cook_time(_cook_time),
				customer_wait(_customer_wait) {};
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
			{1, {1, "../../../assets/textures/ui/icons/soup-1.png", 100}},
			{2, {2, "../../../assets/textures/ui/icons/soup-2.png", 100}},
			{3, {3, "../../../assets/textures/ui/icons/soup-3.png", 100}},
			{4, {4, "../../../assets/textures/ui/icons/soup-4.png", 100}},
		};

		std::map<unsigned __int16, CookRecipe> recipes = {
			{1, {1, "Borsch", "Recipe Description", "../../../assets/textures/ui/icons/soup-1.png", 1, 1.f, 60.f}},
			{2, {2, "Chicken soup", "Recipe Description", "../../../assets/textures/ui/icons/soup-2.png", 2, 5.f, 60.f}},
			{3, {3, "Vegan Soup", "Recipe Description", "../../../assets/textures/ui/icons/soup-3.png", 3, 5.f, 60.f}},
			{4, {4, "Ramen", "Recipe Description", "../../../assets/textures/ui/icons/soup-4.png", 4, 5.f, 60.f}},
		};
};
