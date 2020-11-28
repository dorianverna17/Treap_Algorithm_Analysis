#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

typedef int Type;

typedef struct treapnode {
	Type value;
	int priority;
	struct treapnode *parent;
	struct treapnode *left;
	struct treapnode *right;
} *Node;

typedef struct sequence {
	struct treapnode *node;
	int size;
} *Sequence;

// Returneaza structura vida
Sequence init();

// Insereaza un element in structura pe pozitia index
Sequence insert(Sequence data_structure, Type item, int index);

// Sterge elementul de pe pozitia index din structura
Sequence delete(Sequence data_structure, int index);

// Returneaza valoarea elementului de pe pozitia index
Type lookup(Sequence data_structure, int index);

// Inlocuieste valoarea elementului de pe pozitia index
Sequence set(Sequence data_structure, Type item, int index);

// Returneaza dimensiunea structurii
int size(Sequence data_structure);

// Returneaza cele doua structuri rezultate in urma divizarii
// (rezultatul este retinut intr-un Sequence* cu 2 elemente)
Sequence* split(Sequence data_structure, int index);

// Returneaza structura rezultata dupa concatenare
Sequence concat(Sequence data_structure1, Sequence data_structure2);

// Functii auxiliare
// Returneaza un nod pentru treap
Node newtreapnode(Type value, int index);

// Traversarea in preordine a treapului
void traverse_preorder(Node root);

// Traversarea in inordine a treapului
void traverse_inorder(Node root);

// printeaza structura de date (traversarea in inordine)
void print_data_structure(Sequence data_structure);

// functie auxiliara care ajuta la inserare
Node insert_helper(Node root, Node new);

// Printeaza structura in ordinea index-urilor (prioritatilor)
void print_data_structure_byindex(Sequence data_structure);

// Functie care cauta succesorul in inordine pentru delete
Node get_successor(Node root);
#endif