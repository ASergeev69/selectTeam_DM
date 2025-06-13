#pragma once
#include "Graphs.h"

// ��������� ������� (������ ��������� �� ����������� �����������)
struct Team {
	std::vector<Player> players; // ������ (������) �������
	int cost = 0; // ���� �������

	// ������� ���������� ������ ��� �������
	float getTotalSkill() const;

	// ������� ���������� ����� ��� �������
	int getChimical() const;

	// ����������� ������� (������)
	Team(std::vector<Player> players);
};

// ���������� ��������� �������� �� ��������� ��� ������
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

// ������� ������ ������ ������� (aDi+bXi)
Team findBestTeam(const std::vector<Team>& totalTeams, float a, float b);

// ������� ������������� ��������� ���� ������� �� ��������� ������� �� �����
std::unordered_map<roles, std::vector<Player>> getunordered_setsFromRole(const std::vector<Player>& subGraph);

// ������� ��� ��������� ��������� ������ ��������������� ��������
std::vector<Team> getTotalTeams(const std::unordered_map<std::string, std::vector<Player>>& subGraphs, const int& totalBalance);