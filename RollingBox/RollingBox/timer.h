#ifndef __timerH__
#define __timerH__

#include "d3dfont.h"

class TimerCounter
{
public:
	TimerCounter(IDirect3DDevice9* device);
	~TimerCounter();

	float render(D3DCOLOR color, float timeDelta);
	void plusTime(float time);

private:
	IDirect3DDevice9* _device;
	
	CD3DFont* _font;
	float     _timer;
	char      _timerString[9];
	
};
#endif