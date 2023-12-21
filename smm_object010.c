
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
       int type;
       int credit;
       int energy;
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

#if 0
//�������� ���� 
// smm_Obj -> smm_Obj�ȿ� �����ϴ� ����������. //����ü�� ���߿� �ٲ�.  
static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //���ڿ��� ��Ƽ�� �����ϰ� ������ 2�����迭�� �ϸ� ��.// charname�� 200�� �̳��ΰ� common.h�� ���� 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
#endif

static smmObject_t smmnode[MAX_NODE]; //smmObject_t ����ü smnode�迭 ���� 



//3. ���� �Լ� �迭���� ����ü��  �°� ���� 
//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //main���� �� �Է¹޴�  genNode �Լ� ���� 
{
	#if 0 
    strcpy(smmObj_name[smmObj_noNode], name); //�迭�� �Է°��� ����. ���ڿ��� �ϳ��ϳ��� �����ؾߵ�. strcpy ���� 
    smmObj_type[smmObj_noNode] = type; 
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;
	#endif
	// ���� main�Լ����� ĭ�� ���� ������ �����´����� ���� �����ϴ� ���� 
	// ���� ����ü���ٰ� ���� �ִ� ���� 
	strcpy(smm_node[smmObj_noNode].name, name); // �������� �迭�� ����ü �迭�� �ٲ�. 
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



//3. ���� �Լ� ����: . �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� 
////Node function return
char* smmObj_getNodeName(int node_nr) //���° ����� �̸��� �ް�ͳ� 
{
    return smm_node[node_nr].name; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}
//�Լ��� ��ȯ��= type ��
int smmObj_getNodeType(int node_nr) //type ���� �������ε�, ���° ���� �����ðž�? node number �� �Ű����� 
{
    return smm_node[node_nr].type; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}

int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}


//Food function return
char* smmObj_getFoodName(int food_nr) //���° ����� �̸��� �ް� �ͳ� 
{
    return smm_food[food_nr].name;
	 
}
int smmObj_getFoodEnergy(int food_nr)
{
    return smm_food[food_nr].energy; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}
// Fest function return
char* smmObj_getFestName(int fest_nr) //���° ����� �̸��� �ް� �ͳ� 
{
    return smm_fest[fest_nr].name; //. �����ڸ� �̿��Ͽ� ����ü ��� ������ ���� �� ��ȯ 
}


