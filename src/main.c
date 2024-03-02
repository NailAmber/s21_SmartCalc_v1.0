#include "calculus.h"

int main(void) {
  char *string = "  -+-((((-((10 + 15) ^ 2)) / 1.5) - ((-((-(-1)) * (-(-5)))) * (-((325 ^ (-0.5)) * (-1.5))))) + ((-2) + (-4)))  ";
  char postfix[255] = {'\0'};
  infix_to_postfix(string, postfix);
  long double result;
  printf("postfix is %s\n", postfix);
  if (postfix_result(postfix, &result)) {
  } else {
    printf("result is %.7Lf\n", result);
  }
  printf("is number = %d", is_number("-0.5"));
  return 0;
}
