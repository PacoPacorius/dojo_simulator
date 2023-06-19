#ifndef DEBUG
#define DEBUG

#include "student_generation.h"
/* all in-game debug functions are here */

struct Student dbg_generate_student();
void dbg_remove_student(struct Student* student_list, int *number_of_students);
#endif
