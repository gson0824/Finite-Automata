#include "dfa.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

DFA new_DFA(int nstates) {
    DFA dfa = (DFA)malloc(sizeof(struct DFA));
    dfa->TotalStates = nstates;
    dfa->Accept = (int *)malloc(sizeof(int)*nstates);
    dfa->AcceptIndex = 0;
    for (int i = 0; i < dfa->TotalStates ;i++) {
        dfa->TransitionTable[i] = malloc(sizeof(int)*128);
    }
    for (int i = 0; i < dfa->TotalStates; i++) {
        for(int j = 0; j < 128; j++) {
            dfa->TransitionTable[i][j]--;
        }
    }
    return dfa;
}

int DFA_get_transition(DFA dfa, int src, char sym) {
    if (src > dfa->TotalStates) {
        return -1;
    }
    if (src < 0){
        return -1;
    }
    int temp = (int)sym;
    return dfa->TransitionTable[src][temp];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int temp = (int)sym;
    dfa->TransitionTable[src][temp] = dst;
}

void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    for (int i = 0; i < strlen(str); i++) {
        int temp = (int)str[i];
        dfa->TransitionTable[src][temp] = dst;
    }
}

void DFA_set_transition_all(DFA dfa, int src, int dst) {
    for (int i = 0; i < 128; i++) {
        dfa->TransitionTable[src][i] = dst;
    }
}

void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa->Accept[dfa->AcceptIndex] = state;
    dfa->AcceptIndex++;
}

bool DFA_get_accepting(DFA dfa, int state) {
    for(int i = 0; i < dfa->AcceptIndex; i++) {
        if (dfa->Accept[i] == state) {
            return 1;
        }
    }
    return 0;
}

bool DFA_execute(DFA dfa, char *input) {
    int temp = DFA_get_transition(dfa, 0, input[0]);
    for (int i = 1; i < strlen(input); i++) {
        temp = DFA_get_transition(dfa, temp, input[i]);
        if (temp == -1) {
            return false;
        }
    }
    return DFA_get_accepting(dfa, temp);
}

void DFA_set_transition_all_except(DFA dfa, int src, int dst, int n) {
    for (int i = 0; i < 128; i++) {
        if (i != n) {
            dfa->TransitionTable[src][i] = dst;
        }
    }
}