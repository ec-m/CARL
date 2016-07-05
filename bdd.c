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
#include "bdd_utils.h"

int main() {

	/* Example multi-output boolean function BDD of Figure 1
	 * in "BDD Minimization for Approximate Computing", Mathias
	 * Soeken, Daniel Große, Arun Chandrasekharan and Rolf
	 * Drechsler, ASP-DAC 2016 : 474-479. */
	struct bdd f0x21 = {"x2", 2, &bdd_true, &bdd_false};
	struct bdd f0x22 = {"x2", 2, &bdd_false, &bdd_true};
	struct bdd f0x1 = {"x1", 1, &f0x22, &f0x21};

	struct bdd f12x4 = {"x4", 4, &bdd_true, &bdd_false};

	struct bdd f1x4 = {"x4", 4, &bdd_false, &bdd_true};
	struct bdd f1x31 = {"x3", 3, &f1x4, &f12x4};
	struct bdd f1x32 = {"x3", 3, &f12x4, &f1x4};
	struct bdd f1x2 = {"x2", 2, &f1x32, &f1x31};
	struct bdd f1x1 = {"x1", 1, &f1x2, &f1x31};

	struct bdd f2x31 = {"x3", 3, &bdd_true, &f12x4};
	struct bdd f2x32 = {"x3", 3, &f12x4, &bdd_false};
	struct bdd f2x2 = {"x2", 2, &f2x31, &f2x32};
	struct bdd f2x1 = {"x1", 1, &f2x2, &f2x32};

	/* Original output functions -- Fig. 1a */
	printf("Original output functions: \nf0: ");
	print_dnf(f0x1, 2);
	printf("\n\nf1: ");
	print_dnf(f1x1, 4);
	printf("\n\nf2: ");
	print_dnf(f2x1, 4);
	printf("\n\n\n");

	/* ONLY ONE OPERATOR CAN BE EXECUTED IN ONE RUN!
	 * Uncommented the one you want to try out. */

	/* Rounding down -- Fig. 1b*/
	printf("Output functions after rounding down: \n\nf0: ");
	rounding_down(&f0x1, 3);
	rounding_down(&f1x1, 3);
	rounding_down(&f2x2, 3);
	print_dnf(f0x1, 2);
	printf("\n\nf1: ");
	print_dnf(f1x1, 4);
	printf("\n\nf2: ");
	print_dnf(f2x1, 4);
	printf("\n\n\n");

	/* Rounding up -- Fig. 1c */
	/*printf("Output functions after rounding up: \n\nf0: ");
	rounding_up(&f0x1, 3);
	rounding_up(&f1x1, 3);
	rounding_up(&f2x2, 3);
	print_dnf(f0x1, 2);
	printf("\n\n");
	print_dnf(f1x1, 2);
	printf("\n\n");
	print_dnf(f1x1, 2);
	printf("\n\n");
	int count = 0;
	on_set(f1x1, &count);
	printf("\nf1 On-Set: %d\n", count);
	count = 0;
	off_set(f1x1, &count);
	printf("f1 Off-Set: %d\n", count);
	printf("\n\n");
	count = 0;
	on_set(f2x1, &count);
	printf("\nf2 On-Set: %d\n", count);
	count = 0;
	off_set(f2x1, &count);
	printf("f2 Off-Set: %d\n", count);
	printf("\n\n\n");*/

	/* Rounding -- Fig. 1d */
	/*printf("Output functions after rounding: \n\nf0: ");
	rounding(&f0x1, 3);
	rounding(&f1x1, 3);
	rounding(&f2x2, 3);
	print_dnf(f0x1, 2);
	printf("\n\nf1: ");
	print_dnf(f1x1, 4);
	int count = 0;
	on_set(f1x1, &count);
	printf("\nf1 On-Set: %d\n", count);
	count = 0;
	off_set(f1x1, &count);
	printf("f1 Off-Set: %d\n", count);
	printf("\n\nf2: ");
	print_dnf(f2x1, 4);
	printf("\n\n");*/
}
