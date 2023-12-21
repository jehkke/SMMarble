//  
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop kim on 2023/11/05.
//

#ifndef smm_object_h
#define smm_object_h
// Type의 이름을 2차원 배열에 저장(문자열 배열) 
#define SMMNODE_TYPE_LECTURE            0
#define SMMNODE_TYPE_RESTAURANT         1
#define SMMNODE_TYPE_LABORATORY         2
#define SMMNODE_TYPE_HOME               3
#define SMMNODE_TYPE_GOTOLAB            4
#define SMMNODE_TYPE_FOODCHANCE         5
#define SMMNODE_TYPE_FESTIVAL           6

#define SMMNODE_TYPE_MAX                7

typedef enum smmObjType {
    smmObjType_board = 0,
    smmObjType_card,
    smmObjType_grade
} smmObjType_e;


/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/



//object generation
void smmObj_genObject(char* name, 
smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade);

void smmObj_genFood(char* name, int energy);
void smmObj_genFest(char*name);

//member retrieving //이거 두개 object.c에서 옴 main.c에서 호출받을 수 있게 여기에 함수헤더  선언 
char* smmObj_getNodeName(int node_nr);
int smmObj_getNodeType(int node_nr);
int smmObj_getNodeEnergy(int node_nr);
int smmObj_getNodeCredit(int node_nr);

char* smmObj_getFoodName(int Food_nr);
char* smmObj_getFestName(int Fest_nr);

//element to string
char* smmObj_getTypeName(int type); // getName 함수 선언 


#endif /* smm_object_h */
