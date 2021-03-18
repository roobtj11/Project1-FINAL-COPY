#include "Volleyball_Team.h"
#include <string>
#include <fstream>
#include <sstream>


void vTeam::add(vplayer a){
	vplayers.push_back(a);
}

void vTeam::add(std::string name, std::string number, std::string position){
	add(vplayer(name, number, position));
}

void vTeam::print_roster()
{
	for (int i = 0; i < vplayers.size(); i++) {
		vplayers[i].print_basic();
	}
}

void vTeam::print_roster_stats(){
	for (int i = 0; i < vplayers.size(); i++) {
		vplayers[i].print_full();
	}
}

std::string vTeam::get_player_nums(int player)
{
	return vplayers[player].get_num();
}


vTeam vTeam::read_from_file(std::string path)
{
	std::ifstream stream;
	stream.open(path);
	//Skip the first line
	std::string line;
	std::getline(stream, line);
	vTeam c;
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

void vTeam::add_player_kill(int player){
	vplayers[player].add_kill();
}

void vTeam::add_player_hitting_error(int player){
	vplayers[player].add_hitting_error();
}

void vTeam::add_player_assist(int player){
	vplayers[player].add_assist();
}

void vTeam::add_player_serve(int player){
	vplayers[player].add_serve();
}

void vTeam::add_player_ace(int player){
	vplayers[player].add_ace();
}

void vTeam::add_player_missed_serve(int player){
	vplayers[player].add_missed_serve();
}

int vTeam::get_kill_to_error(int player)
{
	return vplayers[player].kill_to_error();
}

std::string vTeam::get_player_name(int player)
{
	return vplayers[player].get_name();
}
