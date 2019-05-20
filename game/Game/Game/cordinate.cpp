#include "cordinate.h"

Cordinate::Cordinate()
{
}
bool Cordinate::isValid(bool team, int number, std::vector<troop> alliedArmy, std::vector<troop> enemyArmy, map localMap, int x, int y) { //If our Node is an obstacle it is not valid
	if (x < 0 || y < 0 || x >= tileX || y >= tileY) {
		return false;
	}
	else if (localMap.getMapContainer()[x][y].getNoise() > 0 && localMap.getMapContainer()[x][y].getNoise() < 4) {
		/*if (team) {
			for (int i = 0; i < alliedArmy.size(); i++) {
				if (i != number) {
					if (alliedArmy[i].getPos()[0] == x && alliedArmy[i].getPos()[1] == y) {
						return false;
					}
				}
			}
		}
		else {
			for (int i = 0; i < enemyArmy.size(); i++) {
				if (i != number) {
					if (enemyArmy[i].getPos()[0] == x && enemyArmy[i].getPos()[1] == y) {
						return false;
					}
				}
			}
		}*/
		return true;
	}
	return false;
}
bool Cordinate::isDestination(int x, int y, Node dest) {
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}
double Cordinate::calculateH(int x, int y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}
std::vector<Node> Cordinate::makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
	try {
		/*std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "Found a path";
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(1000, 100);*/
		int x = dest.x;
		int y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const std::exception& e) {
		/*std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << e.what();
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(1000, 150);*/
	}
}
std::vector<Node> Cordinate::aStar(bool team, int number, std::vector<troop> alliedArmy, std::vector<troop> enemyArmy, map localMap, Node player, Node dest) {
	std::vector<Node> empty;
	if (isValid(team, number, alliedArmy, enemyArmy, localMap, dest.x, dest.y) == false) {
		/*std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "Destination is an obstacle";
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(1000, 200);*/
		return empty;
		//Destination is invalid
	}
	if (isDestination(player.x, player.y, dest)) {
		/*std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "You are the destination";
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(1000, 250);*/
		return empty;
		//You clicked on yourself
	}
	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

	//Initialize whole map
	//Node allMap[50][25];
	std::array<std::array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
	for (int x = 0; x < (X_MAX / X_STEP); x++) {
		for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	//Initialize our starting list
	int x = player.x;
	int y = player.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP) * (Y_MAX / Y_STEP)) {
		Node node;
		do {
			//This do-while loop could be replaced with extracting the first
			//element from a set, but you'd have to make the openList a set.
			//To be completely honest, I don't remember the reason why I do
			//it with a vector, but for now it's still an option, although
			//not as good as a set performance wise.
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) {
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (isValid(team, number, alliedArmy, enemyArmy, localMap, node.x, node.y) == false);

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		//For each neighbour starting from North-West to South-East
		for (int i = 0; i < 4; i++) {
			int newX, newY;
			switch (i) {
			case 0: newX = -1; newY = 0; break;
			case 1: newX = 1; newY = 0; break;
			case 2: newX = 0; newY = 1; break;
			case 3: newX = 0; newY = -1; break;
			}
			double gNew, hNew, fNew;
			if (isValid(team, number, alliedArmy, enemyArmy, localMap, x + newX, y + newY)) {
				if (isDestination(x + newX, y + newY, dest))
				{
					//Destination found - make path
					allMap[x + newX][y + newY].parentX = x;
					allMap[x + newX][y + newY].parentY = y;
					destinationFound = true;
					return makePath(allMap, dest);
				}
				else if (closedList[x + newX][y + newY] == false)
				{
					gNew = node.gCost + 1.0;
					hNew = calculateH(x + newX, y + newY, dest);
					fNew = gNew + hNew;
					// Check if this path is better than the one already present
					if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
						allMap[x + newX][y + newY].fCost > fNew)
					{
						// Update the details of this neighbour node
						allMap[x + newX][y + newY].fCost = fNew;
						allMap[x + newX][y + newY].gCost = gNew;
						allMap[x + newX][y + newY].hCost = hNew;
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						openList.emplace_back(allMap[x + newX][y + newY]);
					}
				}
			}
		}
	}
	if (destinationFound == false) {
		/*std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "Destination not found";
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(1000, 250);*/
		return empty;
	}
}