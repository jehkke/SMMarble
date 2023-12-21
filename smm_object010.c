
// object.h에 함수 헤더 둠. 
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100 // 보드의 칸(노드) 개수가 몇개 인지 안말함. 100개 정도로 정하기
#define MAX_FOOD        50
#define MAX_FEST        50 // 각 범위 정해두기 


static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "강의",
       "식당",
       "실험실",
       "집",
       "실험실로이동",
       "음식찬스",
       "축제시간"
};
// 유형이름  입력 함수 정의 
char* smmObj_getTypeName(int type) // 유형 값  입력은 main.c에서 i번쨰 노드의 유형을 얻어내는 함수 
{
      return (char*)smmNodeName[type];
}

typedef enum smmObjGrade {
    smmObjGrade_Ap = 0,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;

//이름, 유형, 학점, 에너지 
//1. 구조체 형식 정의 (칸에 대한 구조체의 정의는 여기서만 하고 보여주면 안됨)
typedef struct smmObject {		// 구조체 정의 name,type,credit,energy 변수 멤버, smmObject_t 변수선언 
       char name[MAX_CHARNAME];
       int type;
       int credit;
       int energy;
} smmObject_t;  

typedef struct smmFood { // 구조체 정의와 name,energy 변수 멤버,smmFood_t 변수선언 
		char name[MAX_CHARNAME];
		int energy;
} smmFood_t;


typedef struct smmFest { // 구조체 정의 name 변수 멤버, smmFest_t 변수선언 
       char name[MAX_CHARNAME];
} smmFest_t;  


//2. 구조체 배열 변수 정의 
//static smmObject_t smm_node[MAX_NODE];
//static int smmObj_noNode = 0;
//smmFood_t smm_food[MAX_FOOD];
//static int smmObj_noFood=0;
//smmFest_t smm_fest[MAX_FEST];
//static int smmObj_noFest=0;

#if 0
//전역변수 선언 
// smm_Obj -> smm_Obj안에 존재하는 전역변수다. //구조체로 나중에 바꿈.  
static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //문자열을 멀티로 저장하고 싶으면 2차원배열로 하면 됨.// charname은 200자 이내인거 common.h에 정의 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
#endif

static smmObject_t smmnode[MAX_NODE]; //smmObject_t 구조체 smnode배열 설정 



//3. 관련 함수 배열에서 구조체로  맞게 변경 
//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //main에서 값 입력받는  genNode 함수 정의 
{
	#if 0 
    strcpy(smmObj_name[smmObj_noNode], name); //배열에 입력값을 넣음. 문자열은 하나하나씩 복사해야됨. strcpy 쓰기 
    smmObj_type[smmObj_noNode] = type; 
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;
	#endif
	// 원래 main함수에서 칸에 대한 정보를 가져온다음에 값을 저장하는 형태 
	// 이젠 구조체에다가 값을 넣는 형태 
	strcpy(smm_node[smmObj_noNode].name, name); // 전역변수 배열을 구조체 배열로 바꿈. 
    smm_node[smmObj_noNode].type = type;
    smm_node[smmObj_noNode].credit = credit;
    smm_node[smmObj_noNode].energy = energy;
	
    smmObj_noNode++;  
}




//Food generation function
void smmObj_genFood(char*name, int energy)
{
	 #if 0
	strcpy(smmObj_name[smmObj_noFood],name);
	smmObj_energy[smmObj_noFood] = energy;
	#endif
	
	strcpy(smm_food[smmObj_noFood].name, name);
	smm_food[smmObj_noFood].energy = energy;
	
	smmObj_noFood++;
}

//Festival generatiom function
void smmObj_genFest(char*name)
{
	strcpy(smm_fest[smmObj_noFest].name,name);
	
	smmObj_noFest++;
}



//3. 관련 함수 변경: . 연산자를 이용하여 구조체 멤버 변수로 변경 
////Node function return
char* smmObj_getNodeName(int node_nr) //몇번째 노드의 이름을 받고싶냐 
{
    return smm_node[node_nr].name; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}
//함수의 반환값= type 값
int smmObj_getNodeType(int node_nr) //type 값이 여러개인데, 몇번째 값을 가져올거야? node number 로 매개변수 
{
    return smm_node[node_nr].type; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}

int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}


//Food function return
char* smmObj_getFoodName(int food_nr) //몇번째 노드의 이름을 받고 싶냐 
{
    return smm_food[food_nr].name;
	 
}
int smmObj_getFoodEnergy(int food_nr)
{
    return smm_food[food_nr].energy; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}
// Fest function return
char* smmObj_getFestName(int fest_nr) //몇번째 노드의 이름을 받고 싶냐 
{
    return smm_fest[fest_nr].name; //. 연산자를 이용하여 구조체 멤버 변수로 변경 후 반환 
}


