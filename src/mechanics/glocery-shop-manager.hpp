#pragma once
#define MAX_GLOCERY_SHOP_SLOTS 4
#include <map>

class GloceryShopManager {
	public:
		struct Product {
			std::string name = "";
			unsigned __int32 price = 0;
			unsigned __int16 value = 1;
		};

		std::map<std::string, Product> shop;

		GloceryShopManager() { initStore(); };

		inline void initStore() {
			addProduct("potato", { "Potato", 100 });
			addProduct("tomato", { "Tomato", 100 });
			addProduct("greens", { "Greens", 100 });
			addProduct("onion", { "Onion", 100 });
		};

		inline void addProduct(const std::string name, const Product product) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			if (getProduct(lower_name) == nullptr) {
				shop.emplace(lower_name, product);
			} else getProduct(lower_name)->value += 1;
		};

		inline Product* getProduct(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = shop.find(lower_name);
			return (item != shop.end()) ? &item->second : nullptr;
		};

		inline void removeProduct(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto item = shop.find(lower_name);
			if (item != shop.end()) shop.erase(lower_name);
		};
};