/*********************************************************************
 ** Program Filename:chencho.adventure.c
 ** Author:Chongxian Chen
 ** Date:Feb 8, 2016
 ** Description:Play the Dungeon Game
 ** Input:Room names as the game goes
 ** Output:A folder contains the files generated
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void generate_files(char filenamelist[][30]);
void shuffle_int_array();
void print_int_array(int* array, int size);
void print_room_info(int *cur_room, char important_data_from_file[][10][30], int num_con);

int main() {
    
    //for generating random numbers.
    srand(time(NULL));
    //the array is to store pointers to files opened
    FILE* fplist[7];
    //num_connections will be 2 bigger than the real connection numbers because two extea lines
    //to store how many rooms of connections each room has
    int num_connections[7]={0,0,0,0,0,0,0};
    //store important information into the array after open the files
    char important_data_from_file[7][10][30];
    //store the path of all seven files, initialize it to \0 so there are no weird error happens
    char filenamelist[7][30] = {"\0","\0","\0","\0","\0","\0","\0"};
    //call the function to generate files
    generate_files(filenamelist);
    
    //store temparary stings extracted from the file.
    char buff[255];
    //remember current file
    int cur = 0;
    //for testing
    //printf("filenamelist: %s\n", filenamelist[cur]);
    
    //s[2] is the array to store the token we are looking for in the input file.
    //":" is the token we are looking for to divide the important strings.
    char s[2] = ":";
    char *token;
    //read all data into the important_data_from_file array
    for (cur = 0; cur<7; cur++) {
        fplist[cur] = fopen(filenamelist[cur], "r");
        while (fgets(buff, 255, (FILE*)fplist[cur])) {
            token = strtok(buff, s);
            token = strtok(NULL, s);
            token[strcspn(token, "\n")] = 0;
            strcpy(important_data_from_file[cur][num_connections[cur]], token);
            //printf("%s", token);
            num_connections[cur]++;
        }
        if (!fclose(fplist[cur])) {
            //printf("succ close file\n");
        }
    }
    
    int cur_room = 0;
    int step = 0;
    //remember 255 steps in path array. Can't imagine some one took more than 255 steps to complete the game.
    int path[255];
    
    
    //start playing the game after generating files and read files
    printf("\n");
    printf("********Welcome to the Dungeon Adventure!********\n");
    printf("Find the treasure and leave the dungeon safely!\n");
    printf("\n");
    //if the room index is not the end room
    while (cur_room != 6) {
        path[step] = cur_room;
        print_room_info(&cur_room, important_data_from_file, num_connections[cur_room]);
        //printf("cu room %d\n", cur_room);
        step++;
    }
    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", step);
    int count=0;
    //print the path
    for (count = 1; count < step; count++) {
        printf("%s\n", important_data_from_file[path[count]][0]);
    }
    //print the name of the end room at the end.
    printf("%s\n", important_data_from_file[6][0]);

   return 0;
}


/*********************************************************************
 ** Function:generate_files
 ** Description:Generate files with random connections
 ** Parameters:file paths
 ** Pre-Conditions:filenamelist contains the file paths
 ** Post-Conditions:NONE
 *********************************************************************/
void generate_files(char filenamelist[][30]) {
    
    printf("generating files...\n");
    //get the pid and create the directory to store rooms.
    int id = getpid();
    //printf("%d\n", id);
    char idstr[10];
    sprintf(idstr, "%d", id);
    char dirname[30] = "chencho.rooms.";
    strcat(dirname, idstr);
    //printf("%s\n", dirname);
    mkdir(dirname, 0755);
    
    //create roomnames and write then into files.
    char roomnames[10][5] = {"Oreo", "Ipad", "CHEN", "PSVT", "PSIV", "DEAR", "N3DS", "3DSL", "BASE", "BALL"};
    char filename[30];
    //initialize the filenamelist, if unnitialized, getting weird error.
    //char filenamelist[7][30] = {"\0","\0","\0","\0","\0","\0","\0"};
    
    int array[10]  = {0,1,2,3,4,5,6,7,8,9};
    shuffle_int_array(array, 10);
    //print_int_array(array, 10);
    FILE* fplist[7];

    strcat(filename, "./");
    strcat(filename, dirname);
    strcat(filename, "/");
    //printf("%s\n", filename);
    
    int i;
    for (i = 0; i < 7; i++) {
        //printf("%d\n", i);
        strcat(filenamelist[i], filename);
        strcat(filenamelist[i], roomnames[array[i]]);
        //printf("%s\n", filenamelist[i]);
        fplist[i] = fopen(filenamelist[i], "w+");
        fputs("ROOM NAME:", fplist[i]);
        fputs(roomnames[array[i]], fplist[i]);
        fputs("\n", fplist[i]);
    }
    
    //since we shuffled the array, the rooms connected are randomized.
    //Connection for room 0 and type start room.
    fputs("CONNECTION1:", fplist[0]);
    fputs(roomnames[array[1]], fplist[0]);
    fputs("\n", fplist[0]);
    fputs("CONNECTION2:", fplist[0]);
    fputs(roomnames[array[3]], fplist[0]);
    fputs("\n", fplist[0]);
    fputs("CONNECTION3:", fplist[0]);
    fputs(roomnames[array[5]], fplist[0]);
    fputs("\n", fplist[0]);
    fputs("CONNECTION4:", fplist[0]);
    fputs(roomnames[array[6]], fplist[0]);
    fputs("\n", fplist[0]);
    fputs("ROOM TYPE:START_ROOM\n", fplist[0]);
    
    //Connection for room 1 and type mid room.
    fputs("CONNECTION1:", fplist[1]);
    fputs(roomnames[array[0]], fplist[1]);
    fputs("\n", fplist[1]);
    fputs("CONNECTION2:", fplist[1]);
    fputs(roomnames[array[2]], fplist[1]);
    fputs("\n", fplist[1]);
    fputs("CONNECTION3:", fplist[1]);
    fputs(roomnames[array[6]], fplist[1]);
    fputs("\n", fplist[1]);
    fputs("ROOM TYPE:MID_ROOM\n", fplist[1]);
    
    //Connection for room 2 and type mid room.
    fputs("CONNECTION1:", fplist[2]);
    fputs(roomnames[array[1]], fplist[2]);
    fputs("\n", fplist[2]);
    fputs("CONNECTION2:", fplist[2]);
    fputs(roomnames[array[4]], fplist[2]);
    fputs("\n", fplist[2]);
    fputs("CONNECTION3:", fplist[2]);
    fputs(roomnames[array[5]], fplist[2]);
    fputs("\n", fplist[2]);
    fputs("ROOM TYPE:MID_ROOM\n", fplist[2]);

    //Connection for room 3 and type mid room.
    fputs("CONNECTION1:", fplist[3]);
    fputs(roomnames[array[0]], fplist[3]);
    fputs("\n", fplist[3]);
    fputs("CONNECTION2:", fplist[3]);
    fputs(roomnames[array[4]], fplist[3]);
    fputs("\n", fplist[3]);
    fputs("CONNECTION3:", fplist[3]);
    fputs(roomnames[array[5]], fplist[3]);
    fputs("\n", fplist[3]);
    fputs("ROOM TYPE:MID_ROOM\n", fplist[3]);
    
    //Connection for room 4 and type mid room.
    fputs("CONNECTION1:", fplist[4]);
    fputs(roomnames[array[2]], fplist[4]);
    fputs("\n", fplist[4]);
    fputs("CONNECTION2:", fplist[4]);
    fputs(roomnames[array[3]], fplist[4]);
    fputs("\n", fplist[4]);
    fputs("CONNECTION3:", fplist[4]);
    fputs(roomnames[array[6]], fplist[4]);
    fputs("\n", fplist[4]);
    fputs("ROOM TYPE:MID_ROOM\n", fplist[4]);
    
    //Connection for room 5 and type mid room.
    fputs("CONNECTION1:", fplist[5]);
    fputs(roomnames[array[0]], fplist[5]);
    fputs("\n", fplist[5]);
    fputs("CONNECTION2:", fplist[5]);
    fputs(roomnames[array[2]], fplist[5]);
    fputs("\n", fplist[5]);
    fputs("CONNECTION3:", fplist[5]);
    fputs(roomnames[array[3]], fplist[5]);
    fputs("\n", fplist[5]);
    fputs("ROOM TYPE:MID_ROOM\n", fplist[5]);
    
    //Connection for room 6 and type end room.
    fputs("CONNECTION1:", fplist[6]);
    fputs(roomnames[array[0]], fplist[6]);
    fputs("\n", fplist[6]);
    fputs("CONNECTION2:", fplist[6]);
    fputs(roomnames[array[4]], fplist[6]);
    fputs("\n", fplist[6]);
    fputs("CONNECTION3:", fplist[6]);
    fputs(roomnames[array[1]], fplist[6]);
    fputs("\n", fplist[6]);
    fputs("ROOM TYPE:END_ROOM\n", fplist[6]);

    
    for (i = 0; i < 7; i++) {
        if (!fclose(fplist[i])) {
            //printf("file%d closed successfully\n", i);
        }
    }
}

/*********************************************************************
 ** Function:shuffle_int_array
 ** Description:shuffle an array contains integer
 ** Parameters:the array pointer and the size wanted to shuffle
 ** Pre-Conditions:an array with integers
 ** Post-Conditions:NONE
 *********************************************************************/
void shuffle_int_array(int* array, int size){
    int i=0;
    int j=0;
    int k=0;
    int temp = 0;
    if (size > 1) {
        for (k = 0; k< 10; k++){//loop for k = 10 times
            for (i = 0; i < size-1; i++) {
                j = rand()%size;
                //printf("the value of j is %d\n", j); //for testing purpose
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

/*********************************************************************
 ** Function:print_int_array
 ** Description:print array contains integer
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void print_int_array(int* array, int size) {
    int i =0;
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/*********************************************************************
 ** Function:print_room_info
 ** Description:print the room info as described and change the current room index[important]
 ** Parameters:cur_room, data, number of connections the current room has
 ** Pre-Conditions:data, cur_room index and its room connection numbers
 ** Post-Conditions:change the cur_room index after user connects to another room
 *********************************************************************/
void print_room_info(int *cur_room, char important_data_from_file[][10][30], int num_con) {
    printf("CURRENT LOCATION:");
    printf("%s\n", important_data_from_file[*cur_room][0]);
    printf("POSSIBLE CONNECTIONS:");
    int i = 1;
    //print connections based on connection numbers
    for (i = 1; i < num_con-2; i++) {
        printf("%s, ", important_data_from_file[*cur_room][i]);
    }
    printf("%s.\n", important_data_from_file[*cur_room][i]);
    printf("WHERE TO?>");
    char des[30];
    int connection_check = 1;
    scanf("%s", des);
    printf("\n");
    //connection_check first time
    for (i = 1; i<num_con-1; i++) {
        if (strcmp(des, important_data_from_file[*cur_room][i]) == 0) {
            connection_check = 0;
            break;
        }
    }
    //going into the loop for multipe wrong input
    while (connection_check) {
        printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        printf("\n");
        printf("CURRENT LOCATION:");
        printf("%s\n", important_data_from_file[*cur_room][0]);
        printf("POSSIBLE CONNECTIONS:");
        int i = 1;
        for (i = 1; i < num_con-2; i++) {
            printf("%s, ", important_data_from_file[*cur_room][i]);
        }
        printf("%s.\n", important_data_from_file[*cur_room][i]);
        printf("WHERE TO?>");

        scanf("%s", des);
        printf("\n");
        for (i = 1; i<num_con-1; i++) {
            if (strcmp(des, important_data_from_file[*cur_room][i]) == 0) {
                connection_check = 0;
                break;
            }
        }
    }
    //check which room index according to user input string des
    for (i = 0; i<7; i++) {
        if (strcmp(des, important_data_from_file[i][0]) == 0) {
            *cur_room = i;
            //printf("current room %d\n", *cur_room);
            break;
        }
    }
}
