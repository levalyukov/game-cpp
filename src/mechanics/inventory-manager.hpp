#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>

#define MAX_INVENTORY_SLOTS 10

class InventoryManager {
	public:
		struct Item { 
			std::string caption = "";
			std::string icon_path = ""; 
			unsigned __int16 value = 1;
			unsigned __int16 price = 100;
		};
		std::unordered_map<std::string, Item> inventory;

		inline void addItem(const std::string name, struct Item item) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			if (getItem(lower_name) == nullptr) {
				if (inventory.size() < MAX_INVENTORY_SLOTS)
					inventory.emplace(lower_name, item);
			} else addItemValue(lower_name, 1);
		};

		inline Item* getItem(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(lower_name);
			return (item != inventory.end()) ? &item->second : nullptr;
		};

		inline void removeItem(const std::string& name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(lower_name);
			if (item != inventory.end()) inventory.erase(lower_name);
		};

		inline void setItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) getItem(name)->value = value;
		};

		inline void addItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) getItem(name)->value += value;
		};

		inline void subtractItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) {
				if (getItem(name)->value-value > 0) getItem(name)->value -= value;
				else removeItem(name);
			};
		};
};