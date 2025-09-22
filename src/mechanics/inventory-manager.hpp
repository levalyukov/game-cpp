#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>

#define MAX_SLOTS 10

class InventoryManager {
	public:
		struct Item { 
			std::string caption = "";
			std::string icon_path = ""; 
			unsigned __int8 value = 1;
		};
		std::unordered_map<std::string, Item> inventory;

		inline void addItem(std::string name, struct Item item) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			if (getItem(name) == nullptr) {
				if (inventory.size() < MAX_SLOTS)
					inventory.emplace(name, item);
			};
		};

		inline Item* getItem(std::string name) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(name);
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