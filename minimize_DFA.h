#include <stdio.h>
#include <stdlib.h>

void merge_states(int current_state_numbers[], int destination_number_c[], int destination_number_d[], int array_size) {
	int i, j;
	int* temp = (int*)malloc(sizeof(int) * array_size);

	for ( i = 0; i < array_size; i++ ) {
		temp[i] = i;
	}

	for ( i = 0; i < array_size; i++ ) {
		for ( j = i+1; j < array_size; j++ ) {
			if ( destination_number_c[j] == destination_number_c[i] &&
				 destination_number_d[j] == destination_number_d[i] ) {
				current_state_numbers[j] = current_state_numbers[i];
				destination_number_c[j] = destination_number_c[i];
				destination_number_d[j] = destination_number_d[i];
			//	temp[j] = current_state_numbers[i];
			}
		}
	}

//	for ( i = 0; i < array_size; i++ ) {
//		current_state_numbers[i] = temp[i];
//	}

	free(temp);
}

int find_root(int array[], int i) {
	if ( array[i] == i ) {
		return i;
	} else {
		return array[i] = find_root(array, array[i]);
	}
}
