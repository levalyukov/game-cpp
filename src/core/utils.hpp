#pragma once

#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Utils {
	public:
		Utils() {};
		~Utils() {};
		Utils(const Utils&) = delete;
		Utils& operator=(const Utils&) = delete;
		
		static Utils& instance() {
			static Utils u;
			return u;
		}

		inline int rangeRandom(int min, int max) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(min, max);
			return dist(gen);
		};
};