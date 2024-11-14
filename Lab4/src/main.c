#include "Service.h"
#include "primitives/PrimitiveInput.h"
#include <stdio.h>

#define PROMPT                                                                 \
  "Input program:\n"                                                           \
  " 0 - Static array stack\n"                                                  \
  " 1 - List stack\n"                                                          \
  " 2 - Run experiment\n"                                                      \
  " 3 - Exit\n"

typedef enum { STACK, LIST_STACK, EXPERIMENT, EXIT, OPT_ERROR } OPTIONS;

int main(void) {
  unsigned long option;
  do {
    printf(PROMPT);
    if (inputUnsigned(&option) == INPUT_OK) {
      switch (option) {
      case STACK:
        serviceStack();
        break;
      case LIST_STACK:
        serviceListStack();
        break;
      case EXPERIMENT:
        serviceExperiment();
        break;
      case EXIT:
        break;
      default:
        option = OPT_ERROR;
      }
    } else
      option = OPT_ERROR;

    if (option == OPT_ERROR)
      printf("Unsupported option\n");
  } while (option != EXIT);

  return 0;
}
