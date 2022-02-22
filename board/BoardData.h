#include <vector>
#include <cstdlib>
#include <ctime>
#include<iostream>

using namespace std;

class BoardData
{
private:
    vector<vector<int>> data;
    size_t score = 0;
public:
    bool isGameOver = false;
    BoardData(int SIZE) {
        data = initBoard(SIZE);
    }

    vector<vector<int>> getData() {
        return data;
    }

    size_t getScore() {
        return score;
    }
    // random in [a,b)
    int randRange(int a, int b)
    {
        srand(time(NULL));

        return a + rand() % (b - a);
    }

    vector<vector<int>> initBoard(int SIZE)
    {
        vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));
        return board;
    }
    // Copy from
    // https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
    // So bad at math
    void rotateBoard()
    {
        int SIZE = data.size();
        // Consider all squares one by one
        for (int x = 0; x < SIZE / 2; x++)
        {
            // Consider elements in group
            // of 4 in current square
            for (int y = x; y < SIZE - x - 1; y++)
            {
                // Store current cell in
                // temp variable
                int temp = data[x][y];

                // Move values from right to top
                data[x][y] = data[y][SIZE - 1 - x];

                // Move values from bottom to right
                data[y][SIZE - 1 - x] = data[SIZE - 1 - x][SIZE - 1 - y];

                // Move values from left to bottom
                data[SIZE - 1 - x][SIZE - 1 - y] = data[SIZE - 1 - y][x];

                // Assign temp to left
                data[SIZE - 1 - y][x] = temp;
            }
        }
    }

    // Find arr[i] = arr[x] or 0 from x to stop
    int find(vector<int> arr, int x, int stop)
    {
        if (x == 0)
        {
            // x == 0 than do nothing
            return x;
        }
        else
        {
            for (int i = x - 1; i >= stop; i--)
            {
                if (!(arr[i] == 0))
                {
                    // The merge is impossible, so return next pos
                    if (arr[i] != arr[x])
                    {
                        return i + 1;
                    }
                    else
                    {
                        return i;
                    }
                }
            }

            return stop;
        }
    }

    bool shiftArray(vector<int> &arr)
    {
        // 0 4 0 0
        bool success = false;
        int index = 0, stop = 0;
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] != 0)
            {
                index = find(arr, i, stop);
                // Move or merge
                if (index != i)
                {
                    success = true;
                    // Merge
                    if (arr[index] == arr[i])
                    {
                        arr[index] += arr[i];
                        arr[i] = 0;
                        // avoid double merge
                        stop = index + 1;
                        //score
                        score += arr[index];
                        // cout << score;
                    }
                    else
                    {
                        // Move
                        arr[index] = arr[i];
                        arr[i] = 0;
                    }
                }
            }
        }

        return success;
    }

    bool moveLeft()
    {
        bool success = false;
        for (size_t i = 0; i < data.size(); i++)
        {
            // if one row is valid, that's a valid move
            success = success | shiftArray(data[i]);
        }
        return success;
    }

    bool moveDown()
    {
        // We rotate the table to moveLeft case
        rotateBoard();
        rotateBoard();
        rotateBoard();
        bool success = moveLeft();
        // Return original data
        rotateBoard();

        return success;
    }

    bool moveUp()
    {
        // We rotate the table to moveLeft case
        rotateBoard();
        bool success = moveLeft();
        // Return original 
        rotateBoard();
        rotateBoard();
        rotateBoard();

        return success;
    }

    bool moveRight()
    {
        // We rotate the table to moveLeft case
        rotateBoard();
        rotateBoard();
        bool success = moveLeft();
        // Return original 
        rotateBoard();
        rotateBoard();

        return success;
    }

    void addRandom()
    {
        // we use a list to store empty croods
        int SIZE = data.size();
        int emptyCroods[SIZE * SIZE][2];
        int len = 0;
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                if (data[i][j] == 0)
                {
                    emptyCroods[len][0] = i;
                    emptyCroods[len][1] = j;

                    len++;
                }
            }
        }

        if(len == 0) {
            return;
        }
        int pos = randRange(0, len);
        data[emptyCroods[pos][0]][emptyCroods[pos][1]] = randRange(1, 3) * 2;
    }

    // add rand
    // check move
    // check empty

    int countEmpty()
    {
        int count = 0;
        int SIZE = data.size();
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                if (data[i][j] == 0)
                {
                    count++;
                }
            }
        }

        return count;
    }

    bool canMoveLeft()
    {
        int SIZE = data.size();
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 1; j < SIZE; j++)
            {
                if (data[i][j] == data[i][j - 1])
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool isGameEnded()
    {
        bool notEnd = false;
        if (countEmpty() > 0)
        {
            return false;
        }

        notEnd |= canMoveLeft();
        rotateBoard();
        notEnd |= canMoveLeft();
        rotateBoard();
        notEnd |= canMoveLeft();
        rotateBoard();
        notEnd |= canMoveLeft();
        rotateBoard();

        // rotate 4 time and check left, right, up, down

        return !notEnd;
    }
};