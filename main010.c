//
//  main.c // 게임 흐름 구현 
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt" //Each txt gets information about boards and food and festivals  
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"

#define MAX_PLAYER    100 //player 수 한계 정하기 

//board configuration parameters 보드 구성 매개변수 
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr; //플레이어 수 

static int player_energy[MAX_PLAYER];   //player 에너지
static int player_position[MAX_PLAYER]; //player 위치 
static char player_name[MAX_PLAYER][MAX_CHARNAME]; //player 이름 

//function prototypes 함수 선언 
#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif


void generatePlayers(int n, int initEnergy) //generate a new player 함수 정의 
{
     int i;
     //n time loop 
     for (i=0;i<n;i++) // player n명 있다고 가정하니까 n번 반복  
     {
         //input name
         printf("input player name: ");  
         scanf("%s", player_name[i]); // player 이름 입력받기 
         fflush(stdin);// 입력 스트림 buffer 비우기 

         //set position 초기화 
         player_position[i] = 0; 

         //set energy
         player_energy[i] = initEnergy; //초기 에너지 값 // 플레이어의 상황들을 배열로 나타냄 
     }

}








int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //Save input to c 
    fflush(stdin); //출력 버퍼를 비울때 사용, 표준입력 stdin을 비울 때 사용
	//Used to empty output buffer, used to empty standard input stdin

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1);
}




#if 0 // from this sectioin, 
//action code when a player stays at a node
void actionNode(int player)
{
    switch(type)
    {
        //case lecture:
        default:
            break;
    }
}
#endif // to this section no compile



int main(int argc, const char * argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;

    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;

    srand(time(NULL));


    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    // Bring from BOARDFILEPATH, FOODFILEPATH, FESTFILEPATH. 파일에서 가져옴 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar(); 
        return -1;
    }

    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set //읽기에 성공하는 개수를 반환함 4개 다 못일그면 while문 반복 끝남
 
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy); // smm_object.c에 저장하는 함수를 구현하고 호출 
        board_nr++;                              // main.c에서 object.c로 입력 받은 값을 전달 해야함. 전달하는 함수가 genNode임 
		// 전체 노드 개수(내가 읽어온게 몇개다 라는걸) 넣어야됨. while문 한번 돌때마다 +1됨                         
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    for (i = 0;i<board_nr;i++)// smmObj_getNodeType(i) i번째 노드의 유형값을  얻어내는 함수 유형값값이 나오면 그걸 getTypeName 함수에 집어넣어서 유형이름(강의)얻음. 
    	printf("node %i : %s, %i(%s)\n", i, smmObj_getNodeName(i), smmObj_getNodeType(i),smmObj_getTypeName(smmObj_getNodeType(i)));
		
	printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
		
	
	

	#if 0
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while (fscanf(fp, "%s %i", name, &energy) == 2) //read a food parameter set
    {
        //store the parameter set
        smmObj_genFood(name, energy);
        food_nr++;

    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
     for (i = 0;i<food_nr;i++)
        printf("food %i : %s, %i\n", i, smmObj_getNodeName(i), smmObj_getNodeEnergy(i));




    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s", name) == 1) //read a festival card string
    {
        //store the parameter set
        smmObj_genFest(name);
        festival_nr++;
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    
    for (i = 0;i<festival_nr;i++)
        printf("Fest %i : %s \n", i, smmObj_getFestName(i));



    //2. Player configuration ---------------------------------------------------------------------------------

    do
    {
        //input player number to player_nr
        printf("input player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
	while (player_nr < 0 || player > MAX_PLAYER); // 끝내야 할 조건의 반대를 걸어서 계속 반복 
	
	generatePlayers(player_nr, initEnergy);

    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while () //is anybody graduated?
    {
        int die_result;

        //4-1. initial printing
        //printPlayerStatus();

        //4-2. die rolling (if not in experiment)


        //4-3. go forward
        //goForward();

		//4-4. take action at the destination node of the board
        //actionNode();

        //4-5. next turn

    }
    #endif
    system("PAUSE");
    return 0;
}
