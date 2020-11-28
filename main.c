#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sequence.h"

int main() {
	Sequence root;
	printf("Prima structura:\n");
	root = init();
	root = insert(root, 2, 0);
	root = insert(root, 1, 1);
	root = insert(root, 3, 1);
	root = insert(root, 0, 2);
	root = insert(root, 7, 3);
	root = insert(root, 6, 0);
	root = insert(root, 2, 6);
	root = insert(root, 1, 7);
	root = insert(root, -1, 8);
	print_data_structure(root);
	Sequence root_concat;
	printf("\n");
	printf("A doua structura:\n");
	root_concat = init();
	root_concat = insert(root_concat, 8, 0);
	root_concat = insert(root_concat, 9, 1);
	root_concat = insert(root_concat, 7, 2);
	root_concat = insert(root_concat, 10, 3);
	root_concat = insert(root_concat, 10, 4);
	root_concat = insert(root_concat, 11, 5);
	print_data_structure(root_concat);
	root = concat(root, root_concat);
	printf("\n");
	printf("Structura dupa concatenarea celor doua initiale:\n");
	print_data_structure(root);
	root = delete(root, 9);
	root = delete(root, 9);
	printf("\ndupa stergere:\n");
	print_data_structure(root);
	Sequence *seq3 = split(root, 8);
	printf("\n");
	printf("Structurile dupa split:\n");
	print_data_structure(seq3[0]);
	printf("Dupa index:\n");
	print_data_structure_byindex(seq3[0]);
	printf("\n");
	print_data_structure(seq3[1]);
	printf("Dupa index:\n");
	print_data_structure_byindex(seq3[1]);
	printf("Dimensiunea celei de-a doua structuri: %d\n", size(seq3[1]));
	return 0;
}