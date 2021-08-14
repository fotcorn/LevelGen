// source: https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h
#pragma once

#include "Vec.h"

#include <stack>
#include <vector>
#include <array>
//#include <cmath>
#include <limits>

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost; 
	float fCost;
};

inline bool operator < (const Node& lhs, const Node& rhs)
{
    //We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

template <typename TLevel, int TLevelWidth, int TLevelHeight>
class AStar {

public:
    AStar(const TLevel& level) : m_level(level) {}
    AStar(const TLevel&&) = delete;  // prevents rvalue binding

    std::vector<Vec2i> aStar(const Vec2i& start, const Vec2i& dest) {
        std::vector<Vec2i> empty;
        bool closedList[TLevelHeight][TLevelWidth];

        std::array<std::array<Node, TLevelHeight>, TLevelWidth> allMap;
        for (int x = 0; x < TLevelWidth; x++) {
            for (int y = 0; y < TLevelHeight; y++) {
                allMap[x][y].fCost = std::numeric_limits<float>::max();
                allMap[x][y].gCost = std::numeric_limits<float>::max();
                allMap[x][y].hCost = std::numeric_limits<float>::max();
                allMap[x][y].parentX = -1;
                allMap[x][y].parentY = -1;
                allMap[x][y].x = x;
                allMap[x][y].y = y;

                closedList[x][y] = false;
            }
        }

        // Initialize our starting list
        int x = start.x;
        int y = start.y;
        allMap[x][y].fCost = 0.0;
        allMap[x][y].gCost = 0.0;
        allMap[x][y].hCost = 0.0;
        allMap[x][y].parentX = x;
        allMap[x][y].parentY = y;

        std::vector<Node> openList;	
        openList.emplace_back(allMap[x][y]);

        while (!openList.empty() && openList.size() < TLevelWidth * TLevelHeight) {
            Node node;
            do {
                //This do-while loop could be replaced with extracting the first
                //element from a set, but you'd have to make the openList a set.
                //To be completely honest, I don't remember the reason why I do
                //it with a std::vector, but for now it's still an option, although
                //not as good as a set performance wise.
                float currentCost = std::numeric_limits<float>::max();
                std::vector<Node>::iterator itNode;
                for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it++) {
                    if (it->fCost < currentCost) {
                        currentCost = it->fCost;
                        itNode = it;
                    }
                }
                node = *itNode;
                openList.erase(itNode);
            } while (isValid(node.x, node.y) == false);

            x = node.x;
            y = node.y;
            closedList[x][y] = true;

            //For each neighbour starting from North-West to South-East
            for (int newX = -1; newX <= 1; newX++) {
                for (int newY = -1; newY <= 1; newY++) {
                    double gNew, hNew, fNew;
                    if (isValid(x + newX, y + newY)) {
                        if (isDestination(x + newX, y + newY, dest))
                        {
                            //Destination found - make path
                            allMap[x + newX][y + newY].parentX = x;
                            allMap[x + newX][y + newY].parentY = y;
                            return makePath(allMap, dest);
                        }
                        else if (closedList[x + newX][y + newY] == false)
                        {
                            gNew = node.gCost + 1.0;
                            hNew = calculateH(x + newX, y + newY, dest);
                            fNew = gNew + hNew;
                            // Check if this path is better than the one already present
                            if (allMap[x + newX][y + newY].fCost == std::numeric_limits<float>::max() ||
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
        }
        return empty;
    }

private:
    const TLevel& m_level;

    bool isValid( int x, int y) { //If our Node is an obstacle it is not valid
        if (!m_level.isOccupied(x, y)) {
            if (x < 0 || y < 0 || x >= TLevelWidth || y >= TLevelHeight) {
                return false;
            }
            return true;
        }
        return false;
    }

    bool isDestination(int x, int y, const Vec2i& dest) {
        if (x == dest.x && y == dest.y) {
            return true;
        }
        return false;
    }

    double calculateH(int x, int y, const Vec2i& dest) {
        double H = (sqrt((x - dest.x)*(x - dest.x)
            + (y - dest.y)*(y - dest.y)));
        return H;
    }

    std::vector<Vec2i> makePath(std::array<std::array<Node, TLevelHeight>, TLevelWidth> map, const Vec2i& dest) {
        int x = dest.x;
        int y = dest.y;
        std::stack<Node> path;
        std::vector<Vec2i> usablePath;

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
            usablePath.push_back({{top.x, top.y}});
        }
        return usablePath;
    }
};
