#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sequence.h" 

// Initializeaza un nou nod pentru treap
Node newtreapnode(Type value, int index) {
	Node new = malloc(sizeof(struct treapnode));
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->value = value;
	new->priority = index;
	return new;
}

// Printeaza structura folosind traversarea in inordine
void print_data_structure(Sequence data_structure) {
	traverse_inorder(data_structure->node);
}

// Printeaza structura in ordinea index-urilor (prioritatilor)
void print_data_structure_byindex(Sequence data_structure) {
	int i;
	for (i = 0; i < data_structure->size; i++) {
		printf("%d ", lookup(data_structure, i));
	}
	printf("\n");
}

// Functie folosita pentru traveresarea in preordine a treap-ului
void traverse_preorder(Node root) {
	if (root->left)
		traverse_preorder(root->left);
	printf("%d %d\n", root->value, root->priority);
	if (root->right)
		traverse_preorder(root->right);
}

// Functie folosita pentru traversarea in indordine a treap-ului
void traverse_inorder(Node root) {
	printf("%d %d\n", root->value, root->priority);
	if (root->left)
		traverse_inorder(root->left);
	if (root->right)
		traverse_inorder(root->right);
}

// Functie recursiva ajutatoare pentru cea de insert
Node insert_helper(Node root, Node new) {
	if (root == NULL)
		return new;
	if (root->value >= new->value) {
		root->left = insert_helper(root->left, new);
		if (root->left != NULL)
			root->left->parent = root;
	}
	if (root->value < new->value) {
		root->right = insert_helper(root->right, new);
		if (root->right != NULL)
			root->right->parent = root;
	}
	return root;
}

// Functie asemanatoare cu cea de la heap-uri care se
// ocupa de operatia de a duce elementul cat mai in varful
// arborelui astfel incat sa respecte proprietatile unui
// min-heap dupa index
Sequence prioritize(Sequence data_structure, Node new) {
	Node it = new, aux, aux2;
	if (it->parent)
	while (it->priority <= it->parent->priority) {
		if (!it->parent->parent) {
			aux = it->parent;
			if (it == it->parent->left) {
				if (!it->right) {
					it->right = aux;
					aux->left = NULL;
				} else {
					aux->left = it->right;
					it->right = aux;
				}
			} else {
				if (!it->left) {
					it->left = aux;
					aux->right = NULL;
				} else {
					aux->right = it->left;
					it->left = aux;
				}
			}
			data_structure->node = it;
			aux->parent = it;
			it->parent = NULL;
		} else {
			aux2 = it->parent->parent;
			aux = it->parent;
			if (it == it->parent->left) {
				if (!it->right) {
					it->right = aux;
					aux->left = NULL;
				} else {
					aux->left = it->right;
					it->right = aux;
				}
			} else {
				if (!it->left) {
					it->left = aux;
					aux->right = NULL;
				} else {
					aux->right = it->left;
					it->left = aux;
				}
			}
			aux->parent = it;
			if (aux2->right == aux) {
				aux2->right = it;
			} else {
				aux2->left = it;
			}
			it->parent = aux2;
		}
		if (!it->parent)
			break;
	}
	return data_structure;
}

// Schimba index-urile elementelor la adaugare (index-urile
// elementelor care sunt la index-uri mai mari decat cel la
// care se adauga)
Node reindex(Node root, Node new) {
	if (root != new && root->priority >= new->priority)
		root->priority++;
	if (root->left)
		root->left = reindex(root->left, new);
	if (root->right)
		root->right = reindex(root->right, new);
	return root;
}

// Schimba index-urile dupa ce se face operatia de delete
// (elementele de la indexurile mai mari decat elementul sters
// is scad indexurile cu 1)
Node reindex_delete(Node root, int index) {
	if (root->priority >= index)
		root->priority--;
	if (root->left)
		root->left = reindex_delete(root->left, index);
	if (root->right)
		root->right = reindex_delete(root->right, index);
	return root;
}

// Schimba index-urile elementelor celei de-a doua structuri
// (care se concateneaza la prima)
Node reindex_concat(Node root, int size) {
	root->priority += size;
	if (root->left)
		root->left = reindex_concat(root->left, size);
	if (root->right)
		root->right = reindex_concat(root->right, size);
	return root;
}

// Functie recursiva ajutatoare pentru set (Cauta elementul
// al carui index sa fie schimbat)
Node set_helper(Node root, Type value, int index) {
	if (root->priority > index)
		return root;
	if (root->priority == index)
		root->value = value;
	if (root->left)
		root->left = set_helper(root->left, value, index);
	if (root->right)
		root->right = set_helper(root->right, value, index);
	return root;
}

// Functie recursiva care ajuta functia de lookup
// (returneaza un nod)
Node lookup_helper(Node root, int index) {
	Node aux = NULL;
	if (root->priority > index)
		return aux;
	if (root->priority == index) {
		aux = root;
		return aux;
	}
	if (root->left) {
		aux = lookup_helper(root->left, index);
		if (aux)
			return aux;
	}
	if (root->right)
		aux = lookup_helper(root->right, index);
	return aux;
}

// Functie care cauta succesorul in inordine pentru delete
Node get_successor(Node root) {
	Node aux = NULL;
	int ok = 0;
	if (root->right) {
		aux = root->right;
		while (aux->left) {
			ok = 1;
			aux = aux->left;
		}
		if (ok == 1)
			aux->parent->left = aux->right;
		return aux;
	}
	return NULL;
}

// Returneaza structura vida
Sequence init() {
	Sequence new = malloc(sizeof(struct sequence));
	new->size = 0;
	return new;
}

// Insereaza un element in structura pe pozitia index
Sequence insert(Sequence data_structure, Type item, int index) {
	Node new = newtreapnode(item, index);
	data_structure->node = insert_helper(data_structure->node, new);
	data_structure = prioritize(data_structure, new);
	data_structure->node = reindex(data_structure->node, new);
	data_structure->size++;
	return data_structure;
}

// Sterge elementul de pe pozitia index din structura
Sequence delete(Sequence data_structure, int index) {
	int ok = 0, auxiliary;
	Node node = lookup_helper(data_structure->node, index);
	if (node->left == NULL && node->right == NULL) {
		if (node->parent->left == node) {
			node->parent->left = NULL;
		} else {
			node->parent->right = NULL;
		}
	} else {
		if (!node->left && node->right) {
			if (node->parent->left == node) {
				node->parent->left = node->right;
			} else {
				node->parent->right = node->right;
			}
			node->right->parent = node->parent;
		} else {
			if (node->left && !node->right) {
				if (node->parent->left == node) {
					node->parent->left = node->left;
				} else {
					node->parent->right = node->left;
				}
				node->left->parent = node->parent;
			} else {
				Node aux = get_successor(node);
				auxiliary = aux->priority;
				if (aux->priority - node->priority > 1) {
					ok = 1;
					aux->priority = node->priority;
				}
				if (node->parent->left == node) {
					node->parent->left = aux;
				} else {
					node->parent->right = aux;
				}
				aux->parent = node->parent;
				if (node->right == aux)
					node->right->parent = node->parent;
				if (node->right != aux)
					node->right->parent = aux;
				aux->left = node->left;
				node->left->parent = aux;
				if (aux != node->right)
					aux->right = node->right;
			}
		}
	}
	free(node);
	if (ok == 0)
		data_structure->node = reindex_delete(data_structure->node, index);
	else {
		index = auxiliary; 
		data_structure->node = reindex_delete(data_structure->node, index);
	}
	data_structure->size--;
	return data_structure;
}

// Returneaza valoarea elementului de pe pozitia index
Type lookup(Sequence data_structure, int index) {
	Node root = lookup_helper(data_structure->node, index);
	return root->value;
}

// Inlocuieste valoarea elementului de pe pozitia index
Sequence set(Sequence data_structure, Type item, int index) {
	data_structure->node = set_helper(data_structure->node, item, index);
	return data_structure;
}

// Returneaza dimensiunea structurii
int size(Sequence data_structure) {
	return data_structure->size;
}

// Returneaza cele doua structuri rezultate in urma divizarii
// (rezultatul este retinut intr-un Sequence* cu 2 elemente)
Sequence* split(Sequence data_structure, int index) {
	Sequence *split = malloc(2 * sizeof(struct sequence));
	Sequence data_structure2 = init();
	Type aux, aux_index = index;
	while (data_structure->size > index + 1) {
		aux = lookup(data_structure, index);
		data_structure2 = insert(data_structure2, aux, data_structure2->size);
		index++;
	}
	int i;
	while (data_structure->size > aux_index + 1) {
		data_structure = delete(data_structure, data_structure->size - 1);
	}
	split[0] = data_structure;
	split[1] = data_structure2;
	return split;
}


// Functie recursiva care cauta locul in care sa fie
// pus treap-ul reprezentat de root2
Node concat_helper(Node root1, Node root2) {
	if (root1 == NULL)
		return root2;
	if (root1->value >= root2->value) {
		root1->left = concat_helper(root1->left, root2);
		if (root1->left != NULL)
			root1->left->parent = root1;
	}
	if (root1->value < root2->value) {
		root1->right = concat_helper(root1->right, root2);
		if (root1->right != NULL)
			root1->right->parent = root1;
	}
	return root1;	
}

// Returneaza structura rezultata dupa concatenare
Sequence concat(Sequence data_structure1, Sequence data_structure2) {
	data_structure2->node = reindex_concat(data_structure2->node, data_structure1->size);
	data_structure1->node = concat_helper(data_structure1->node, data_structure2->node);
	data_structure1->size += data_structure2->size;
	return data_structure1;
}
