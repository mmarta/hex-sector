#include "vqueue.h"

u8 vQueueColor[V_QUEUE_LENGTH], vQueueTime[V_QUEUE_LENGTH], vQueueNextSpot = 0, vQueueFront = 0, vQueueSize = 0;

void vQueueDequeue();

void vQueueEnqueue(u8 vColor, u8 vTime) {
	if(vQueueSize == V_QUEUE_LENGTH) {
		return; //Can't enqueue, queue is full
	}

	vQueueColor[vQueueNextSpot] = vColor;
	vQueueTime[vQueueNextSpot] = vTime;

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
