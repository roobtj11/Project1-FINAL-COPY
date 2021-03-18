#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <sstream>
#include "Source.h"
#include "Volleyball_Players.h"
#include "Volleyball_Team.h"

vTeam MVP;
vTeam MVC;
vTeam EPIC;
vTeam RVA;
vTeam Spike;
vTeam Capitol;
vTeam Sting;
vTeam Adversity;
const int num_teams = 8;
const int num_side = 6;
const int num_rost = 11;
std::string vteam_names[num_teams];
std::vector<vTeam> teams;
std::string vteams_seeds[8];

std::string serving;


std::string vhome_name;
std::string home_lineup[num_side];

std::string vaway_name;
std::string away_lineup[num_side];
int vhome_score, vaway_score;
int vhome_int, vaway_int;
bool vgame_played;

void vget_team_info();
void vprint_rosters();
void vget_teams_seed();
void volleyball_menu();
void vteam_lookup();
void vtournament_bracket();
void start_game();
void get_game_information();
void get_lineup(int team, std::string lineup[], std::string team_name);
void record_game();
void visual_court();
void record_visual_court();
void make_sub(int team, std::string lineup[], std::string team_name);

void point_play();
void point_won(int winning_team, std::string winning_team_name, std::string winning_lineup[], int losing_team, std::string losing_team_name, std::string losing_lineup[]);
void team_rotate(std::string lineup[]);
void get_team_mvp();
void get_overall_mvp();


void  volleyball() {
	vgame_played = false;
	vget_team_info();

	vget_teams_seed();

	volleyball_menu();
	return;
}
void vget_team_info(){
	MVP = vTeam::read_from_file("Volleyball\\MVP.csv");
	MVC = vTeam::read_from_file("Volleyball\\MVC.csv");
	EPIC = vTeam::read_from_file("Volleyball\\EPIC.csv");
	Adversity = vTeam::read_from_file("Volleyball\\Adversity.csv");
	Spike = vTeam::read_from_file("Volleyball\\Spike.csv");
	Sting = vTeam::read_from_file("Volleyball\\Sting.csv");
	RVA = vTeam::read_from_file("Volleyball\\RVA.csv");
	Capitol = vTeam::read_from_file("Volleyball\\Capitol.csv");
	
	teams.push_back(MVP);
	teams.push_back(MVC);
	teams.push_back(EPIC);
	teams.push_back(Adversity);
	teams.push_back(Spike);
	teams.push_back(Sting);
	teams.push_back(RVA);
	teams.push_back(Capitol);

	vteam_names[0] = "MVP";
	vteam_names[1] = "MVC";
	vteam_names[2] = "EPIC";
	vteam_names[3] = "Adversity";
	vteam_names[4] = "Spike";
	vteam_names[5] = "Sting";
	vteam_names[6] = "RVA";
	vteam_names[7] = "Capitol";
}
void vprint_rosters() {
	for (int i = 0; i < teams.size(); i++) {
		std::cout << "\t" << vteam_names[i] << std::endl;
		teams[i].print_roster();
		std::cout << std::endl;
	}
}
void vget_teams_seed() {
	std::cout << "There are " << num_teams << " teams here at the tournament today. \n";
	for (int i = 0; i < num_teams; i++) {
		std::cout << i + 1 << ")\t" << vteam_names[i] << std::endl;
	}
	std::cout << "Please enter each teams seed 1 - 8:" << std::endl;
	int check[8] = {};
	bool valid;
	for (int i = 0; i < 8; i++)
	{
	checkpoint:
		valid = true;
		std::cout << vteam_names[i] << ".\t";
		std::string str_seed;
		std::getline(std::cin, str_seed);
		int seed;
		try {
			seed = std::stoi(str_seed);
		}
		catch (...) {
			std::cout << "Please make sure you enter a number" << std::endl;
			goto checkpoint;
		}
		for (int v = 0; v < 8; v++) {
			if (seed == check[v] || seed < 1 || seed > 8) {
				valid = false;
			}
		}
		if (valid) {
			vteams_seeds[seed - 1] = vteam_names[i];
			check[i] = seed;
		}
		else {
			std::cout << "Please make sure to only enter each seed number once, and that the seed given is between 1 and 8." << std::endl << std::endl;
			goto checkpoint;
		}
	}
	std::cout << "\n\n\n";
}
void volleyball_menu() {
	std::cout << "has a game been played? " << vgame_played << std::endl;
	
	std::cout << "Do you want to (enter the corresponding number)\n1) look at a specific teams roster, \n2) Tournament bracket, \n3) Record a game\n4) Get Team MVP\n5) Get Overall MVP\n6) Leave Volleyball" << std::endl;
	int choice;
	try {
		std::cin >> choice;
		if (choice < 1 || choice > 6){
			throw (1);
		}
	}
	catch (...) {
		std::cout << "Please enter an appropriate value" << std::endl << std::endl;
		volleyball_menu();
	}
	if (choice == 1) {
		vteam_lookup();
	}
	else if (choice == 2) {
		vtournament_bracket();
	}
	else if (choice == 3){
		vgame_played = true;
		start_game();
	}
	else if (choice == 4) {
		get_team_mvp();
	}
	else if (choice == 5) {
		get_overall_mvp();
	}
	else if (choice == 6) {
		return;
	}
}
void vteam_lookup() {
	std::cout << "What team do you want to look up?" << std::endl;
	std::string lookup_team;
	std::cin >> lookup_team;
	bool valid = false;
	for (int i = 0; i < teams.size(); i++) {
		if (lookup_team == vteam_names[i]) {
			valid = true;
			teams[i].print_roster_stats();
		}
	}
	if (valid) {
		std::cout << "Enter 1 when you are done looking." << std::endl;
		std::string done;
		std::cin >> done;
		volleyball_menu();
	}
	else {
		std::cout << "Please make sure you enter the team name correctly. If you need the list of names again enter 1 otherwise enter any other number followed by enter.";
		std::string names;
		std::cin >> names;
		if (names == "1") {
			for (int i = 0; i < num_teams; i++) {
				std::cout << i + 1 << ")\t" << vteam_names[i] << std::endl;
			}
		}
		vteam_lookup();
	}	
}
void vtournament_bracket() {
	std::cout << std::endl << std::endl << std::endl;
	std::cout << vteams_seeds[0] << "          " << vteams_seeds[1] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << vteams_seeds[2] << "          " << vteams_seeds[3] << std::endl;
	std::cout << std::endl << "     __________" << std::endl << std::endl;
	std::cout << vteams_seeds[4] << "          " << vteams_seeds[5] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << vteams_seeds[6] << "          " << vteams_seeds[7] << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	volleyball_menu();
}
void start_game(){
	
	get_game_information();
	get_lineup(vhome_int, home_lineup, vhome_name);
	get_lineup(vaway_int, away_lineup, vaway_name);

	vhome_score = 0;
	vaway_score = 0;

	while (vhome_score != 25 && vaway_score != 25) {
		visual_court();
		point_play();
	}
	if (vhome_score == 25) {
		std::cout << vhome_name << " won the game! The score was " << vhome_score << "-" << vaway_score << "." << std::endl;
	}
	else {
		std::cout << vaway_name << " won the game! The score was " << vaway_score << "-" << vhome_score << "." << std::endl;
	}
	
	volleyball_menu();
}
void get_game_information() {
	for (int t = 0; t < 2; t++) {
		std::cout << "Who is the ";
		if (t == 0) {
			std::cout << "Home";
		}
		else { 
			std::cout << "Away";
		} 
		std::cout << " team?" << std::endl;

		std::string team_input;
		std::cin >> team_input;
		bool valid = false;
		for (int i = 0; i < teams.size(); i++) {
			if (team_input == vteam_names[i]) {
				valid = true;
				if (t == 0) {
					vhome_name = team_input;

					vhome_int = i;
				}
				else{
					vaway_name = team_input;

					vaway_int = i;
				}
			}
		}
		if (!valid) {
			std::cout << "Make sure to enter an accepted team name." << std::endl;
			get_game_information();
		}
	}

whos_serving:
	std::cout << "Who is serving?" << std::endl;
	std::getline(std::cin, serving);
	if (serving == vhome_name || serving == vaway_name) {
		return;
	}
	else{
		std::cout << "The serving team should either be: " << vhome_name << " or " << vaway_name << std::endl;
		goto whos_serving;
	}
}
void get_lineup(int team, std::string lineup[], std::string team_name){
	std::cout << "Here is the Roster for " << team_name << std::endl;
	teams[team].print_roster();
	for (int i = 0; i < num_side; i++) {
	checkpoint:
		std::cout << "Who is in position " << i + 1 << "? Enter their number:\t";
		std::string number_str;
		std::getline(std::cin, number_str);
		bool valid = false;
		for (int p = 0; p < num_rost; p++) {
			std::string player_num = teams[team].get_player_nums(p);
			if (player_num == number_str) {
				lineup[i] = number_str;
				valid = true;
			}
		}
		if (!valid) {
			std::cout << "Please enter a number of a player on the roster" << std::endl;
			goto checkpoint;
		}
	}
}
void make_sub(int team, std::string lineup[], std::string team_name) {
substitution:
	std::cout << std::endl << "Here is the current court:" << std::endl;
	visual_court();
	std::cout << "What Position do you want to sub for " << team_name << ": (enter 1-6)\t"<< std::endl;
	std::string pos_str;
	int pos;
	std::getline(std::cin, pos_str);
	pos = std::stoi(pos_str);
	if (pos < 7 && pos > 0) {
		std::cout << "Here is the roster for " << team_name << "." << std::endl;
		teams[team].print_roster();
		std::cout << "What number do you want going in ? " << std::endl;
		std::string number_str;
		std::getline(std::cin, number_str);
		for (int p = 0; p < num_rost; p++) {
			std::string player_num = teams[team].get_player_nums(p);
			if (player_num == number_str) {
				lineup[pos-1] = number_str;
			}
		}
	}
	else {
		std::cout << "Make sure to enter a number between 1 and 6" << std::endl;
		goto substitution;
	}
	
}
void record_game() {
	std::ofstream fw("Game_Record.txt", std::ofstream::out);
	
	if (fw.is_open())
	{
		fw << "Here is the starting lineup" << std::endl;
		fw.close();
	}
	visual_court();

	

}
void visual_court() {
	std::cout << " ____________________ " << std::endl;
	std::cout << "|      |      |      |" << std::endl;
	std::cout << "|  " << home_lineup[0] << "  |  " << home_lineup[5] << "  |  " << home_lineup[4] << "  |" << std::endl;
	std::cout << "|------|------|------|\t" << vhome_name;
	if (serving == vhome_name) { std::cout << "\tServing"; } std::cout << std::endl;
	std::cout << "|  " << home_lineup[1] << "  |  " << home_lineup[2] << "  |  " << home_lineup[3] << "  |" << std::endl;
	std::cout << "======================" << "\t " << vhome_name << " " << vhome_score << "-" << vaway_score << " " << vaway_name << std::endl;
	std::cout << "|  " << away_lineup[3] << "  |  " << away_lineup[2] << "  |  " << away_lineup[1] << "  |" << std::endl;
	std::cout << "|------|------|------|\t" << vaway_name;
	if (serving == vaway_name) { std::cout << "\tServing"; } std::cout << std::endl;
	std::cout << "|  " << away_lineup[4] << "  |  " << away_lineup[5] << "  |  " << away_lineup[0] << "  |" << std::endl;
	std::cout << "|______|______|______|" << std::endl;
}
void record_visual_court() {
	std::ofstream fw("Game_Record.txt", std::ofstream::app);
	fw << " ____________________ " << std::endl;
	fw << "|      |      |      |" << std::endl;
	fw << "|  " << home_lineup[0] << "  |  " << home_lineup[5] << "  |  " << home_lineup[4] << "  |" << std::endl;
	fw << "|------|------|------|\t" << vhome_name;
	if (serving == vhome_name) { fw << "\tServing"; } fw << std::endl;
	fw << "|  " << home_lineup[1] << "  |  " << home_lineup[2] << "  |  " << home_lineup[3] << "  |" << std::endl;
	fw << "======================" << "\t " << vhome_name << " " << vhome_score << "-" << vaway_score << " " << vaway_name << std::endl;
	fw << "|  " << away_lineup[3] << "  |  " << away_lineup[2] << "  |  " << away_lineup[1] << "  |" << std::endl;
	fw << "|------|------|------|\t" << vaway_name;
	if (serving == vaway_name) { fw << "\tServing"; } fw << std::endl;
	fw << "|  " << away_lineup[4] << "  |  " << away_lineup[5] << "  |  " << away_lineup[0] << "  |" << std::endl;
	fw << "|______|______|______|" << std::endl;
	fw.close();
}
void point_play() {
substitution:
	std::cout << "Do you want to sub any players? (Enter Yes, or anything else)" << std::endl;
	
winner:
	std::cout << "Either enter who won the point or type SUB to make a substitution:" << std::endl;
	std::string point_winner;
	std::getline(std::cin, point_winner);

	if (point_winner == vhome_name) {
		point_won(vhome_int, vhome_name, home_lineup, vaway_int, vaway_name, away_lineup);
		if (serving == vaway_name) {
			serving = vhome_name;
			team_rotate(home_lineup);
		}
		vhome_score++;
	}
	else if(point_winner == vaway_name) {
		point_won(vaway_int, vaway_name, away_lineup, vhome_int, vhome_name, home_lineup);
		if (serving == vhome_name) {
			serving = vaway_name;
			team_rotate(away_lineup);
		}
		vaway_score++;
	}
	else if (point_winner == "SUB") {
		std::cout << "What team is making the sub?" << std::endl;
		std::string subbing_team;
		std::getline(std::cin, subbing_team);
		if (subbing_team == vhome_name) {
			make_sub(vhome_int, home_lineup, vhome_name);
		}
		else if (subbing_team == vaway_name) {
			make_sub(vaway_int, away_lineup, vaway_name);
		}
		else {
			std::cout << "Make sure to either enter " << vhome_name << " or " << vaway_name << std::endl;
			goto substitution;
		}
	}
	else {
		std::cout << "MAKE SURE TO ENTER EITHER " << vhome_name << " or " << vaway_name << "or if you want to make a Sub type SUB." << std::endl;
		goto winner;
	}
}
void point_won(int winning_team, std::string winning_team_name, std::string winning_lineup[], int losing_team, std::string losing_team_name, std::string losing_lineup[]) {
	std::cout << "\nSo " << winning_team_name << " won the point" << std::endl;
	std::cout << "Was the point won off of a 'serve' a 'kill' or an 'error'?" << std::endl;
	std::string winning_event;
checkpoint:
	std::getline(std::cin, winning_event);
	if (winning_event == "serve") {
		if (serving == winning_team_name) {
			for (int t = 0; t < num_rost; t++) {
				std::string player_num = teams[winning_team].get_player_nums(t);
				if (player_num == winning_lineup[0]) {
					teams[winning_team].add_player_ace(t);
					teams[winning_team].add_player_serve(t);
				}
			}
		}
		else {
			for (int t = 0; t < num_rost; t++) {
				std::string player_num = teams[losing_team].get_player_nums(t);
				if (player_num == losing_lineup[0]) {
					teams[losing_team].add_player_missed_serve(t);
					teams[losing_team].add_player_serve(t);
				}
			}
		}
	}
	else if(winning_event == "kill"){
		std::cout << "Who made the kill (Winning Team Player):\t";
		std::string kill_maker;
		std::getline(std::cin, kill_maker);
		for (int i = 0; i < num_side; i++) {
			if (kill_maker == winning_lineup[i]){
				for (int t = 0; t < num_rost; t++) {
					std::string player_num = teams[winning_team].get_player_nums(t);
					if (player_num == winning_lineup[0]) {
						teams[winning_team].add_player_kill(t);
					}
				}
			}
		}
		std::cout << "Who had the assist (Winning Team Player):\t";
		std::string assist_maker;
		std::getline(std::cin, assist_maker);
		for (int i = 0; i < num_side; i++) {
			if (assist_maker == winning_lineup[i]) {
				for (int t = 0; t < num_rost; t++) {
					std::string player_num = teams[winning_team].get_player_nums(t);
					if (player_num == winning_lineup[0]) {
						teams[winning_team].add_player_assist(t);
					}
				}
			}
		}
	}
	else if (winning_event == "error") {
		std::cout << "Who made the error (Losing Team Player):\t";
		std::string error_maker;
		std::getline(std::cin, error_maker);
		for (int i = 0; i < num_side; i++) {
			if (error_maker == losing_lineup[i]) {
				for (int t = 0; t < num_rost; t++) {
					std::string player_num = teams[losing_team].get_player_nums(t);
					if (player_num == losing_lineup[0]) {
						teams[losing_team].add_player_hitting_error(t);
					}
				}
			}
		}
	}
	else {
		std::cout << "Please enter (kill, error, or serve)." << std::endl;
		goto checkpoint;
	}
}
void team_rotate(std::string lineup[])
{
	std::string temp1, temp2;
	temp1 = lineup[1];
	lineup[1] = lineup[0];
	temp2 = lineup[2];
	lineup[2] = temp1;
	temp1 = lineup[3];
	lineup[3] = temp2;
	temp2 = lineup[4];
	lineup[4] = temp1;
	temp1 = lineup[5];
	lineup[5] = temp2;
	lineup[0] = temp1;
}

void get_team_mvp() {

	int kte = 0;
	int player = 0, team_num = 0;
	bool valid = false;

	if (!vgame_played) {
		std::cout << "Make sure that a game has been played!" << std::endl;
		volleyball_menu();
	}
	else {
	enter_name:
		std::cout << "What team do you want to calculate the MVP for?" << std::endl;
		std::string lookup_team_name;

		std::cin >> lookup_team_name;
		
		for (int t = 0; t < teams.size(); t++) {
			if (vteam_names[t] == lookup_team_name) {
				valid = true;
				team_num = t;
				for (int p = 0; p < num_rost; p++) {
					int pkte = teams[t].get_kill_to_error(p);
					if (pkte > kte) {
						player = p;
						kte = pkte;
						
					}
				}
			}

		}
		if (!valid) {
			std::cout << "Please make sure to enter an appropriate team name." << std::endl;
			goto enter_name;
		}
		std::cout << "The MVP for " << vteam_names[team_num] << " was:" << teams[team_num].get_player_name(player) << " with a Kill to Error value of: " << kte << std::endl;
		volleyball_menu();
	}
	
}

void get_overall_mvp() {
	if (!vgame_played) {
		std::cout << vgame_played << std::endl;
		std::cout << "Make sure that a game has been played!" << std::endl;
		volleyball_menu();
	}
	else
	{
		std::cout << "The overall MVP for the tournament was: " << std::endl;
		int team = 0, player = 0;
		double kte = 0;
		for (int i = 0; i < teams.size(); i++) {
			for (int p = 0; p < num_rost; p++) {
				int pkte = teams[i].get_kill_to_error(p);
				if (pkte > kte) {
					team = i;
					player = p;
					kte = pkte;
				}
			}
		}

		std::cout << "The MVP for the tournament was on " << vteam_names[team] << " his name was " << teams[team].get_player_name(player) << " with Kill to Error value of: " << kte << std::endl;
		volleyball_menu();
	}
	
}