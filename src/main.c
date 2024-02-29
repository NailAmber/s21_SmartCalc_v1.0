#include "calculus.h"

int main(void) {
  char *string = "5*6+(2-9)+1*2/2*51*(2/2)+3-3-(2+3)";
  char postfix[255];
  infix_to_postfix(string, postfix);

  printf("%s\n", postfix);

  return 0;
}
