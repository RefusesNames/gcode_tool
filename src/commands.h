#pragma once

#include <string_view>
#include <vector>

namespace gcode
{
    struct command
    {
        struct parameter
        {
            char name;
            float value;
        };

        enum code : uint32_t
        {
            G28 = 0,
            G0,
            G1
        };

        code code;
        std::vector<parameter> parameters;
    };
}
