#pragma once
#include "Player.h"
#include <vector>
#include <fstream>
#include <string>

// ����� ����� (���������, ���) 
struct Edge {
	Player from; // ������� ������ ������� �����
	Player to;   // ������� ���� �������� �����

	std::string lang; // ���� (����) �����
};

// ������� �������� ����������� (���������, ���)
struct coloredMultiGraph {
	std::vector<Player> players; // ������� ����� (������)
	std::vector<Edge> edges;     // ���� �����

	// ����������� ����� (������ �� ����� � ����������)
	coloredMultiGraph(std::string fileName);
};

// ������ ��� ��������� ��������� �� ������ (������)
std::unordered_map<std::string, std::vector<Player>> getSubGraphs(const coloredMultiGraph& graph);


// ���������� ���� (��� ������� ��� ��� ����� �������)
struct weightGraph {
	std::vector<Player> players; // ������� ����� (������)
	int tableWeight = 0; // ����� ��� ���� ����

	int table[5][5]{}; // ������� ��������� (������� �����)

	// ������� ��� ����������� ������� ��������� (�����)
	void createTable();

	// ������� ��� �������� ���� ����
	int getWeight(Player player1, Player player2);

	// ����������� ����������� �����
	weightGraph(std::vector<Player> players);
};