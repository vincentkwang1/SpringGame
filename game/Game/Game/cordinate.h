#ifndef CORDINATE_H
#define CORDINATE_H
#pragma once
#include <stack>
#include <vector>
#include <array>
#include "global.h"
#include "map.h"
#define X_MAX 12
#define X_STEP 1
#define Y_MAX 12
#define Y_STEP 1


inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}
class Cordinate {
public:
	Cordinate();
	static bool isValid(bool team, int number, std::vector<troop> alliedArmy, std::vector<troop> enemyArmy, map localMap, int x, int y);
	static bool isDestination(int x, int y, Node dest);
	static double calculateH(int x, int y, Node dest);
	static std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest);
	static std::vector<Node> aStar(bool team, int number, std::vector<troop> alliedArmy, std::vector<troop> enemyArmy, map localMap, Node player, Node dest);
};
#endif