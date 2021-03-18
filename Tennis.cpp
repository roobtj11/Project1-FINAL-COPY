#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <sstream>
#include "Tennis_Player.h"
#include "Tennis_Team.h"
#include "Source.h"

Team Arrowhead;
Team CMH;
Team KM;
Team MUK;
Team Muskego;
Team North;
Team South;
Team West;
const int num_teams = 8;
std::string team_names[num_teams];
std::vector<Team> teams;
std::string teams_seeds[8];
int home_score, away_score, home_int, away_int;
std::string home_name, away_name;
const int num_courts = 7;


void tennis();
void get_team_info();
void print_rosters();

void get_teams_seed();
void team_lookup();
void tournament_bracket();
void start_a_meet();
void get_meet_info();
void print_matches();
void tennis_menu();

void  tennis() {
	get_team_info();
	
	get_teams_seed();

	tennis_menu();
}

void print_rosters() {
	for (int i = 0; i < teams.size(); i++) {
		std::cout << "\t" << team_names[i] << std::endl;
		teams[i].print_roster();
		std::cout << std::endl;
	}
}

void get_team_info() {

	team_names[0] = "Arrowhead";
	team_names[1] = "CMH";
	team_names[2] = "KM";
	team_names[3] = "MUK";
	team_names[4] = "Muskego";
	team_names[5] = "North";
	team_names[6] = "South";
	team_names[7] = "West";

	teams.push_back(Arrowhead);
	teams.push_back(CMH);
	teams.push_back(KM);
	teams.push_back(MUK);
	teams.push_back(Muskego);
	teams.push_back(North);
	teams.push_back(South);
	teams.push_back(West);

	for (int i = 0; i < num_teams; i++) {
		std::string p = "Tennis_rosters\\" + team_names[i] + ".csv";
		teams[i] = Team::read_from_file(p);
	}	
}

void get_teams_seed() {
	std::cout << "There are " << num_teams << " teams in the confrence give each team a seed. \n";
	for (int i = 0; i < num_teams; i++) {
		std::cout << i + 1 << ")\t" << team_names[i] << std::endl;
	}
	std::cout << "Please enter each teams seed 1 - 8:" << std::endl;
	int check[8] = {};
	bool valid;
	for (int i = 0; i < 8; i++)
	{
	checkpoint:
		valid = true;
		std::cout << team_names[i] << ".\t";
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
			teams_seeds[seed - 1] = team_names[i];
			check[i] = seed;
		}
		else {
			std::cout << "Please make sure to only enter each seed number once, and that the seed given is between 1 and 8." << std::endl << std::endl;
			goto checkpoint;
		}
	}
	std::cout << "\n\n\n";
}


void tennis_menu() {
menu:

	std::cout << "Do you want to (enter the corresponding number)\n1) look at a specific teams roster, \n2) Confrence bracket, \n3) Meet lineup\n4) Leave Tennis" << std::endl;
	int choice;
	std::string choice_str;
	std::getline(std::cin, choice_str);
	
	try {
		choice = std::stoi(choice_str);		
	}
	catch (...) {
		std::cout << "Please enter an appropriate value" << std::endl << std::endl;
		goto menu;
	}
	if (choice < 1 || choice > 4) {
		std::cout << "Please enter an appropriate value" << std::endl << std::endl;
		goto menu;
	}
	else if (choice == 1) {
		team_lookup();
	}
	else if (choice == 2) {
		tournament_bracket();
	}
	else if (choice == 3) {
		start_a_meet();
	}
	else if (choice == 4) {
		std::cin.clear();
		std::cin.ignore(1);
		return;
	}
}

void team_lookup() {
lookup:
	std::cout << "What team do you want to look up?" << std::endl;
	std::string lookup_team;
	std::cin >> lookup_team;
	bool valid = false;
	for (int i = 0; i < teams.size(); i++) {
		if (lookup_team == team_names[i]) {
			valid = true;
			teams[i].print_roster();
		}
	}
	if (valid) {
		tennis_menu();
	}
	else {
		std::cout << "Please make sure you enter the team name correctly. Here are the list of options in case you forgot.";
		for (int i = 0; i < num_teams; i++) {
			std::cout << i + 1 << ")\t" << team_names[i] << std::endl;
		}
		goto lookup;
	}
}

void tournament_bracket() {
	std::cout << std::endl << std::endl << std::endl;
	std::cout << teams_seeds[0] << "          " << teams_seeds[1] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << teams_seeds[2] << "          " << teams_seeds[3] << std::endl;
	std::cout << std::endl << "     __________" << std::endl << std::endl;
	std::cout << teams_seeds[4] << "          " << teams_seeds[5] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << teams_seeds[6] << "          " << teams_seeds[7] << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	tennis_menu();
}

void start_a_meet(){
	home_score = 0;
	away_score = 0;
	get_meet_info();
	std::cout << "This meet will be played on 7 courts, and the matches are as follows:" << std::endl << std::endl;
	print_matches();
	if (home_score > away_score) {
		std::cout << home_name << " Won the meet " << home_score << " to " << away_score;
	}
	else {
		std::cout << away_name << " Won the meet " << away_score << " to " << home_score << std::endl << std::endl;
	}
	std::cout << std::endl << std::endl;
	tennis_menu();
}

void get_meet_info() {
name:

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
			if (team_input == team_names[i]) {
				valid = true;
				if (t == 0) {
					home_name = team_input;
					home_int = i;
				}
				else {
					away_name = team_input;
					away_int = i;
				}
			}
		}
		if (home_name == away_name) {
			std::cout << home_name << " Cannot be both home and away!" << std::endl << std::endl;
			goto name;
		}
		if (!valid) {
			std::cout << "Make sure to enter an accepted team name." << std::endl;
			goto name;
		}
	}
}

void print_matches()
{
	int court_number = 1;
	std::string winner;
	for (int i = 1; i < 5; i++) {
		if (i < 4) {
		winner1:
			std::cout << "On court " << court_number << " Playing " << i << " doubles:\t" << std::endl;
			std::cout << home_name << ": " << teams[home_int].get_doubles_by_rank(i) << " V.S. " << away_name << ": " << teams[away_int].get_doubles_by_rank(i) << ". \n";
			court_number++;
			std::cout << "Did " << home_name << " Win this match or did " << away_name << " win?" << std::endl;
			std::cin >> winner;
			if (winner == home_name) {
				home_score++;
			}
			else if (winner == away_name) {
				away_score++;
			}
			else {
				std::cout << "Who won it has to be either " << home_name << " or " << away_name << std::endl;
				goto winner1;
			}
		}
	winner2:
		std::cout << std::endl << std::endl;
		std::cout << "On court " << court_number << " Playing " << i << " singles:\t" << std::endl;
		std::cout <<  home_name << ": " << teams[home_int].get_singles_by_rank(i) << " V.S. " << away_name << ": " << teams[away_int].get_singles_by_rank(i) << ". \n";
		court_number++;
		std::cout << "Did " << home_name << " Win this match or did " << away_name << " win?" << std::endl << std::endl;
		std::cin >> winner;
		if (winner == home_name) {
			home_score++;
		}
		else if (winner == away_name) {
			away_score++;
		}
		else {
			std::cout << "\n\n\nWho won it has to be either " << home_name << " or " << away_name << std::endl << std::endl;
			goto winner2;
		}
	}
}

