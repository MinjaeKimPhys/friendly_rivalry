#include <stdio.h>
#include <stdlib.h>

int check_including(int original_array[], int array_size, int value) {
	int i;
	for ( i = 0; i < array_size; i++ ) {
		if ( original_array[i] == value ) {
			return 1;
		}
	}

	return 0;
}

void delete_duplicates(int original_array[], int destination_numbers_c[], int destination_numbers_d[], int *array_size){
	int i;
	int count = 0;
	int* temp_current_state_numbers = malloc(sizeof(int) * *array_size);
	int* temp_destination_numbers_c = malloc(sizeof(int) * *array_size);
	int* temp_destination_numbers_d = malloc(sizeof(int) * *array_size);

	for ( i = 0; i < *array_size; i++ ){
		temp_current_state_numbers[i] = original_array[i];
	}

	for ( i = 0; i < *array_size; i++ ) {
		if ( check_including(temp_current_state_numbers, count, original_array[i]) == 0 ) {
			temp_current_state_numbers[count] = original_array[i];
			temp_destination_numbers_c[count] = destination_numbers_c[i];
			temp_destination_numbers_d[count] = destination_numbers_d[i];
			count += 1;
		}
	}

	for ( i = 0; i < count; i++ ) {
		original_array[i] = temp_current_state_numbers[i];
		destination_numbers_c[i] = temp_destination_numbers_c[i];
		destination_numbers_d[i] = temp_destination_numbers_d[i];
	}

	*array_size = count;

	free(temp_current_state_numbers);
	free(temp_destination_numbers_c);
	free(temp_destination_numbers_d);
}

void sort(int unsorted_array[], int array_size) {
	int i, j;
	int temp;
	int count;

	for ( i = 0; i < array_size; i++ ) {
		count = 0;
		for ( j = 0; j < array_size-1; j++) {
			if ( unsorted_array[j] > unsorted_array[j+1] ) {
				temp = unsorted_array[j];
				unsorted_array[j] = unsorted_array[j+1];
				unsorted_array[j+1] = temp;
				
				count += 1;
			}
		}
		if ( count == 0 ) {
			break;
		}
	}
}
