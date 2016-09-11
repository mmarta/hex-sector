#include "vqueue.h"

u8 vQueueColor[V_QUEUE_LENGTH], vQueueTime[V_QUEUE_LENGTH], vQueueNextSpot = 0, vQueueFront = 0, vQueueSize = 0;
u8 virusLatestTime[LOCATION_COUNT], vQueueAngryRandom[V_QUEUE_LENGTH];

void vQueueDequeue();

void vQueueClear() {
    u8 i = LOCATION_COUNT;
    
    vQueueNextSpot = 0;
    vQueueFront = 0;
    vQueueSize = 0;
    
    while(i--) {
        virusLatestTime[i] = 0;
    }
}

void vQueueEnqueue(u8 vColor, u8 vTime, u8 angryRandom) {
    if(vQueueSize == V_QUEUE_LENGTH) {
        return; //Can't enqueue, queue is full
    }

    if(virusLatestTime[vColor] > 165) {
        return;
    } else if(virusLatestTime[vColor] + 90 > vTime) {
        vTime = virusLatestTime[vColor] + 90;
    }
    
    vQueueColor[vQueueNextSpot] = vColor;
    vQueueTime[vQueueNextSpot] = vTime;
    vQueueAngryRandom[vQueueNextSpot] = angryRandom;
    virusLatestTime[vColor] = vTime;

    vQueueNextSpot++;
    if(vQueueNextSpot >= V_QUEUE_LENGTH) {
        vQueueNextSpot = 0;
    }
    vQueueSize++;
}

void vQueueCycle() {
    u8 i = 0, next = vQueueFront;
    while(i < vQueueSize) {
        if(vQueueTime[next] == 0) {
            vQueueDequeue();
        } else {
            vQueueTime[next]--;
            virusLatestTime[vQueueColor[next]] = vQueueTime[next];
        }
        
        i++;
        next++;
        if(next >= V_QUEUE_LENGTH) {
            next = 0;
        }
    }
}

void vQueueDequeue() {
    u8 angryNum = rand();
    //u8 angryNum = 100;
    
    if(vQueueSize == 0) {
        return; //Can't dequeue, queue is empty
    }

    virusInit(vQueueColor[vQueueFront], (vQueueAngryRandom[vQueueFront] && angryNum < 32) ? 1 : 0);

    vQueueFront++;
    if(vQueueFront >= V_QUEUE_LENGTH) {
        vQueueFront = 0;
    }
    vQueueSize--;
}
