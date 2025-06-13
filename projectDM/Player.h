#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

// ������� ��������� ����� �������
enum class roles {
	IGL,
	RIFLER,
	AWPER,
	LURKER,
	NONE
};

// �������������� ���������� ���� ���� � ���������� ���� ������
std::string roleToString(roles r);
// �������������� ���������� ���� ������ � ���������� ���� ������ ����
roles stringToRole(const std::string& str);


// ��������� (���) ���������� ��� ������ � ����� �����
struct FullName {
	std::string last;
	std::string first;
	std::string patronymic;
};

// ������ (���������, ���) ���������� � ���� ������ �� ������ (��� �����)
struct Player {
	std::string nickname;                             // ���-���� (��������) ������
	FullName FIO;                                     // ��� ������

	roles role;                                       // ������� ���� ������
	std::unordered_set<std::string> langs;            // ��������� (���������) ������ �� ������� ������� �����
	
	int cost;                                         // ��������� ������
	std::unordered_map<std::string, float> paramsInd; // ������������ �������������� ������������� ������
	std::unordered_map<std::string, int> paramsComp;  // ������������ ������������� ������������� ������

	// ������� ���������� "�"
	int getFirstCharact();

	// ������� ���������� ������ ��� ���������� ������
	float getSkillRate();

	// ����������� ������
	Player(std::string nickname, FullName FIO, roles role, std::unordered_set<std::string> langs, int cost, std::unordered_map<std::string, float> paramsInd, std::unordered_map<std::string, int> paramsComp);
};

// ���������� ��������� ��� �������� �� ��������� ���� �������
bool operator==(const Player& a, const Player& b);
namespace std {
	template <>
	struct hash<Player> {
		std::size_t operator()(const Player& p) const {
			return std::hash<std::string>()(p.nickname);
		}
	};
}