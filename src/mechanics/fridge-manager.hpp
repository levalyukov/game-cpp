#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <stdint.h>

class FridgeManager {
	public:
		struct Item {
			std::wstring title;
			const std::string icon;
			uint8_t value = 0;
		};

		std::map<uint32_t, Item> storage;

		inline void addItem(const uint32_t id, const struct Item product) {
			if (getItem(id) == nullptr) storage.emplace(id, product); 
			else getItem(id)->value += 1;
		};

		inline Item* getItem(const uint32_t id) {
			auto item = storage.find(id);
			return (item != storage.end()) ? &item->second : nullptr;
		};

		inline void removeItem(const uint32_t id) {
			auto item = storage.find(id);
			if (item != storage.end()) storage.erase(item);
		};
};