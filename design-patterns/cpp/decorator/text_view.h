#pragma once

class TextView {
public:
    virtual ~TextView() = default;
    virtual void render() = 0;
}; 