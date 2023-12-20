//  
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop kim on 2023/11/05.
//

#ifndef smm_object_h
#define smm_object_h



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
void smmObj_genNode(char* name, int type, int credit, int energy);
void smmObj_genFood(char* name, int energy);
void smmObj_genFest(char*name);
//member retrieving //이거 두개 object.c에서 옴 main.c에서 호출받을 수 있게 여기에 선언 
char* smmObj_getNodeName(int node_nr);
int smmObj_getNodeType(int node_nr);
int smmObj_getNodeEnergy(int node_nr);
char* smmObj_getFestName(int Fest_nr);

//element to string



#endif /* smm_object_h */
