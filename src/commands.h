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

        enum code
        {
            G0,
            G1,
            G28
        };

        code code;
        std::vector<parameter> parameters;
    };
}
