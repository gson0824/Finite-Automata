#include <stdio.h>
#include "dfa.c"
#include <string.h>
#include "nfa.c"

void DFA_run(DFA dfa, char *input) {
    if (DFA_execute(dfa, input) == true) { 
        printf("Result for input %s: true\n",input);
    }
    else {
        printf("Result for input %s: false\n",input);
    }
}

void DFA_repl(DFA dfa) {
    while(1) {
        printf("Enter an input ('quit' to quit): ");
        char input[128];
        fgets(input, 128, stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp("quit", input) == 0) {
            break;
        }
        else {
            DFA_run(dfa, input);
        }
    }
}

void NFA_run(NFA nfa, char *input) {
    if (NFA_execute(nfa, input) == true) { 
        printf("Result for input %s: true\n",input);
    }
    else {
        printf("Result for input %s: false\n",input);
    }  
}

void NFA_repl(NFA nfa){
    while(1) {
       printf("Enter an input ('quit' to quit): ");
        char input[128];
        fgets(input, 128, stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp("quit", input) == 0) {
            break;
        }
        else {
            NFA_run(nfa, input); 
        }
    }
}

DFA dfa_ullman() {
    DFA ullman = new_DFA(7);
    DFA_set_transition(ullman, 0, 'u', 1);
    DFA_set_transition(ullman, 1, 'l', 2);
    DFA_set_transition(ullman, 2, 'l', 3);
    DFA_set_transition(ullman, 3, 'm', 4);
    DFA_set_transition(ullman, 4, 'a', 5);
    DFA_set_transition(ullman, 5, 'n', 6);
    DFA_set_accepting(ullman, 6, 1);
    return ullman;
}

DFA dfa_com() {
    DFA com = new_DFA(4);
    DFA_set_accepting(com, 3, 1);
    DFA_set_transition(com, 0, 'c', 1);
    DFA_set_transition(com, 1, 'o', 2);
    DFA_set_transition(com, 2, 'm', 3);
    DFA_set_transition_all(com, 3, 3);
    return com;
}

DFA dfa_threes() {
    DFA threes = new_DFA(4);
    DFA_set_accepting(threes, 3, 1);
    DFA_set_transition(threes, 0, '3', 1);
    DFA_set_transition(threes, 1, '3', 2);
    DFA_set_transition(threes, 2, '3', 3);
    DFA_set_transition_all_except(threes, 0, 0, 51);
    DFA_set_transition_all_except(threes, 1, 1, 51);
    DFA_set_transition_all_except(threes, 2, 2, 51);
    DFA_set_transition_all_except(threes, 3, 3, 51);
    return threes;
}

DFA dfa_bin(){
    DFA bin = new_DFA(4);
    DFA_set_transition(bin, 0, '1', 1);
    DFA_set_transition(bin, 1, '1', 0);
    DFA_set_transition(bin, 0, '0', 2);
    DFA_set_transition(bin, 2, '0', 0);
    DFA_set_transition(bin, 1, '0', 3);
    DFA_set_transition(bin, 3, '0', 1);
    DFA_set_transition(bin, 2, '1', 3);
    DFA_set_transition(bin, 3, '1', 2);
    DFA_set_accepting(bin, 1, 1);
    return bin;
}

NFA nfa_gs() {
    NFA gs = new_NFA(3);
    NFA_add_transition(gs,0, 'g', 1);
    NFA_add_transition_all(gs, 0, 0);
    NFA_add_transition(gs, 1, 's', 2);
    NFA_set_accepting(gs, 2, 1);
    return gs;
}

NFA nfa_mas() {
    NFA mas = new_NFA(4);
    NFA_add_transition(mas, 0, 'm', 1);
    NFA_add_transition_all(mas, 0, 0);
    NFA_add_transition(mas, 1, 'a', 2);
    NFA_add_transition(mas, 2, 's', 3);
    NFA_add_transition_all(mas, 3, 3);
    NFA_set_accepting(mas, 3, 1);
    return mas;
}

NFA nfa_codebreaker() {
    NFA codebreaker = new_NFA(19);
    NFA_add_transition_all(codebreaker, 0, 0);
    NFA_add_transition(codebreaker, 0, 'a', 1);
    NFA_add_transition_Except(codebreaker, 1, 97, 1);
    NFA_add_transition(codebreaker, 1, 'a', 2);
    NFA_set_accepting(codebreaker, 2, 1);
    NFA_add_transition(codebreaker, 0, 'b', 3);
    NFA_add_transition_Except(codebreaker, 3, 98, 3);
    NFA_add_transition(codebreaker, 3, 'b', 4);
    NFA_set_accepting(codebreaker, 4, 1);
    NFA_add_transition(codebreaker, 0, 'c', 5);
    NFA_add_transition_Except(codebreaker, 5, 99, 5);
    NFA_add_transition(codebreaker, 5, 'c', 6);
    NFA_set_accepting(codebreaker, 6, 1);
    NFA_add_transition(codebreaker, 0, 'd', 7);
    NFA_add_transition_Except(codebreaker, 5, 100, 5);
    NFA_add_transition(codebreaker, 7, 'd', 8);
    NFA_set_accepting(codebreaker, 8, 1);
    NFA_add_transition(codebreaker, 0, 'k', 9);
    NFA_add_transition_Except(codebreaker, 9, 107, 9);
    NFA_add_transition(codebreaker, 9, 'k', 10);
    NFA_set_accepting(codebreaker, 10, 1);
    NFA_add_transition(codebreaker, 0, 'o', 11);
    NFA_add_transition_Except(codebreaker, 11, 111, 11);
    NFA_add_transition(codebreaker, 11, 'o', 12);
    NFA_set_accepting(codebreaker, 12, 1);
    NFA_add_transition(codebreaker, 0, 'r', 13);
    NFA_add_transition_Except(codebreaker, 13, 114, 13);
    NFA_add_transition(codebreaker, 13, 'r', 14);
    NFA_add_transition_Except(codebreaker, 14, 114, 14);
    NFA_add_transition(codebreaker, 14, 'r', 15);
    NFA_set_accepting(codebreaker, 15, 1);
    NFA_add_transition(codebreaker, 0, 'e', 16);
    NFA_add_transition_Except(codebreaker, 16, 101, 16);
    NFA_add_transition(codebreaker, 16, 'e', 17);
    NFA_add_transition_Except(codebreaker, 17, 101, 17);
    NFA_add_transition(codebreaker, 17, 'e', 18);
    NFA_add_transition_Except(codebreaker, 18, 101, 18);
    NFA_add_transition(codebreaker, 18, 'e', 19);
    NFA_set_accepting(codebreaker, 19, 1);
    return codebreaker;
}

int main(int argc, const char * argv[]) {
    printf("Testing DFA that recognizes exactly 'ullman'...\n");
    DFA_repl(dfa_ullman());

    printf("\nTesting DFA that recognizes words that start with 'com'...\n");
    DFA_repl(dfa_com());
    
    printf("\nTesting DFA that recognizes words with exactly three '3's...\n");
    DFA_repl(dfa_threes());
    
    printf("\nTesting DFA that recognizes binary inputs with an even number of '0's and an odd number of '1's...\n");
    DFA_repl(dfa_bin());

    printf("\nTesting NFA that recognizes words that end with 'gs'...\n");
    NFA_repl(nfa_gs());
    
    printf("\nTesting NFA that recognizes words that contain 'mas'...\n");
    NFA_repl(nfa_mas());
    
    printf("\nTesting NFA that recognizes words that can't be an anagram of 'codebreaker'...\n");
    NFA_repl(nfa_codebreaker());
}