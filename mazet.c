#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char maze[1000][1000];
int contor = 0;



int move(int x, int y) {

    if (maze[x][y] == 'E') {

        maze[x][y] = '!';
        printf("End coordinates: (%d,%d)\n", x, y);
        return 1;
    }

    maze[x][y] = '.';
    contor++;

    if ((maze[x - 1][y] == ' ' || maze[x - 1][y] == 'E') && move(x - 1, y)) return 1;

    if ((maze[x][y + 1] == ' ' || maze[x][y + 1] == 'E') && move(x, y + 1)) return 1;

    if ((maze[x + 1][y] == ' ' || maze[x + 1][y] == 'E') && move(x + 1, y)) return 1;

    if ((maze[x][y - 1] == ' ' || maze[x][y - 1] == 'E') && move(x, y - 1)) return 1;

    maze[x][y] = ' ';
    contor--;
    
    return 0;
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {   
        printf("Error not enough arguments.\n");
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if(!input_file)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    
    if(!output_file)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    int maze_lines=0, maze_columns = 0,x,y;
    char start_x, start_y,line[1000];

    //linii si coloane
    while(fgets(line, 1000, input_file))
    {
        maze_lines++;
        if(strlen(line) > maze_columns)
            maze_columns = strlen(line);
    }

    printf("lines: %d \ncolumns: %d \n", maze_lines, maze_columns);

    rewind(input_file);

    // labirintul
    int i = 0;
    while(fgets(line, 1000, input_file))
    {
        for(int j = 0; j < maze_columns; j++)
            {
                maze[i][j] = line[j];
            }
        i++;
    }

    //gasirea startului
    for(x = 0; x < maze_lines; x++)
    {
        for(y = 0; y < maze_columns; y++)
            if(maze[x][y] == 'S') 
            {
                start_x = x;
                start_y = y;
                break;
            }
    }
    printf("Start coordinates: (%d,%d)\n", start_x, start_y); 

    move(start_x, start_y);
    
    //afisarea labirintului
    for(int i = 0; i < maze_lines; i++)
    {
        for(int j = 0; j < maze_columns; j++)
            fprintf(output_file, "%c", maze[i][j]);
    }
    printf("Number of steps: %d\n", contor);
    return 0;
}
