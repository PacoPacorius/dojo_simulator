#include <string.h>
#include "name_generator.h"

char* random_name(){
    char* male_first_name[] = { "John ", "Alex ", "Big Guy ", "Skip ", "Jack ", "James ", "Jimmy ", "Chris ", 
                                      "Thomas ", "Harry ", "Alfred ", "Christian ", "Christopher ", "Alessio ",
                                      "Jamie ", "Dave ", "Aaron ", "Vern ", "Justin ", "Jared ", "David Scott ",
                                      "Kurtis ", "Ethan ", "Billy ", "Taylor ", "Timmy ", "AJ ", "Donald ",
                                      "Tracy ", "Rick ", "Mike ", "Big Mike ", "Mark ", "Erin ", "Ben ", "Grant ",
                                      "Renato ", "Shotaro ", "Masahiro ", "Kiyoshi " };

    char* female_first_name[] = { "Jean ", "Jane ", "Victoria ", "Mary ", "Chris ", "Vicky ", "Tanya ", "Maria ",
                                        "Jamie ", "Sara ", "Alice ", "Margaret ", "Kelly ", "Peyton ", "Alex ", "Alexia ",
                                        "Violet ", "Kathleen ", "Cathy ", "Hanna ", "Billy ", "Connie ", "Tracy ",
                                        "Regina ", "Erin " "Adrienne ", "Vic ", "Sophia ", "Anna ", "Natalia ", "Eddie ",
                                        "Tilda ", "Helena ", "Chloe ", "Suzy ", "Suzie ", "Mia ", "Susanna ", "Vanda ",
                                        "Olivia ", "Halla ", "Madame ", "Eva " };

    char* last_name[] = { "McGee", "Green", "Brown", "Smith", "McKenzie", "Abbott", "Baker", "Godard", "Chalkias",
                                "Cox", "Oliver", "Knudson", "Lee", "Chamberlain", "Gillespie", "Cook", "Lund", "Rumsey", 
                                "Trosper", "Warren", "Seckington", "Sandeno", "Stone", "Glass", "Osborne", "Bighorse",
                                "Mayo", "Roditis", "Mayugba", "Sgarbossa", "Allen", "Moreno", "Tartol", "Duck", "Bratton",
                                "Froberg", "Kennedy", "Reis", "Trombino", "Common", "Frederiksen", "Preston", "Quinby", "McTague",
                                "Dudley", "Nottke", "Brandell", "Swanton", "Laufey", "Goth", "Griffith", "Blanc", "Albrecht", 
                                "Harper", "Bennett", "Leda", "Akiyama" };
    int gender, index;
    int array_size;
    char* first_name;
    char* surname;
    char* full_name;

    /* 0 is male, 1 is female */
    gender = rand_lim(1);

    if(gender == 0){
        array_size = sizeof(male_first_name) / sizeof(male_first_name[0]);
//      printf("\nArray Size: %d", array_size);
        index = rand_lim(array_size - 1);
//      printf("\nIndex: %d", index);
        first_name = male_first_name[index];
//      printf("\nFirst Name: %s\n", first_name);
    }
    else{
        array_size = sizeof(female_first_name) / sizeof(female_first_name[0]);
        index = rand_lim(array_size - 1);
//      printf("\nArray Size: %d", array_size);
//      printf("\nIndex: %d", index);
        first_name = female_first_name[index];
//      printf("\nFirst Name: %s\n", first_name);
    }

    array_size = sizeof(last_name) / sizeof(last_name[0]);
//  printf("\nArray Size: %d", array_size);
//  printf("\nIndex: %d", index);
    index = rand_lim(array_size - 1);
    surname = last_name[index];
//  printf("\nLast Name: %s\n", surname);

    full_name = (char *)malloc((1 + strlen(first_name) + strlen(surname) * sizeof(char)));
    strcpy(full_name, first_name);
    strcat(full_name, surname);

    return full_name;
    
}


