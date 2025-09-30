#pragma once

class IHUD {
public:
    virtual ~IHUD() = default;
    virtual void update() = 0;
};