#pragma once

#include <vector>
#include <string>
#include <optional>

#include "commands.h"

namespace gcode
{
	class reader
	{
		public:
			std::vector<command> read_file(std::string_view const path) const;

		private:
			std::optional<command> read_line(std::string_view const line) const;
			void remove_trailing_spaces(std::string_view & line) const;
			void remove_comment(std::string_view & line) const;

			std::string_view get_command(std::string_view line) const;

			std::vector<command::parameter> get_command_parameters(std::string_view line) const;
	};
}
