#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define N 3
#define MAX_STATES 10000

struct Node {
    int puzzle[N][N];
    int x, y;       // blank tile position
    int g;          // cost so far
    int h;          // heuristic
    int f;          // total cost = g+h
    Node* parent;
};

// Goal state
int goal[N][N] = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

// Manhattan distance heuristic
int calculateH(int puzzle[N][N]) {
    int h = 0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            int val = puzzle[i][j];
            if(val != 0) {
                int targetX = (val-1)/N;
                int targetY = (val-1)%N;
                h += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return h;
}

// Check if puzzle is goal
bool isGoal(int puzzle[N][N]) {
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(puzzle[i][j] != goal[i][j]) return false;
    return true;
}

// Print puzzle
void printPuzzle(int puzzle[N][N]) {
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------\n";
}

// Copy puzzle
void copyPuzzle(int src[N][N], int dest[N][N]) {
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            dest[i][j] = src[i][j];
}

// Moves: up, down, left, right
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

// Priority queue (manual)
Node* openList[MAX_STATES];
int openCount = 0;

Node* popBest() {
    int bestIdx = 0;
    for(int i=1;i<openCount;i++) {
        if(openList[i]->f < openList[bestIdx]->f)
            bestIdx = i;
    }
    Node* best = openList[bestIdx];
    for(int i=bestIdx;i<openCount-1;i++)
        openList[i] = openList[i+1];
    openCount--;
    return best;
}

void pushNode(Node* n) {
    if(openCount < MAX_STATES)
        openList[openCount++] = n;
}

// Reconstruct path
void printPath(Node* node) {
    if(node == NULL) return;
    printPath(node->parent);
    printPuzzle(node->puzzle);
}

// Solve 8 puzzle with A*
void solve(int start[N][N], int x, int y) {
    Node* startNode = new Node;
    copyPuzzle(start, startNode->puzzle);
    startNode->x = x; startNode->y = y;
    startNode->g = 0;
    startNode->h = calculateH(startNode->puzzle);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;

    pushNode(startNode);

    while(openCount > 0) {
        Node* current = popBest();

        if(isGoal(current->puzzle)) {
            cout << "Solution found!\n";
            printPath(current);
            return;
        }

        for(int dir=0; dir<4; dir++) {
            int newX = current->x + dx[dir];
            int newY = current->y + dy[dir];

            if(newX>=0 && newX<N && newY>=0 && newY<N) {
                Node* child = new Node;
                copyPuzzle(current->puzzle, child->puzzle);

                // Swap blank
                int temp = child->puzzle[newX][newY];
                child->puzzle[newX][newY] = child->puzzle[current->x][current->y];
                child->puzzle[current->x][current->y] = temp;

                child->x = newX; child->y = newY;
                child->g = current->g + 1;
                child->h = calculateH(child->puzzle);
                child->f = child->g + child->h;
                child->parent = current;

                pushNode(child);
            }
        }
    }
    cout << "No solution found.\n";
}

int main() {
    int start[N][N] = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };

    // Find blank tile (0)
    int x,y;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(start[i][j]==0) { x=i; y=j; }

    solve(start, x, y);

    return 0;
}
