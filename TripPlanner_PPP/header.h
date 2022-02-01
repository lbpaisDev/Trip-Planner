#ifndef HEADER
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
// #include <windows.h>
#define HEADER
#define BUFFSIZE 1024
#endif

/*Main Structures
Point of Interest*/
typedef struct poi{
	char name[BUFFSIZE];
	char desc[BUFFSIZE];
	char wperiod[BUFFSIZE];
	int fav;
	int popularity;
	int hot;
}PoI;

//PoI linked list
typedef struct lnode *poiList;
typedef struct lnode{
	PoI info;
    poiList next;
}nodeList;

//Place
typedef struct place{
	char cityName[BUFFSIZE];
    int popularity;
    int fav;
	poiList listPoi;
}Place;

//Place Linked List
typedef struct llnode *pList;
typedef struct llnode{
	Place info;
    pList next;
}pnodeList;

//User
typedef struct user{
	char name[BUFFSIZE];
	char pw[BUFFSIZE];
	char address[BUFFSIZE];
	char birth[BUFFSIZE];
	char phoneNum[BUFFSIZE];
    char hot[BUFFSIZE];
    char favPoi[60][BUFFSIZE];
    char favLoc[3][BUFFSIZE];
    int globalFavLoc;
    int globalFavPoi;
    int globalHot;
	Place trip[3];
}User;


//INIT
User usr;
pList localList;

//Main Functions
//Menus
void header();
void exitMenu();
void mytripMenu();
void localMenu();
void settingsMenu();
void preferencesMenu();
void tripMenu();
void loginMenu();
void registerMenu();
void accessMenu();
void welcomeMenu();

//Auxiliary Functions
//****GET INPUTS****
int getInt();
int getInput(char temp[BUFFSIZE]);

//****REGISTER*****
int checkCred(char *id, char *pw);
int registerUser(char *id, char*pw, char *address, char *db, char *phone);

//****USER RELATED****
void getSettings(User usr);

//****PRINT STRUCTS****
void printUser(User usr);
void printLocal(Place local);
void printPoi(PoI poi);

//****TRIP RELATED****
int generateTrip();
float evaluateTrip();

//****FUNCTIONALITY****
poiList getPoi(pList list, char *key);
void fndHt(poiList list, poiList *prev, poiList *curr);
poiList findHot(poiList list);
void fndFv(poiList list, poiList *prev, poiList *curr);
poiList findFav(poiList list);

//****POI LIST****
poiList createPoiList();
int emptyPoiList(poiList list);
poiList destroyPoiList(poiList list);
void srchPoiList(poiList list, char *key, poiList *prev, poiList *curr);
poiList searchPoiList(poiList list, char *key);
void insertPoiList(poiList list, PoI poi);
void printPoiList(poiList list);
void insertPoiListTail(poiList list, PoI poi);
void insertPoiListFront(poiList list, PoI poi);

//****PLACE LIST****
pList CreatePlaceList();
int emptyPoiList(poiList list);
pList destroyPlaceList(pList list);
void srchPlaceList(pList list, char *key, pList *prev, pList *curr);
pList searchPlaceList(pList list, char *key);
void insertPlaceList(pList list, Place pl);
void printPlaceList(pList list);

//****AUX****
void dataRead(pList placeList);
void bubbleSortPlaceAlph(pList placeList);
void bubbleSortPoiAlph(poiList listPoi);
void bubbleSortPlacePop(pList placeList);
void bubbleSortPoiPop(poiList listPoi);
void saveDataBase(pList ListaLocais);
int getCountpList(pList ListaLocais);
int getCountPOIs(poiList list);
void userDataChange(User user);

