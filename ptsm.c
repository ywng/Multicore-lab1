/* parallel travelling salesman problem
 * Author: Yik Wai Ng
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int threads, cities, bestDist = 9999999;
int* bestPath;

void searchPath(int level, int city, int cost, int** matrix, int path[], int visited[])
{
    if(cost>=bestDist) return;
    if(level==cities) {
        #pragma omp critical
        if(cost<bestDist) {
            bestDist = cost;

            #pragma omp parallel
            for(int k=0; k<cities; k++) {
                bestPath[k]=path[k];
            }
        }
    }


    for(int i=0; i<cities; i++) {
        #pragma omp critical
        if(i==city || visited[i]) continue;

        #pragma omp critical
        path[level] = i;
        #pragma omp critical
        visited[i] = 1;

        searchPath(level+1, i, cost+matrix[city][i], matrix, path, visited);

        #pragma omp critical
        visited[i] = 0;
    }

}

int main(int argc, char **argv)
{
    char* inputFile;
    cities = atoi(argv[1]);
    threads = atoi(argv[2]);
    inputFile = argv[3];

    //set number of parallel threads
    omp_set_num_threads(threads);

    int **matrix;
    matrix = malloc(cities * sizeof(int *));
    for(int i=0; i<cities; i++) {
        matrix[i] = malloc(cities * sizeof(int));
    }

    FILE *file=fopen(inputFile, "r");

    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++) {
              int n;
              fscanf(file, "%d", &n);
              matrix[i][j] = n;
        }
    }

    int visited[cities];
    int path[cities];
    bestPath = malloc(cities * sizeof(int));

    # pragma omp parallel
    for(int i=0; i<cities; i++) {
        visited[i] = 0;
    }

    visited[0] = 1;
    path[0] = 0;
    searchPath(1, 0, 0, matrix, path, visited);

    printf("Best path: ");
    for(int i=0; i<cities; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("\n");
    printf("Distance: %d\n", bestDist);
}

