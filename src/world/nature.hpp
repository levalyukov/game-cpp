#pragma once

class Nature {
	public:
		inline static Nature& instance() {
			static Nature n;
			return n;
		}

	private:
		Nature() {};
		~Nature() {};
		Nature(Nature& const) = delete;
		Nature& operator=(Nature& const) = delete;
};