#include "drawText.h"
#include <cstdio>

drawText::drawText(IDirect3DDevice9* device)
{
	_device = device;

	_font = new CD3DFont("Times New Roman", 48, 0);
	_font->InitDeviceObjects( _device );
	_font->RestoreDeviceObjects();

}

drawText::~drawText()
{
	if( _font )
	{
		_font->InvalidateDeviceObjects();
		_font->DeleteDeviceObjects();
		delete _font;
	}
}


bool drawText::renderBullet(D3DCOLOR color, int bullet)
{
	if( _font )
	{
		
		sprintf(_String, "Bullet : %d", bullet);
		_String[10] = '\0'; // mark end of string		

		
		_font->DrawText(100, 620, color, _String);	
		return true;
	}
	else return false;
}

bool drawText::renderKey(D3DCOLOR color, bool key)
{
	if( _font )
	{

		if(key == true)
		{
			sprintf(_String, "You have a Key");
			_String[20] = '\0'; // mark end of string		
		}
		else{
			sprintf(_String, "You don't have a Key");
			_String[20] = '\0'; // mark end of string	
		}


		_font->DrawText(100, 670, color, _String);	
		return true;
	}
	else return false;
}

bool drawText::renderLogo(D3DCOLOR color)
{
	if( _font )
	{
		sprintf(_String, "LOGO");
		_String[10] = '\0'; // mark end of string		
		
		_font->DrawText(400, 350, color, _String);	
		return true;
	}
	else return false;

}

bool drawText::renderMenu(D3DCOLOR color, int _count)
{
	if( _font )
	{
		sprintf(_String, "MENU");
		_String[10] = '\0'; // mark end of string		

		_font->DrawText(400, 150, color, _String);	
		
		if(_count == 0){
			sprintf(_String, "GAME");
			_String[10] = '\0'; // mark end of string		

			_font->DrawText(400, 450, color, _String);
		}
		if(_count == 1){
			sprintf(_String, "MENUAL");
			_String[10] = '\0'; // mark end of string		

			_font->DrawText(400, 450, color, _String);
		}
		if(_count == 2){
			sprintf(_String, "EXIT");
			_String[10] = '\0'; // mark end of string		

			_font->DrawText(400, 450, color, _String);
		}

		return true;
	}
	else return false;

}

bool drawText::renderMenual(D3DCOLOR color)
{
	if( _font )
	{
		sprintf(_String, "MENUAL");
		_String[10] = '\0'; // mark end of string		

		_font->DrawText(400, 350, color, _String);	
		return true;
	}
	else return false;
}

bool drawText::renderStory(D3DCOLOR color)
{
	if( _font )
	{
		sprintf(_String, "STORY");
		_String[10] = '\0'; // mark end of string		

		_font->DrawText(400, 350, color, _String);	
		return true;
	}
	else return false;

}

bool drawText::renderGameover(D3DCOLOR color)
{
	if( _font )
	{
		sprintf(_String, "GAME OVER");
		_String[10] = '\0'; // mark end of string		

		_font->DrawText(400, 350, color, _String);	
		return true;
	}
	else return false;

}

bool drawText::renderEnding(D3DCOLOR color)
{
	if( _font )
	{
		sprintf(_String, "ENDING");
		_String[10] = '\0'; // mark end of string		

		_font->DrawText(400, 350, color, _String);	
		return true;
	}
	else return false;

}