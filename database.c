#include "database.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

IndexNodeString * createNodeString (char * root_value, Persona * persona){
    IndexNodeString * root = malloc (sizeof(IndexNodeString));
    root->value = root_value;
    root->person= persona;
    root->left = NULL;
    root ->right = NULL;
    return (root);
}

IndexNodeInt * createNodeInt (int root_value, Persona * persona){
    IndexNodeInt * root = malloc (sizeof(IndexNodeInt));
    root->value = root_value;
    root->person = persona;
    root->left = NULL;
    root ->right = NULL;
    return (root);
}

void insertString (IndexNodeString * database,  char * string, Persona * persona){
    if(strcmp(database->value,string)>= 0){
        if(database->left == NULL){
            IndexNodeString * Node = createNodeString(string, persona);
            database->left = Node;
            return;
        }
        insertString(database->left, string, persona);
        return;
    }
    if((database->right) == NULL){
        IndexNodeString * Node = createNodeString(string, persona);
        database->right = Node;
        return;
    }
    insertString((database->right), string, persona);
    return;
}



void insertInt (IndexNodeInt * database, int age, Persona * persona){
    if((database->value)>= age){
        if((database->left) == NULL){
            IndexNodeInt * a = createNodeInt(age, persona);
            database->left = a;
            return;
        }
        insertInt((database->left), age, persona);
        return;
    }
    if((database->right) == NULL){
        IndexNodeInt * a = createNodeInt(age, persona);
        database->right = a;
        return;
    }
    insertInt((database->right), age, persona);
    return;
}

void create (Database * database, Persona * persona){
    database->name = createNodeString (persona->name, persona);
    database->surname = createNodeString (persona->surname, persona);
    database->address = createNodeString (persona->address, persona);
    database ->age =createNodeInt (persona->age, persona);
}

void insert(Database * database, Persona * persona){

    if(database == NULL || persona == NULL)return;

    Persona * p = malloc (sizeof(Persona));
    strcpy (p->address, persona->address);
    strcpy (p->name, persona->name);
    strcpy (p->surname, persona->surname);
    p->age = persona->age;

    if (database->name  == NULL){
        create(database, p);
        return;
    }
    else insertString(database->name, p->name, p);

    insertInt(database->age, p->age, p);
    
    insertString (database->surname, p->surname, p);
    insertString (database->address, p->address, p);
}

Persona* findByStringRicorsivo(IndexNodeString * database, char * str){
    if(database == NULL)return 0;
    if(strcmp (database->value, str) == 0) return (database->person);
    if(strcmp (database->value, str) > 0) findByStringRicorsivo(database->left, str);
    else findByStringRicorsivo(database->right, str);
}

Persona* findByName(Database * database, char * name){
    return findByStringRicorsivo (database->name, name);
}

Persona* findBySurname(Database * database, char * surname){
    return findByStringRicorsivo (database->surname, surname);
}

Persona* findByAddress(Database * database, char * address){
    return findByStringRicorsivo (database->address, address);
}

Persona * findByAgeR(IndexNodeInt * database, int age){
    if(database == NULL)return 0;
    if(database->value == age) return (database->person);
    if(database->value > age) findByAgeR(database->left, age);
    else findByAgeR(database->right, age);
}

Persona* findByAge(Database * database, int age){
    return findByAgeR (database->age, age);
}

void freeNodesString(IndexNodeString * node){
    if(node == NULL) return;
    freeNodesString (node->left);
    freeNodesString (node->right);
    free(node);
}

void freeNodesInt(IndexNodeInt * node){
    if(node == NULL) return;
    freeNodesInt(node->left);
    freeNodesInt (node->right);
    free(node->person);
    free(node);
}

void freeDatabase(Database* database){
    freeNodesString(database->name);
    freeNodesString(database->surname);
    freeNodesString(database->address);
    freeNodesInt (database->age);
    free (database);
}