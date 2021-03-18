#pragma once
#include <iostream>
class player
{
	std::string name;
	std::string type;
	int rank;
public:
	player(std::string name, std::string type, int rank);

	void print();
	std::string get_name();
	std::string get_type();
	int get_rank();
};

