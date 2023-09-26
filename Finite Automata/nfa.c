#include "nfa.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "IntHashSet.c"

NFA new_NFA(int nstates) {
        NFA nfa = (NFA)malloc(sizeof(struct NFA));
        nfa->TotalStates = nstates;
        nfa->Accept = (int *)malloc(nstates*sizeof(int));
        nfa->AcceptIndex = 0;
        for (int i = 0; i < nfa->TotalStates; i++){
                nfa->TransitionTable[i] = (IntHashSet*)malloc(128*sizeof(IntHashSet));
        }
        for (int i = 0; i < nfa->TotalStates; i++) {
                for (int j = 0; j < 128; j++){
                        nfa->TransitionTable[i][j] = new_IntHashSet(nstates);
                }
        }
        return nfa;
}

IntHashSet NFA_get_transitions(NFA nfa, int state, char sym) {
    if (state > nfa->TotalStates || state<0) {
        return NULL;
    }
    int temp = (int)sym;
    return nfa->TransitionTable[state][temp];
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst) {
    int temp = (int) sym;
    IntHashSet_insert(nfa->TransitionTable[src][temp], dst);
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst) {
    for (int i = 0; i < strlen(str); i++) {
        int temp = (int)str[i];
        IntHashSet_insert(nfa->TransitionTable[src][temp], dst);
    }
}

void NFA_add_transition_all(NFA nfa, int src, int dst) {
    for (int i = 0; i < 128; i++) {
        IntHashSet_insert(nfa->TransitionTable[src][i], dst);
    }
}

void NFA_add_transition_Except(NFA nfa, int src, int n, int dst) {
    for (int i = 0; i < 128; i++) {
        if (i != n) {
            IntHashSet_insert(nfa->TransitionTable[src][i], dst);
        }
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value) {
    nfa->Accept[nfa->AcceptIndex]=state;
    nfa->AcceptIndex++;
}

bool NFA_get_accepting(NFA nfa, int state) {
    for (int i = 0; i < nfa->AcceptIndex; i++) {
        if (nfa->Accept[i] == state) {
            return 1;
        }
    }
    return 0;
}

bool NFA_execute(NFA nfa, char *input) {
    IntHashSet temp = new_IntHashSet(nfa->TotalStates);
    temp = NFA_get_transitions(nfa, 0, input[0]);
    IntHashSet temp1 = new_IntHashSet(nfa->TotalStates);
    IntHashSetIterator iterator;
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        iterator = IntHashSet_iterator(temp);
        while(IntHashSetIterator_hasNext(iterator)) {
            int element = IntHashSetIterator_next(iterator);
            IntHashSet_union(temp1, NFA_get_transitions(nfa, element, input[i]));
        }
        temp = temp1;
        temp1 = new_IntHashSet(nfa->TotalStates);
    }
    free(iterator);
    IntHashSet_free(temp1);
    IntHashSetIterator iterator1 = IntHashSet_iterator(temp);
    while (IntHashSetIterator_hasNext(iterator1)) {
        int element1 = IntHashSetIterator_next(iterator1);
        if (NFA_get_accepting(nfa, element1) == 1) {
            free(iterator1);
            IntHashSet_free(temp);
            return 1;
        }
    }
    free(iterator1);
    IntHashSet_free(temp);
    return 0;
}