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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bdd_utils.h"

struct bdd bdd_true = {"TRUE", 0, NULL, NULL};
struct bdd bdd_false = {"FALSE", 0, NULL, NULL};

void print_node(struct bdd b) {
	printf("%s", b.var);
}

void print_path(struct bdd b, int pathlen, int *path) {
	struct bdd iter = {b.var, b.level, b.high, b.low};
	struct bdd *tmp = NULL;
	for (int i = 0; i < pathlen - 1; i++) {
		if (path[i]) {
			print_node(iter);
			iter.var = (iter.high)->var;
			iter.level = (iter.high)->level;
			tmp = iter.high;
			iter.high = (iter.high)->high;
			iter.low = tmp->low;
		} else {
			printf("not ");
			print_node(iter);
			iter.var = (iter.low)->var;
			iter.level = (iter.low)->level;
			tmp = iter.low;
			iter.high = (iter.low)->high;
			iter.low = tmp->low;
		}
		printf(" and ");
	}
	if (path[pathlen - 1]) {
		print_node(iter);
	} else {
		printf(" not ");
		print_node(iter);
	}
}

void print_dnf_rec(struct bdd b, struct bdd original, int size,
			int pathlen, int *path, int *print_or) {
	if (strcmp(b.var, "FALSE") == 0) {
		return;
	} else if (strcmp(b.var, "TRUE") == 0) {
		if (*print_or) {
			printf(" or ");
		} else {
			*print_or = 1;
		}
		print_path(original, pathlen, path);
		free(path);
	} else {
		/* recursion on higher child */
		int *highpath = malloc(size * sizeof(int));
		if (highpath == NULL) {
			perror("Error allocating memory: ");
			exit(EXIT_FAILURE);
		}
		memcpy(highpath, path, size * sizeof(int));
		highpath[pathlen] = 1;
		print_dnf_rec(*b.high, original, size, pathlen + 1, highpath, print_or);
		/* recursion on lower child */
		int *lowpath = malloc(size * sizeof(int));
		if (lowpath == NULL) {
			perror("Error allocating memory: ");
			exit(EXIT_FAILURE);
		}
		memcpy(lowpath, path, size * sizeof(int));
		lowpath[pathlen] = 0;
		print_dnf_rec(*b.low, original, size, pathlen + 1, lowpath, print_or);
	}
}

void print_dnf(struct bdd b, int size) {
	int *path = calloc(size, sizeof(int));
	if (path == NULL) {
		perror("Error allocating memory: ");
		exit(EXIT_FAILURE);
	}
	int print_or = 0;
	print_dnf_rec(b, b, size, 0, path, &print_or);
	free(path);
}

void onoff_set_helper(struct bdd b, int *count, char *boolean1, char *boolean2) {
	if (strcmp(b.var, boolean1) == 0) {
		return;
	} else if (strcmp(b.var, boolean2) == 0) {
		*count = *count + 1;
	} else {
		onoff_set_helper(*b.high, count, boolean1, boolean2);
		onoff_set_helper(*b.low, count, boolean1, boolean2);
	}
}

void on_set(struct bdd b, int *count) {
	onoff_set_helper(b, count, "FALSE", "TRUE");
}

void off_set(struct bdd b, int *count) {
	onoff_set_helper(b, count, "TRUE", "FALSE");
}

void rounding(struct bdd *b, int level) {
	if (b->level == 0) { /* Terminal node */
		return;
	} else if (b->level != level) {
		rounding(b->high, level);
		rounding(b->low, level);
	} else {
		int onset = 0, offset = 0;
		on_set(*b, &onset);
		off_set(*b, &offset);
		if (onset > offset) {
			/* Lower child has smaller On-Set */
			b->var = "TRUE";
			b->high = NULL;
			b->low = NULL;
		} else {
			/* Higher child has smaller/equally big On-Set */
			b->var = "FALSE";
			b->high = NULL;
			b->low = NULL;
		}
	}
}

void rounding_updown_helper(struct bdd *b, struct bdd *terminal, int level) {
	if (b->level == 0) { /* Terminal node */
		return;
	} else if (b->level < level) {
		rounding_updown_helper(b->high, terminal, level);
		rounding_updown_helper(b->low, terminal, level);
	} else {
		int highcount = 0, lowcount = 0;
		on_set(*b->high, &highcount);
		on_set(*b->low, &lowcount);
		if (highcount > lowcount) {
			/* Lower child has smaller On-Set */
			b->low = terminal;
			rounding_updown_helper(b->high, terminal, level);
		} else {
			/* Higher child has smaller/equally big On-Set */
			b->high = terminal;
			rounding_updown_helper(b->low, terminal, level);
		}
	}
}

void rounding_up(struct bdd *b, int level) {
	rounding_updown_helper(b, &bdd_true, level);
}

void rounding_down(struct bdd *b, int level) {
	rounding_updown_helper(b, &bdd_false, level);
}
