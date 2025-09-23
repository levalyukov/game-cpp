#pragma once

class Economy {
	public:
		inline void setMoney(int value) { if (value >= 0) money = value; };
		inline void addMoney(int value) { if (value >= 0) money += value; };
		inline void removeMoney(int value) { 
			if (value >= 0) {
				if (value <= money) {
					money -= value;
				} else {
					money = 0;
				}
			} 
		}
		inline int getMoney() const { return money; };

	private:
		unsigned int money = 0;
};