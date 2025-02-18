#ifndef HOSTMODULE_HPP
#define HOSTMODULE_HPP

#include "AModule.hpp"

namespace Krell {
    class HostModule : public AModule
    {
    public:
        HostModule();
        ~HostModule();

        void update() override;
    };
}

#endif