#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class EntityManager {
	public:
		EntityManager(void) {};

    inline void update(void) {
      printf("Hello from EntityManager!\n\t");
    };

	private:
};

#endif ENTITY_MANAGER_H