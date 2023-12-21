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

 

//board configuration parameters 보드 구성 매개변수 
static int board_nr;
static int food_nr;
static int festival_nr;


static int player_nr; //플레이어 수  
 // 전역변수 배열로 정의한 요소들을 player 구조체로 묶어서 정의
typedef struct player {  //1. 구조체 형식 정의  
        int energy;
        int position;
        char name[MAX_CHARNAME];//문자열이니까 char배열 
        int accumCredit;
        int flag_graduate;
} player_t; 
//2. 구조체 배열 선언 
static player_t cur_player[MAX_PLAYER];

#if 0
static int player_energy[MAX_PLAYER];   //player 에너지
static int player_position[MAX_PLAYER]; //player 위치 
static char player_name[MAX_PLAYER][MAX_CHARNAME]; //player 이름 
#endif
 
//function prototypes 함수 선언 
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


 
void printPlayerStatus(void) //plaeyer의 현재 상태(이름,학점,에너지,위치)를 나타내는 함수 정의함. 
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
//3. 기존함수 수정 및 새로 작성

// player 수는 게임 시작 시 입력받으며, 각 플레이어의 이름을 입력받음
//player가 이동할 때 거치는 노드 이름을 모두 출력해야 함.
//입력된 순으로 player가 돌아가면서 주사위를 던지고 이동하며 턴 시작 시 모든 플레이어의 상태, 위치, 실험 중 상태, 누적학점,현재에너지를 출력해야 함. 
void generatePlayers(int n, int initEnergy) //generate a new player 함수 정의 
{
     int i;
     //n time loop 
     for (i=0;i<n;i++) // player n명 있다고 가정하니까 n번 반복  
     {
         //input name
         printf("input player %i's name: ",i); 
		 scanf("%s", cur_player[i].name); // cur_player 배열의 i번째 요소에 해당하는 구조체의 name 필드에 사용자가 입력한 문자열을 저장
          // player 이름 입력받기 
         fflush(stdin);// 입력 스트림 buffer 비우기 

         //set position 초기화 
         //player_position[i] = 0; 
         cur_player[i].position=0; //조체 배열 cur_player에서 i번째 요소의 position 멤버 변수를 0으로 초기화

         //set energy
         //player_energy[i] = initEnergy; //초기 에너지 값 // 플레이어의 상황들을 배열로 나타냄 
     	 cur_player[i].energy = initEnergy;
         cur_player[i].accumCredit = 0; //누적 학점 0으로 초기화. 
         cur_player[i].flag_graduate = 0; //0으로 초기화.player가 졸업을 할 수 있는 상태인지 아닌지 나타냄. flag가 1인 상태로 도착하면 졸업.
		  
	 
	 
	 }

}




int rolldie(int player) //주사위 랜덤숫자 함수정의 
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //Save input to c 
	fflush(stdin); 
     //출력 버퍼를 비울때 사용, 표준입력 stdin을 비울 때 사용
	//Used to empty output buffer, used to empty standard input stdin

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1); //랜덤으로 주사위 굴림 
}





//action code when a player stays at a node
int ramdom() {
    return (rand() % 6) + 1;  // 1~6랜덤숫자 함수 정의 
}

void actionNode(int player)

{
	int type = smmObj_getNodeType( cur_player[player].position );
	
    switch(type)
    {	
        //case lecture  현재 에너지가 소요 에너지 이상 있고 이전에 듣지 않은 강의이면 수강 가능하며, 수강 혹은 드랍을 선택할 수 잇음.
		//(수강하면 성적이 A+,A0,A-,B+,B0,B-,C+,C0,C-중 하나가 랜덤으로 나옴. 
        case SMMNODE_TYPE_LECTURE:
        {
                // 현재 에너지가 소요에너지 이상이고, 이전에 듣지 않은 강의인지 여부를 확인
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
                        // 드랍 선택
                        printf("You dropped the lecture.\n");
                    } else {
                        printf("Invalid choice. No action taken.\n");
                    }
                } else {
                    printf("Not enough energy to attend the lecture.\n");
                }
            }
            break;

        // case retaurant 보충 에너지만큼 플레이어의 현재 에너지가 더해짐. 
        case SMMNODE_TYPE_RESTAURANT:
         	cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
            break;
       
        //case home 시작점이자 종료점.지나가는 순간 지정된 보충에너지만큼 현재 에너지에 더해짐. 
        case SMMNODE_TYPE_HOME:
            cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
            break;
            
        //case GOTOLAB 
        case SMMNODE_TYPE_GOTOLAB:
        	srand(time(NULL));  // 난수 발생
              int criterion = random();  //랜덤 함수 호출 
              printf("Experiment Success Criterion Values: %d\n", criterion); // 
              
              cur_player[player].position = SMMNODE_TYPE_LABORATORY; // Laboratory로 이동
              break;
 
        //case laboratory 
        case SMMNODE_TYPE_LABORATORY:
              cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position); // 실험 시도마다 소요된 에너지 차감
              srand(time(NULL));  // 난수 발생기를 초기화 (프로그램을 실행할 때 한 번만 수행)
              int result = ramdom();  // 1에서 6까지의 랜덤한 숫자를 생성

              if (result >= criterion) {
                  printf("you can escape.\n");
              } else {
                  printf("You can't escape', try next turn.\n");
              return;
              }
              break;

        //case foodchance
        
        case SMMNODE_TYPE_FOODCHANCE:
        	srand(time(NULL));  // 난수 발생기를 초기화
    		int randomfood = rand() % food_nr;  // 음식 카드 중 무작위로 하나 선택
    		void*foodObj = smmdb_getData(LISTNO_FOODCARD,randomfood);
    	
    
        //case festival
        case SMMNODE_TYPE_FESTIVAL:
			srand(time(NULL));  // 난수 발생기를 초기화
    		int randomFestival = rand() % festival_nr;  // 축제 카드 중 무작위로 하나 선택
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
        if(type == SMMNODE_TYPE_HOME)
        	initEnergy = energy;
		board_nr++;                              // main.c에서 object.c로 입력 받은 값을 전달 해야함. 전달하는 함수가 genNode임 
		// 전체 노드 개수(내가 읽어온게 몇개다 라는걸) 넣어야됨. while문 한번 돌때마다 +1됨                         
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    for (i = 0;i<board_nr;i++)// smmObj_getNodeType(i) i번째 노드의 유형값을  얻어내는 함수 유형값값이 나오면 그걸 getTypeName 함수에 집어넣어서 유형이름(강의)얻음. 
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
	while (player_nr < 0 || player_nr > MAX_PLAYER); // 끝내야 할 조건의 반대를 걸어서 계속 반복 
	
	generatePlayers(player_nr, initEnergy);
	
	
	#if 0 
	//턴을 돌면서 플레이어가 동작하는 코드 
	//주어진 while문을 채워서 반복적으로 플레이어 동작이 이루어지도록 함( 무한 반복) 
	// 한번의 반복에서 한 플레이어가 한턴 동작 수행 
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;

        //4-1. initial printing 
        printPlayerStatus(); 

        //4-2. die rolling (if not in experiment) 동
		die_result = rolldie(turn); // turn은 player 순서  

        //4-3. go forward 주사위에 따라 이동 
        goForward(turn,die_result);

		//4-4. take action at the destination node of the board 에너지 관련 동작 
        actionNode(turn);
		// 강의 칸에 머물때 학점 채우는 동작 
        //4-5. next turn
        turn=(turn+1)%player_nr

    }
#endif
    system("PAUSE");
    return 0;
	}

