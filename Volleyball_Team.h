#pragma once
#include "Volleyball_Players.h"
#include <vector>
#include <iostream>
class vTeam
{
	std::vector<vplayer> vplayers;

public:
	void add(vplayer a);
	void add(std::string name, std::string number, std::string position);

	void print_roster();
	void print_roster_stats();

	std::string get_player_nums(int player);

	static vTeam read_from_file(std::string path);

	void add_player_kill(int player);

	void add_player_hitting_error(int player);

	void add_player_assist(int player);

	void add_player_serve(int player);

	void add_player_ace(int player);

	void add_player_missed_serve(int player);

	int get_kill_to_error(int player);

	std::string get_player_name(int player);
};

