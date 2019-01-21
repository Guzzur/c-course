#include <stdio.h>
#include <math.h>

#define MAX_BATTLE_SIZE (15)
#define CELL_SIZE (5)
#define MAX_MOVE_RANGE (25)
#define MAX_NORMAL_ATTACK_RANGE (10)
#define NORMAL_ATTACK_STRENGTH (10)

enum BattleResult
{
  POSITIVE_WIN,
  NEGATIVE_WIN,
  NO_RESULT
};

void initBattle(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int *actual_length, int *actual_width);
void initBattleActionOrder(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width, int *action_order);
void displayBoard(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width);
void attack(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate);
void move(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
          int first_length_index, int first_width_index, int second_length_index, int second_width_index);
double getDistance(int first_length_index, int first_width_index, int second_length_index, int second_width_index);
enum BattleResult getBattleResult(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width);
void findClosestEnemy(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                      int first_length_index, int first_width_index, int *closest_enemy_length, int *closest_enemy_width);

int main()
{
  int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE] = {{0}};
  int battlefield_action_order[2 * MAX_BATTLE_SIZE * MAX_BATTLE_SIZE + 1];
  int actual_length, actual_width, current_action_index = 0;
  int enemy_first_index, enemy_second_index;

  /* Here you need to add initialization of the battle, using "initBattle" function */

  while (NO_RESULT == getBattleResult(battlefield, actual_length, actual_width))
  {
    if (-1 == battlefield_action_order[current_action_index])
    { /* We finished iterating on all the soliders and have to create a new order according to new locations */
      /* call to the initBattleActionOrder function. */
    }
    /* manage the solider step here */

    /*The solider turn ended, so we need to move two steps ahead in the battlefield_action_index array, because we used here two values from the array: row and column numbers */
    current_action_index += 2;
  }

  switch (getBattleResult(battlefield, actual_length, actual_width))
  {
  case POSITIVE_WIN:
    printf("Positive win!\n");
    break;
  case NEGATIVE_WIN:
    printf("Negative win!\n");
    break;
  default:
    break;
  }
  displayBoard(battlefield, actual_length, actual_width);
  return 0;
}

void initBattle(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int *actual_length, int *actual_width)
{
  /* Fill me! */
}

void initBattleActionOrder(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width, int *action_order)
{
  int i, j, k = 0;
  for (i = 0; i < actual_length; i++)
  {
    for (j = 0; j < actual_width; j++)
    {
      if (0 != battlefield[i][j])
      {
        /* Store i and j at the next two available cells of the action_order array */
      }
    }
  }
  *(action_order + k) = -1; /* We store -1 to signal that in this place the action_order array is finished */
}

double getDistance(int first_length_index, int first_width_index, int second_length_index, int second_width_index)
{
  int length_delta = (second_length_index - first_length_index) * CELL_SIZE;
  int width_delta = (second_width_index - first_width_index) * CELL_SIZE;
  int value_to_square = length_delta * length_delta + width_delta * width_delta;
  return sqrt(value_to_square);
}

enum BattleResult getBattleResult(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width)
{
  /* Fill me! */
}

void displayBoard(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width)
{
  int i, j;
  for (i = 0; i < actual_length; i++)
  {
    for (j = 0; j < actual_width; j++)
    {
      printf("|%4d", battlefield[i][j]);
    }
    printf("|\n");
  }
}

void move(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
          int first_length_index, int first_width_index, int second_length_index, int second_width_index)
{

  /* Fill me! */
}

void attack(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate)
{
  /* Fill me! */
}

void findClosestEnemy(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                      int first_length_index, int first_width_index, int *closest_enemy_length, int *closest_enemy_width)
{
  /* Fill me! */
}
