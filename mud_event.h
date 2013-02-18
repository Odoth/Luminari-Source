/**
* @file mud_event.h
* Mud_Event Header file.
* 
* Part of the core tbaMUD source code distribution, which is a derivative
* of, and continuation of, CircleMUD.
* 
* This source code, which was not part of the CircleMUD legacy code,
* is attributed to:
* Copyright 2012 by Joseph Arnusch.                                                    
*/

#ifndef _MUD_EVENT_H_
#define _MUD_EVENT_H_

#include "dg_event.h"

#define EVENT_WORLD 0
#define EVENT_DESC  1
#define EVENT_CHAR  2

#define NEW_EVENT(event_id, struct, var, time) (attach_mud_event(new_mud_event(event_id, struct,  var), time))

typedef enum {
    eNULL,
    ePROTOCOLS,		/* The Protocol Detection Event */
    eWHIRLWIND,		/* The Whirlwind Attack */
    eCASTING,		     //  casting time 
    eLAYONHANDS,	     //  lay on hands
    eTREATINJURY,	     //  treat injury
    eTAUNT,		     //  taunt
    eTAUNTED,		     //  taunted
    eMUMMYDUST,	     //  mummy dust
    eDRAGONKNIGHT,	     //  dragon knight
    eGREATERRUIN,	     //  greater ruin
    eHELLBALL,		     //  hellball
    eEPICMAGEARMOR,	     //  epic mage armor
    eEPICWARDING,	     //  epic warding
    eMEMORIZING,	     //  memorization
    eSTUNNED,	          //  stunning fist stun
    eSTUNNINGFIST,	     //  stunner's cooldown for stunning fist
    eCRAFTING,           //  crafting event
    eCRYSTALFIST,        //  crystal fist cooldown
    eCRYSTALBODY,        //  crystal body cooldown
    eRAGE,               //  rage skill cooldown
    eACIDARROW,          //  acid arrow damage event
    eD_ROLL,             //  rogue's defensive roll cooldown
    ePURIFY,             //  paladin's disease removal skill cooldown
    eC_ANIMAL,           //  animal companion cooldown
    eC_FAMILIAR,         //  familiar cooldown
    eC_MOUNT,            //  paladin's called mount cooldown
    eIMPLODE,          //  implode damage event
} event_id;
/* probaly a smart place to mention to not forget to update:
   act.informative.c
   players.c (if you want it to save)
 */

struct mud_event_list {
  const char * event_name;
  EVENTFUNC(*func);
  int iEvent_Type;
};

struct mud_event_data {
  struct  event * pEvent;      /***< Pointer reference to the event */
  event_id        iId;         /***< General ID reference */  
  void          * pStruct;     /***< Pointer to NULL, Descriptor, Character .... */
  char          * sVariables;	 /***< String variable */
}; 

/* Externals */
extern struct list_data * world_events;
extern struct mud_event_list mud_event_index[];

/* Local Functions */
void init_events(void);
struct mud_event_data *new_mud_event(event_id iId, void *pStruct, char *sVariables);
void attach_mud_event(struct mud_event_data *pMudEvent, long time);
void free_mud_event(struct mud_event_data *pMudEvent);
struct mud_event_data * char_has_mud_event(struct char_data * ch, event_id iId);
void clear_char_event_list(struct char_data * ch);
void change_event_duration(struct char_data * ch, event_id iId, long time);

/* Events */
EVENTFUNC(event_countdown);
EVENTFUNC(get_protocols);
EVENTFUNC(event_whirlwind);
EVENTFUNC(event_casting);
EVENTFUNC(event_memorizing);
EVENTFUNC(event_crafting);
EVENTFUNC(event_acid_arrow);
EVENTFUNC(event_implode);
#endif /* _MUD_EVENT_H_ */
