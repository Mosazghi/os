#include <stdio.h>
#define START_NUMBERLOLLIPOPS 100
#define MAX_AT_ONCE 30

int main() {
  int numcandy;
  double cost;
  int numberlollipopps;
  double totalcost;

  numberlollipopps = START_NUMBERLOLLIPOPS; // set start value to our constant
  totalcost = 0;

  while (numberlollipopps > 0) {

    printf("(%d left) How many lollipops do you want (-1 quits): ",
           numberlollipopps);
    // scanf("%d", &numcandy);
    if (numcandy ==
        -1)  // since this if has only one statement brackets are not needed
      break; // exit out of the while loop
    else if (numcandy > MAX_AT_ONCE || numcandy <= 0 ||
             numcandy > numberlollipopps) {
      printf("You cannot have that many, enter another number\n");
    } else {
      cost = 0.55 * numcandy;
      printf("\nPlease pay $%.2f to the cashier!\n", cost);
      totalcost = totalcost + cost;
      numberlollipopps = numberlollipopps - numcandy;
    }
  }
  printf("All the lollipopps have been sold for : $%.2f\n", totalcost);

  return 0;
}
