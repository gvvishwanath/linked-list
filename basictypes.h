/* 
 * G V Vishwanath, 18th May 2019, v1.0
 * Header file containing basic type declarations for sorting algorithms
 *
 * The following types are declared in this file:
 * a) Element: For array elements. Another name for int
 * b) Index: For array indices. Another name for int
 * c) Length: For array lengths. Another name for int
 */

#ifndef BASICTYPES_H
#define BASICTYPES_H

	// To distinguish between integer elements and integer indices, lengths, etc. Elements can be of other types.
	// Other type elements can have appropriate comparators, without much change in underlying algorithm.
	typedef int Element;

	// For array indices
	typedef int Index;

	// For general lengths
	typedef int Length;

#endif
