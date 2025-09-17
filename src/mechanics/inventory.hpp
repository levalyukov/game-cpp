#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>

class InventoryManager {
	public:
		const int MAX_SLOTS = 4;
		struct Item { std::string caption; std::string icon_path; };
		std::unordered_map<std::string, Item> inventory;
		// Test only //////////////////////////////////////////
		InventoryManager() {
			addItem("bread0", { "Test1", "../../../assets/textures/ui/inventory/items/item_0.png"});
			addItem("bread1", { "Test3", "../../../assets/textures/ui/inventory/items/item_0.png"});
			addItem("bread2", { "Test2", "../../../assets/textures/ui/inventory/items/item_0.png"});
			addItem("bread3", { "Test4", "../../../assets/textures/ui/inventory/items/item_0.png"});
		}
		///////////////////////////////////////////////////////

		inline void addItem(std::string name, struct Item item) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			inventory.emplace(name, item);
		};

		inline Item getItem(std::string name) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(name);
			return (item != inventory.end()) ? item->second : Item{};
		};

		inline void removeItem(std::string name) {
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = inventory.find(name);
			if (item != inventory.end()) inventory.erase(name);
		};
};