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
#define MAX_NODE        100 // ������ ĭ(���) ������ � ���� �ȸ���. 100�� ������ ���ϱ�



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


//�������� ���� 
// smm_Obj -> smm_Obj�ȿ� �����ϴ� ����������. //����ü�� ���߿� �ٲ�.  
static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //���ڿ��� ��Ƽ�� �����ϰ� ������ 2�����迭�� �ϸ� ��.// charname�� 200�� �̳��ΰ� common.h�� ���� 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0; //�迭�� �Է°��� ����. ó������ �ƹ��͵� �����ϱ� 0��°�� ä����. 
static int smmObj_noFood=0;
static int smmObj_noFest=0;

//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //main���� �� �Է¹޴�  genNode �Լ� ���� 
{
    strcpy(smmObj_name[smmObj_noNode], name); //�迭�� �Է°��� ����. ���ڿ��� �ϳ��ϳ��� �����ؾߵ�. strcpy ���� 
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
char* smmObj_getNodeName(int node_nr) //���° ����� �̸��� �ް�ͳ� 
{
    return smmObj_name[node_nr]; 
}
//�Լ��� ��ȯ��= type ��
int smmObj_getNodeType(int node_nr) //type ���� �������ε�, ���° ���� �����ðž�? node number �� �Ű����� 
{
    return smmObj_type[node_nr]; //�Է¹��� ��� �ѹ��� ��ȯ�� 
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smmObj_energy[node_nr]; 
}

//Food function return
char* smmObj_getFoodName(int Food_nr) //���° ����� �̸��� �ް� �ͳ� 
{
    return smmObj_name[Food_nr]; 
}
int smmObj_getFoodEnergy(int Food_nr)
{
    return smmObj_energy[Food_nr]; 
}
// Fest function return
char* smmObj_getFestName(int Fest_nr) //���° ����� �̸��� �ް� �ͳ� 
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
