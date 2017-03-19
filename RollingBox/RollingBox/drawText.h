#ifndef __drawTextH__
#define __drawTexttH__

#include "d3dfont.h"

class drawText
{
public:
	drawText(IDirect3DDevice9* device);
	~drawText();

	bool renderBullet(D3DCOLOR color, int bullet);
	bool renderKey(D3DCOLOR color, bool key);
	
	// юс╫ц
	bool renderLogo(D3DCOLOR color);
	bool renderMenu(D3DCOLOR color, int _count);
	bool renderMenual(D3DCOLOR color);
	bool renderStory(D3DCOLOR color);
	bool renderGameover(D3DCOLOR color);
	bool renderEnding(D3DCOLOR color);

private:
	IDirect3DDevice9* _device;

	CD3DFont* _font;
	float     _drawText;
	char      _String[20];

};
#endif