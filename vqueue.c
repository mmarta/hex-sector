#include "vqueue.h"

u8 vQueueColor[V_QUEUE_LENGTH], vQueueTime[V_QUEUE_LENGTH], vQueueNextSpot = 0;

void vQueueDequeue();

void vQueueEnqueue(u8 vColor, u8 vTime) {
	if(vQueueNextSpot >= V_QUEUE_LENGTH) {
		return; //Can't enqueue, queue is full
	}

	vQueueColor[vQueueNextSpot] = vColor;
	vQueueTime[vQueueNextSpot] = vTime;
	vQueueNextSpot++;
}

void vQueueCycle() {
	u8 i = 0;
	while(i < vQueueNextSpot) {
		if(vQueueTime[i] == 0) {
			vQueueDequeue();
		} else {
			i++;
		}
	}
}

void vQueueDequeue() {
	u8 i = 0;
	virusInit(vQueueColor[0]);
	while(i < vQueueNextSpot - 1) {
		vQueueColor[i] = vQueueColor[i + 1];
		vQueueTime[i] = vQueueTime[i + 1];
		i++;
	}
	vQueueNextSpot--;
}
