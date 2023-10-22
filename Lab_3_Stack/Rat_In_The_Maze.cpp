#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

class node
{
public:
    int x, y;
    int dir;
    node(int i, int j)
    {
        x = i;
        y = j;

        // Initially direction
        // set to 0
        dir = 0;
    }
};

bool canEatFood(int maze[5][5], int fx, int fy)
{
    /*TODO*/
    int x = 0, y = 0;
    stack<node> Path;
    node cur(x, y);
    bool saveStep[5][5];
    memset(saveStep, true, sizeof(saveStep));
    Path.push(cur); // Khởi tạo Stack và vị trí đầu tiên
    while (!Path.empty())
    {
        cur = Path.top();
        int direction = cur.dir;
        x = cur.x;
        y = cur.y;
        cur.dir++;
        Path.pop();
        Path.push(cur);
        if (x == fx && y == fy)
            return true; // Đụng thức ăn
        switch (direction)
        {
        case 0:
        {
            if (x - 1 >= 0 && saveStep[x - 1][y] && maze[x - 1][y])
            {
                node cur1(x - 1, y);
                saveStep[x - 1][y] = false;
                Path.push(cur1);
            }
            break;
        }
        case 1:
        {
            if (y - 1 >= 0 && saveStep[x][y - 1] && maze[x][y - 1])
            {
                node cur1(x, y - 1);
                saveStep[x][y - 1] = false;
                Path.push(cur1);
            }
            break;
        }
        case 2:
        {
            if (x + 1 < 5 && saveStep[x + 1][y] && maze[x + 1][y])
            {
                node cur1(x + 1, y);
                saveStep[x + 1][y] = false;
                Path.push(cur1);
            }
            break;
        }
        case 3:
        {
            if (y + 1 < 5 && saveStep[x][y + 1] && maze[x][y + 1])
            {
                node cur1(x, y + 1);
                saveStep[x][y + 1] = false;
                Path.push(cur1);
            }
            break;
        }
        default:
        {
            saveStep[cur.x][cur.y] = true;
            Path.pop();
        }
        }
    }
    return false; // Stack rỗng = không có đường đi
}
int main()
{
    // Maze matrix
    int maze[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 1, 0}};

    // Food coordinates
    int fx = 1, fy = 4;

    cout << canEatFood(maze, fx, fy);
}