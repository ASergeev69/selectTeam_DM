#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

// Словарь возможных ролей игроков
enum class roles {
	IGL,
	RIFLER,
	AWPER,
	LURKER,
	NONE
};

// Преобразование переменной типа роли в переменную типа строки
std::string roleToString(roles r);
// Преобразование переменной типа строки в переменную типа строки роли
roles stringToRole(const std::string& str);


// Структура (Тип) содержащий ФИО игрока в одном месте
struct FullName {
	std::string last;
	std::string first;
	std::string patronymic;
};

// Объект (Структура, тип) содержащий в себе данные об игроке (Сам игрок)
struct Player {
	std::string nickname;                             // Ник-нейм (Прозвище) игрока
	FullName FIO;                                     // ФИО игрока

	roles role;                                       // Игровая роль игрока
	std::unordered_set<std::string> langs;            // Множество (коллекция) языков на которых говорит игрок
	
	int cost;                                         // Стоимость игрока
	std::unordered_map<std::string, float> paramsInd; // Совокупность индивидуальных характеристик игрока
	std::unordered_map<std::string, int> paramsComp;  // Совокупность характеристик совместимости игрока

	// Подсчёт коэфицента "а"
	int getFirstCharact();

	// Подсчёт коэфицента скилла для отдельного игрока
	float getSkillRate();

	// Конструктор игрока
	Player(std::string nickname, FullName FIO, roles role, std::unordered_set<std::string> langs, int cost, std::unordered_map<std::string, float> paramsInd, std::unordered_map<std::string, int> paramsComp);
};

// Перегрузка оператора для проверки на равенство двух игроков
bool operator==(const Player& a, const Player& b);
namespace std {
	template <>
	struct hash<Player> {
		std::size_t operator()(const Player& p) const {
			return std::hash<std::string>()(p.nickname);
		}
	};
}