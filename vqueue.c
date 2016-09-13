#include "vqueue.h"

u8 vQueueColor[V_QUEUE_LENGTH], vQueueTime[V_QUEUE_LENGTH], vQueueNextSpot = 0, vQueueFront = 0, vQueueSize = 0;
u8 vQueueLatestLocationTime[LOCATION_COUNT], vQueueAngryRandom[V_QUEUE_LENGTH];

void vQueueDequeue();

void vQueueClear() {
    u8 i = LOCATION_COUNT;
    
    vQueueNextSpot = 0;
    vQueueFront = 0;
    vQueueSize = 0;
    
    while(i--) {
        vQueueLatestLocationTime[i] = 0;
    }
}

u8 vQueueEnqueue(u8 vColor, u8 vTime, u8 angryRandom) {
    if(vQueueSize == V_QUEUE_LENGTH) {
        return 0; //Can't enqueue, queue is full
    }

    if(vQueueLatestLocationTime[vColor] > 165) {
        return 0; //Queue too time-full for location.
    } else if(vQueueLatestLocationTime[vColor] + 90 > vTime) {
        vTime = vQueueLatestLocationTime[vColor] + 90;
    } else if(vQueueSize >= 1 && vQueueTime[vQueueNextSpot] <= vTime) {
        if(vQueueTime[vQueueNextSpot] >= 251) {
            return 0; //Queue too time-full.
        }
        vTime = vQueueTime[vQueueNextSpot] + 5;
    }
    
    vQueueColor[vQueueNextSpot] = vColor;
    vQueueTime[vQueueNextSpot] = vTime;
    vQueueAngryRandom[vQueueNextSpot] = angryRandom;
    vQueueLatestLocationTime[vColor] = vTime;

    vQueueNextSpot++;
    if(vQueueNextSpot >= V_QUEUE_LENGTH) {
        vQueueNextSpot = 0;
    }
    vQueueSize++;
    
    return 1;
}

void vQueueCycle() {
    u8 i = 0, next = vQueueFront;
    while(i < vQueueSize) {
        if(vQueueTime[next] == 0) {
            vQueueDequeue();
            return;
        } else {
            vQueueTime[next]--;
        }
        
        i++;
        next++;
        if(next >= V_QUEUE_LENGTH) {
            next = 0;
        }
    }
    
    i = LOCATION_COUNT;
    while(i--) {
        if(vQueueLatestLocationTime[i] > 0) {
            vQueueLatestLocationTime[i]--;
        }
    }
}

void vQueueDequeue() {
    u8 angryNum = rand();
    
    if(vQueueSize == 0) {
        return; //Can't dequeue, queue is empty
    }

    if(!virusInit(vQueueColor[vQueueFront], (vQueueAngryRandom[vQueueFront] && angryNum < 32) ? 1 : 0)) {
        return;
    }

    vQueueFront++;
    if(vQueueFront >= V_QUEUE_LENGTH) {
        vQueueFront = 0;
    }
    vQueueSize--;
}
