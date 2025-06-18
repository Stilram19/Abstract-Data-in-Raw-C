
#ifndef STACK_H
# define STACK_H

# include <stddef.h>

# define STACK_OK   0   ///< indicates a successful stack operation
# define STACK_ERR -1   ///< indicates a failed stack operation

/**
 * opaque structure representing a stack
 * implemented using a dynamic array internally
 */
typedef struct Stack Stack;

/**
 * creates a new stack that holds elements of a given size
 *
 * @param elem_size size in bytes of each element
 * @return pointer to the created stack, or NULL on failure
 */
Stack *stack_create(size_t elem_size);

/**
 * destroys the stack and frees all associated memory
 *
 * @param s pointer to the stack to destroy
 */
void stack_destroy(Stack *s);

/**
 * pushes an element onto the stack
 *
 * @param s pointer to the stack
 * @param elem pointer to the element to be pushed
 * @return STACK_OK on success, STACK_ERR on failure
 */
int stack_push(Stack *s, const void *elem);

/**
 * removes the top element from the stack
 *
 * @param s pointer to the stack
 * @return STACK_OK on success, STACK_ERR if the stack is empty or invalid
 */
int stack_pop(Stack *s);

/**
 * returns a pointer to the top element of the stack
 *
 * @param s pointer to the stack
 * @return pointer to the top element, or NULL if the stack is empty or invalid
 */
void *stack_top(const Stack *s);

/**
 * returns the number of elements in the stack
 *
 * @param s pointer to the stack
 * @return number of elements, or 0 if the stack is invalid
 */
size_t stack_size(const Stack *s);

/**
 * checks whether the stack is empty
 *
 * @param s pointer to the stack
 * @return non-zero if empty or invalid, 0 otherwise
 */
int stack_is_empty(const Stack *s);

#endif // STACK_H

