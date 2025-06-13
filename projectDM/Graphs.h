#pragma once
#include "Player.h"
#include <vector>
#include <fstream>
#include <string>

// Ребро графа (Структура, тип) 
struct Edge {
	Player from; // Вершина откуда исходит ребро
	Player to;   // Вершина куда приходит ребро

	std::string lang; // Язык (цвет) ребра
};

// Цветной языковой мультиграаф (Структура, тип)
struct coloredMultiGraph {
	std::vector<Player> players; // Вершины графа (игроки)
	std::vector<Edge> edges;     // Дуги графа

	// Конструктор графа (Запись из файла и построение)
	coloredMultiGraph(std::string fileName);
};

// Функия для выделения подграфов по языкам (цветам)
std::unordered_map<std::string, std::vector<Player>> getSubGraphs(const coloredMultiGraph& graph);


// Взвешенный граф (Все вершины так или иначе связаны)
struct weightGraph {
	std::vector<Player> players; // Вершины графа (игроки)
	int tableWeight = 0; // Общий вес всех рёбер

	int table[5][5]{}; // Таблица смежности (Таблица весов)

	// Функция для составления таблицы смежности (весов)
	void createTable();

	// Функция для подсчёта веса дуги
	int getWeight(Player player1, Player player2);

	// Конструктор взвешенного графа
	weightGraph(std::vector<Player> players);
};