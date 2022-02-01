#include "header.h"

//****GET INPUTS****
//Get input properly protected
int getInt(){
    int n = 0;
    char buffer[BUFFSIZE];
    fgets(buffer, BUFFSIZE, stdin);
    n = atoi(buffer);
    return (n > 23 || n < 1) ? 0 : n;
}

int getInput(char temp[BUFFSIZE]){
    fgets(temp, BUFFSIZE, stdin);
    if(strlen(temp) < 3 || !(temp) || strlen(temp) > BUFFSIZE){
        return 0;
    }
    return 1;
}

//****REGISTER*****
//Read and write in the register log properly protected
int checkCred(char *id, char *pw){
    FILE *fin;
    fin = fopen("../Files/registerlog.txt", "r");
    char tempStr[BUFFSIZE];
    char userSetts[BUFFSIZE];
    char aux[BUFFSIZE];
    char *tempID;
    char *tempPw;
    char aux2[20];
    while(fgets(tempStr, BUFFSIZE, fin) != NULL){
        strcpy(userSetts, tempStr);
        tempID = strtok(tempStr, "\t");
        tempPw = strtok(NULL, "\t");
        if((strcmp(tempID, strtok(id, "\n")) == 0) && (strcmp(tempPw, strtok(pw, "\n")) == 0)){
            strcpy(usr.name, strtok(userSetts, "\t"));
            strcpy(usr.pw, strtok(NULL, "\t"));
            strcpy(usr.address, strtok(NULL, "\t"));
            strcpy(usr.birth, strtok(NULL, "\t"));
            strcpy(usr.phoneNum, strtok(NULL, "\t"));
            usr.globalFavLoc = atoi(strtok(NULL, "\t"));
            usr.globalFavPoi = atoi(strtok(NULL, "\t"));
            usr.globalHot = atoi(strtok(NULL, "\t"));

            memset(aux,0,strlen(aux));
            strcpy(aux, strtok(NULL, "\t"));
            if(strcmp(aux,"#")==0){
                strcpy(usr.hot,"\0");
            }else{
                strcpy(usr.hot,aux);
            }

            memset(aux,0,strlen(aux));
            strcpy(aux, strtok(NULL, "\t"));
            if(strcmp(aux,"#")==0){
                strcpy(usr.favLoc[0],"\0");
                usr.globalFavLoc=0;
            }else{
                strcpy(usr.favLoc[0],aux);
            }

            memset(aux,0,strlen(aux));
            strcpy(aux, strtok(NULL, "\t"));
            if(strcmp(aux,"#")==0){
                strcpy(usr.favLoc[1],"\0");
            }else{
                strcpy(usr.favLoc[1],aux);
            }

            memset(aux,0,strlen(aux));
            strcpy(aux, strtok(NULL, "\n"));
            if(strcmp(aux,"#")==0){
                strcpy(usr.favLoc[2],"\n");
            }else{
                strcpy(usr.favLoc[2],aux);
            }
            return 1;
        }
    }
    return 0;
}

int registerUser(char *id, char*pw, char *address, char *db, char *phone){
    FILE *fout;
    fout = fopen("../Files/registerlog.txt", "a");
    char *aux="#";
    if(fout != NULL){
        fprintf(fout, "%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%s\t%s\n", strtok(id,"\n"), strtok(pw, "\n"), strtok(address, "\n"), strtok(db, "\n"), strtok(phone, "\n"), 0, 0, 0,aux,aux,aux,aux);
        fclose(fout);
        return 1;
    }
    return 0;
}

//****USER RELATED****
//User related functions
void getSettings(User usr){
    printUser(usr);
    if(usr.globalHot == 0){
        printf("\n\t\tNo Hot Point of Interest chosen");
    }else{
        printf("\n\t\tHot Point: %s", usr.hot);
    }
    if(usr.globalFavPoi == 0 ){
        printf("\n\t\tNo Points of Interest favorites chosen");
    }else{
        printf("\n\t\tFavorite Points: ");
        for(int i = 0; i < (usr.globalFavPoi); i++){
            printf("\n\t\t\t%s", usr.favPoi[i]);
        }
    }
    if(usr.globalFavLoc == 0 ){
        printf("\n\t\tNo locals of Interest favorites chosen");
    }else{
        printf("\n\t\tFavorites Places: ");
        for(int i = 0; i < (usr.globalFavLoc); i++){
            printf("\n\t\t\t%s", usr.favLoc[i]);
        }
    }
}

//****PRINT STRUCTS****
void printUser(User usr){
    printf("\n\t\tName: %s", usr.name);
    printf("\n\t\tPassword: %s", usr.pw);
    printf("\n\t\tAddress: %s", usr.address);
    printf("\n\t\tDate of birth: %s", usr.birth);
    printf("\n\t\tPhone Number: %s", usr.phoneNum);
}

void printLocal(Place local){
    printf("\n\t\tCity Name: %s", local.cityName);
    printf("\n\t\tPopularity: %d", local.popularity);
    printPoiList(local.listPoi);

}

void printPoi(PoI poi){
    printf("\n\t\t\t\tPOI Name: %s", poi.name);
    printf("\n\t\t\t\tDescription: %s", poi.desc);
    printf("\n\t\t\t\tWorking period: %s", poi.wperiod);
    printf("\n\t\t\t\tPopularity: %d", poi.popularity);
    //printf("\n\t\t\t\tHot: %d", poi.hot);
    printf("\n");
}

//****TRIP RELATED****
//Trip related functions
void printTrip(){
    for(int i = 0; i < 3; i++){
        printLocal(usr.trip[i]);
    }
}

int generateTrip(){
    pList auxPlNode;
    poiList auxPoiNode;
    int tripPop = 0;
    int j = 0;

    for(int i = 0; i < 3; i++){
        j = 0;
        if((auxPlNode = searchPlaceList(localList, usr.favLoc[i])) != NULL){
            strcpy(usr.trip[i].cityName, auxPlNode->info.cityName);
            usr.trip[i].fav = auxPlNode->info.fav;
            usr.trip[i].popularity = auxPlNode->info.popularity;
            usr.trip[i].listPoi = createPoiList();

            tripPop += usr.trip[i].popularity;

            bubbleSortPoiPop(auxPlNode->info.listPoi);
            auxPoiNode = auxPlNode->info.listPoi->next;
            while(auxPoiNode != NULL && j < 3){
                tripPop += auxPoiNode->info.popularity;
                insertPoiListTail(usr.trip[i].listPoi, auxPoiNode->info);
                j++;
                auxPoiNode = auxPoiNode->next;
            }
        }
    }
    printTrip();
    return tripPop;
}

float evaluateTrip(){
    int tripPop = generateTrip();
    int totalPop = 0;


    pList curr = localList->next;
    while(curr != NULL){
        totalPop += curr->info.popularity;
        poiList currPoi = curr->info.listPoi->next;
        while(currPoi != NULL){
            totalPop += currPoi->info.popularity;
            currPoi = currPoi->next;
        }
        curr = curr->next;
    }

    return ((double) tripPop)/((double) totalPop);
}

//****FUNCTIONALITY****
poiList getPoi(pList list, char *key){
    pList curr;
    poiList prev;
    poiList auxCurr;

    curr = list->next;
    while(curr != NULL){
        srchPoiList(curr->info.listPoi, key, &prev, &auxCurr);
        if(auxCurr != NULL){
            return auxCurr;
        }
        curr = curr ->next;
    }
    return NULL;
}

//****POI LIST****
//PoI List
poiList createPoiList(){
    poiList aux;
    aux = (poiList)malloc(sizeof(nodeList));
    if(aux != NULL){
        strcpy(aux->info.name, "");
        strcpy(aux->info.desc, "");
        strcpy(aux->info.wperiod, "");
        aux->info.fav = 0;
        aux->info.popularity = 0;
        aux->info.hot = 0;
        aux->next = NULL;
    }
    return aux;
}

int emptyPoiList(poiList list){
    return (list->next == NULL) ? 1 : 0;
}

poiList destroyPoiList(poiList list){
    poiList tempPtr;
    while(emptyPoiList(list) == 0){
        tempPtr = list;
        list = list->next;
        free(tempPtr);
    }
    free(list);
    return NULL;
}

void srchPoiList(poiList list, char *key, poiList *prev, poiList *curr){
    *prev = list;
    *curr = list->next;
    while((*curr != NULL) && (strcmp((*curr)->info.name, key) < 0)){
        *prev = *curr;
        *curr = (*curr)->next;
    }
    if((*curr != NULL) && (strcmp((*curr)->info.name, key) != 0)){
        *curr = NULL;
    }
}

poiList searchPoiList(poiList list, char *key){
    poiList prev;
    poiList curr;

    srchPoiList(list, key, &prev, &curr);

    return curr;
}

void insertPoiList(poiList list, PoI poi){
    poiList node;
    poiList prev, useless;
    node = (poiList)malloc(sizeof(nodeList));
    if(node != NULL){
        strcpy(node->info.name, poi.name);
        strcpy(node->info.desc, poi.desc);
        strcpy(node->info.wperiod, poi.wperiod);
        node->info.popularity = poi.popularity;
        node->info.fav = poi.fav;
        node->info.hot = poi.hot;
        srchPoiList(list, poi.name, &prev, &useless);
        node->next = prev->next;
        prev->next = node;
    }
}

void insertPoiListTail(poiList list, PoI poi){
    poiList prev, node;

    for(prev = list; prev->next; prev = prev->next)
        ;
    node = (poiList)malloc(sizeof(nodeList));
    strcpy(node->info.name, poi.name);
    strcpy(node->info.desc, poi.desc);
    strcpy(node->info.wperiod, poi.wperiod);
    node->info.popularity = poi.popularity;
    node->info.fav = poi.fav;
    node->info.hot = poi.hot;
    prev->next = node;
    node->next = NULL;
}

void insertPoiListFront(poiList list, PoI poi){
    poiList node = (poiList)malloc(sizeof(nodeList));

    strcpy(node->info.name, poi.name);
    strcpy(node->info.desc, poi.desc);
    strcpy(node->info.wperiod, poi.wperiod);
    node->info.popularity = poi.popularity;
    node->info.fav = poi.fav;
    node->info.hot = poi.hot;
    node->next = list->next;
    list->next = node;
}

void printPoiList(poiList list){
    poiList curr = list->next;
    while(curr){
        printPoi(curr->info);
        curr = curr->next;
    }
}

//****PLACE LIST****
//Place list
pList CreatePlaceList(){
    pList aux;
    aux = (pList)malloc(sizeof(pnodeList));
    if(aux != NULL){
        strcpy(aux->info.cityName, "");
        aux->info.popularity = 0;
        aux->info.listPoi = NULL;
        aux->info.fav = 0;
        aux->next = NULL;
    }
    return aux;
}

int emptyPlaceList(pList list){
    return (list->next == NULL) ? 1 : 0;
}

pList destroyPlaceList(pList list){
    pList tempPtr;
    while(emptyPlaceList(list) == 0){
        tempPtr = list;
        list = list->next;
        free(tempPtr);
    }
    free(list);
    return NULL;
}

void srchPlaceList(pList list, char *key, pList *prev, pList *curr){
    *prev = list;
    *curr = list->next;
    while((*curr != NULL) && (strcmp((*curr)->info.cityName, key) < 0)){
        *prev = *curr;
        *curr = (*curr)->next;
    }
    if((*curr != NULL) && (strcmp((*curr)->info.cityName, key) != 0)){
        *curr = NULL;
    }
}

pList searchPlaceList(pList list, char *key){
    pList prev;
    pList curr;

    srchPlaceList(list, key, &prev, &curr);

    return curr;
}

void insertPlaceList(pList list, Place pl){
    pList node;
    pList prev, useless;
    node = (pList)malloc(sizeof(pnodeList));
    if(node != NULL){
        strcpy(node->info.cityName, pl.cityName);
        node->info.popularity = pl.popularity;
        node->info.listPoi = pl.listPoi;
        node->info.fav = pl.fav;
        srchPlaceList(list, pl.cityName, &prev, &useless);
        node->next = prev->next;
        prev->next = node;
    }
}

void printPlaceList(pList list){
    pList curr = list->next;
    int i = 0;
    while(curr){
        printLocal(curr->info);
        i++;
        curr = curr->next;
    }
}

//****AUX****
void dataRead(pList placeList){
    FILE *fp;
    char buffer[BUFFSIZE];
    char aux[BUFFSIZE];
    int size=BUFFSIZE;

    fp = fopen("../Files/database.txt", "r");
    if(fp==NULL){
        return;
    }

    Place local;
    localList = CreatePlaceList();
    while(fgets(buffer,size,fp)!=NULL){
        strcpy(aux,strtok(buffer,"\n"));
        int pop;
        if(strcmp(aux,"local")== 0){
            fgets(buffer,size,fp);
            strcpy(aux,strtok(buffer,","));
            strcpy(local.cityName,aux);
            strcpy(aux,strtok(NULL,";"));
            pop=atoi(aux);
            local.popularity=pop;
            local.listPoi = createPoiList();
            insertPlaceList(localList, local);
        }else if(strcmp(aux,"local")!=0){
            PoI Point;
            strcpy(aux,strtok(buffer,","));
            strcpy(Point.name,aux);
            strcpy(aux,strtok(NULL,","));
            strcpy(Point.desc,aux);
            strcpy(aux,strtok(NULL,","));
            strcpy(Point.wperiod,aux);
            strcpy(aux,strtok(NULL,";"));
            pop=atoi(aux);
            Point.popularity=pop;
            insertPoiList(local.listPoi, Point);
        }
    }
    fclose(fp);
}

void bubbleSortPlaceAlph(pList placeList){
    int swapped;
    pList ptr;

    do{
        Place temp;
        swapped = 0;
        ptr = placeList->next;
        while (ptr->next != NULL){
            bubbleSortPoiAlph(ptr->info.listPoi);
            if (strcmp(ptr->info.cityName, ptr->next->info.cityName) > 0){

                strcpy(temp.cityName, ptr->info.cityName);
                temp.listPoi = ptr->info.listPoi;
                temp.popularity = ptr->info.popularity;

                strcpy(ptr->info.cityName, ptr->next->info.cityName);
                ptr->info.listPoi = ptr->next->info.listPoi;
                ptr->info.popularity = ptr->next->info.popularity;

                strcpy(ptr->next->info.cityName, temp.cityName);
                ptr->next->info.listPoi = temp.listPoi;
                ptr->next->info.popularity = temp.popularity;

                swapped = 1;
            }
            ptr = ptr->next;
        }
    }while(swapped);
}

void bubbleSortPoiAlph(poiList listPoi){
    int swapped;
    poiList ptr;

    do{
        PoI temp;
        swapped = 0;
        ptr = listPoi->next;
        while (ptr->next != NULL){
            if (strcmp(ptr->info.name, ptr->next->info.name) > 0){

                strcpy(temp.name, ptr->info.name);
                strcpy(temp.desc, ptr->info.desc);
                strcpy(temp.wperiod, ptr->info.wperiod);
                temp.popularity = ptr->info.popularity;

                strcpy(ptr->info.name, ptr->next->info.name);
                strcpy(ptr->info.desc, ptr->next->info.desc);
                strcpy(ptr->info.wperiod, ptr->next->info.wperiod);
                ptr->info.popularity = ptr->next->info.popularity;

                strcpy(ptr->next->info.name, temp.name);
                strcpy(ptr->next->info.desc, temp.desc);
                strcpy(ptr->next->info.wperiod, temp.wperiod);
                ptr->next->info.popularity = temp.popularity;

                swapped = 1;
            }
            ptr = ptr->next;
        }
    }while(swapped);
}

void bubbleSortPlacePop(pList placeList){
    int swapped;
    pList ptr;

    do{
        Place temp;
        swapped = 0;
        ptr = placeList->next;
        while (ptr->next != NULL){

            bubbleSortPoiPop(ptr->info.listPoi);
            if (ptr->info.popularity < ptr->next->info.popularity){

                strcpy(temp.cityName, ptr->info.cityName);
                temp.listPoi = ptr->info.listPoi;
                temp.popularity = ptr->info.popularity;

                strcpy(ptr->info.cityName, ptr->next->info.cityName);
                ptr->info.listPoi = ptr->next->info.listPoi;
                ptr->info.popularity = ptr->next->info.popularity;

                strcpy(ptr->next->info.cityName, temp.cityName);
                ptr->next->info.listPoi = temp.listPoi;
                ptr->next->info.popularity = temp.popularity;

                swapped = 1;
            }
            ptr = ptr->next;
        }
    }while(swapped);
}

void bubbleSortPoiPop(poiList listPoi){
    int swapped;
    poiList ptr;

    do{
        PoI temp;
        swapped = 0;
        ptr = listPoi->next;
        while (ptr->next != NULL){
            if (ptr->info.popularity < ptr->next->info.popularity){

                strcpy(temp.name, ptr->info.name);
                strcpy(temp.desc, ptr->info.desc);
                strcpy(temp.wperiod, ptr->info.wperiod);
                temp.popularity = ptr->info.popularity;

                strcpy(ptr->info.name, ptr->next->info.name);
                strcpy(ptr->info.desc, ptr->next->info.desc);
                strcpy(ptr->info.wperiod, ptr->next->info.wperiod);
                ptr->info.popularity = ptr->next->info.popularity;

                strcpy(ptr->next->info.name, temp.name);
                strcpy(ptr->next->info.desc, temp.desc);
                strcpy(ptr->next->info.wperiod, temp.wperiod);
                ptr->next->info.popularity = temp.popularity;

                swapped = 1;
            }
            ptr = ptr->next;
        }
    }while(swapped);
}

void saveDataBase(pList ListaLocais){
    FILE *fp;
    fp=fopen("../Files/database.txt","w");
    int count=0;
    int noslocal=getCountpList(ListaLocais);
    pList curr=ListaLocais->next;
    Place local;
    poiList pois;
    while(count<noslocal){
        int nospois=getCountPOIs(curr->info.listPoi);
        local=curr->info;
        pois=local.listPoi;
        fprintf(fp,"local\n");
        fprintf(fp,"%s,%d;\n",local.cityName,local.popularity);
        int i=0;
        poiList curr1=pois->next;
        while(i<nospois){
            fprintf(fp,"%s,%s,%s,%d;\n",curr1->info.name,curr1->info.desc,curr1->info.wperiod,curr1->info.popularity);
            curr1=curr1->next;
            i++;
        }
        curr=curr->next;
        count++;
    }
    fclose(fp);
}

int getCountpList(pList ListaLocais){
    int count = 0;
    pList curr=ListaLocais->next;
    while(curr){
        count++;
        curr=curr->next;
    }
    return count;
}

int getCountPOIs(poiList list){
    int count=0;
    poiList curr = list->next;
    while(curr){
        count++;
        curr = curr->next;
    }
    return count;
}

void userDataChange(User user){
    FILE *fp;
    FILE *fpsave;
    char buffer[BUFFSIZE];
    char aux[BUFFSIZE];
    int size=BUFFSIZE;
    char newline[BUFFSIZE];
    char *nome;
    nome = (char*) malloc(sizeof(user.name));
    strcpy(nome, user.name);
    int countlinhas;
    int alinha;
    char *nameorigin="../Files/registerlog.txt";
    char *namesave="../Files/registsave.txt";

    fp = fopen("../Files/registerlog.txt", "r");
    if(fp==NULL){
        printf("Erro a abrir o ficheiro\n");
        fclose(fp);
        return;
    }
    fpsave=fopen("../Files/registsave.txt", "w+");
    if (fpsave==NULL){
        printf("Unable to open a temporary file to write!!\n");
        fclose(fpsave);
        return;
    }
    while(fgets(buffer,size,fp)!=NULL){
        strcpy(aux,strtok(buffer,"\t"));
        if(strcmp(aux,nome)==0){
            alinha=countlinhas;
            strcpy(newline,buffer);
            break;
        }
        countlinhas++;
    }
    fseek ( fp,0, SEEK_SET );
    int count=0;
    strcpy(buffer, "\0");
    while (fgets(buffer,size,fp)!=NULL){
        if (count != alinha){
            fprintf(fpsave, "%s\n", strtok(buffer,"\0"));
        }
        count++;
        strcpy(buffer, "\0");
    }
    if(strcmp(user.hot,"\0")==0){
        strcpy(user.hot,"#");
    }
    if(strcmp(user.favLoc[0],"\0")==0){
        strcpy(user.favLoc[0],"#");
    }
    if(strcmp(user.favLoc[1],"\0")==0){
        strcpy(user.favLoc[1],"#");
    }
    if(strcmp(user.favLoc[2],"\0")==0){
        strcpy(user.favLoc[2],"#");
    }

    fprintf(fpsave,"%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%s\t%s\n", user.name,user.pw,user.address,user.birth,user.phoneNum,user.globalFavLoc, user.globalFavPoi,user.globalHot,user.hot,user.favLoc[0],user.favLoc[1],user.favLoc[2]);

    fclose(fp);
    fclose(fpsave);
    if(remove(nameorigin) != 0){
        perror("\nCouldn't remove file");
        //sleep(1000);
    }
    if(rename(namesave, nameorigin) != 0){
        perror("\nCouldn't rename file");
        //sleep(1000);
        perror("\nCouldn't remove file");
        //sleep(1000);
    }
}

