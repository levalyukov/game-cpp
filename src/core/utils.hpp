#pragma once

#include <random>

class Utils {
	public:
		inline int randi_range(int min, int max) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(min, max);
			return dist(gen);
		};
};