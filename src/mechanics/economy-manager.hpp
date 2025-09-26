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

	private:
		unsigned __int32 money = 0;
};