#include "calculus.h"

int main(void) {
  char *string = "10^10";
  char postfix[255];
  infix_to_postfix(string, postfix);
  long double result;
  printf("postfix is %s\n", postfix);
  postfix_result(postfix, &result);

  printf("result is %Lf\n", result);

  return 0;
}
