#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "student_generation.h"

struct Student generate_student(char* new_name){
    struct Student temp;
    temp.name = new_name;

    /* generate age */
    temp.age = rand_lim(45) + 16;

    /* generate weight class */
    temp.weight_class = generate_weight_class();

    /* physical stats (0-100) */
    // generate agility
    // temp.agility = generate_agility(int weight_class);
    temp.agility = generate_agility(temp.weight_class, temp.age);
    temp.strength = generate_strength(temp.weight_class, temp.age);
    temp.flexibility = generate_flexibility(temp.weight_class, temp.age);
    temp.stamina = generate_stamina(temp.weight_class, temp.age);

    /* skill stats (0-100) */
    temp.holds = 0;
    temp.striking = 0;
    temp.kicking = 0;

    
    /* personality stats (0-100) */
    temp.motivation = 100;

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

    return temp;
}

int rand_lim(int limit) {
    /* return a random number between 0 and limit inclusive.*/

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int randint(int limit){
    if((limit - 1) == RAND_MAX) return rand();
    else {
        assert(limit <= RAND_MAX);

        int end = RAND_MAX / limit;
        assert(end > 0);
        end *= limit;

        int r;
        while((r = rand()) >= end);

        return r % limit;
    }
}
int generate_weight_class(){
    int r = 0;

    r = randint(RAND_MAX);
    if(r < RAND_MAX / 6){
        /* if student is in the minority that isn't a lightweight, a middleweight or a light heavy, 50 50 chance to be really big or really small*/
        r = rand_lim(1);
        if(r == 1){
            r = rand_lim(1) + 5 + 1; // Heavy or Super Heavy
        }
        else r = rand_lim(1) + 1; // Small or Very Small
    }
    else { // majority, lightweight, middleweight, light heavy
        r = rand_lim(2) + 2 + 1;
    }
    
    return r;
}

int generate_agility(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30) + 10;
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(20);
        }
        else {
            /* the best of the rest */
            r = rand_lim(30);
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(10);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(25);
        }
        else if( weight_class > 5){
            r = rand_lim(10);
        }
        else {
            r = rand_lim(20);
        }
    }

    return r;
}

int generate_stamina(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30) + 20;
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(30);
        }
        else {
            /* the best of the rest */
            r = rand_lim(30) + 10;
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(5);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(40);
        }
        else if( weight_class > 5){
            r = rand_lim(20);
        }
        else {
            r = rand_lim(30);
        }
    }

    return r;
}
int generate_flexibility(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30);
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(10);
        }
        else {
            /* the best of the rest */
            r = rand_lim(20);
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(5);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(20);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(10);
        }
    }

    return r;
}
int generate_strength(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < LIGHTWEIGHT){   
            /* small & very small only */
            r = rand_lim(30);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            /* heavyweights and super heavyweights only */
            r = rand_lim(30) + 30;
        }
        else {
            /* the best of the rest */
            r = rand_lim(30) + 10;
        }
    }
    else if(age > 45){
        if(weight_class < LIGHTWEIGHT){
            r = rand_lim(20);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            r = rand_lim(30) + 20;
        }
        else {
            r = rand_lim(30);
        }
    }
    else {
        if(weight_class < LIGHTWEIGHT){
            r = rand_lim(40);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            r = rand_lim(30) + 40;
        }
        else {
            r = rand_lim(30) + 20;
        }
    }

    return r;
}

void generate_destiny_values(struct Student* stud){
    stud->destiny_agility = get_gaussdist_number(30, 100);
    stud->destiny_flexibility = get_gaussdist_number(30, 100);
    stud->destiny_strength = get_gaussdist_number(30, 100);
    stud->destiny_stamina = get_gaussdist_number(30, 100);

    stud->destiny_striking = get_gaussdist_number(30, 100);
    stud->destiny_kicking = get_gaussdist_number(30, 100);
    stud->destiny_holds = get_gaussdist_number(30, 100);
    
    /* add body type bonuses / penalties */
}

double get_gaussdist_number(int lower_lim, int upper_lim){
    double gaussian_num = -1.0;
    double uniform_nums;
    double uniform_numu;
    int uniform_number;

    /* Box-Muller transform */
    while(gaussian_num < lower_lim || gaussian_num > upper_lim){
        uniform_nums = (double)rand_lim(RAND_MAX - 1) / RAND_MAX;
        uniform_numu = (double)rand_lim(RAND_MAX - 1) / RAND_MAX;

        gaussian_num = sqrt(-2*log(uniform_numu))*cos(2*M_PI*uniform_nums);
        gaussian_num *= 60;
    }

    return gaussian_num;
}
