#ifndef ANAGRAFE_H
    #define ANAGRAFE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #define ANAGRAFE_PERSONE_CAP 100

    typedef struct {
        char* nome;
        char* cognome;
        char* padre;
        char* madre;
    } persona;
    
    typedef struct{
        persona persone[ANAGRAFE_PERSONE_CAP];
        int count;
    } anagrafe;
    
    // funzioni di gestione anagrafe:
    persona* crea_persona(char* nome, char* cognome, char* padre, char* madre){
        persona* result = (persona*) malloc(sizeof(persona));
        
        if(result == NULL){
            return NULL;
        }
        
        result->nome = nome;
        result->cognome = cognome;
        result->padre = padre;
        result->madre = madre;
        
        return result;
    }
    
    anagrafe* crea_anagrafe(int size){
        anagrafe* result = (anagrafe*) malloc(sizeof(anagrafe)*size);
        
        if(result == NULL){
            return NULL;
        }
        
        result->count=0;
        
        return result;
    }
    
    void aggiungi_persona(anagrafe* anagrafe, persona* persona){
        if(anagrafe == NULL || persona == NULL){
            return;
        }
        anagrafe->persone[anagrafe->count] = *persona;
        anagrafe->count=anagrafe->count+1;
    }
    
    bool cerca_persona(anagrafe* anagrafe, char* nome){
        bool found = false;
        int i=0;
        for(; i<anagrafe->count && strcmp(anagrafe->persone[i].nome, nome) != 0; i++){}
        
        found = i < anagrafe->count;
        
        return found;
    }
    
    char* get_madre(persona* persona){
        if(persona == NULL){
            return NULL;
        }
        
        return persona->madre;
    }
    
    char* get_padre(persona* persona){
        if(persona == NULL){
            return NULL;
        }
        
        return persona->padre;
    }
    
    char* get_parente(persona* persona, anagrafe* anagrafe){
        if(persona == NULL || anagrafe == NULL){
            return NULL;
        }

        bool found = false;
        int i=0;
        for(; i<anagrafe->count && strcmp(anagrafe->persone[i].padre, persona->padre) || strcmp(anagrafe->persone[i].madre, persona->madre) != 0; i++){}

        found = i < anagrafe->count;

        if(!found){
            return NULL;
        }
        
        return anagrafe->persone[i].nome;
    }
#endif
