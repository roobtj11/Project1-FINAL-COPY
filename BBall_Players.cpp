#include "BBall_Players.h"

bplayer::bplayer(std::string name, std::string number, std::string position, int points, int three_points, int assists, int steals, int rebounds, int turnovers) {
	this->name = name;
	this->number = number;
	this->position = position;
	this->points = points;
	this->three_points = three_points;
	this->assists = assists;
	this->steals = steals;
	this->rebounds = rebounds;
	this->turnovers = turnovers;
}

bplayer::bplayer(std::string name, std::string number, std::string position) : bplayer(name, number, position, 0, 0, 0, 0, 0, 0) {
}

void bplayer::print_basic() {
	std::cout << name
		<< "\t"
		<< number
		<< "\t"
		<< position
		<< std::endl;
}

std::string bplayer::get_num() {
	return number;
}

int bplayer::get_point()
{
	return points;
}

int bplayer::get_three_point()
{
	return three_points;
}

int bplayer::get_assist()
{
	return assists;
}

int bplayer::get_steal()
{
	return steals;
}

int bplayer::get_rebound()
{
	return rebounds;
}

int bplayer::get_turnover()
{
	return turnovers;
}



void bplayer::add_point(int scored_points) {
	if (scored_points == 3) {
		points = points + 3;
	}
	else if (scored_points == 2) {
		points = points + 2;
	}
	else if(scored_points == 1){
		points++;
	}
}

std::string bplayer::get_name()
{
	return name;
}

void bplayer::add_three_point() {
	three_points++;
}

void bplayer::add_assist() {
	assists++;
}

void bplayer::add_steal() {
	steals++;
}

void bplayer::add_rebound() {
	rebounds++;
}

void bplayer::add_turnover() {
	turnovers++;
}

void bplayer::print_full() {
	std::cout << name
		<< "\t"
		<< number
		<< "\t"
		<< position
		<< "\n\nPoints:\t" << points
		<< "\n3 Point Shots:\t" << three_points
		<< "\nAssists:\t" << assists
		<< "\nSteals:\t" << steals
		<< "\nRebounds:\t" << rebounds
		<< "\nTurnovers:\t" << turnovers
		<< std::endl << std::endl << std::endl;
}

int bplayer::avg_stat()
{
	return ((points + assists + steals + rebounds - turnovers) / 4);
}