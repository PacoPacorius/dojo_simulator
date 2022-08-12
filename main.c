#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "queue.h"
#include "student_generation.h"


#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

int main(){
    int i, j, weeks, months, years;
    int number_of_students = 5;
    int training_focus = 0; // default to no focus
    char c;
    struct Student stud_muffin[5];
    srand((unsigned int)time(NULL));
        stud_muffin[0] = generate_student("John Doe");
        stud_muffin[1] = generate_student("Jane Doe");
        stud_muffin[2] = generate_student("Hammer Hadley");
        stud_muffin[3] = generate_student("Commander Kawagishi");
        stud_muffin[4] = generate_student("Fujio Narahashi");
    for(i = 0; i < 5; i++){ 
        print_student_stats(stud_muffin[i]);
    }



    weeks = 0;
    months = 0;
    years = 0;
    while(c != 'q' && c != 'Q'){
        c = getchar();
        switch(c){
            case '\n':
            printf("\nWeeks/Months/Years passed: %d/%d/%d", weeks, months, years);
            printf("\n1. Advance 1 Week");
            printf("\n2. Set training focus");
            printf("\n3. Show your students' stats");
            printf("\n4. Show your students' stat increase history");
            printf("\nQuit\n");
            printf("\nWhat do? ");
            break;
            case '1':
            weeks++;
            /* increase all of the students' stats */
            for(i = 0; i < 5; i++){             
                increase_physical_stats(&stud_muffin[i], training_focus, weeks);
                increase_skill_stats(&stud_muffin[i], training_focus, weeks);
                motivation_updater(&stud_muffin[i], training_focus);
            }
            break;
            case '2':
            do{
                c = getchar();
                printf("\n0. No Focus");
                printf("\n1. Striking Focus");
                printf("\n2. Kicking Focus");
                printf("\n3. Holds Focus\n");
                printf("\nSelect training focus: ");
            } while(c < '0' || c > 3 + '0');
            i = c - '0'; 
            training_focus = i;
            break;
            case '3':
            /* show student stats */
            do{
                c = getchar();
                for(i = 0; i < number_of_students; i++)
                   printf("\n%d. %s", i, stud_muffin[i].name);
                printf("\nWhich student? ");
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';
            print_student_stats(stud_muffin[i]);
            break;
            case '4':
            /* choose student */
            do{         
                c = getchar();
                /* print students' names */
                for(i = 0; i < number_of_students; i++)
                    printf("\n%d. %s", i, stud_muffin[i].name);
                printf("\nWhich student? ");
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';

            /* choose stat */
            do{                 
                c = getchar();
                printf("\n\n1. Striking");
                printf("\n2. Kicking");
                printf("\n3. Holds");
                printf("\n4. Agility");
                printf("\n5. Strength");
                printf("\n6. Stamina");
                printf("\n7. Flexibility");
                printf("\nWhich stat would you like to see? ");
            } while(c < '1' || c > 7 + '0');
            j = c - '0';
            print_student_stat_history(stud_muffin[i], j);
            break;
        }
        if(weeks == 5){
            months++;
            weeks = 0;
        }
        if(months == 12){
            months = 0;
            years++;
            for(i = 0; i < 5; i++) stud_muffin[i].age++;
        }

        printf("\n");
    }

    return 0;
}

