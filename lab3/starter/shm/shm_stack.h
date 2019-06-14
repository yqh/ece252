/**
 * @brief  stack API header  
 * @author yqhuang@uwaterloo.ca
 */

struct int_stack;

int sizeof_shm_stack(int size);
int init_shm_stack(struct int_stack *p, int stack_size);
struct int_stack *create_stack(int size);
void destroy_stack(struct int_stack *p);
int is_full(struct int_stack *p);
int is_empty(struct int_stack *p);
int push(struct int_stack *p, int item);
int pop(struct int_stack *p, int *p_item);
