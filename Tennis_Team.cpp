#include "Tennis_Team.h"
#include <string>
#include <fstream>
#include <sstream>

void Team::add(player a){
	players.push_back(a);
}

void Team::add(std::string name, std::string type, int rank){
	add(player(name, type, rank));
}

void Team::print_roster() {
	std::vector<int> one_doubles;
	std::vector<int> two_doubles;
	std::vector<int> three_doubles;
	std::vector<int> singles = { 3,6,9,10 };
	for (int i = 0; i < players.size(); i++) {
		if (players[i].get_type() == "Doubles") {
			if (players[i].get_rank() == 1) {
				one_doubles.push_back(i);
			}
			else if (players[i].get_rank() == 2) {
				two_doubles.push_back(i);
			}
			else if (players[i].get_rank() == 3) {
				three_doubles.push_back(i);
			}
		}
		else {
			int rank = players[i].get_rank() - 1;
			singles[rank] = i;
		}
	}

	std::cout << std::endl << players[one_doubles[0]].get_name() << " and " << players[one_doubles[1]].get_name() << " play 1 doubles." << std::endl;
	std::cout << players[two_doubles[0]].get_name() << " and " << players[two_doubles[1]].get_name() << " play 2 doubles." << std::endl;
	std::cout << players[three_doubles[0]].get_name() << " and " << players[three_doubles[1]].get_name() << " play 3 doubles." << std::endl << std::endl;
	for (int i = 0; i < singles.size(); i++) {
		std::cout << players[singles[i]].get_name() << " plays " << players[singles[i]].get_rank() << " singles." << std::endl;
	}
	std::cout << std::endl << std::endl;
}

std::string Team::get_player_names(int player)
{
	return players[player].get_name();
}

std::string Team::get_player_types(int player)
{
	return players[player].get_type();
}

int Team::get_player_nums(int player)
{
	return players[player].get_rank();
}

std::string Team::get_doubles_by_rank(int rank)
{
	std::string doubles_team;
	
	std::vector<int> one_doubles;
	std::vector<int> two_doubles;
	std::vector<int> three_doubles;
	std::vector<int> singles = { 3,6,9,10 };
	std::vector<int> doubles_teams[3] = { one_doubles, two_doubles, three_doubles };
	for (int i = 0; i < players.size(); i++) {
		if (players[i].get_type() == "Doubles") {
			if (players[i].get_rank() == 1) {
				doubles_teams[0].push_back(i);
			}
			else if (players[i].get_rank() == 2) {
				doubles_teams[1].push_back(i);
			}
			else if (players[i].get_rank() == 3) {
				doubles_teams[2].push_back(i);
			}
		}
	}
	doubles_team = players[doubles_teams[rank - 1][0]].get_name() + " and " + players[doubles_teams[rank-1][1]].get_name();
	return doubles_team;
}

std::string Team::get_singles_by_rank(int rank)
{
	std::vector<int> singles = { 3,6,9,10 };

	for (int i = 0; i < players.size(); i++) {
		if (players[i].get_type() == "Singles") {
			int set_rank = players[i].get_rank() - 1;
			singles[set_rank] = i;
		}
	}
	return players[singles[rank - 1]].get_name();
}

Team Team::read_from_file(std::string path)
{
	std::ifstream stream;
	stream.open(path);
	//Skip the first line
	std::string line;
	std::getline(stream, line);
	Team c;
	//Read every line in the file
	while (std::getline(stream, line)) { // this gets us the whole row

		std::stringstream ss(line);
		//get the Name
		std::string name;
		std::getline(ss, name, ',');
		//Get the Number
		std::string type;
		std::getline(ss, type, ',');

		//get the Position
		std::string substr;
		int rank;
		std::getline(ss, substr, ',');
		rank = stoi(substr);

		c.add(name, type, rank);
	}
	stream.close();
	return c;
}
