#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateAdjacencyMatrix(int n, int **graph) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j];
            }
        }
    }
}

void printAdjacencyMatrix(int n, int **graph) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int calculateEdgesByAdjacencyMatrix(int n, int **graph) {
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edgeCount += graph[i][j];
        }
    }
    return edgeCount;
}

void findSpecialVerticesByAdjacencyMatrix(int n, int **graph) {
    int degree;
    int isolated = 0, pendant = 0, dominating = 0;

    for (int i = 0; i < n; i++) {
        degree = 0;
        for (int j = 0; j < n; j++) {
            degree += graph[i][j];
        }

        if (degree == 0) {
            printf("Вершина %d: изолированная (по матрице смежности)\n", i + 1);
            isolated++;
        } else if (degree == 1) {
            printf("Вершина %d: концевая (по матрице смежности)\n", i + 1);
            pendant++;
        } else if (degree == n - 1) {
            printf("Вершина %d: доминирующая (по матрице смежности)\n", i + 1);
            dominating++;
        }
    }

    printf("\nПо матрице смежности: изолированных вершин = %d, конечных = %d, доминирующих = %d\n", isolated, pendant, dominating);
}

void generateIncidenceMatrix(int n, int **graph, int **incidence, int *edgeCount) {
    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] == 1) {
                incidence[i][edgeIndex] = 1;
                incidence[j][edgeIndex] = 1;
                edgeIndex++;
            }
        }
    }
    *edgeCount = edgeIndex;
}

void printIncidenceMatrix(int n, int edgeCount, int **incidence) {
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incidence[i][j]);
        }
        printf("\n");
    }
}

int calculateEdgesByIncidenceMatrix(int edgeCount) {
    return edgeCount;
}

void findSpecialVerticesByIncidenceMatrix(int n, int edgeCount, int **incidence) {
    int isolated = 0, pendant = 0, dominating = 0;

    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < edgeCount; j++) {
            degree += incidence[i][j];
        }

        if (degree == 0) {
            printf("Вершина %d: изолированная (по матрице инцидентности)\n", i + 1);
            isolated++;
        } else if (degree == 1) {
            printf("Вершина %d: концевая (по матрице инцидентности)\n", i + 1);
            pendant++;
        } else if (degree == n - 1) {
            printf("Вершина %d: доминирующая (по матрице инцидентности)\n", i + 1);
            dominating++;
        }
    }

    printf("\nПо матрице инцидентности: изолированных вершин = %d, конечных = %d, доминирующих = %d\n", isolated, pendant, dominating);
}

int main() {
    srand(time(0));

    int n;
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    if (n > 10) {
        printf("Количество вершин не может превышать 10\n");
        return 1;
    }

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    int **incidence = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        incidence[i] = (int *)calloc(n * (n - 1) / 2, sizeof(int));
    }

    int edgeCount;

    generateAdjacencyMatrix(n, graph);
    printAdjacencyMatrix(n, graph);

    int edgesAdjacency = calculateEdgesByAdjacencyMatrix(n, graph);
    printf("\nРазмер графа по матрице смежности: %d\n", edgesAdjacency);

    generateIncidenceMatrix(n, graph, incidence, &edgeCount);
    printIncidenceMatrix(n, edgeCount, incidence);

    int edgesIncidence = calculateEdgesByIncidenceMatrix(edgeCount);
    printf("\nРазмер графа по матрице инцидентности: %d\n", edgesIncidence);

    // Поиск специальных вершин по матрице смежности
    findSpecialVerticesByAdjacencyMatrix(n, graph);

    // Поиск специальных вершин по матрице инцидентности
    findSpecialVerticesByIncidenceMatrix(n, edgeCount, incidence);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
        free(incidence[i]);
    }
    free(graph);
    free(incidence);
    return 0;
}
