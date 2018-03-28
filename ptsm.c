/* parallel travelling salesman problem
 * Author: Yik Wai Ng
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int threads, cities, bestDist = 9999999;
int* bestPath;

void searchPath(int level, int city, int cost, int** matrix, int path[], int visited[]) {
    //the subtree search ends if the cost up to here is already >= the best path we have so far
    if(cost>=bestDist) return;

    if(level==cities) {
        //we need critical section here as different subtree search may find a better path at the same time
        #pragma omp critical
        if(cost<bestDist) {
            //update the best path cost and the best path content
            bestDist = cost;
            for(int k=0; k<cities; k++) {
                bestPath[k]=path[k];
            }
        }

    }

    //we don't need critical section here as we don't parallel the search of subtree
    for(int i=0; i<cities; i++) {
        if(i==city || visited[i]) continue;

        path[level] = i;
        visited[i] = 1;

        searchPath(level+1, i, cost+matrix[city][i], matrix, path, visited);

        visited[i] = 0;
    }

}

int main(int argc, char **argv) {
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
    if(!file) {
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

    //to store the best path found
    bestPath = malloc(cities * sizeof(int));

    /* I decide to unroll the first two level or the combination tree. Then, we start from level 3 to do the path search.
     * We can treat each of these level 3 starting point search as a task and we are doing task parallelism.
     * The unrolling make sure the load for the given number of threads can be distributed evenly.
     */
    #pragma omp parallel for collapse(2)
    for(int i=1; i<cities; i++) {
        for(int j=1; j<cities; j++) {
            if(i!=j) {
                //visited[] and path[] are private to the thread
                int visited[cities];
                for(int i=0; i<cities; i++) {
                    visited[i] = 0;
                }
                int path[cities];

                //we update the visited[] and path[] based on the first two cities we choose
                //and then start the search of the remaining subtree
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

