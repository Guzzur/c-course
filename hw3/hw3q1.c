#include <stdio.h>

/*

1. Player enters input of chars with '!' in the end
2. If there is 'SUP' in the input - player gets $100
3. If there is 'N', the player loses $10 for each
4. If there is 'B'*3 or more, the player loses $20

*/
int main()
{
  int currChar = 0;
  int prevChar = 0;
  int prevPrevChar = 0;
  int strikeCount = 0;
  int negativeCount = 0;
  int blackCount = 0;

  int summary;

  while ((currChar = getchar()) != '!')
  {
    /* Check if 'SUP' is supplied */
    if (prevPrevChar == 'S' && prevChar == 'U' && currChar == 'P')
      strikeCount++;

    if (currChar == 'N')
      negativeCount++;

    if (currChar == 'B')
      blackCount++;

    /* Move chars backwards */
    prevPrevChar = prevChar;
    prevChar = currChar;
  }

  summary = (strikeCount * 100) - (negativeCount * 10) - ((blackCount >= 3) ? 20 : 0);

  if (summary >= 0)
    printf("You gain %d", summary);
  else
    printf("You lost %d", -summary);

  return 0;
}
