//
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


//전역변수 선언 
// smm_Obj -> smm_Obj안에 존재하는 전역변수다. //구조체로 나중에 바꿈.  
static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //문자열을 멀티로 저장하고 싶으면 2차원배열로 하면 됨.// charname은 200자 이내인거 common.h에 정의 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0; //배열에 입력값을 넣음. 처음에는 아무것도 없으니까 0번째에 채워짐. 
static int smmObj_noFood=0;
static int smmObj_noFest=0;

//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //main에서 값 입력받는  genNode 함수 정의 
{
    strcpy(smmObj_name[smmObj_noNode], name); //배열에 입력값을 넣음. 문자열은 하나하나씩 복사해야됨. strcpy 쓰기 
    smmObj_type[smmObj_noNode] = type;
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;

    smmObj_noNode++;  
}
//Food generation function
void smmObj_genFood(char*name, int energy)
{
	strcpy(smmObj_name[smmObj_noFood],name);
	smmObj_energy[smmObj_noFood] = energy;
	
	smmObj_noFood++;
}
//Festival generatiom function
void smmObj_genFest(char*name)
{
	strcpy(smmObj_name[smmObj_noFest],name);
	
	smmObj_noFest++;
}



////Node function return
char* smmObj_getNodeName(int node_nr) //몇번째 노드의 이름을 받고싶냐 
{
    return smmObj_name[node_nr]; 
}
//함수의 반환값= type 값
int smmObj_getNodeType(int node_nr) //type 값이 여러개인데, 몇번째 값을 가져올거야? node number 로 매개변수 
{
    return smmObj_type[node_nr]; //입력받은 노드 넘버를 반환함 
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smmObj_energy[node_nr]; 
}

//Food function return
char* smmObj_getFoodName(int Food_nr) //몇번째 노드의 이름을 받고 싶냐 
{
    return smmObj_name[Food_nr]; 
}
int smmObj_getFoodEnergy(int Food_nr)
{
    return smmObj_energy[Food_nr]; 
}
// Fest function return
char* smmObj_getFestName(int Fest_nr) //몇번째 노드의 이름을 받고 싶냐 
{
    return smmObj_name[Fest_nr]; 
}

#if 0


//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

#endif
