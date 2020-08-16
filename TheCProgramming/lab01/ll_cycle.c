#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    node *tortoise = head;
    node *hare = head;
    int i;
    while (1) {
        for (i = 1; i < 3; i++) {
            if ((hare + i) == NULL) {
                return 0;
            }
            hare += i;
        }
        tortoise++;
        if (hare == tortoise) {
            return 1;
        }
    }
}