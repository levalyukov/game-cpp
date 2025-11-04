#pragma once

#include <map>
#include <string>
#include <stdint.h>

class Items {
	public:
		struct Item {
			unsigned int id = 0;
			std::string icon;
			unsigned int price = 0;
		};

		struct CookRecipe {
			unsigned int id = 0;
			std::wstring title;
			std::wstring description;
			std::string icon;
			unsigned int output = 0;
			float cook_time = 0.f;
			float customer_wait = 0.f;

			CookRecipe() = default;
			CookRecipe(
				const unsigned int _id,
				const std::wstring _title,
				const std::wstring _description,
				const std::string _icon_path,
				const unsigned int _output,
				const float _cook_time,
				const float _customer_wait
			) : id(_id),
				title(_title),
				description(_description),
				output(_output),
				icon(_icon_path),
				cook_time(_cook_time),
				customer_wait(_customer_wait) {};
		};

		inline bool hasRecipe(const uint8_t id) const {
			return (recipes.find(id) != recipes.end()) ? true : false;
		};

		inline bool hasItem(const uint8_t id) const {
			return (items.find(id) != items.end()) ? true : false;
		};

		inline CookRecipe* getRecipeInfo(const uint8_t id) {
			auto item = recipes.find(id);
			return (item != recipes.end()) ? &item->second : nullptr;
		};

		inline Item* getItemInfo(const uint8_t id) {
			auto item = items.find(id);
			return (item != items.end()) ? &item->second : nullptr;
		};

		inline size_t getAllItems() const { return items.size(); };
		inline size_t getAllRecipes() const { return recipes.size(); };

	private:
		std::map<uint16_t, Item> items = {
			{1, {1, "../../../assets/textures/ui/icons/soup-1.png", 100}},
			{2, {2, "../../../assets/textures/ui/icons/soup-2.png", 100}},
			{3, {3, "../../../assets/textures/ui/icons/soup-3.png", 100}},
			{4, {4, "../../../assets/textures/ui/icons/soup-4.png", 100}},
		};

		std::map<uint16_t, CookRecipe> recipes = {
			{1, {1, L"Борщ", L"Recipe Description", "../../../assets/textures/ui/icons/soup-1.png", 1, 1.f, 60.f}},
			{2, {2, L"Куриный", L"Recipe Description", "../../../assets/textures/ui/icons/soup-2.png", 2, 1.f, 60.f}},
			{3, {3, L"Щи", L"Recipe Description", "../../../assets/textures/ui/icons/soup-3.png", 3, 1.f, 60.f}},
			{4, {4, L"Рамен", L"Recipe Description", "../../../assets/textures/ui/icons/soup-4.png", 4, 1.f, 60.f}},
		};
};
