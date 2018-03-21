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
            for(int k=0; k<cities; k++) {
                bestPath[k]=path[k];
            }
        }

    }

    for(int i=0; i<cities; i++) {
        if(i==city || visited[i]) continue;

        path[level] = i;
        visited[i] = 1;

        searchPath(level+1, i, cost+matrix[city][i], matrix, path, visited);

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
    if(!file)
    {
        printf("Cannot open file %s\n", inputFile);
        exit(1);
    }

    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++) {
              int n;
              fscanf(file, "%d", &n);
              matrix[i][j] = n;
        }
    }

    bestPath = malloc(cities * sizeof(int));

    #pragma omp parallel for collapse(2)
    for(int i=1; i<cities; i++) {
        for(int j=1; j<cities; j++) {
            if(i!=j) {
                int visited[cities];
                for(int i=0; i<cities; i++) {
                    visited[i] = 0;
                }
                int path[cities];
                visited[0] = 1;
                path[0] = 0;
                visited[i] = 1;
                path[1] = i;
                visited[j] = 1;
                path[2] = j;

                searchPath(3, j, matrix[0][i]+matrix[i][j], matrix, path, visited);
            }
        }
    }



    printf("Best path: ");
    for(int i=0; i<cities; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("\n");
    printf("Distance: %d\n", bestDist);
}

