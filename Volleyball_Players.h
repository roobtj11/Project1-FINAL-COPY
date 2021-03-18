#pragma once
#include <iostream>
class vplayer
{
	std::string name;
	std::string number;
	std::string position;
	int kills;
	int hitting_errors;
	int assists;
	int serves;
	int aces;
	int missed_serves;

public:
	vplayer(std::string name, std::string number, std::string position, int kills, int hitting_errors, int assists, int serves, int aces, int missed_serves);
	vplayer(std::string name, std::string number, std::string position);
	void print_basic();
	void print_full();

	std::string get_name();
	std::string get_num();
	int get_kill();
	int get_hitting_error();
	int get_assist();
	int get_serve();
	int get_ace();
	int get_missed_serve();
	void add_kill();
	void add_hitting_error();
	void add_assist();
	void add_serve();
	void add_ace();
	void add_missed_serve();
	int kill_to_error();
};



