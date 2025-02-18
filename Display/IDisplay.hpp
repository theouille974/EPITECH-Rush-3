#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "../Modules/IModule.hpp"
#include <deque>

namespace Krell {
    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;
        virtual void run(const std::deque<IModule*>& modules) = 0;
        virtual void render(const std::deque<IModule*>& modules) = 0;
    };
}

#endif