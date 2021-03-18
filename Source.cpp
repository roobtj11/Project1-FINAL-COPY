#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Source.h"

void volleyball();
void start();

void Startup_Script() {
	std::cout << "                       Welcome to the" << std::endl;
	std::cout << "                       SPORTS MACHINE" << std::endl;
	std::cout << "             Made by: Tyler Roob and Jack Schnor" << std::endl;
	std::cout << "- This program will let you, Keep track of team rosters for -" << std::endl
		<< "              Volleyball, Basketball, and Tennis\n " << std::endl << std::endl;
}

std::string Sport_Select(std::string sport) {
	std::cout << "Which sport would you like to access?" << std::endl;
	std::getline(std::cin, sport);

	return(sport);
}

void Menu_Direct(std::string choice)
{
	if (choice == "Basketball")
	{
		basketball();
		start();
	}
	else if (choice == "Volleyball")
	{
		volleyball();
		start();
	}
	else if (choice == "Tennis")
	{
		tennis();
		start();
	}
}

void start() {
	std::cin.clear();
	std::cin.ignore(1);
	Startup_Script();
	std::string selection;
	selection = Sport_Select(selection);
	std::cout << "you chose " << selection << std::endl;
	Menu_Direct(selection);
}

int main() {
	start();
	return 0;
}