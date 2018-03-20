#include<stdio.h>
 
int matrix[25][25], visited_cities[10], limit, cost = 0;
 
int tsp(int c)
{
      int count, nearest_city = 999;
      int minimum = 999, temp;
      for(count = 0; count < limit; count++)
      {
            if((matrix[c][count] != 0) && (visited_cities[count] == 0))
            {
                  if(matrix[c][count] < minimum)
                  {
                        minimum = matrix[count][0] + matrix[c][count];
                  }
                  temp = matrix[c][count];
                  nearest_city = count;
            }
      }
      if(minimum != 999)
      {
            cost = cost + temp;
      }
      return nearest_city;
}
 
void minimum_cost(int city)
{
      int nearest_city;
      visited_cities[city] = 1;
      printf("%d ", city + 1);
      nearest_city = tsp(city);
      if(nearest_city == 999)
      {
            nearest_city = 0;
            printf("%d", nearest_city + 1);
            cost = cost + matrix[city][nearest_city];
            return;
      }
      minimum_cost(nearest_city);
}
 
int main(int argc, char **argv)
{ 
      int threads, cities;
      cities = argv[1];
      threads = argv[2];
      char[] input = argv[3];

      int **matrix;
      matrix = malloc(cities * sizeof(int *));
      for(int i=0; i<cities; i++) {
            matrix[i] = malloc(cities * sizeof(int));
      }

      FILE *file=fopen(input,"r")

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