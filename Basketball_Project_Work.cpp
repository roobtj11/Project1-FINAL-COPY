#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "BBall_Players.h"
#include "BBall_Team.h"
#include "Source.h"

bTeam KCDS;
bTeam RVC;
bTeam CL;
bTeam RC;
bTeam BIL;
bTeam IQRA;
bTeam BHS;
bTeam STARR;
const int num_teams = 8;
const int num_side = 5;
const int num_rost = 10;
std::string bteam_names[num_teams];
std::vector<bTeam> bteams;
std::string b_teams_seeds[8];

std::string b_serving;


std::string b_home_name;
std::string b_home_lineup[num_side];

std::string b_away_name;
std::string b_away_lineup[num_side];
int b_home_score, b_away_score;
int b_home_int, b_away_int;
bool game_played;

void b_get_team_info();
void b_print_rosters();
void b_get_teams_seed();
void basketball_menu();
void b_team_lookup();
void b_tournament_bracket();
void b_start_game();
void b_get_game_information();
void get_starters(int team, std::string lineup[], std::string team_name);
void b_make_sub(int team, std::string lineup[], std::string team_name);
void play_game();
int score_event(int winning_team, std::string winning_team_name, std::string winning_lineup[], int losing_team, std::string losing_team_name, std::string losing_lineup[], int winning_score, int losing_score);
void rebound_event(int rebound_team, std::string rebound_team_name, std::string rebound_lineup[]);
void steal_event(int steal_team, std::string steal_team_name, std::string steal_team_lineup[], int turnover_team, std::string turnover_team_name, std::string turnover_team_lineup[]);
void assist_event(int winning_team, std::string winning_team_name, std::string winning_lineup[]);
void b_get_team_mvp();
void b_get_overall_mvp();


void basketball() {
	game_played = true;
	b_get_team_info();

	b_get_teams_seed();

	basketball_menu();
}
void b_get_team_info() {
	KCDS = bTeam::read_from_file("Basketball\\KCDS.csv");
	RVC = bTeam::read_from_file("Basketball\\RVC.csv");
	CL = bTeam::read_from_file("Basketball\\CL.csv");
	RC = bTeam::read_from_file("Basketball\\RC.csv");
	BIL = bTeam::read_from_file("Basketball\\BIL.csv");
	IQRA = bTeam::read_from_file("Basketball\\IQRA.csv");
	BHS = bTeam::read_from_file("Basketball\\BHS.csv");
	STARR = bTeam::read_from_file("Basketball\\STARR.csv");

	bteams.push_back(KCDS);
	bteams.push_back(RVC);
	bteams.push_back(CL);
	bteams.push_back(RC);
	bteams.push_back(BIL);
	bteams.push_back(IQRA);
	bteams.push_back(BHS);
	bteams.push_back(STARR);

	bteam_names[0] = "KCDS";
	bteam_names[1] = "RVC";
	bteam_names[2] = "CL";
	bteam_names[3] = "RC";
	bteam_names[4] = "BIL";
	bteam_names[5] = "IQRA";
	bteam_names[6] = "BHS";
	bteam_names[7] = "STARR";
}
void b_print_rosters() {
	for (unsigned int i = 0; i < bteams.size(); i++) {
		std::cout << "\t" << bteam_names[i] << std::endl;
		bteams[i].print_roster();
		std::cout << std::endl;
	}
}
void b_get_teams_seed() {
	std::cout << "There are " << num_teams << " teams here at the tournament today. \n";
	for (int i = 0; i < num_teams; i++) {
		std::cout << i + 1 << ")\t" << bteam_names[i] << std::endl;
	}
	std::cout << "Please enter each teams seed 1 - 8:" << std::endl;
	int check[8] = {};
	bool valid;
	for (int i = 0; i < 8; i++)
	{
	checkpoint:
		valid = true;
		std::cout << bteam_names[i] << ".\t";
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
			b_teams_seeds[seed - 1] = bteam_names[i];
			check[i] = seed;
		}
		else {
			std::cout << "Please make sure to only enter each seed number once, and that the seed given is between 1 and 8." << std::endl << std::endl;
			goto checkpoint;
		}
	}
	std::cout << "\n\n\n";
}
void basketball_menu() {

	std::cout << "Do you want to (enter the corresponding number)\n1) look at a specific teams roster, \n2) Tournament bracket, \n3) Play a game\n4) Get Team MVP\n5) Get Overall MVP" << std::endl;
	int choice;
	try {
		std::cin >> choice;
		if (choice < 1 || choice > 5) {
			throw (1);
		}
	}
	catch (...) {
		std::cout << "Please enter an appropriate value" << std::endl << std::endl;
		basketball_menu();
	}
	if (choice == 1) {
		bteams[1].add_player_point(1, 3);
		b_team_lookup();
	}
	else if (choice == 2) {
		b_tournament_bracket();
	}
	else if (choice == 3) {
		game_played = true;
		b_start_game();
	}
	else if (choice == 4) {
		b_get_team_mvp();
	}
	else if (choice == 5) {
		b_get_overall_mvp();
	}
	else {
		std::cout << "Please enter an appropriate value" << std::endl << std::endl;
		basketball_menu();
	}
}
void b_team_lookup() {
	std::cout << "What team do you want to look up?" << std::endl;
	std::string lookup_team;
	std::cin >> lookup_team;
	bool valid = false;
	for (unsigned int i = 0; i < bteams.size(); i++) {
		if (lookup_team == bteam_names[i]) {
			valid = true;
			bteams[i].print_roster_stats();
		}
	}
	if (valid) {
		std::cout << "Press 1 when you are done looking." << std::endl;
		std::string done;
		std::cin >> done;
		basketball_menu();
	}
	else {
		std::cout << "Please make sure you enter the team name correctly. If you need the list of names again enter 1 otherwise enter any other number followed by enter.";
		std::string names;
		std::cin >> names;
		if (names == "1") {
			for (int i = 0; i < num_teams; i++) {
				std::cout << i + 1 << ")\t" << bteam_names[i] << std::endl;
			}
		}
		b_team_lookup();
	}
}
void b_tournament_bracket() {
	std::cout << std::endl << std::endl << std::endl;
	std::cout << b_teams_seeds[0] << "          " << b_teams_seeds[1] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << b_teams_seeds[2] << "          " << b_teams_seeds[3] << std::endl;
	std::cout << std::endl << "     __________" << std::endl << std::endl;
	std::cout << b_teams_seeds[4] << "          " << b_teams_seeds[5] << std::endl;
	std::cout << "_____          _____" << std::endl;
	std::cout << "_____|--------|_____" << std::endl;
	std::cout << b_teams_seeds[6] << "          " << b_teams_seeds[7] << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	basketball_menu();
}
void b_start_game() {

	b_get_game_information();
	get_starters(b_home_int, b_home_lineup, b_home_name);
	get_starters(b_away_int, b_away_lineup, b_away_name);

	b_home_score = 0;
	b_away_score = 0;
	//score of 50 so the game is short enough for a full test without spending too much time
	while (b_home_score < 50 && b_away_score < 50) {
		play_game();
	}
	if (b_home_score == 50 || b_home_score > 50) {
		std::cout << b_home_name << " won the game! The score was " << b_home_score << "-" << b_away_score << "." << std::endl;
	}
	else if (b_away_score == 50 || b_away_score > 50) {
		std::cout << b_away_name << " won the game! The score was " << b_away_score << "-" << b_home_score << "." << std::endl;
	}

	basketball_menu();
}
void b_get_game_information() {
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
		for (unsigned int i = 0; i < bteams.size(); i++) {
			if (team_input == bteam_names[i]) {
				valid = true;
				if (t == 0) {
					b_home_name = team_input;

					b_home_int = i;
				}
				else {
					b_away_name = team_input;

					b_away_int = i;
				}
			}
		}
		if (!valid) {
			std::cout << "Make sure to enter an accepted team name." << std::endl;
			b_get_game_information();
		}
	}

whos_starting:
	std::cout << "Which team is starting with the ball?" << std::endl;
	std::getline(std::cin, b_serving);
	if (b_serving == b_home_name || b_serving == b_away_name) {
		return;
	}
	else {
		std::cout << "The starting team should either be: " << b_home_name << " or " << b_away_name << std::endl;
		goto whos_starting;
	}
}
void get_starters(int team, std::string lineup[], std::string team_name) {
	std::cout << "Here is the Roster for " << team_name << std::endl;
	bteams[team].print_roster();
	for (int i = 0; i < num_side; i++) {
	checkpoint:
		std::cout << "Who is in position " << i + 1 << "? Enter their number:\t";
		std::string number_str;
		std::getline(std::cin, number_str);
		bool valid = false;
		for (int p = 0; p < num_rost; p++) {
			std::string player_num = bteams[team].get_player_nums(p);
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
void b_make_sub(int team, std::string lineup[], std::string team_name) {
substitution:
	std::cout << std::endl << "Here is the current court:" << std::endl;
	std::cout << "What Position do you want to sub for " << team_name << ": (enter 1-6)\t" << std::endl;
	std::string pos_str;
	int pos;
	std::getline(std::cin, pos_str);
	pos = std::stoi(pos_str);
	if (pos < 7 && pos > 0) {
		std::cout << "Here is the roster for " << team_name << "." << std::endl;
		bteams[team].print_roster();
		std::cout << "What number do you want going in ? " << std::endl;
		std::string number_str;
		std::getline(std::cin, number_str);
		for (int p = 0; p < num_rost; p++) {
			std::string player_num = bteams[team].get_player_nums(p);
			if (player_num == number_str) {
				lineup[pos - 1] = number_str;
			}
		}
	}
	else {
		std::cout << "Make sure to enter a number between 1 and 6" << std::endl;
		goto substitution;
	}

}
void play_game() {
substitution:
	std::cout << "Do you want to sub any players?" << std::endl;

game_progress:
	std::cout << b_home_name << " score: " << b_home_score << "     " << b_away_name << " score: " << b_away_score << std::endl;
	std::cout << "Either enter which 'Score' if a score was made, 'Rebound' if a rebound was made, 'Steal' if a steal was made, or 'SUB' to make a substitution:" << std::endl;
	std::string option;
	std::getline(std::cin, option);

	if (option == "Score") {
	who_scored:
		std::string Scoring_Team;
		std::cout << "What team scored?" << std::endl;
		std::getline(std::cin, Scoring_Team);
	
		if (Scoring_Team == b_home_name) {
			b_home_score = score_event(b_home_int, b_home_name, b_home_lineup, b_away_int, b_away_name, b_away_lineup, b_home_score, b_away_score);
		}
		else if (Scoring_Team == b_away_name) {
			b_away_score = score_event(b_away_int, b_away_name, b_away_lineup, b_home_int, b_home_name, b_home_lineup, b_away_score, b_home_score);
		}
		else if (Scoring_Team != b_home_name && Scoring_Team != b_away_name) {
				std::cout << "Please enter either " << b_home_name << " or " << b_away_name << std::endl;
				goto who_scored;
		}
	}
	else if (option == "Rebound") {
	who_rebounded:
		std::string Rebound_Team;
		std::cout << "Which team made the rebound?" << std::endl;
		std::getline(std::cin, Rebound_Team);
		if (Rebound_Team != b_home_name && Rebound_Team != b_away_name) {
			std::cout << "Please enter either " << b_home_name << " or " << b_away_name << std::endl;
			goto who_rebounded;
		}
		if (Rebound_Team == b_home_name) {
			rebound_event(b_home_int, b_home_name, b_home_lineup);
		}
		else if (Rebound_Team == b_away_name) {
			rebound_event(b_away_int, b_away_name, b_away_lineup);
		}
	}
	else if (option == "Steal") {
	who_stole:
		std::string Steal_Team;
		std::cout << "Which team made the steal?" << std::endl;
		std::getline(std::cin, Steal_Team);
		if (Steal_Team != b_home_name && Steal_Team != b_away_name) {
			std::cout << "Please enter either " << b_home_name << " or " << b_away_name << std::endl;
			goto who_stole;
		}
		if (Steal_Team == b_home_name) {
			steal_event(b_home_int, b_home_name, b_home_lineup, b_away_int, b_away_name, b_away_lineup);
		}
		else if (Steal_Team == b_away_name) {
			steal_event(b_away_int, b_away_name, b_away_lineup, b_home_int, b_home_name, b_home_lineup);
		}
	}
	else if (option == "SUB") {
		std::cout << "What team is making the sub?" << std::endl;
		std::string subbing_team;
		std::getline(std::cin, subbing_team);
		if (subbing_team == b_home_name) {
			b_make_sub(b_home_int, b_home_lineup, b_home_name);
		}
		else if (subbing_team == b_away_name) {
			b_make_sub(b_away_int, b_away_lineup, b_away_name);
		}
		else {
			std::cout << "Make sure to either enter " << b_home_name << " or " << b_away_name << std::endl;
			goto substitution;
		}
	}
	else {
		std::cout << "MAKE SURE TO ENTER EITHER " << b_home_name << " or " << b_away_name << "or if you want to make a Sub type SUB." << std::endl;
		goto game_progress;
	}
}
void rebound_event(int rebound_team, std::string rebound_team_name, std::string rebound_lineup[]) {
	std::cout << "Who made the rebound? (Player): \t";
	std::string rebounder;
	std::getline(std::cin, rebounder);
	for (int t = 0; t < num_rost; t++) {
		std::string player_num = bteams[rebound_team].get_player_nums(t);
		if (player_num == rebound_lineup[0]) {
			bteams[rebound_team].add_player_rebound(t);
		}
	}
}
void steal_event(int steal_team, std::string steal_team_name, std::string steal_team_lineup[], int turnover_team, std::string turnover_team_name, std::string turnover_team_lineup[]) {
	std::cout << "Who made the steal? (Player): \t";
	std::string stealer;
	std::getline(std::cin, stealer);
	for (int t = 0; t < num_rost; t++) {
		std::string player_num = bteams[steal_team].get_player_nums(t);
		if (player_num == steal_team_lineup[0]) {
			bteams[steal_team].add_player_steal(t);
		}
	}
	std::cout << "Who made the turnover? (Player): \t";
	std::string turner;
	std::getline(std::cin, turner);
	for (int t = 0; t < num_rost; t++) {
		std::string player_num = bteams[turnover_team].get_player_nums(t);
		if (player_num == turnover_team_lineup[0]) {
			bteams[turnover_team].add_player_turnover(t);
		}
	}
}
int score_event(int winning_team, std::string winning_team_name, std::string winning_lineup[], int losing_team, std::string losing_team_name, std::string losing_lineup[], int winning_score, int losing_score) {
	int new_score;
	std::cout << "\nSo " << winning_team_name << " scored" << std::endl;
	std::cout << "Was the score a freethrow, a 2 point shot, or a 3 point shot?" << std::endl;
	std::string winning_event;
checkpoint:
	std::getline(std::cin, winning_event);
	if (winning_event == "freethrow") {
		std::cout << "Who made the freethrow? (Player):\t";
		std::string scorer;
		std::getline(std::cin, scorer);
		for (int t = 0; t < num_rost; t++) {
			std::string player_num = bteams[winning_team].get_player_nums(t);
			if (player_num == winning_lineup[0]) {
				bteams[winning_team].add_player_point(t, 1);
			}
		}
		new_score = winning_score + 1;

		return (new_score);
	}
	else if (winning_event == "2 point shot") {
		std::cout << "Who made the shot? (Player):\t";
		std::string scorer;
		std::getline(std::cin, scorer);
		for (int t = 0; t < num_rost; t++) {
			std::string player_num = bteams[winning_team].get_player_nums(t);
			if (player_num == winning_lineup[0]) {
				bteams[winning_team].add_player_point(t, 2);
			}
		}
		new_score = winning_score + 2;
		assist_event(winning_team, winning_team_name, winning_lineup);
		return (new_score);
	}
	else if (winning_event == "3 point shot") {
		std::cout << "Who made the shot? (Winning Team Player):\t";
		std::string scorer;
		std::getline(std::cin, scorer);
		for (int t = 0; t < num_rost; t++) {
			std::string player_num = bteams[winning_team].get_player_nums(t);
			if (player_num == winning_lineup[0]) {
					bteams[winning_team].add_player_point(t, 3);
					bteams[winning_team].add_player_three_point(t);
			}
		}
		new_score = winning_score + 3;
		assist_event(winning_team, winning_team_name, winning_lineup);
		return (new_score);
	}
	
	else {
		std::cout << "Please enter (freethrow, 2 point shot, or 3 point shot)." << std::endl;
		goto checkpoint;
	}
}
void assist_event(int winning_team, std::string winning_team_name, std::string winning_lineup[]) {
	std::cout << "Who had the assist? (Player):\t";
	std::string assist_maker;
	std::getline(std::cin, assist_maker);
	for (int t = 0; t < num_rost; t++) {
		std::string player_num = bteams[winning_team].get_player_nums(t);
		if (player_num == winning_lineup[0]) {
			bteams[winning_team].add_player_assist(t);
		}
	}
}
void b_get_team_mvp() {

	int stat = 0;
	int player = 0, team_num = 0;
	bool valid = false;

	if (!game_played) {
		std::cout << "Make sure that a game has been played!" << std::endl;
		basketball_menu();
	}
	else {
	enter_name:
		std::cout << "What team do you want to calculate the MVP for?" << std::endl;
		std::string lookup_team_name;

		std::cin >> lookup_team_name;

		for (unsigned int t = 0; t < bteams.size(); t++) {
			if (bteam_names[t] == lookup_team_name) {
				valid = true;
				team_num = t;
				for (int p = 0; p < num_rost; p++) {
					int pstat = bteams[t].get_avg_stat(p);
					if (pstat > stat) {
						player = p;
						stat = pstat;

					}
				}
			}

		}
		if (!valid) {
			std::cout << "Please make sure to enter an appropriate team name." << std::endl;
			goto enter_name;
		}
		std::cout << "The MVP for " << bteam_names[team_num] << " was:" << bteams[team_num].get_player_name(player) << std::endl;
		void basketball_menu();
	}

}
void b_get_overall_mvp() {
	if (!game_played) {
		std::cout << game_played << std::endl;
		std::cout << "Make sure that a game has been played!" << std::endl;
		basketball_menu();
	}
	else
	{
		std::cout << "The overall MVP for the tournament was: " << std::endl;
		int team = 0, player = 0;
		double stat = 0;
		for (unsigned int i = 0; i < bteams.size(); i++) {
			for (int p = 0; p < num_rost; p++) {
				int pstat = bteams[i].get_avg_stat(p);
				if (pstat > stat) {
					team = i;
					player = p;
					stat = pstat;
				}
			}
		}

		std::cout << "The MVP for the tournament was on " << bteam_names[team] << " his name was " << bteams[team].get_player_name(player) << std::endl;
		void basketball_menu();
	}

}
