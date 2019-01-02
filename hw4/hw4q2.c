#include <stdio.h>

int main()
{
  /*
    For input: 
    3 5 AFBRSNVFABBQMADAB
                       ^^
    first letter ______||
    second letter ______|

    We will going to get:
      0 1 2 3 4
    0 A F B R S
    1 N V F A B
    2 B Q M A D

    N = 3,
    M = 5

    And the response is:
    (0,0)(2,0)
    (0,0)(1,4)
    (1,3)(0,2)
    (1,3)(1,4)
    (2,3)(1,4)
    (2,3)(0,2)
  */

  int sizeN,
      sizeM,
      indexN,
      indexM,
      left,
      right,
      top,
      bottom;

  char firstLetter, secondLetter;

  scanf("%d", &sizeM);
  scanf("%d", &sizeN);

  char input[sizeM][sizeN];

  /* Remove space after N and M inputs */
  getchar();

  for (indexM = 0; indexM < sizeM; indexM++)
  {
    for (indexN = 0; indexN < sizeN; indexN++)
    {
      input[indexM][indexN] = getchar();
    }
  }

  firstLetter = getchar();
  secondLetter = getchar();

  /* REMOVE */
  /*
  for (indexM = 0; indexM < sizeM; indexM++)
  {
    for (indexN = 0; indexN < sizeN; indexN++)
    {
      putchar(input[indexM][indexN]);
    }
    putchar('\n');
  }
  */
  /* REMOVE */

  for (indexM = 0; indexM < sizeM; indexM++)
  {
    for (indexN = 0; indexN < sizeN; indexN++)
    {
      bottom = (indexN + 1 < sizeN) ? (indexN + 1) : (0);
      top = (indexN - 1 > -1) ? (indexN - 1) : (sizeN - 1);
      right = (indexM + 1 < sizeM) ? (indexM + 1) : (0);
      left = (indexM - 1 > -1) ? (indexM - 1) : (sizeM - 1);

      /* TOP */
      if (input[indexM][indexN] == firstLetter && input[indexM][top] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, indexM, top);
      /* BOTTOM */
      if (input[indexM][indexN] == firstLetter && input[indexM][bottom] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, indexM, bottom);
      /* RIGHT */
      if (input[indexM][indexN] == firstLetter && input[right][indexN] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, right, indexN);
      /* LEFT */
      if (input[indexM][indexN] == firstLetter && input[left][indexN] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, left, indexN);
      /* RIGHT TOP */
      if (input[indexM][indexN] == firstLetter && input[right][top] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, right, top);
      /* RIGHT BOTTOM */
      if (input[indexM][indexN] == firstLetter && input[right][bottom] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, right, bottom);
      /* LEFT TOP */
      if (input[indexM][indexN] == firstLetter && input[left][top] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, left, top);
      /* LEFT BOTTOM */
      if (input[indexM][indexN] == firstLetter && input[left][bottom] == secondLetter)
        printf("(%d,%d),(%d,%d)\n", indexM, indexN, left, bottom);
    }
  }

  return 0;
}
