#include <iostream>
#include <string>
#include "commands.hpp"
// Basic commmands:
// Read: commmand: prg.exe read file

void line(int);

void checkCommands(int, char *commands[]);

int main(int args, char *argv[])
{
	if (args > 1)
	{
		checkCommands(args, argv);
	}
	else
	{
		line(1);
		std::cout << "\033[31mNo Commmand Provided\033[0m" << std::endl;
		line(1);
	}

	return 0;
}


void checkCommands(int args, char *commands[])
{
	std::string command = commands[1];
	if (command == "read")
	{
		read(args, commands);
	}
	else if (command == "search")
	{
		search(args, commands);
	}
	else if (command == "write")
	{
		write(args, commands);
	}
	else if (command == "delete")
	{
		Delete(args, commands);
	}
	else if (command == "append") {
		append(args, commands);
	}
	else if (command == "--help")
	{
		help();
	}
	else
	{
		line(1);
		std::cerr << "\033[31m\"" << commands[1] << "\" " << "Command not recognized" << "\033[0m" << std::endl;
		line(1);
	}
}
