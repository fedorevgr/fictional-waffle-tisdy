#ifndef LAB1_GRAPHICS_H
#define LAB1_GRAPHICS_H

#include <stdio.h>

#define PROMPT "Enter big number: "

#define printSepLine() printf("---------------------------------------------------------\n")

void
renderRuler(void);

#define renderPrompt() renderRuler(), printf(PROMPT)

#endif //LAB1_GRAPHICS_H
