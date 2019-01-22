#include <stdio.h>
#include <math.h>

#define MAX_BATTLE_SIZE (15)
#define CELL_SIZE (5)
#define MAX_MOVE_RANGE (25)
#define MAX_NORMAL_ATTACK_RANGE (10)
#define NORMAL_ATTACK_STRENGTH (10)
#define INFINITE_DISTANCE (999999)

#define FALSE 0
#define TRUE 1

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
int isEnemy(int myValue, int otherValue);

int closest_enemy_length, closest_enemy_width;

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
      initBattleActionOrder(battlefield, actual_length, actual_width, battlefield_action_order);
    }

    /* DEBUG
    displayBoard(battlefield, actual_length, actual_width);
    printf("Current player is at [%d,%d]\n",
           battlefield_action_order[current_action_index], battlefield_action_order[current_action_index + 1]);
    /* DEBUG */

    /* Manages the solider steps */
    findClosestEnemy(battlefield, actual_length, actual_width,
                     battlefield_action_order[current_action_index],
                     battlefield_action_order[current_action_index + 1],
                     &closest_enemy_length, &closest_enemy_width);

    /* Check if battle is possible, if there are enemies that are close enough */
    if (closest_enemy_length >= 0 && closest_enemy_width >= 0 &&
        battlefield[closest_enemy_length][closest_enemy_width] != 0 &&
        /*
        isEnemy(battlefield
                    [battlefield_action_order[current_action_index]]
                    [battlefield_action_order[current_action_index + 1]],
                battlefield[closest_enemy_length][closest_enemy_width]) &&
        */
        getDistance(battlefield_action_order[current_action_index],
                    battlefield_action_order[current_action_index + 1],
                    closest_enemy_length,
                    closest_enemy_width) <= MAX_NORMAL_ATTACK_RANGE)
    {
      /* DEBUG
      printf("-- Attacking [%d,%d] from range %.2f\n",
             closest_enemy_length,
             closest_enemy_width,
             getDistance(battlefield_action_order[current_action_index],
                         battlefield_action_order[current_action_index + 1],
                         closest_enemy_length, closest_enemy_width));
      /* DEBUG */

      attack(battlefield, closest_enemy_length, closest_enemy_width);
    }
    /* Did not find enemies, move */
    else
    {
      /* DEBUG
      printf("-- Moving [%d,%d] toward [%d,%d]\n",
             battlefield_action_order[current_action_index],
             battlefield_action_order[current_action_index + 1],
             closest_enemy_length, closest_enemy_width);
      /* DEBUG */

      move(battlefield, actual_length, actual_width,
           battlefield_action_order[current_action_index],
           battlefield_action_order[current_action_index + 1],
           closest_enemy_length, closest_enemy_width);
    }

    /* DEBUG
    printf("\n");
    /* DEBUG */

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
  int row, col, curr;
  scanf("%d", actual_length);
  scanf("%d", actual_width);

  for (row = 0; row < *actual_length; row++)
  {
    for (col = 0; col < *actual_width; col++)
    {
      scanf("%d", &curr);
      battlefield[row][col] = curr;
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
  int row, col;
  int new_row = first_length_index, new_col = first_width_index,
      curr_distance, prev_distance = INFINITE_DISTANCE, distance_from_origin,
      distance = getDistance(first_length_index,
                             first_width_index,
                             second_length_index,
                             second_width_index);

  for (col = actual_width - 1; col >= 0; col--)
  {
    for (row = actual_length - 1; row >= 0; row--)
    {
      curr_distance = getDistance(row, col, second_length_index, second_width_index);
      distance_from_origin = getDistance(row, col, first_length_index, first_width_index);

      if (curr_distance < prev_distance &&
          curr_distance < distance &&
          distance_from_origin < MAX_MOVE_RANGE &&
          battlefield[row][col] == 0)
      {
        /* DEBUG
        printf("---- Moving to [%d,%d]\n", row, col);
        /* DEBUG */

        new_row = row;
        new_col = col;
      }
      prev_distance = curr_distance;
    }
  }

  if (new_row != first_length_index || new_col != first_width_index)
  {
    battlefield[new_row][new_col] = battlefield[first_length_index][first_width_index];
    battlefield[first_length_index][first_width_index] = 0;
  }
}

void attack(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate)
{
  if (battlefield[attacked_first_coordinate][attacked_second_coordinate] > 0)
  {
    battlefield[attacked_first_coordinate][attacked_second_coordinate] -= NORMAL_ATTACK_STRENGTH;
    if (battlefield[attacked_first_coordinate][attacked_second_coordinate] < 0)
      battlefield[attacked_first_coordinate][attacked_second_coordinate] = 0;
  }
  else if (battlefield[attacked_first_coordinate][attacked_second_coordinate] < 0)
  {
    battlefield[attacked_first_coordinate][attacked_second_coordinate] += NORMAL_ATTACK_STRENGTH;
    if (battlefield[attacked_first_coordinate][attacked_second_coordinate] > 0)
      battlefield[attacked_first_coordinate][attacked_second_coordinate] = 0;
  }

  /* if (battlefield[attacked_first_coordinate][attacked_second_coordinate] == 0) do nothing */
}

void findClosestEnemy(int battlefield[MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                      int first_length_index, int first_width_index, int *closest_enemy_length, int *closest_enemy_width)
{
  int row, col, closest_enemy_distance = INFINITE_DISTANCE;

  *closest_enemy_length = -1;
  *closest_enemy_width = -1;

  for (row = actual_length - 1; row >= 0; row--)
  {
    for (col = 0; col < actual_width; col++)
    {
      if (battlefield[row][col] != 0 &&
          isEnemy(battlefield[first_length_index][first_width_index], battlefield[row][col]) &&
          getDistance(row, col, first_length_index, first_length_index) < closest_enemy_distance)
      {
        closest_enemy_distance = getDistance(row, col, first_length_index, first_width_index);
        *closest_enemy_length = row;
        *closest_enemy_width = col;
        /* DEBUG
        printf("-- Closest enemy to [%d,%d] is at [%d,%d], %dm far\n",
               first_length_index,
               first_width_index,
               row,
               col,
               closest_enemy_distance);
        /* DEBUG */
      }
    }
  }
}

int isEnemy(int myValue, int otherValue)
{
  /* DEBUG
  printf("-- Is enemy [%d] to [%d] = %d\n",
         myValue, otherValue, myValue * otherValue < 0);
  /* DEBUG */

  return myValue * otherValue < 0;
}
