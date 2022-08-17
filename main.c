#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "queue.h"
#include "student_generation.h"


#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

void belt_test(struct Student* student);

int main(){
    int i, j, weeks, months, years;
    int number_of_students = 5;
    int training_focus = 0; // default to no focus
    char c;
    /* when a student leaves, move the student that is last in the array in his place */
    struct Student stud_muffin[5];
    srand((unsigned int)time(NULL));
        stud_muffin[0] = generate_student("Big Ned");
        stud_muffin[1] = generate_student("Mamra O Pantotinos");
        stud_muffin[2] = generate_student("Eisaku Hoshino");
        stud_muffin[3] = generate_student("Hiroyasu Gakusha");
        stud_muffin[4] = generate_student("Toshiharu Hyobanshi");
    for(i = 0; i < number_of_students; i++){ 
        print_student_stats(stud_muffin[i]);
    }



    weeks = 0;
    months = 0;
    years = 0;
    while(c != 'q' && c != 'Q'){
        printf("\nWeeks/Months/Years passed: %d/%d/%d", weeks, months, years);
        printf("\n1. Advance 1 Week");
        printf("\n2. Set training focus");
        printf("\n3. Show your students' stats");
        printf("\n4. Show your students' stat increase history");
        printf("\nQuit\n");
        printf("\nWhat do? ");
        c = getchar();
        getchar();  // consumes newline
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
            for(i = 0; i < number_of_students; i++){             
                /* increase all of the students' stats */
                increase_physical_stats(&stud_muffin[i], training_focus, weeks);
                increase_skill_stats(&stud_muffin[i], training_focus, weeks);

                /* update motivation */
                motivation_updater(&stud_muffin[i], training_focus);

                /* check to see if it is time for exam, this should be more tidy when I expand it, maybe move some of the ifs inside the function */
                /* in the first week of july or january, if it has been at least 6 months since last test and the student has lower belt rank than red / black belt, belt exams */
                if(stud_muffin[i].months_since_previous_test >= 6 && stud_muffin[i].belt_rank < RED_BLACK_BELT && (months == 6 || months == 0) && weeks == 1 ){
                    belt_test(&stud_muffin[i]);
                }
                /* in the first week of january, if it has been at least 12 months since last test and the student has red / black belt rank, belt exams */
                else if(stud_muffin[i].months_since_previous_test >= 12 && stud_muffin[i].belt_rank == RED_BLACK_BELT && months == 0 && weeks == 1 ){
                    belt_test(&stud_muffin[i]);
                }

                if(will_they_leave(&stud_muffin[i]) == 1){
                    leave_dojo(stud_muffin, &number_of_students, i);
                }
            }
            break;
            case '2':
            do{
                
                printf("\n0. No Focus");
                printf("\n1. Striking Focus");
                printf("\n2. Kicking Focus");
                printf("\n3. Holds Focus\n");
                printf("\nSelect training focus: ");
                c = getchar();
                getchar();
            } while(c < '0' || c > 3 + '0');
            i = c - '0'; 
            training_focus = i;
            break;
            case '3':
            /* show student stats */
            do{
                for(i = 0; i < number_of_students; i++)
                   printf("\n%d. %s", i, stud_muffin[i].name);
                printf("\nWhich student? ");
                c = getchar();
                getchar();
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';
            print_student_stats(stud_muffin[i]);
            break;
            case '4':
            /* choose student */
            do{         
                /* print students' names */
                for(i = 0; i < number_of_students; i++)
                    printf("\n%d. %s", i, stud_muffin[i].name);
                printf("\nWhich student? ");
                c = getchar();
                getchar();
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';

            /* choose stat */
            do{                 
                printf("\n\n1. Striking");
                printf("\n2. Kicking");
                printf("\n3. Holds");
                printf("\n4. Agility");
                printf("\n5. Strength");
                printf("\n6. Stamina");
                printf("\n7. Flexibility");
                printf("\nWhich stat would you like to see? ");
                c = getchar();
                getchar();
            } while(c < '1' || c > 7 + '0');
            j = c - '0';
            print_student_stat_history(stud_muffin[i], j);
            break;
        }
        if(weeks == 5){
            months++;
            /* update months since previous belt rank test */
            for(i = 0; i < number_of_students; i++){
                stud_muffin[i].months_since_previous_test++; 
                stud_muffin[i].months_at_dojo++;
            }
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

void belt_test(struct Student* student){
    student->months_since_previous_test = 0;
    student->belt_rank++;
    if(student->motivation + 20 < 100) student->motivation += 20;
    else student->motivation = 100;

    /* this is additive to the previous motivation boost */
    if(student->belt_rank == DAN_1ST){
        if(student->motivation + 20 < 100) student->motivation += 40;
        else student->motivation = 100;
    }
    
    if(student->belt_rank <= DAN_1ST){
        switch(student->belt_rank){
            case 1:
                printf("\n%s: White Belt -> White / Yellow Belt\tCongrats!", student->name);
                break;
            case 2:
                printf("\n%s: White / Yellow Belt -> Yellow Belt\tCongrats!", student->name);
                break;
            case 3:
                printf("\n%s: Yellow / Green Belt -> Green Belt\tCongrats!", student->name);
                break;
            case 4:
                printf("\n%s: Green Belt -> Green / Blue Belt\tCongrats!", student->name);
                break;
            case 5:
                printf("\n%s: Green Belt -> Green / Blue Belt\tCongrats!", student->name);
                break;
            case 6:
                printf("\n%s: Green / Blue Belt -> Blue Belt\tCongrats!", student->name);
                break;
            case 7:
                printf("\n%s: Blue Belt -> Blue / Red Belt\tCongrats!", student->name);
                break;
            case 8:
                printf("\n%s: Blue / Red Belt -> Red Belt\tCongrats!", student->name);
                break;
            case 9:
                printf("\n%s: Red Belt -> Red / Black Belt\tCongrats!", student->name);
                break;
            case 10:
                printf("\n%s: Red / Black Belt -> Black Belt, 1st Dan\tCongrats!", student->name);
                break;
        }
    }
    printf("\n");

}
