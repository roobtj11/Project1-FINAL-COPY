#include "BBall_Team.h"
#include <string>
#include <fstream>
#include <sstream>


void bTeam::add(bplayer a) {
	bplayers.push_back(a);
}

void bTeam::add(std::string name, std::string number, std::string position) {
	add(bplayer(name, number, position));
}

void bTeam::print_roster()
{
	for (unsigned int i = 0; i < bplayers.size(); i++) {
		bplayers[i].print_basic();
	}
}

void bTeam::print_roster_stats() {
	for (unsigned int i = 0; i < bplayers.size(); i++) {
		bplayers[i].print_full();
	}
}

std::string bTeam::get_player_nums(int player)
{
	return bplayers[player].get_num();
}


bTeam bTeam::read_from_file(std::string path)
{
	std::ifstream stream;
	stream.open(path);
	//Skip the first line
	std::string line;
	std::getline(stream, line);
	bTeam c;
	//Read every line in the file
	while (std::getline(stream, line)) { // this gets us the whole row

		std::stringstream ss(line);
		std::string substr;
		//get the Name
		std::string name;
		std::getline(ss, name, ',');
		//Get the Number
		std::getline(ss, substr, ',');

		//get the Position
		std::string position;
		std::getline(ss, position, ',');

		c.add(name, substr, position);
	}
	stream.close();
	return c;
}

void bTeam::add_player_point(int player, int scored_point) {
	bplayers[player].add_point(scored_point);
}

void bTeam::add_player_three_point(int player) {
	bplayers[player].add_three_point();
}

void bTeam::add_player_assist(int player) {
	bplayers[player].add_assist();
}

void bTeam::add_player_steal(int player) {
	bplayers[player].add_steal();
}

void bTeam::add_player_rebound(int player) {
	bplayers[player].add_rebound();
}

void bTeam::add_player_turnover(int player) {
	bplayers[player].add_turnover();
}

int bTeam::get_avg_stat(int player)
{
	return bplayers[player].avg_stat();
}

std::string bTeam::get_player_name(int player)
{
	return bplayers[player].get_name();
}