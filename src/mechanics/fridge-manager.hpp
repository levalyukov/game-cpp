#pragma once

#include <map>
#include <string>
#include <algorithm>

class FridgeManager {
	public:
		struct Item {
			std::string title = "";
			const std::string icon = "";
			unsigned __int8 value = 0;
		};

		std::map<std::string, Item> storage;

		inline void addItem(const std::string name, const struct Item product) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), 
				[](unsigned char c) {return std::tolower(c); });
			if (getItem(lower_name) == nullptr) {
				storage.emplace(lower_name, product);
			} else getItem(lower_name)->value += 1;
		};

		inline Item* getItem(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), 
				[](unsigned char c) {return std::tolower(c); });
			auto item = storage.find(lower_name);
			return (item != storage.end()) ? &item->second : nullptr;
		};

		inline void removeItem(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = storage.find(lower_name);
			if (item != storage.end()) storage.erase(item);
		};
};