#pragma once

class EconomyManager {
	public:
		inline int getMoney() const { return money; };
		inline void setMoney(const int value) { if (value >= 0) money = value; };
		inline void addMoney(const int value) { if (value >= 0) money += value; };
		inline void removeMoney(const int value) {
			if (value >= 0) {
				if (value <= money) money -= value;
				else money = 0;
			};
		};
		inline void removeMoney(const int value) { if (money >= value) money -= value; };

	private:
		unsigned __int32 money = 0;
};