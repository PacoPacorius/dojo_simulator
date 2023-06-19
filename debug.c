#include <string.h>

#include "debug.h"
#include "student_generation.h"
#include "name_generator.h"

struct Student dbg_generate_student(){
    struct Student temp;
    char* dummy_name = random_name();
    strcpy(temp.name, dummy_name);
    free(dummy_name);

    printf("\n\nGenerating new student (debug)...");
    printf("\nNew student's name: %s", temp.name);

    /* generate age */
    do{
        printf("\nEnter age: (16-90) ");
        scanf("%d", &temp.age);
    } while(temp.age < 15 || temp.age > 91);

    /* generate weight class */
    do{
        printf("\nEnter weight class (1 (Very Small) - 7 (Super Heavyweight)): ");
        scanf("%d", &temp.weight_class);
    } while(temp.weight_class > 7 || temp.weight_class < 1);

    /* physical stats (0-100) */
    temp.agility = generate_agility(temp.weight_class, temp.age);
    temp.strength = generate_strength(temp.weight_class, temp.age);
    temp.flexibility = generate_flexibility(temp.weight_class, temp.age);
    temp.stamina = generate_stamina(temp.weight_class, temp.age);

    /* skill stats (0-100) */
    temp.holds = 0;
    temp.striking = 0;
    temp.kicking = 0;

    
    /* personality stats (0-100) */
    temp.motivation = 50;
    temp.training_preference = rand_lim(4) - 1;
    temp.months_at_dojo = 0;

    /* hidden stats (0-100) */
    generate_destiny_values(&temp);

    /* initialize stat increase queues */
    temp.striking_incr = create_queue();
    temp.kicking_incr = create_queue();
    temp.holds_incr = create_queue();

    temp.agility_incr = create_queue();
    temp.strength_incr = create_queue();
    temp.stamina_incr = create_queue();
    temp.flexibility_incr = create_queue();

    /* belt rank */
    temp.belt_rank = WHITE_BELT;
    temp.months_since_previous_test = 0;

    return temp;
}

void debug_remove_student(){}
