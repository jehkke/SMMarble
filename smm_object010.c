
// object.h�� �Լ� ��� ��. 
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
#define MAX_NODE        100 // ������ ĭ(���) ������ � ���� �ȸ���. 100�� ������ ���ϱ�
#define MAX_FOOD        50
#define MAX_FEST        50 // �� ���� ���صα� 


static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "����",
       "�Ĵ�",
       "�����",
       "��",
       "����Ƿ��̵�",
       "��������",
       "�����ð�"
};
// �����̸�  �Է� �Լ� ���� 
char* smmObj_getTypeName(int type) // ���� ��  �Է��� main.c���� i���� ����� ������ ���� �Լ� 
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

//�̸�, ����, ����, ������ 
//1. ����ü ���� ���� (ĭ�� ���� ����ü�� ���Ǵ� ���⼭�� �ϰ� �����ָ� �ȵ�)
typedef struct smmObject {		// ����ü ���� name,type,credit,energy ���� ���, smmObject_t �������� 
       char name[MAX_CHARNAME];
       smmObjType_e objType; 
       int type;
       int credit;
       int energy;
       smmObjGrade_e grade;
} smmObject_t;  

typedef struct smmFood { // ����ü ���ǿ� name,energy ���� ���,smmFood_t �������� 
		char name[MAX_CHARNAME];
		int energy;
} smmFood_t;


typedef struct smmFest { // ����ü ���� name ���� ���, smmFest_t �������� 
       char name[MAX_CHARNAME];
} smmFest_t;  


//2. ����ü �迭 ���� ���� 
//static smmObject_t smm_node[MAX_NODE];
//static int smmObj_noNode = 0;
//smmFood_t smm_food[MAX_FOOD];
//static int smmObj_noFood=0;
//smmFest_t smm_fest[MAX_FEST];
//static int smmObj_noFest=0;




//3. ���� �Լ� �迭���� ����ü��  �°� ���� 
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



//3. ���� �Լ� ����: . �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� 
////Node function return
char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;

    return ptr->name; 
}
//�Լ��� ��ȯ��= type ��
int smmObj_getNodeType(void* obj) //type ���� �������ε�, ���° ���� �����ðž�? node number �� �Ű����� 
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
char* smmObj_getFoodName(void* food) //���° ����� �̸��� �ް� �ͳ� 
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
char* smmObj_getFestName(void* fest) //���° ����� �̸��� �ް� �ͳ� 
{
    smmFest_t* ptr = (smmFest_t*)fest;
    
    return ptr-> name;
  
}


