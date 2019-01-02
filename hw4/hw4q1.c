#include <stdio.h>
#include <math.h>

int main()
{
  int size,
      input,
      base,
      index,
      currDigit,
      output = 0;

  scanf("%d", &size);
  scanf("%x", &input);
  scanf("%d", &base);

  for (index = 0; input > 0 && index < size; input = input / base)
  {
    currDigit = input % base;
    output += currDigit * pow(base, index);
    /* printf("%d, %d, %d, %d\n", output, currDigit, base, index); */
    index++;
  }

  printf("%d\n", output);

  return 0;
}
