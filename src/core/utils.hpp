#pragma once

#include <string>
#include <random>
#include <algorithm>

class Utils {
	public:
		Utils() {};
		~Utils() {};
		Utils(Utils& const) = delete;
		Utils& operator=(Utils& const) = delete;
		
		static Utils& instance() {
			static Utils u;
			return u;
		}

		inline int randi_range(int min, int max) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(min, max);
			return dist(gen);
		};

		inline std::string remove_spaces(std::string current_string) {
			current_string.erase(
				std::remove(
					current_string.begin(),
					current_string.end(),
					' '
				),
				current_string.end()
			); return current_string;
		}
};