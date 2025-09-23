#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>

#define MAX_SLOTS 10

class InventoryManager {
	public:
		struct Item { 
			std::string caption = "";
			std::string icon_path = ""; 
			unsigned __int16 value = 1;
		};
		std::unordered_map<std::string, Item> inventory;

		inline void addItem(std::string name, struct Item item) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			if (getItem(name) == nullptr) {
				if (inventory.size() < MAX_SLOTS)
					inventory.emplace(name, item);
			} else addItemValue(name, 1);
		};

		inline Item* getItem(const std::string& name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(lower_name);
			return (item != inventory.end()) ? &item->second : nullptr;
		};

		inline void removeItem(std::string name) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(name);
			if (item != inventory.end()) inventory.erase(name);
		};

		inline void setItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) {
				getItem(name)->value = value;
			};
		};

		inline void addItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) {
				getItem(name)->value += value;
			};
		};

		inline void subtractItemValue(std::string name, unsigned __int8 value = 0) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (getItem(name) != nullptr) {
				getItem(name)->value -= value;
			};
		};
};