#pragma once
#include "Graphs.h"

// Структура команды (пятёрка элементов из декартового произведния)
struct Team {
	std::vector<Player> players; // Пятёрка (массив) игроков
	int cost = 0; // Цена команды

	// Подсчёт коэфицента скилла для команды
	float getTotalSkill() const;

	// Подсчёт коэфицента химии для команды
	int getChimical() const;

	// Конструктор команды (пятёрки)
	Team(std::vector<Player> players);
};

// Перегрузка оператора проверки на равенство для команд
bool operator==(const Team& a, const Team& b);
namespace std {
	template <>
	struct hash<Team> {
		std::size_t operator()(const Team& t) const {
			std::size_t h = 0;
			for (const auto& p : t.players) {
				h ^= std::hash<std::string>()(p.nickname) + 0x9e3779b9 + (h << 6) + (h >> 2);
			}
			return h;
		}
	};
}

// Функция поиска лучшей команды (aDi+bXi)
Team findBestTeam(const std::vector<Team>& totalTeams, float a, float b);

// Функция распределения множества всех игроков на множества игроков по ролям
std::unordered_map<roles, std::vector<Player>> getunordered_setsFromRole(const std::vector<Player>& subGraph);

// Функция для получения множества команд удовлетворяющих условиям
std::vector<Team> getTotalTeams(const std::unordered_map<std::string, std::vector<Player>>& subGraphs, const int& totalBalance);