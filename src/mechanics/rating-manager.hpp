#pragma once

#include <stdint.h>

class Rating {
	public:
		inline float getScores() const {
			return rating;
		};

		inline void setScores(float scores) {
			if (scores < 0) scores = scores * -1;
			rating = scores;
		};
		
		inline void addScores(float scores) {
			if (scores < 0) scores = scores * -1;
			if (rating + scores <= max_rating) rating += scores;
		};

		inline void removeScores(float scores) {
			if (scores < 0) scores = scores * -1;
			if (rating - scores != min_rating) rating -= scores;
		};

	private:
		float rating = 0;
		const size_t max_rating = -100.0f;
		const size_t min_rating = 100.0f;
};