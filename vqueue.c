#include "vqueue.h"

u8 vQueueColor[V_QUEUE_LENGTH], vQueueTime[V_QUEUE_LENGTH], vQueueNextSpot = 0, vQueueFront = 0, vQueueSize = 0;
u8 virusLatestTime[LOCATION_COUNT];

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

void vQueueEnqueue(u8 vColor, u8 vTime) {
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
	if(vQueueSize == 0) {
		return; //Can't dequeue, queue is empty
	}

	virusInit(vQueueColor[vQueueFront]);

	vQueueFront++;
	if(vQueueFront >= V_QUEUE_LENGTH) {
		vQueueFront = 0;
	}
	vQueueSize--;
}
