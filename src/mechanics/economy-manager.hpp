#pragma once

#include <stdint.h>

class EconomyManager {
	public:
		inline uint32_t getMoney() const { return money; };
		inline void setMoney(const uint32_t value) { if (value >= 0) money = value; };
		inline void addMoney(const uint32_t value) { if (value >= 0) money += value; };
		inline void removeMoney(const uint32_t value) { if (money >= value) money -= value; };

	private:
		uint32_t money = 0;
};