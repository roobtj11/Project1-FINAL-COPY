#pragma once
#include <iostream>
class bplayer
{
	std::string name;
	std::string number;
	std::string position;
	int points;
	int three_points;
	int assists;
	int steals;
	int rebounds;
	int turnovers;

public:
	bplayer(std::string name, std::string number, std::string position, int points, int three_pointers, int assists, int steals, int rebounds, int turnovers);
	bplayer(std::string name, std::string number, std::string position);
	void print_basic();
	void print_full();

	std::string get_name();
	std::string get_num();
	int get_point();
	int get_three_point();
	int get_assist();
	int get_steal();
	int get_rebound();
	int get_turnover();
	void add_point(int scored_points);
	void add_three_point();
	void add_assist();
	void add_steal();
	void add_rebound();
	void add_turnover();
	int avg_stat();
};
