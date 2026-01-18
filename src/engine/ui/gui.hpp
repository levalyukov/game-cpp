#pragma once
#ifndef GUI_H
#define GUI_H

#include <memory>
#include "elements/label.hpp"

class GUI {
  public:
    inline std::unique_ptr<Label> addLabel() {
      return std::make_unique<Label>();
    };
};

#endif