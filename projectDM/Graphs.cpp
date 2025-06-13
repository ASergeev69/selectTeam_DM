#include "Graphs.h"

// ����������� ����� (������ �� ����� � ����������)
coloredMultiGraph::coloredMultiGraph(std::string fileName)
{
	std::ifstream file(fileName); // ��������� ����

	std::string nickname;
	FullName FIO;

	std::string tmp = "";
	roles role;
	std::string lang;

	int cost;
	std::unordered_map<std::string, float> paramsInd;
	std::unordered_map<std::string, int> paramsComp;

	// ���� � ����� ���� ��� ���������, �� ���������
	while (file >> nickname >> FIO.first >> FIO.last >> FIO.patronymic >> tmp)
	{
		std::unordered_set<std::string> langs;
		std::string token;

		// ������� � ���� �����, ��������� ���� ���� �� ����� �����
		while (file >> token) {
			if (isdigit(token[0])) {
				cost = stoi(token);
				break;
			}
			langs.insert(token);
		}

		file >> paramsInd["winRate"] >> paramsInd["KD"] >> paramsInd["HeadRate"]
			>> paramsInd["hours"] >> paramsInd["HLTV"] >> paramsInd["ADR"] >> paramsComp["couchRate"] >> paramsComp["E"] >> paramsComp["R"] >> paramsComp["O"] >> paramsComp["K"] >> paramsComp["A"];


		// ��������� ������ � ��������� ������
		players.push_back(Player(nickname, FIO, stringToRole(tmp), langs, cost, paramsInd, paramsComp));
	}

	// ������ ���� ���� ���� ���� ������� ���������
	for (int i = 0; i < players.size(); ++i)
	{
		for (int j = i + 1; j < players.size(); ++j)
		{
			for (std::string lang : players[i].langs)
			{
				if (players[j].langs.count(lang))
					edges.push_back({ players[i], players[j], lang });
			}
		}
	}
}

// ������ ��� ��������� ��������� �� ������ (������)
std::unordered_map<std::string, std::vector<Player>> getSubGraphs(const coloredMultiGraph& graph)
{
	std::unordered_map<std::string, std::unordered_set<Player>> subGraphs;

	for (const Edge& edge : graph.edges)
	{
		subGraphs[edge.lang].insert(edge.from);
		subGraphs[edge.lang].insert(edge.to);
	}

	std::unordered_map<std::string, std::vector<Player>> result;
	for (const auto& [lang, playerunordered_set] : subGraphs)
	{
		result[lang] = std::vector<Player>(playerunordered_set.begin(), playerunordered_set.end());
	}

	return result;
}

// ������� ��� ����������� ������� ��������� (�����)
void weightGraph::createTable()
{
	for (int i = 0; i < 5; ++i)
		for (int j = i + 1; j < 5; ++j)
		{
			table[i][j] = getWeight(players[i], players[j]);
			tableWeight += table[i][j];
		}
	tableWeight *= 5;
}

// ������� ��� �������� ���� ����
int weightGraph::getWeight(Player player1, Player player2)
{
	int weight{};
	if (player1.getFirstCharact() == player2.getFirstCharact())
	{
		weight = 1;
	}

	weight += player1.paramsComp["couchRate"];
	weight += player2.paramsComp["couchRate"];

	return weight;
}

// ����������� ����������� �����
weightGraph::weightGraph(std::vector<Player> players)
{
	this->players = players;

	createTable();
}