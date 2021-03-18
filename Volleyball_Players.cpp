#include "Volleyball_Players.h"

vplayer::vplayer(std::string name, std::string number, std::string position, int kills, int hitting_errors, int assists, int serves, int aces, int missed_serves){
	this->name = name;
	this->number = number;
	this->position = position;
	this->kills = kills;
	this->hitting_errors = hitting_errors;
	this->assists = assists;
	this->serves = serves;
	this->aces = aces;
	this->missed_serves = missed_serves;
}

vplayer::vplayer(std::string name, std::string number, std::string position) : vplayer(name, number, position, 0, 0, 0, 0, 0, 0){
}

void vplayer::print_basic(){
	std::cout << name
		<< "\t"
		<< number
		<< "\t"
		<< position
		<< std::endl;
}

std::string  vplayer::get_num(){
	return number;
}

int vplayer::get_kill()
{
	return kills;
}

int vplayer::get_hitting_error()
{
	return hitting_errors;
}

int vplayer::get_assist()
{
	return assists;
}

int vplayer::get_serve()
{
	return serves;
}

int vplayer::get_ace()
{
	return aces;
}

int vplayer::get_missed_serve()
{
	return missed_serves;
}

void vplayer::add_kill(){
	
	kills++;
}

std::string vplayer::get_name()
{
	return name;
}

void vplayer::add_hitting_error(){
	hitting_errors++;
}

void vplayer::add_assist(){
	assists++;
}

void vplayer::add_serve(){
	serves++;
}

void vplayer::add_ace(){
	aces++;
}

void vplayer::add_missed_serve(){
	missed_serves++;
}

void vplayer::print_full() {
	std::cout << name
		<< "\t"
		<< number
		<< "\t"
		<< position
		<< "\n\nKills:\t" << kills
		<< "\nHitting Errors:\t" << hitting_errors
		<< "\nAssists:\t" << assists
		<< "\nServes:\t" << serves
		<< "\nAces:\t" << aces
		<< "\nMissed Serves:\t" << missed_serves
		<< std::endl << std::endl << std::endl;
}

int vplayer::kill_to_error()
{
	return (kills + assists + aces) - (hitting_errors, missed_serves);
}