#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

void initChessboard(int n, int chessboard[n][n]);
void knight_travails(int n, int chessboard[n][n], int x_src, int y_src, int x_dst, int y_dst, int knight_path[n * n][2]);
void print_board(int n, int chessboard[n][n]);
int print_path(int x_dst, int y_dst, int x_src, int y_src, int m, int n, int chessboard[n][n]);
void initPath(int n, int knight_path[n * n][2]);

typedef struct Coordinates
{
    int x;
    int y;
} Coordinates;

typedef struct Queue
{
    Coordinates queue[100];
    int count;
} Q;

int nextX(int x, int move, int n)
{
    switch(move){
        case 0: x=x+1; break;
        case 1: x=x+2; break;
        case 2: x=x+2; break;
        case 3: x=x+1; break;
        case 4: x=x-1; break;
        case 5: x=x-2; break;
        case 6: x=x-2; break;
        case 7: x=x-1; break;
    }
    if (x < 0 || x > 8)
    {
        return -1;
    }
    else
    {
        return x;
    }
}

int nextY(int y, int move, int n)
{
    switch(move){
        case 0: y=y-2; break;
        case 1: y=y-1; break;
        case 2: y=y+1; break;
        case 3: y=y+2; break;
        case 4: y=y+2; break;
        case 5: y=y+1; break;
        case 6: y=y-1; break;
        case 7: y=y-2; break;
    }

    if (y < 0 || y > n)
    {
        return -1;
    }
    else
    {
        return y;
    }
}

int main()
{
    int n, x_src, y_src, x_dst, y_dst, ans = 0;

    printf("Enter the size of the chessboard: ");
    scanf("%d", &n);

    int chessboard[n][n];
    int knight_path[n * n][2];
    initChessboard(n, chessboard);
    initPath(n, knight_path);

    printf("The chessboard has been initialized:\n");

    print_board(n, chessboard);

    printf("\nEnter the source y-coordinates: ");
    scanf("%d", &x_src);
    printf("Enter the source x-coordinates: ");
    scanf("%d", &y_src);

    printf("Enter the destination y-coordinates: ");
    scanf("%d", &x_dst);
    printf("Enter the destination x-coordinates: ");
    scanf("%d", &y_dst);

    if (0 <= x_src && 0 <= y_src && 0 <= x_dst && 0 <= y_dst && x_src < n && y_src < n && x_dst < n && x_dst < n)
    {
        knight_travails(n, chessboard, x_src, y_src, x_dst, y_dst, knight_path);
    }
    else
    {
        printf("Invalid positions");
        return 0;
    }

    if ((n == 3 && (x_dst == 1 && y_dst == 1) || (x_src == 1 && y_src == 1)) || n < 3)
    {
        printf("Knight cannot reach this square");
        return 0;
    }
    else
    {
        printf("\nOrder of traversal:\n");
        print_board(n, chessboard);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ans < chessboard[i][j])
            {
                ans = chessboard[i][j];
            }
        }
        printf("\n");
    }
    printf("The knight's travail is %d squares\n", ans - 1);
    printf("The path taken is ");
    print_path(x_dst, y_dst, x_src, y_src, ans, n, chessboard);

    return 0;
}

void initChessboard(int n, int chessboard[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            chessboard[i][j] = 0;
        }
    }
}

void initPath(int n, int knight_path[n * n][2])
{
    for (int i = 0; i < n * n; i++)
    {
        knight_path[i][0] = -1;
        knight_path[i][1] = -1;
    }
}

void print_board(int n, int chessboard[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", chessboard[i][j]);
        }
        printf("\n");
    }
}

void knight_travails(int n, int chessboard[n][n], int x_src, int y_src, int x_dst, int y_dst, int knight_path[n * n][2])
{
    Coordinates q[100];
    int f = 0, r = -1;

    q[0].x = x_src;
    q[0].y = y_src;
    r++;
    chessboard[x_src][y_src] = 1;
    knight_path[0][0] = x_src;
    knight_path[0][1] = y_src;

    while (f <= r)
    {
        int x = q[f].x;
        int y = q[f].y;
        f++;

        for (int i = 0; i < 8; i++)
        {
            int new_x = nextX(x, i, n);
            int new_y = nextY(y, i, n);

            if (new_x != -1 && new_y != -1 && chessboard[new_x][new_y] == 0)
            {
                r++;
                q[r].x = new_x;
                q[r].y = new_y;
                chessboard[new_x][new_y] = chessboard[x][y] + 1;

                knight_path[chessboard[new_x][new_y] - 1][0] = new_x;
                knight_path[chessboard[new_x][new_y] - 1][1] = new_y;

                if (new_x == x_dst && new_y == y_dst)
                {
                    return;
                }
            }
        }
    }
}

int print_path(int x_dst, int y_dst, int x_src, int y_src, int m, int n, int chessboard[n][n])
{
    int knight_path[m][2];
    int x = x_dst;
    int y = y_dst;
    int dist = m - 1;

    while (x != x_src || y != y_src)
    {
        knight_path[dist][0] = x;
        knight_path[dist][1] = y;
        
        for (int i = 0; i < 8; i++)
        {
            int new_x = nextX(x, i, n);
            int new_y = nextY(y, i, n);

            if (new_x < n && 0 <= new_x && new_y < n && 0 <= new_y && chessboard[new_x][new_y] == dist)
            {
                x = new_x;
                y = new_y;
                dist--;
                break;
            }
        }
    }

    printf("(%d,%d)", x_src, y_src);
    for (int i = 1; i < m; i++)
    {
        printf("->(%d,%d)", knight_path[i][0], knight_path[i][1]);
    }
    return 0;
}