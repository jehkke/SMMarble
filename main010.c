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

 

//board configuration parameters ���� ���� �Ű����� 
static int board_nr;
static int food_nr;
static int festival_nr;


static int player_nr; //�÷��̾� ��  
 // �������� �迭�� ������ ��ҵ��� player ����ü�� ��� ����
typedef struct player {  //1. ����ü ���� ����  
        int energy;
        int position;
        char name[MAX_CHARNAME];//���ڿ��̴ϱ� char�迭 
        int accumCredit;
        int flag_graduate;
} player_t; 
//2. ����ü �迭 ���� 
static player_t cur_player[MAX_PLAYER];

#if 0
static int player_energy[MAX_PLAYER];   //player ������
static int player_position[MAX_PLAYER]; //player ��ġ 
static char player_name[MAX_PLAYER][MAX_CHARNAME]; //player �̸� 
#endif
 
//function prototypes �Լ� ���� 
#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player) //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif


 
void printPlayerStatus(void) //plaeyer�� ���� ����(�̸�,����,������,��ġ)�� ��Ÿ���� �Լ� ������. 
{
     int i;

     for (i=0;i<player_nr;i++)
     {
         printf("%s : credit %i, energy %i, position %i\n", 
                      cur_player[i].name,
                      cur_player[i].accumCredit,
                      cur_player[i].energy,
                      cur_player[i].position);
     }
}
//3. �����Լ� ���� �� ���� �ۼ�

// player ���� ���� ���� �� �Է¹�����, �� �÷��̾��� �̸��� �Է¹���
//player�� �̵��� �� ��ġ�� ��� �̸��� ��� ����ؾ� ��.
//�Էµ� ������ player�� ���ư��鼭 �ֻ����� ������ �̵��ϸ� �� ���� �� ��� �÷��̾��� ����, ��ġ, ���� �� ����, ��������,���翡������ ����ؾ� ��. 
void generatePlayers(int n, int initEnergy) //generate a new player �Լ� ���� 
{
     int i;
     //n time loop 
     for (i=0;i<n;i++) // player n�� �ִٰ� �����ϴϱ� n�� �ݺ�  
     {
         //input name
         printf("input player %i's name: ",i); 
		 scanf("%s", cur_player[i].name); // cur_player �迭�� i��° ��ҿ� �ش��ϴ� ����ü�� name �ʵ忡 ����ڰ� �Է��� ���ڿ��� ����
          // player �̸� �Է¹ޱ� 
         fflush(stdin);// �Է� ��Ʈ�� buffer ���� 

         //set position �ʱ�ȭ 
         //player_position[i] = 0; 
         cur_player[i].position=0; //��ü �迭 cur_player���� i��° ����� position ��� ������ 0���� �ʱ�ȭ

         //set energy
         //player_energy[i] = initEnergy; //�ʱ� ������ �� // �÷��̾��� ��Ȳ���� �迭�� ��Ÿ�� 
     	 cur_player[i].energy = initEnergy;
         cur_player[i].accumCredit = 0; //���� ���� 0���� �ʱ�ȭ. 
         cur_player[i].flag_graduate = 0; //0���� �ʱ�ȭ.player�� ������ �� �� �ִ� �������� �ƴ��� ��Ÿ��. flag�� 1�� ���·� �����ϸ� ����.
		  
	 
	 
	 }

}




int rolldie(int player) //�ֻ��� �������� �Լ����� 
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //Save input to c 
	fflush(stdin); 
     //��� ���۸� ��ﶧ ���, ǥ���Է� stdin�� ��� �� ���
	//Used to empty output buffer, used to empty standard input stdin

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1); //�������� �ֻ��� ���� 
}





//action code when a player stays at a node
int ramdom() {
    return (rand() % 6) + 1;  // 1~6�������� �Լ� ���� 
}

void actionNode(int player)

{
	int type = smmObj_getNodeType( cur_player[player].position );
	
    switch(type)
    {	
        //case lecture  ���� �������� �ҿ� ������ �̻� �ְ� ������ ���� ���� �����̸� ���� �����ϸ�, ���� Ȥ�� ����� ������ �� ����.
		//(�����ϸ� ������ A+,A0,A-,B+,B0,B-,C+,C0,C-�� �ϳ��� �������� ����. 
        case SMMNODE_TYPE_LECTURE:
        {
                // ���� �������� �ҿ信���� �̻��̰�, ������ ���� ���� �������� ���θ� Ȯ��
                if (cur_player[player].energy >= smmObj_getNodeEnergy(cur_player[player].position)) {
                    printf("Do you want to attend the lecture? (1: Attend, 0: Drop): ");
                    int choice;
                    scanf("%d", &choice);

                    if (choice == 1) {
                       
                        cur_player[player].accumCredit += smmObj_getNodeCredit(cur_player[player].position);
                        cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);

                        
                        char* grades[] = {"A+", "A0", "A-", "B+", "B0", "B-", "C+", "C0", "C-"};
                        int randomIndex = rand() % 9;
                        printf("You attended the lecture and received grade: %s\n", grades[randomIndex]);
                    } else if (choice == 0) {
                        // ��� ����
                        printf("You dropped the lecture.\n");
                    } else {
                        printf("Invalid choice. No action taken.\n");
                    }
                } else {
                    printf("Not enough energy to attend the lecture.\n");
                }
            }
            break;

        // case retaurant ���� ��������ŭ �÷��̾��� ���� �������� ������. 
        case SMMNODE_TYPE_RESTAURANT:
         	cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
            break;
       
        //case home ���������� ������.�������� ���� ������ ���濡������ŭ ���� �������� ������. 
        case SMMNODE_TYPE_HOME:
            cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
            break;
            
        //case GOTOLAB 
        case SMMNODE_TYPE_GOTOLAB:
        	srand(time(NULL));  // ���� �߻�
              int criterion = random();  //���� �Լ� ȣ�� 
              printf("Experiment Success Criterion Values: %d\n", criterion); // 
              
              cur_player[player].position = SMMNODE_TYPE_LABORATORY; // Laboratory�� �̵�
              break;
 
        //case laboratory 
        case SMMNODE_TYPE_LABORATORY:
              cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position); // ���� �õ����� �ҿ�� ������ ����
              srand(time(NULL));  // ���� �߻��⸦ �ʱ�ȭ (���α׷��� ������ �� �� ���� ����)
              int result = ramdom();  // 1���� 6������ ������ ���ڸ� ����

              if (result >= criterion) {
                  printf("you can escape.\n");
              } else {
                  printf("You can't escape', try next turn.\n");
              return;
              }
              break;

        //case foodchance
        
        case SMMNODE_TYPE_FOODCHANCE:
        	srand(time(NULL));  // ���� �߻��⸦ �ʱ�ȭ
    		int randomfood = rand() % food_nr;  // ���� ī�� �� �������� �ϳ� ����
    		void*foodObj = smmdb_getData(LISTNO_FOODCARD,randomfood);
    	
    
        //case festival
        case SMMNODE_TYPE_FESTIVAL:
			srand(time(NULL));  // ���� �߻��⸦ �ʱ�ȭ
    		int randomFestival = rand() % festival_nr;  // ���� ī�� �� �������� �ϳ� ����
    		void*festObj = smmdb_getData(LISTNO_FESTCARD,randomFestival);

    		printf("You encountered a festival: %s. Mission: Perform a task!\n", smmObj_getNodeName);
    		break;
    		
    break;
            
        default:
            break;
    }
}


void goForward(int player, int step)
{
     cur_player[player].position += step;

     printf("%s go to node %i (name: %s)\n", 
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(cur_player[player].position));
}



int main(int argc, const char * argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
	int initEnergy;
	int turn=0;
	
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
        if(type == SMMNODE_TYPE_HOME)
        	initEnergy = energy;
		board_nr++;                              // main.c���� object.c�� �Է� ���� ���� ���� �ؾ���. �����ϴ� �Լ��� genNode�� 
		// ��ü ��� ����(���� �о�°� ��� ��°�) �־�ߵ�. while�� �ѹ� �������� +1��                         
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    for (i = 0;i<board_nr;i++)// smmObj_getNodeType(i) i��° ����� ��������  ���� �Լ� ���������� ������ �װ� getTypeName �Լ��� ����־ �����̸�(����)����. 
    	printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(i), 
                     smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),
                     smmObj_getNodeCredit(i), smmObj_getNodeEnergy(i));

	
	


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
	while (player_nr < 0 || player_nr > MAX_PLAYER); // ������ �� ������ �ݴ븦 �ɾ ��� �ݺ� 
	
	generatePlayers(player_nr, initEnergy);
	
	
	#if 0 
	//���� ���鼭 �÷��̾ �����ϴ� �ڵ� 
	//�־��� while���� ä���� �ݺ������� �÷��̾� ������ �̷�������� ��( ���� �ݺ�) 
	// �ѹ��� �ݺ����� �� �÷��̾ ���� ���� ���� 
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;

        //4-1. initial printing 
        printPlayerStatus(); 

        //4-2. die rolling (if not in experiment) ��
		die_result = rolldie(turn); // turn�� player ����  

        //4-3. go forward �ֻ����� ���� �̵� 
        goForward(turn,die_result);

		//4-4. take action at the destination node of the board ������ ���� ���� 
        actionNode(turn);
		// ���� ĭ�� �ӹ��� ���� ä��� ���� 
        //4-5. next turn
        turn=(turn+1)%player_nr

    }
#endif
    system("PAUSE");
    return 0;
	}

