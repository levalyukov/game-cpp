#pragma once
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <map>
#include <vector>
#include <string.h>

#include "gui.hpp"
#include "elements/element.hpp"

class UIManager {
	public:
    std::vector<UIElement*> elementsSort;
    std::map<std::string, std::unique_ptr<UIElement>> elements;

    inline void addElement(std::string name, std::unique_ptr<UIElement> element) {};
    inline void removeElement(std::string name) {};
    inline void getElement(std::string name) {};
    inline void update(void) {};

	private:
};

#endif 