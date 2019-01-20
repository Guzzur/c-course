#include <stdio.h>
#define MAX_SIZE 15
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define ASCII_NUM_OFFSET 48
#define ASCII_CHAR_OFFSET 55

int main()
{
  int size,
      base,
      index,
      output = 0,
      powIndex,
      pow;

  char currDigit, inputChar[MAX_SIZE];

  scanf("%d", &size);

  getchar();

  index = 0;
  while ((currDigit = getchar()) && (currDigit != ' ') && (index < size))
  {
    inputChar[index] = currDigit;
    index++;
  }

  scanf("%d", &base);

  for (index = size-1; index >= 0; index--)
  {
    if (inputChar[index] >= ASCII_CHAR_OFFSET)
        currDigit = inputChar[size-index-1] - ASCII_CHAR_OFFSET;
    else
        currDigit = inputChar[size-index-1] - ASCII_NUM_OFFSET;

    pow = 1;
    for (powIndex = index; powIndex > 0; powIndex--)
    {
        pow *= base;
    }
    output += currDigit * pow;
    /* printf("output %d, pow %d, currDigit %d, base %d, inputChar %d, index %d\n", output, pow, currDigit, base, inputChar[index], index); */
  }

  printf("%d\n", output);

  return 0;
}
