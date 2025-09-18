#include <iostream>
using namespace std;

bool visited[100][100];

bool dfs(int x, int y, int jug1, int jug2, int target) {
    if(visited[x][y]) return false;
    visited[x][y] = true;

    cout << "(" << x << "," << y << ")\n";

    if(x == target || y == target) {
        cout << "Goal reached!\n";
        return true;
    }

    // next states
    State nextStates[6] = {
        {jug1, y}, // Fill Jug1
        {x, jug2}, // Fill Jug2
        {0, y},    // Empty Jug1
        {x, 0},    // Empty Jug2
        {x - min(x, jug2 - y), y + min(x, jug2 - y)}, // Pour Jug1 -> Jug2
        {x + min(y, jug1 - x), y - min(y, jug1 - x)}  // Pour Jug2 -> Jug1
    };

    for(int i=0; i<6; i++) {
        if(dfs(nextStates[i].x, nextStates[i].y, jug1, jug2, target))
            return true;
    }

    return false;
}

int main() {
    int jug1 = 4, jug2 = 3, target = 2;
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) visited[i][j] = false;

    dfs(0, 0, jug1, jug2, target);
    return 0;
}
