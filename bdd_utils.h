/* This file is part of CARL.
 * Author: Eva Charlotte Mayer <eva-charlotte.mayer@posteo.de>
 *
 * CARL is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, Version 3.
 *
 * CARL is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

struct bdd {
	char *var;
	int level;	/* root has level 1, children of root 2, .. */
	struct bdd *high;
	struct bdd *low;
};

extern struct bdd bdd_true;
extern struct bdd bdd_false;

/* Prints the name of the variable for a given node. */
void print_node(struct bdd b);

/* Prints the function represented by a given BDD in Disjunctive Normal Form.
 * Parameter size equals the highest level in the BDD. */
void print_dnf(struct bdd b, int size);

/* Helper functions for printDNF. */
void print_path(struct bdd b, int pathlen, int *path);
void print_dnf_rec(struct bdd b, struct bdd original, int size, int pathlen,
		int *path, int *print_or);

/* Calculates the ON-set for a given BDD. The ON-set is the number of paths
 * leading to the terminal node TRUE. */
void on_set(struct bdd b, int *count);

/* Calculates the OFF-set for a given BDD. The OFF-set is the number of paths
 * leading to the terminal node FALSE. */
void off_set(struct bdd b, int *count);

/* Helper function for onSet and offSet. */
void onoff_set_helper(struct bdd b, int *count, char *boolean1, char *boolean2);

/* Approximation operators that are applied on the specified level for a given
 * BDD. */
void rounding(struct bdd *b, int level);
void rounding_up(struct bdd *b, int level);
void rounding_down(struct bdd *b, int level);

/* Helper function for rounding up and down. */
void rounding_updown_helper(struct bdd *b, struct bdd *terminal, int level);
