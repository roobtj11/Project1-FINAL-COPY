#pragma once
#include "BBall_Players.h"
#include <vector>
#include <iostream>
class bTeam
{
	std::vector<bplayer> bplayers;

public:
	void add(bplayer a);
	void add(std::string name, std::string number, std::string position);

	void print_roster();
	void print_roster_stats();

	std::string get_player_nums(int player);

	static bTeam read_from_file(std::string path);

	void add_player_point(int player, int scored_point);

	void add_player_three_point(int player);

	void add_player_assist(int player);

	void add_player_steal(int player);

	void add_player_rebound(int player);

	void add_player_turnover(int player);

	int get_avg_stat(int player);

	std::string get_player_name(int player);
};