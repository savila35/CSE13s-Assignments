#include "set.h"

#include <stdbool.h>
#include <stdio.h>

Set set_empty(void) {
    Set s = 0x00;
    return s;
}

Set set_universal(void) {
    Set u = 0xff;
    return u;
}

Set set_insert(Set s, int x) {
    s = s | (0x01 << x);
    return s;
}

Set set_remove(Set s, int x) {
    s = s & set_complement(0x01 << x);
    return s;
}

bool set_member(Set s, int x) {
    if (s & (0x01 << x)) {
        return true;
    }
    return false;
}

Set set_intersect(Set s, Set t) {
    s = s & t;
    return s;
}

Set set_difference(Set s, Set t) {
    s = s & set_complement(t);
    return s;
}

Set set_complement(Set s) {
    s = ~s;
    return s;
}
