#include "Tennis_Player.h"

player::player(std::string name, std::string type, int rank){
	this->name = name;
	this->type = type;
	this->rank = rank;
}

void player::print(){
	std::cout << name << "\t" << type << "\t" << rank << std::endl;
}

std::string player::get_name()
{
	return name;
}

std::string player::get_type()
{
	return type;
}

int player::get_rank()
{
	return rank;
}
