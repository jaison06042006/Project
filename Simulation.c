#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX];
int nodes = 0;

int stack[MAX];
int top = -1;
 
int path[MAX];
int pathLen = 0;

void push(int v) {
    if (top == MAX - 1) return;
    stack[++top] = v;
}

int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

void resetStack() {
    top = -1;
}

void addConnection(int u, int v) {
    if (u >= nodes || v >= nodes) {
        printf("Invalid nodes!\n");
        return;
    }
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void displayNetwork() {
    printf("\nNetwork Topology (Adjacency Matrix):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void transmitPacket(int src, int dest) {
    if (src >= nodes || dest >= nodes) {
        printf("Invalid nodes!\n");
        return;
    }

    int visited[MAX] = {0};
    int parent[MAX];
    for (int i = 0; i < MAX; i++) parent[i] = -1;

    resetStack();
    push(src);
    visited[src] = 1;

    int found = 0;
    while (top != -1) {
        int current = pop();
        printf("Packet at Node %d\n", current);

        if (current == dest) {
            found = 1;
            break;
        }
        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                push(i);
                visited[i] = 1;
                parent[i] = current;
            }
        }
    }

    if (!found) {
        printf("No path found from Node %d to Node %d\n", src, dest);
        return;
    }

    
    pathLen = 0;
    for (int v = dest; v != -1; v = parent[v]) {
        path[pathLen++] = v;
    }

    printf("Packet successfully delivered!\nPath: ");
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    int choice, u, v, src, dest;

    printf("Enter number of nodes in network: ");
    scanf("%d", &nodes);

    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            graph[i][j] = 0;

    while (1) {
        printf("\n--- Computer Network Simulation ---\n");
        printf("1. Add Connection\n");
        printf("2. Display Network Topology\n");
        printf("3. Transmit Packet\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter nodes (u v) to connect: ");
                scanf("%d %d", &u, &v);
                addConnection(u, v);
                break;
            case 2:
                displayNetwork();
                break;
            case 3:
                printf("Enter Source and Destination nodes: ");
                scanf("%d %d", &src, &dest);
                transmitPacket(src, dest);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}