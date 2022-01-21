#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "minimize_DFA.h"
#include "sort.h"

int main()
{
	int n = 2;
	int m = 3;
	int n_states = pow(n, n*m);
	int one_person_array_size = m*pow(n,m);
	int states_size = 2*one_person_array_size*pow(n,m);
	int comparing = 1;
	int step = 1;
	int i, j, k;

	int A_memory[m];
	int B_memory[m];
	int one_person_states[one_person_array_size];
	int states[states_size];
	int current_state_numbers_size = 64;
	int next_state_numbers_size = 2*current_state_numbers_size;
	int root_state_numbers_size = current_state_numbers_size;

	int* current_state_numbers = (int*)malloc(sizeof(int) * current_state_numbers_size);
	int* previous_state_numbers = (int*)malloc(sizeof(int) * current_state_numbers_size);
	int* next_states_c = (int*)malloc(sizeof(int) * states_size);
	int* next_states_d = (int*)malloc(sizeof(int) * states_size);
	int* next_state_numbers_c = (int*)malloc(sizeof(int) * current_state_numbers_size);
	int* next_state_numbers_d = (int*)malloc(sizeof(int) * current_state_numbers_size);
	int* next_state_numbers = (int*)malloc(sizeof(int) * next_state_numbers_size);

	char strategy[64] = "cddcccddcccdddddcccdddccdddcddcdcccccdddddcddcddcdccdddddcdccccd";

	for ( i = 0; i < current_state_numbers_size; i++ ) {
		current_state_numbers[i] = i;
		next_state_numbers_c[i] = i;
		next_state_numbers_d[i] = i;
	}

	for ( i = 0; i < m; i++) {
		A_memory[i] = 0;
		B_memory[i] = 0;
	}

	for (i = 0; i < one_person_array_size; i++ ) {
		one_person_states[i] = 0;
	}

	for (i = 0; i < states_size; i++ ) {
		states[i] = 0;
		next_states_c[i] = 0;
		next_states_d[i] = 0;
	}

	for ( i = 0; i < 8; i++ ) {
		int current_i = i;
		while ( current_i != 0 ) {
			for ( j = m-1; j >= 0; j-- ) {
				if ( current_i%2 != 0) {
					one_person_states[i*m+j] = 1;
				}
				current_i = current_i/2;
			}
		}
	}

	for ( i = 0; i < pow(n,m); i++ ) {
		for ( j = 0; j < pow(n,m); j++ ) {
			for ( k = 0; k < m; k++ ) {
				states[48*i+6*j+k] = one_person_states[3*i+k];
			}
		}
	}

	for ( i = 0; i < pow(n,m); i++ ) {
		for ( j = 0; j < pow(n,m); j++ ) {
			for ( k = 0; k < m; k++ ) {
				states[48*i+3+6*j+k] = one_person_states[3*j+k];
			}
		}
	}

	for ( i = 0; i < n_states; i++ ) {
		for ( j = 0; j < m; j++ ) {
			A_memory[j] = states[6*i+j];
			B_memory[j] = states[6*i+3+j];
		}

		for ( j = 0; j < m-1; j++ ) {
			A_memory[j] = A_memory[j+1];
			B_memory[j] = B_memory[j+1];
		}

		if ( strategy[i] == 'c' ) {
			A_memory[2] = 0;
		}
		else A_memory[2] = 1;

		for( j = 0; j < m-1; j++ ) {
			next_states_c[6*i+j] = A_memory[j];
			next_states_c[6*i+3+j] = B_memory[j];
		}
		next_states_c[6*i+2] = A_memory[2];
		next_states_c[6*i+5] = 0;

		for ( j = 0; j < m-1; j++ ) {
			next_states_d[6*i+j] = A_memory[j];
			next_states_d[6*i+3+j] = B_memory[j];
		}
		next_states_d[6*i+2] = A_memory[2];
		next_states_d[6*i+5] = 1;
	}

	printf("Strategy: ");
	for ( i = 0; i < n_states; i++ ) {
		printf("%c", strategy[i]);
	}
	printf("\n\n");

	printf("%d players and %d-memory length's all states:\n", n, m);
	for ( i = 0; i < states_size; i++ ) {
		if ( i % 48 == 0 ) {
			printf("\n");
		}
		if ( i % 6 == 0 ) { printf(" "); }
		printf("%d", states[i]);
	}
	printf("\n\n");

	printf("Next states when Bob cooperates:\n");
	for ( i = 0; i < states_size; i++ ) {
		if ( i % 48 == 0 ) {
			printf("\n");
		}
		if ( i % 6 == 0 ) { printf(" "); }
		printf("%d", next_states_c[i]);
	}
	printf("\n\n");

	printf("Next states when Bob defects:\n");
	for ( i = 0; i < states_size; i++ ) {
		if ( i % 48 == 0 ) {
			printf("\n");
		}
		if ( i % 6 == 0 ) { printf(" "); }
		printf("%d", next_states_d[i]);
	}
	printf("\n\n");

	for ( i = 0; i < current_state_numbers_size; i++ ) {
		for ( j = 0; j < n_states; j++ ) {
			if ( next_states_c[6*current_state_numbers[i]] == states[6*j] &&
				 next_states_c[6*current_state_numbers[i]+1] == states[6*j+1] &&
				 next_states_c[6*current_state_numbers[i]+2] == states[6*j+2] &&
				 next_states_c[6*current_state_numbers[i]+3] == states[6*j+3] &&
				 next_states_c[6*current_state_numbers[i]+4] == states[6*j+4] &&
				 next_states_c[6*current_state_numbers[i]+5] == states[6*j+5] ) {
	
				next_state_numbers_c[i] = j;
			}
	
			if ( next_states_d[6*current_state_numbers[i]] == states[6*j] &&
				 next_states_d[6*current_state_numbers[i]+1] == states[6*j+1] &&
				 next_states_d[6*current_state_numbers[i]+2] == states[6*j+2] &&
				 next_states_d[6*current_state_numbers[i]+3] == states[6*j+3] &&
				 next_states_d[6*current_state_numbers[i]+4] == states[6*j+4] &&
				 next_states_d[6*current_state_numbers[i]+5] == states[6*j+5] ) {
				next_state_numbers_d[i] = j;
			}
		}
	}

//	for ( i = 0; i < current_state_numbers_size; i++ ) {
//		printf("%d %d %d %d\n", i, current_state_numbers[i], next_state_numbers_c[i], next_state_numbers_d[i]);
//	}

	for ( i = 0; i < current_state_numbers_size; i++ ) {
		previous_state_numbers[i] = -1;
	}

	merge_states(current_state_numbers, next_state_numbers_c, next_state_numbers_d, current_state_numbers_size);
	while ( comparing == 1 ) {
	//	for ( i = 0; i < current_state_numbers_size; i++ ) {
	//		printf("%d ", current_state_numbers[i]);
	//	}
	//	printf("\n\n");
		for ( i = 0; i < current_state_numbers_size; i++ ) {
			next_state_numbers_c[i] = current_state_numbers[next_state_numbers_c[i]];
			next_state_numbers_d[i] = current_state_numbers[next_state_numbers_d[i]];
		}

		merge_states(current_state_numbers, next_state_numbers_c, next_state_numbers_d, current_state_numbers_size);
	//	for ( i = 0; i < current_state_numbers_size; i++ ) {
	//		printf("%d ", current_state_numbers[i]);
	//	}
	//	printf("\n\n");

		comparing = 0;
		for ( i = 0; i < current_state_numbers_size; i++ ) {
			if ( previous_state_numbers[i] != current_state_numbers[i] ) {
				comparing = 1;
				break;
			}
		}

		for ( i = 0; i < current_state_numbers_size; i++ ) {
			previous_state_numbers[i] = current_state_numbers[i];
		}

		step += 1;
	}

	printf("\n");
	printf("escape at step: %d\n", step);

	for ( i = 0; i < current_state_numbers_size; i++ ) {
		if ( current_state_numbers[i] == i ) {
			int count_elements = 0;
			printf("%d - > [", current_state_numbers[i]);
			for ( j = 0; j < current_state_numbers_size; j++ ) {
				if ( current_state_numbers[j] == current_state_numbers[i] ) {
					printf("%d, ", j);
					count_elements += 1;
				}
			}
			printf("], %d\n", count_elements);
		}
	}
	printf("\n");
	delete_duplicates(current_state_numbers, next_state_numbers_c, next_state_numbers_d, &current_state_numbers_size);
	printf("# of nodes: %d\n", current_state_numbers_size);


	printf("Final nodes after the iterated DFA:\n");
	for ( i = 0; i < current_state_numbers_size; i++ ) {
		printf("%d ", current_state_numbers[i]);
	}
	printf("\n\n");

	printf("Next state when Bob cooperates:\n");
	for ( i = 0; i < current_state_numbers_size; i++ ) {
		printf("%d ", next_state_numbers_c[i]);
	}
	printf("\n\n");

	printf("Next state when Bob defects:\n");
	for ( i = 0; i < current_state_numbers_size; i++ ) {
		printf("%d ", next_state_numbers_d[i]);
	}
	printf("\n\n");


	free(current_state_numbers);
	free(previous_state_numbers);
	free(next_state_numbers_c);
	free(next_state_numbers_d);
	free(next_state_numbers);
	free(next_states_c);
	free(next_states_d);

	current_state_numbers = NULL;
	previous_state_numbers = NULL;
	next_state_numbers_c = NULL;
	next_state_numbers_d = NULL;
	next_state_numbers = NULL;
	next_states_c = NULL;
	next_states_d = NULL;

	return 0;
}
