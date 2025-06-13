#include "TeamManager.h"

// ������� ���������� ������ ��� �������
float Team::getTotalSkill() const {
	float totalSkill = 0;
	for (Player player : players)
		totalSkill += player.getSkillRate();
	return totalSkill;
}

// ������� ���������� ����� ��� �������
int Team::getChimical() const {
	weightGraph graph(players);
	return graph.tableWeight;
}

// ����������� ������� (������)
Team::Team(std::vector<Player> players) {
	this->players = players;
	for (Player player : players)
		cost += player.cost;
}

// ���������� ��������� �������� �� ��������� ��� ������
bool operator==(const Team& a, const Team& b) {
	if (a.players.size() != b.players.size()) return false;
	for (size_t i = 0; i < a.players.size(); ++i)
		if (a.players[i].nickname != b.players[i].nickname)
			return false;
	return true;
}

// ������� ������ ������ ������� (aSi+bXi )
Team findBestTeam(const std::vector<Team>& totalTeams, float a, float b)
{
	const float EPSILON = 1e-6f;
	float bestScore = -1.0f;
	std::vector<const Team*> bestTeams;

	// ����������������� ������ ������� ������ (�� ������� �������� � ����������� ����)
	for (const Team& team : totalTeams) {
		float chemistry = static_cast<float>(team.getChimical());
		float skill = team.getTotalSkill();
		float score = a * chemistry + b * skill;

		if (score > bestScore + EPSILON) {
			bestScore = score;
			bestTeams.clear();
			bestTeams.push_back(&team);
		}
		else if (std::abs(score - bestScore) < EPSILON) {
			bestTeams.push_back(&team);
		}
	}

	const Team* best = bestTeams[0];
	for (const Team* team : bestTeams) {
		if (team->cost < best->cost)
			best = team;
	}

	return *best;
}

// ������� ������������� ��������� ���� ������� �� ��������� ������� �� �����
std::unordered_map<roles, std::vector<Player>> getunordered_setsFromRole(const std::vector<Player>& subGraph)
{
	std::unordered_map<roles, std::vector<Player>> unordered_setsFromRole;
	for (Player player : subGraph)
		unordered_setsFromRole[player.role].push_back(player);
	return unordered_setsFromRole;
}

// ������� ��� ��������� ��������� ������ ��������������� ��������
std::vector<Team> getTotalTeams(const std::unordered_map<std::string, std::vector<Player>>& subGraphs, const int& totalBalance)
{
	std::unordered_set<Team> totalTeams;

	// ���������� ��� �������� ��������
	for (const auto& [lang, players] : subGraphs) {
		std::unordered_map<roles, std::vector<Player>> unordered_setsFromRole = getunordered_setsFromRole(players);

		// ���� ��� ������� ����� �� ����, ���������� ����
		if (unordered_setsFromRole[roles::IGL].empty() || unordered_setsFromRole[roles::RIFLER].size() < 2 ||
			unordered_setsFromRole[roles::AWPER].empty() || unordered_setsFromRole[roles::LURKER].empty()) continue;

		const auto& igls = unordered_setsFromRole[roles::IGL],riflers = unordered_setsFromRole[roles::RIFLER],
			awpers = unordered_setsFromRole[roles::AWPER], lurkers = unordered_setsFromRole[roles::LURKER];

		std::vector<Team> localTeams;

		// ��������� ������������ 5-�� �������� (����������� ������)
		#pragma omp parallel for collapse(4) schedule(dynamic)
		for (int iglIdx = 0; iglIdx < static_cast<int>(igls.size()); ++iglIdx) {
			for (int i = 0; i < static_cast<int>(riflers.size()); ++i) {
				for (int j = i + 1; j < static_cast<int>(riflers.size()); ++j) {
					for (int awpIdx = 0; awpIdx < static_cast<int>(awpers.size()); ++awpIdx) {
						for (int lurkIdx = 0; lurkIdx < static_cast<int>(lurkers.size()); ++lurkIdx) {
							Team currTeam({ igls[iglIdx], riflers[i], riflers[j], awpers[awpIdx], lurkers[lurkIdx] });

							if (currTeam.cost <= totalBalance) {
								#pragma omp critical
								totalTeams.insert(currTeam); // ��������� ������� ���� ���������� ����
							}
						}
					}
				}
			}
		}
	}

	return std::vector<Team>(totalTeams.begin(), totalTeams.end());
}