//
//  main.c // ���� �帧 ���� 
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

#define MAX_PLAYER    100 //player �� �Ѱ� ���ϱ� 

//board configuration parameters ���� ���� �Ű����� 
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr; //�÷��̾� �� 

static int player_energy[MAX_PLAYER];   //player ������
static int player_position[MAX_PLAYER]; //player ��ġ 
static char player_name[MAX_PLAYER][MAX_CHARNAME]; //player �̸� 

//function prototypes �Լ� ���� 
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


void generatePlayers(int n, int initEnergy) //generate a new player �Լ� ���� 
{
     int i;
     //n time loop 
     for (i=0;i<n;i++) // player n�� �ִٰ� �����ϴϱ� n�� �ݺ�  
     {
         //input name
         printf("input player name: ");  
         scanf("%s", player_name[i]); // player �̸� �Է¹ޱ� 
         fflush(stdin);// �Է� ��Ʈ�� buffer ���� 

         //set position �ʱ�ȭ 
         player_position[i] = 0; 

         //set energy
         player_energy[i] = initEnergy; //�ʱ� ������ �� // �÷��̾��� ��Ȳ���� �迭�� ��Ÿ�� 
     }

}








int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //Save input to c 
    fflush(stdin); //��� ���۸� ��ﶧ ���, ǥ���Է� stdin�� ��� �� ���
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
    // Bring from BOARDFILEPATH, FOODFILEPATH, FESTFILEPATH. ���Ͽ��� ������ 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar(); 
        return -1;
    }

    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set //�б⿡ �����ϴ� ������ ��ȯ�� 4�� �� ���ϱ׸� while�� �ݺ� ����
 
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy); // smm_object.c�� �����ϴ� �Լ��� �����ϰ� ȣ�� 
        board_nr++;                              // main.c���� object.c�� �Է� ���� ���� ���� �ؾ���. �����ϴ� �Լ��� genNode�� 
		// ��ü ��� ����(���� �о�°� ��� ��°�) �־�ߵ�. while�� �ѹ� �������� +1��                         
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    for (i = 0;i<board_nr;i++)// smmObj_getNodeType(i) i��° ����� ��������  ���� �Լ� ���������� ������ �װ� getTypeName �Լ��� ����־ �����̸�(����)����. 
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
	while (player_nr < 0 || player > MAX_PLAYER); // ������ �� ������ �ݴ븦 �ɾ ��� �ݺ� 
	
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
