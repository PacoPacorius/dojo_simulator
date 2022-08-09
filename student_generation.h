#ifndef STUDENT_GENERATION
#define STUDENT_GENERATION

#include "stack.h"

#define V_SMALL         1
#define SMALL           2
#define LIGHTWEIGHT     3
#define MIDDLEWEIGHT    4
#define L_HEAVYWEIGHT   5
#define HEAVYWEIGHT     6
#define S_HEAVYWEIGHT   7

struct Student {
    char* name;
    int age;

    /* skill stats (0-100) */
    float holds;
    float striking;
    float kicking;

    /* physical stats (0-100) */
    float agility;
    float strength;
    float flexibility;
    float stamina;

    /* weight class */
    int weight_class;
    
    /* personality stats (0-100) */
    float motivation;

    /* hidden stats (0-100) */
    int destiny_agility;
    int destiny_strength;
    int destiny_flexibility;
    int destiny_stamina;

    int destiny_striking;
    int destiny_kicking;
    int destiny_holds;

    int decline_age;

    /* stat increase history */
    struct Stack striking_incr;
    struct Stack kicking_incr;
    struct Stack holds_incr;

    struct Stack agility_incr;
    struct Stack strength_incr;
    struct Stack stamina_incr;
    struct Stack flexibility_incr;
};

int rand_lim(int limit);
double get_gaussdist_number(int lower_lim, int upper_lim);

struct Student generate_student(char* new_name);
int generate_weight_class();
int generate_agility(int weight_class, int age);
int generate_strength(int weight_class, int age);
int generate_flexibility(int weight_class, int age);
int generate_stamina(int weight_class, int age);
void generate_destiny_values(struct Student* stud);

#endif
