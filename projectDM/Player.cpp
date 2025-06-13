#include "Player.h"

// Преобразование переменной типа роли в переменную типа строки
std::string roleToString(roles r) {
	switch (r) {
	case roles::IGL:
		return "IGL";
	case roles::RIFLER:
		return "RIFLER";
	case roles::AWPER:
		return "AWPER";
	case roles::LURKER:
		return "LURKER";
	default:
		return "NONE";
	}
}

// Преобразование переменной типа строки в переменную типа строки роли
roles stringToRole(const std::string& str) {
	if (str == "IGL")    return roles::IGL;
	if (str == "RIFLER") return roles::RIFLER;
	if (str == "AWPER")  return roles::AWPER;
	if (str == "LURKER") return roles::LURKER;
	return roles::NONE;
}


// Подсчёт коэфицента скилла для отдельного игрока
float Player::getSkillRate()
{
	return paramsInd["KD"] + paramsInd["HeadRate"] / 100 + paramsInd["hours"] / 10000 + paramsInd["HLTV"] + paramsInd["ADR"] / 100 + paramsInd["winRate"] / 10;
}

// Подсчёт для z "булевая функция"
int Player::getFirstCharact()
{
	return ((paramsComp["E"] && paramsComp["O"]) && paramsComp["A"]) || ((paramsComp["R"] && paramsComp["O"]) && ((!(paramsComp["K"])) && paramsComp["A"]));
}

// Перегрузка оператора для проверки на равенство двух игроков
bool operator==(const Player& a, const Player& b) {
	return a.nickname == b.nickname;
}

// Конструктор игрока
Player::Player(std::string nickname, FullName FIO, roles role, std::unordered_set<std::string> langs, int cost, std::unordered_map<std::string, float> paramsInd, std::unordered_map<std::string, int> paramsComp)
{
	this->nickname = nickname;
	this->FIO = FIO;
	this->role = role;
	this->langs = langs;
	this->cost = cost;
	this->paramsInd = paramsInd;
	this->paramsComp = paramsComp;
}