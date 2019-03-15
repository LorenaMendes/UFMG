#ifndef _SET_H
#define _SET_H

/*
 * The type signature of the Set datatype. Only its typedefinition appears in
 * this header file. The concrete implementation is elsewhere.
 */
typedef struct set_concrete* Set;

/*
 * This function initialized a set s. It should be called before any operation
 * is performed on the set. If some operation is performed on an uninitialized
 * set, then the result is undefined.
 * @param s: a pointer to the set to be initialized. Must pass a pointer, as
 * we want the effect of the initialization reflected outside the function.
 */
void initialize(Set* s);

/*
 * This function inserts a new element into a set.
 * @param s: the set that shall be updated.
 * @param i: the new integer that shall be added into the set.
 */
void insert(Set s, int i);

/*
 * This function lets us know if some element is in a set.
 * @param s: the set that we are querying.
 * @param i: the element that we are looking for.
 */
int contains(Set s, int i);

/*
 * This function terminates a set. It should be invoked to liberate resources.
 * Once terminated, a set should not be used. The result of performing any
 * operation on a closed set is undefined.
 * @param s: the set that will be closed.
 */
void close(Set s);

#endif
