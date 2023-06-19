#include <string.h>

#include "debug.h"
#include "student_generation.h"
#include "name_generator.h"

struct Student dbg_generate_student(){
    char decision;
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
    } while(temp.age < 16 || temp.age > 90);

    /* generate weight class */
    do{
        printf("\nEnter weight class (1 (Very Small) - 7 (Super Heavyweight)): ");
        scanf("%d", &temp.weight_class);
    } while(temp.weight_class > 7 || temp.weight_class < 1);

    getchar(); /* eliminate newline */

    /* physical stats (0-100) */
    do{
        printf("Would you like to set physical stats? (y/n) ");
        scanf("%c", &decision);
    } while(decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N');

    if(decision == 'n' || decision == 'N'){
        temp.agility = generate_agility(temp.weight_class, temp.age);
        temp.strength = generate_strength(temp.weight_class, temp.age);
        temp.flexibility = generate_flexibility(temp.weight_class, temp.age);
        temp.stamina = generate_stamina(temp.weight_class, temp.age);
    }
    else if(decision == 'y' || decision == 'Y'){
        do{
            printf("\nEnter Agility: (0-100) ");
            scanf("%f", &temp.agility);
        } while(temp.agility < 0 || temp.agility > 100);
        do{
            printf("\nEnter Strength: (0-100) ");
            scanf("%f", &temp.strength);
        } while(temp.strength < 0 || temp.strength > 100);
        do{
            printf("\nEnter Flexibility: (0-100) ");
            scanf("%f", &temp.flexibility);
        } while(temp.flexibility < 0 || temp.flexibility > 100);
        do{
            printf("\nEnter Stamina: (0-100) ");
            scanf("%f", &temp.stamina);
        } while(temp.stamina < 0 || temp.stamina > 100);
    }

    getchar(); /* consume newline */

    /* skill stats (0-100) */
    do{
        printf("Would you like to set skill stats? (y/n) ");
        scanf("%c", &decision);
    } while(decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N');

    if(decision == 'n' || decision == 'N'){
        temp.striking = 0;
        temp.kicking = 0;
        temp.holds = 0;
    }
    else if(decision == 'y' || decision == 'Y'){
        do{
            printf("\nEnter Striking: (0-100) ");
            scanf("%f", &temp.striking);
        } while(temp.striking < 0 || temp.striking > 100);
        do{
            printf("\nEnter Kicking: (0-100) ");
            scanf("%f", &temp.kicking);
        } while(temp.kicking < 0 || temp.kicking > 100);
        do{
            printf("\nEnter Holds: (0-100) ");
            scanf("%f", &temp.holds);
        } while(temp.holds < 0 || temp.holds > 100);
    }

    getchar(); /* consume newline */
    
    /* personality stats (0-100) */
    do{
        printf("\nEnter Motivation: (0-100) ");
        scanf("%f", &temp.motivation);
    } while(temp.holds < 0 || temp.holds > 100);
    do{
        printf("\n-1. No preference\n0. General Training\n1. Striking\n2. Kicking\n3. Holds\nEnter Training Preference: ");
        scanf("%d", &temp.training_preference);
    } while(temp.training_preference < -1 || temp.training_preference > 3);
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

void dbg_remove_student(struct Student* student_list, int *number_of_students){
    int i;
    do{
        for(i = 0; i < *number_of_students; i++)
            printf("\n%d. %s", i, student_list[i].name);
        printf("\n\nPress -1 to go back to the main menu...\n");
        printf("\nWhich student will you kick out of the dojo? (debug) ");
        scanf("%d", &i);
        getchar();
    } while(i < -1 || i > *number_of_students - 1);
    if(i != -1) {
       student_list[i] = student_list[*number_of_students - 1];
       *number_of_students -= 1;
    }
}
