#pragma once

#include <string>
#include <unordered_map>

#define MAX_ORDERS 4

class OrdersManager {
	public:
		struct Order {
			unsigned int id;
			std::string title;
			float timeout = 0;
			const std::string iconPath;
			float customer_wait = 0.f;
			bool cookeed = false;
		};

		std::unordered_map<std::string, Order> orders;

		inline void addOrder(const std::string name, const Order order) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			if (orders.size() < MAX_ORDERS) {
				if (getOrder(lower_name) == nullptr) orders.emplace(lower_name, order);
			};
		};

		inline Order* getOrder(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = orders.find(lower_name);
			return (item != orders.end()) ? &item->second : nullptr;
		};

		inline void removeOrder(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = orders.find(lower_name);
			if (item != orders.end()) orders.erase(lower_name);
		};
};