
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
       smmObjType_e objType; 
       int type;
       int credit;
       int energy;
       smmObjGrade_e grade;
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




//3. 관련 함수 배열에서 구조체로  맞게 변경 
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType,
 int type, int credit, int energy, smmObjGrade_e grade)
{
	smmObject_t* ptr;
	ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
	
	strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return ptr;
  
}




//Food generation function
void* smmObj_genFood(char*name, int energy)
{
	smmFood_t*ptr;
	ptr = (smmFood_t*)malloc(sizeof(smmFood_t));
	
	strcpy(ptr->name, name);
    ptr->energy = energy;

    return ptr;
	
}

//Festival generatiom function
void* smmObj_genFest(char*name)
{
	smmFest_t*ptr;
	ptr = (smmFest_t*)malloc(sizeof(smmFest_t));
	
	strcpy(ptr->name, name);
	
	return ptr;
	
}



//3. 관련 함수 변경: . 연산자를 이용하여 구조체 멤버 변수로 변경 
////Node function return
char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;

    return ptr->name; 
}
//함수의 반환값= type 값
int smmObj_getNodeType(void* obj) //type 값이 여러개인데, 몇번째 값을 가져올거야? node number 로 매개변수 
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr-> type;
}

int smmObj_getNodeEnergy(void* obj)
{
     smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr-> energy;
}

int smmObj_getNodeCredit(void* obj)
{
     smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr-> credit;
}


//Food function return
char* smmObj_getFoodName(void* food) //몇번째 노드의 이름을 받고 싶냐 
{	
	smmFood_t* ptr = (smmFood_t*)food;
    
    return ptr-> name;
   
	 
}
int smmObj_getFoodEnergy(void* food)
{
    smmFood_t* ptr = (smmFood_t*)food;
    
    return ptr-> energy;
  
}
// Fest function return
char* smmObj_getFestName(void* fest) //몇번째 노드의 이름을 받고 싶냐 
{
    smmFest_t* ptr = (smmFest_t*)fest;
    
    return ptr-> name;
  
}


