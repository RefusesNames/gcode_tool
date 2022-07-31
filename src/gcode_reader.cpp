#include "gcode_reader.h"

#include <iostream>
#include <fstream>
#include <string>

namespace gcode
{
	std::vector<command> reader::read_file(std::string_view const path) const
	{
		std::cout << "Reading from: " << path << std::endl;
		std::ifstream stream(path.data());
		std::vector<command> commands;

		if (!stream.is_open())
		{
			std::cerr << "Failed to open file: " << path << std::endl;
			return commands;
		}

		for (std::string line; std::getline(stream, line);)
		{
			auto maybeCommand = read_line(line);
			if (maybeCommand.has_value())
				commands.push_back(maybeCommand.value());
		}

		std::cout << "Finished reading from " << path << std::endl;
		return commands;
	}

	std::optional<command> reader::read_line(std::string_view line) const
	{
		remove_comment(line);
		remove_trailing_spaces(line);

		if (line.size() == 0)
			return std::nullopt;

		auto command = get_command(line);

		if (command == "G0")
		{
			struct command command;
			command.code = command::G0;
			command.parameters = get_command_parameters(line);
			return command;
		}

		if (command == "G1")
		{
			struct command command;
			command.code = command::G1;
			command.parameters = get_command_parameters(line);
			return command;
		}

		if (command == "G28")
		{
			struct command command;
			command.code = command::G28;
			command.parameters = get_command_parameters(line);
			return command;
		}

		return std::nullopt;
	}

	void reader::remove_trailing_spaces(std::string_view & line) const
	{
		auto index = line.find_last_not_of(" ");
		if (index != std::string::npos)
			line.remove_suffix(line.size() - index - 1);
	}

	void reader::remove_comment(std::string_view & line) const
	{
		auto index = line.find_first_of(";;");
		if (index != std::string::npos)
			line.remove_suffix(line.size() - index);
	}

	std::string_view reader::get_command(std::string_view line) const
	{
		auto index = line.find_first_of(" ");
		if (index != std::string::npos)
			line.remove_suffix(line.size() - index);
		return line;
	}

	std::vector<command::parameter> reader::get_command_parameters(std::string_view line) const
	{
		auto index_of_first_space = line.find_first_of(" ");
		if (index_of_first_space == std::string::npos)
			return {};

		line.remove_prefix(index_of_first_space + 1);

		size_t index_behind_parameter;
		std::vector<command::parameter> commands;
		do {
			index_behind_parameter = line.find_first_of(" ");
			auto parameter_value = line.substr(1, index_behind_parameter);
			commands.push_back(command::parameter { line[0], std::stof(parameter_value.data()) });

			line.remove_prefix(index_behind_parameter + 1);
		} while (index_behind_parameter != std::string::npos);

		return commands;
	}
}
