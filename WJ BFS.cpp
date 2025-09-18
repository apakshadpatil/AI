#include <iostream>
using namespace std;

struct State {
    int x, y; // jug1, jug2
};

const int MAX = 100; // limit for queue
State queueArr[MAX];
int frontIdx = 0, rearIdx = 0;

bool visited[100][100]; // visited states

void enqueue(State s) {
    if(rearIdx < MAX) queueArr[rearIdx++] = s;
}

State dequeue() {
    return queueArr[frontIdx++];
}

bool isEmpty() {
    return frontIdx == rearIdx;
}

bool bfs(int jug1, int jug2, int target) {
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) visited[i][j] = false;

    enqueue({0,0});

    while(!isEmpty()) {
        State s = dequeue();

        if(visited[s.x][s.y]) continue;
        visited[s.x][s.y] = true;

        cout << "(" << s.x << "," << s.y << ")\n";

        if(s.x == target || s.y == target) {
            cout << "Goal reached!\n";
            return true;
        }

        // possible states
        State nextStates[6] = {
            {jug1, s.y}, // Fill Jug1
            {s.x, jug2}, // Fill Jug2
            {0, s.y},    // Empty Jug1
            {s.x, 0},    // Empty Jug2
            {s.x - min(s.x, jug2 - s.y), s.y + min(s.x, jug2 - s.y)}, // Pour Jug1 -> Jug2
            {s.x + min(s.y, jug1 - s.x), s.y - min(s.y, jug1 - s.x)}  // Pour Jug2 -> Jug1
        };

        for(int i=0; i<6; i++) {
            if(!visited[nextStates[i].x][nextStates[i].y]) {
                enqueue(nextStates[i]);
            }
        }
    }
    cout << "No solution found.\n";
    return false;
}

int main() {
    int jug1 = 4, jug2 = 3, target = 2;
    bfs(jug1, jug2, target);
    return 0;
}
