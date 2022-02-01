#include "header.h"

void header(){
    system("cls");
    printf("*****************************");
    printf("\n*  [Trip_Planner2k19 v0.2]  *");
    printf("\n*\t\t\t    *\n*****************************");
}

void exitMenu(){
    header();

    printf("\n\n\t************************************************************");
    printf("\n\t\t\tWE HOPE TO SEE YOU SOON ");
    printf("\n\n\n\n\t\t   THIS WILL BE THE BEST TRIP EVER ");
    printf("\n\n\n\n\t\t\t    SAFE TRAVEL ");
    printf("\n\t************************************************************");

    // if(strcmp(usr.name,"\0")!=0){
    //     userDataChange(usr);   
    // }
    saveDataBase(localList);
    destroyPlaceList(localList);

    exit(0);
}

void mytripMenu(){
    header();

    float popRet;

    printf("\n\tTHE PERFECT TRIP:\n\t\t");
    if(((usr.globalFavLoc) >= 3)){
        popRet = evaluateTrip();
    }else{
        printf("\n\t\tPlease don't forget to choose at least tree favorite points of interest and one hot point!!\n\t\tOr else we won't be able to generate your trip");
    }

    int opt;
    printf("\n\n\tHere's your main menu!");
    printf("\n\n\t\t[1] - Back ");
    if(usr.globalFavLoc >= 3){
        printf("\n\n\t\t[2] - Evaluate Trip ");
    }
    printf("\n\n\tChoose an option: ");
    opt = getInt();
    switch(opt){
        case 1:
            tripMenu();
            break;
        case 2:
            system("cls");
            printf("\n\n\t\t\tTRIP POPULARITY: %f", popRet);
            printf("\n\n\tHere's your main menu!");
            printf("\n\n\t\t[1] - Back ");
            printf("\n\n\tChoose an option: ");
            opt = getInt();
            switch(opt){
                case 1:
                    tripMenu();
                    break;
                default:
                    mytripMenu();
            }
        default:
            mytripMenu();
            break;

    }
}

void popularityMenu(){
    header();

    printf("\n\tAvailable Places:\n\t\t");

    bubbleSortPlacePop(localList);
    printPlaceList(localList);

    int opt;
    printf("\n\n\tHere's your main menu!");
    printf("\n\n\t\t[1] - Back ");
    printf("\n\n\tChoose an option: ");

    opt = getInt();
    switch(opt){
        case 1:
            tripMenu();
            break;
        default:
            popularityMenu();
            break;
    }
}

void preferencesMenu(){
    char key[BUFFSIZE];
    poiList auxPoi;
    pList auxPlace;

    header();

    printf("\n\n\tPlease set your favorites using the numbers...");
    printf("\n\tAvailable Places:\n\t\t");

    bubbleSortPlaceAlph(localList);
    printPlaceList(localList);

    int opt;
    printf("\n\n\tHere's your main menu!");
    printf("\n\tThis will be the mission control for this trip...");
    printf("\n\n\t\t[1] - Add favorite PDIs");
    if(usr.globalFavLoc < 3){
          printf("\n\n\t\t[2] - Add favorite Places ");
    }
    if(usr.globalFavPoi > 0){
        printf("\n\n\t\t[3] - Remove favorite PDIs ");
    }
    if(usr.globalFavLoc > 0){
        printf("\n\n\t\t[4] - Remove favorite Places ");
    }
    if(usr.globalHot == 0){
        printf("\n\n\t\t[5] - SET PDI HOT ");
    }else{
        printf("\n\n\t\t[6] - REMOVE PDI HOT ");
    }
    printf("\n\n\t\t[7] - Back ");
    printf("\n\n\tChoose an option: ");

    opt = getInt();
    switch(opt){
        case 1:
            printf("\tInsert Name: ");
            if(getInput(key) != 1){
                printf("\tInvalid Input\nTry again...");
                //sleep(1500);
                preferencesMenu();
            }
            if((auxPoi = getPoi(localList, strtok(key, "\n"))) != NULL){
                auxPoi->info.fav = 1;
                auxPoi->info.popularity += 1;
                strcpy(usr.favPoi[usr.globalFavPoi], key);
                usr.globalFavPoi++;
                printf("\n\t--->Point set!");
                //sleep(1500);
                preferencesMenu();
            }else{
                printf("\n\t--->That point doesn't exist try again...");
                //sleep(1500);
                preferencesMenu();
            }
            break;
        case 2:
            printf("\tInsert Name: ");
            if(getInput(key) != 1){
                printf("\tInvalid Input\nTry again...");
                //sleep(1500);
                preferencesMenu();
            }
            if((auxPlace = searchPlaceList(localList, strtok(key, "\n"))) != NULL){
                auxPlace->info.fav = 1;
                auxPlace->info.popularity += 1;
                strcpy(usr.favLoc[usr.globalFavLoc], key);
                usr.globalFavLoc++;
                printf("\n\t--->Place set!");
                //sleep(1500);
                preferencesMenu();
            }else{
                printf("\n\t--->That place doesn't exist try again...");
                //sleep(1500);
                preferencesMenu();
            }
            break;
        case 3:
            if((auxPoi = getPoi(localList, usr.favPoi[usr.globalFavPoi])) != NULL){
                auxPoi->info.fav = 0;
            }
            strcpy(usr.favPoi[usr.globalFavPoi], "");
            usr.globalFavPoi--;
            printf("\n\t--->Last Point Removed!");
            //sleep(1500);
            preferencesMenu();
            break;
        case 4:
            if((auxPlace = searchPlaceList(localList, usr.favLoc[usr.globalFavLoc])) != NULL){
                auxPlace->info.fav = 0;
            }
            strcpy(usr.favLoc[usr.globalFavLoc], "");
            usr.globalFavLoc--;
            printf("\n\t--->Last Place Removed!");
            //sleep(1500);
            preferencesMenu();
            break;
        case 5:
            printf("\tInsert Name: ");
            if(getInput(key) != 1){
                printf("\tInvalid Input\nTry again...");
                //sleep(1500);
                preferencesMenu();
            }
            if((auxPoi = getPoi(localList, strtok(key, "\n"))) != NULL){
                auxPoi->info.hot = 1;
                auxPoi->info.popularity++;
                strcpy(usr.hot, key);
                usr.globalHot = 1;
                printf("\n\t--->Point set!");
                //sleep(1500);
                preferencesMenu();
            }else{
                printf("\n\t--->That point doesn't exist try again...");
                //sleep(1500);
                preferencesMenu();
            }
            break;
        case 6:
            strcpy(usr.hot, "");
            usr.globalHot = 0;
            printf("\n\t--->Hot Point Removed...");
            //sleep(1500);
            preferencesMenu();
            break;
        case 7:
            tripMenu();
            break;
        default:
            preferencesMenu();
            break;
        }
}

void settingsMenu(){
    char aux[BUFFSIZE];
    header();

    printf("\n\tHere are your settings:\n\t\t");
    getSettings(usr);

    int opt;
    printf("\n\n\tHere's your main menu!");
    printf("\n\n\t\t[1] - Change Password ");
    printf("\n\n\t\t[2] - Change Address ");
    printf("\n\n\t\t[3] - Change Date of Birth ");
    printf("\n\n\t\t[4] - Change Phone Number ");
    printf("\n\n\t\t[5] - Back ");
    printf("\n\n\tChoose an option: ");

    opt = getInt();
    switch(opt){
        case 1:
            printf("\tInsert New Password: ");
            if(getInput(aux) == 1){
                strcpy(usr.pw, strtok(aux, "\n"));
                printf("\n\t--->Password Changed");
                //sleep(1500);
                settingsMenu();
            }else{
                printf("\n\t--->Not changes were made\nPlease try again...");
                //sleep(1000);
                settingsMenu();
            }
            break;
        case 2:
            printf("\tInsert New Address: ");
            if(getInput(aux) == 1){
                strcpy(usr.address, strtok(aux, "\n"));
                printf("\n\t--->Address Changed");
                //sleep(1000);
                settingsMenu();
            }else{
                printf("\n\t--->Not changes were made\nPlease try again...");
                //sleep(1000);
                settingsMenu();
            }
            break;
        case 3:
            printf("\tInsert New Date of Birth: ");
            if(getInput(aux) == 1){
                strcpy(usr.birth, strtok(aux, "\n"));
                printf("\n\t--->Date of Birth Changed");
                //sleep(1000);
                settingsMenu();
            }else{
                printf("\n\t--->\tNot changes were made\nPlease try again...");
                //sleep(1000);
                settingsMenu();
            }
            break;
        case 4:
            printf("\tInsert New Phone Number: ");
            if(getInput(aux) == 1){
                strcpy(usr.phoneNum, strtok(aux, "\n"));
                printf("\n\t--->\tPhone Number Changed");
                //sleep(1000);
                settingsMenu();
            }else{
                printf("\n\t--->\tNot changes were made\nPlease try again...");
                //sleep(1000);
                settingsMenu();
            }
            break;
        case 5:
            tripMenu();
            break;
        default:
            settingsMenu();
            break;
    }
}

void tripMenu(){
    header();

    int opt;
    printf("\n\n\tHere's your main menu!");
    printf("\n\tThis will be the mission control for this trip...");
    printf("\n\n\t\t[1] - My Trip ");
    printf("\n\n\t\t[2] - Locations Popularity ");
    printf("\n\n\t\t[3] - Locations Preferences ");
    printf("\n\n\t\t[4] - Settings ");
    printf("\n\n\t\t[5] - Log Off ");
    printf("\n\n\tChoose an option: ");

    opt = getInt();
    switch(opt){
        case 1:
            mytripMenu();
            break;
        case 2:
            popularityMenu();
            break;
        case 3:
            preferencesMenu();
            break;
        case 4:
            settingsMenu();
            break;
        case 5:
            if(strcmp(usr.name,"\0")!=0){
                userDataChange(usr);   
            }
            // userDataChange(usr);
            saveDataBase(localList);
            accessMenu();
            break;
        default:
            tripMenu();
            break;
    }
 }

void loginMenu(){
    char id[BUFFSIZE], pw[BUFFSIZE];
    int flag = 0;
    header();

    printf("\n\n\tPlease insert your ID and Password... ");
    printf("\n\n\t\tID: ");
    if(getInput(id) != 1){
        flag++;
    }
    printf("\t\tPassword: ");
    if(getInput(pw) != 1){
        flag++;
    }

    if(flag > 0){
        printf("\n\tWrong credentials... \n\tPlease try again!\n");
        //sleep(1000);
        accessMenu();
    }

    else if((checkCred(id, pw) != 1)){
        printf("\n\tWrong credentials... \n\tPlease try again!\n");
        //sleep(1000);
        accessMenu();
    }

    printf("\n\tWelcome!!");
    //sleep(1000);
    tripMenu();
}

void registerMenu(){
    char id[BUFFSIZE], pw[BUFFSIZE], address[BUFFSIZE], db[BUFFSIZE], phone[BUFFSIZE];
    int flag = 0;

    header();

    printf("\n\n\tPlease provide the following information... ");
    printf("\n\n\t\tName: ");
    if(getInput(id) == 1){
        strtok(id, "\n");
        strcpy(usr.name, id);
    }else{
        flag++;
    }
    printf("\t\tPassword: ");
    if(getInput(pw) == 1){
        strtok(pw, "\n");
        strcpy(usr.pw, pw);
    }else{
        flag++;
    }
    printf("\t\tAddress: ");
    if(getInput(address) == 1){
        strtok(address, "\n");
        strcpy(usr.address, address);
    }else{
        flag++;
    }
    printf("\t\tDate of Birth(dd/mm/yyyy): ");
    if(getInput(db) == 1){
        strtok(db, "\n");
        strcpy(usr.birth, db);
    }else{
        flag++;
    }
    printf("\t\tPhone number: ");
    if(getInput(phone) == 1){
        strtok(phone, "\n");
        strcpy(usr.phoneNum, phone);
    }else{
        flag++;
    }

    if((flag > 0)){
        printf("\n\tWe couldn't register you... \n\tPlease try again!\n");
        //sleep(1500);
        accessMenu();
    }
    else if((registerUser(id, pw, address, db, phone) != 1)){
        printf("\n\tWe couldn't register you... \n\tPlease try again!\n");
        //sleep(1500);
        accessMenu();
    }else{
        printf("\n\tYou are now registered...\n\tWelcome!!\n\tYou can now login!");
        //sleep(1500);
        accessMenu();
    }
}

void accessMenu(){
    header();

    int opt;
    printf("\n\n\tHi there!!");
    printf("\n\tPlease start by signing in...");
    printf("\n\n\t\t[1] - Login ");
    printf("\n\n\t\t[2] - Register ");
    printf("\n\n\t\t[3] - Exit ");
    printf("\n\n\tChoose an option: ");

    opt = getInt();
    switch(opt){
        case 1:
            loginMenu();
            break;
        case 2:
            registerMenu();
            break;
        case 3:
            exitMenu();
            break;
        default:
            accessMenu();
            break;
    }
}

void welcomeMenu(){
    header();

    dataRead(localList);

    printf("\n\n\t************************************************************");
    printf("\n\t\t\t\t   WELCOME ");
    printf("\n\n\n\n\t\t\tTHIS WILL BE THE BEST TRIP EVER ");
    printf("\n\n\n\n\t\t\t    PRESS ENTER TO CONTINUE ");
    printf("\n\t************************************************************");

    if(getchar()){
        accessMenu();
    }
}

int main(){
    welcomeMenu();
    return 0;
}
