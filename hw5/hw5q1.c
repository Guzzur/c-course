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

  /* Initialization of the battle, using "initBattle" function */
  initBattle(battlefield, &actual_length, &actual_width);
  battlefield_action_order[current_action_index] = -1;

  while (NO_RESULT == getBattleResult(battlefield, actual_length, actual_width))
  {
    if (-1 == battlefield_action_order[current_action_index])
    {
      /* We finished iterating on all the soliders and have to create a new order according to new locations */
      initBattleActionOrder(battlefield, actual_length, actual_width, action_order);
    }

    /* manage the solider step here */

    /* The solider turn ended, so we need to move two steps ahead in the battlefield_action_index array, because */
    /* we used here two values from the array: row and column numbers */
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
  int row, col;
  scanf("%d", &actual_length);
  scanf("%d", &actual_width);

  for (row = 0; row < actual_length; row++)
  {
    for (col = 0; col < actual_width; col++)
    {
      scanf("%d", battlefield[row][col]);
    }
  }
}

void initBattleActionOrder(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width, int *action_order)
{
  int row, col, combined = 0;
  for (row = 0; row < actual_length; row++)
  {
    for (col = 0; col < actual_width; col++)
    {
      if (0 != battlefield[row][col])
      {
        /* Stores row and col at the next two available cells of the action_order array */
        *(action_order + combined++) = row;
        *(action_order + combined++) = col;
      }
    }
  }
  *(action_order + combined) = -1; /* We store -1 to signal that in this place the action_order array is finished */
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
  int row, col, negatives = 0, positives = 0;
  for (row = 0; row < actual_length; row++)
  {
    for (col = 0; col < actual_width; col++)
    {
      if (battlefield[row][col] > 0)
        positives++;
      else if (battlefield[row][col] < 0)
        negatives++;
    }
  }
  return (negatives > 0 && positives == 0) ? NEGATIVE_WIN : ((negatives == 0 && positives > 0) ? POSITIVE_WIN : NO_RESULT);
}

void displayBoard(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width)
{
  int row, col;
  for (row = 0; row < actual_length; row++)
  {
    for (col = 0; col < actual_width; col++)
    {
      printf("|%4d", battlefield[row][col]);
    }
    printf("|\n");
  }
}

void move(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
          int first_length_index, int first_width_index, int second_length_index, int second_width_index)
{
}

void attack(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate)
{
  if (battlefield[attacked_first_coordinate][attacked_second_coordinate] > 0)
    battlefield[attacked_first_coordinate][attacked_second_coordinate] -= NORMAL_ATTACK_STRENGTH;
  else if (battlefield[attacked_first_coordinate][attacked_second_coordinate] < 0)
    battlefield[attacked_first_coordinate][attacked_second_coordinate] += NORMAL_ATTACK_STRENGTH;

  /* if (battlefield[attacked_first_coordinate][attacked_second_coordinate] == 0) do nothing */
}

void findClosestEnemy(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                      int first_length_index, int first_width_index, int *closest_enemy_length, int *closest_enemy_width)
{
  int row, col;
  int sign = (battlefield[actual_length][actual_width] > 0) ? 1 : -1;
  for (row = first_length_index; row < first_length_index + closest_enemy_length; row++)
  {
    for (col = first_width_index + closest_enemy_width; col = first_width_index; col--)
    {
      if (isEnemy(sign, battlefield[row][col]))
      {
        /* TODO: Do I need to return something here? But it is a void func... */
      }
    }
  }
}

int isEnemy(int myValue, int otherValue)
{
  return myValue * otherValue < 0;
}
