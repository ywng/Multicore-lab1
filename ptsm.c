/* parallel travelling salesman problem
 * Author: Yik Wai Ng
 */

#include <stdio.h>
#include <stdlib.h>

int matrix[25][25], visited_cities[10], limit, cost = 0;


int main(int argc, char **argv)
{
      int threads, cities;
      char* inputFile;
      cities = atoi(argv[1]);
      threads = atoi(argv[2]);
      inputFile = argv[3];

      int **matrix;
      matrix = malloc(cities * sizeof(int *));
      for(int i=0; i<cities; i++) {
            matrix[i] = malloc(cities * sizeof(int));
      }

      FILE *file=fopen(inputFile,"r");

      for (int i = 0; i < cities; i++) {
            for (int j = 0; j < cities; j++) {
                  int n;
                  fscanf(file, "%d", &n);
                  printf("(%d,%d) = %d\n", i, j, n);
                  matrix[i][j] = n;
            }
      }



      printf("Best path: \n");
      printf("Distance: \n");
}