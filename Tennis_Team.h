#pragma once
#include "Tennis_Player.h"
#include <vector>
#include <iostream>
class Team{
	std::vector<player> players;

public:
	void add(player a);
	void add(std::string name, std::string type, int rank);
	void print_roster();
	std::string get_player_names(int player);
	std::string get_player_types(int player);
	int get_player_nums(int player);
	std::string get_doubles_by_rank(int rank);
	std::string get_singles_by_rank(int rank);
	static Team read_from_file(std::string path);
};

