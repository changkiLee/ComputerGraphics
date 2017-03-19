#include "timer.h"
#include <cstdio>

TimerCounter::TimerCounter(IDirect3DDevice9* device)
{
	_device = device;

	_font = new CD3DFont("Times New Roman", 48, 0);
	_font->InitDeviceObjects( _device );
	_font->RestoreDeviceObjects();

	// 초기시간
	_timer         = 10.0f;
}

TimerCounter::~TimerCounter()
{
	if( _font )
	{
		_font->InvalidateDeviceObjects();
		_font->DeleteDeviceObjects();
		delete _font;
	}
}

void TimerCounter::plusTime(float time)
{
	_timer += time;
}


float TimerCounter::render(D3DCOLOR color, float timeDelta)
{
	if( _font )
	{
		_timer -= timeDelta;

		sprintf(_timerString, "%f", _timer);
		_timerString[4] = '\0'; // mark end of string		

		_font->DrawText(460, 100, color, _timerString);	
		return _timer;
	}
	else return -1;
}