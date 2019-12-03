/*
 * (C) 2019 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

// Font creation flags
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define D3DFONT_CENTERED_X  0x0001
#define D3DFONT_CENTERED_Y  0x0002
#define D3DFONT_FILTERED    0x0008

class CD3D9Font
{
	// Font properties
	WCHAR m_strFontName[80];
	DWORD m_dwFontHeight;
	DWORD m_dwFontFlags;

	LPDIRECT3DDEVICE9       m_pd3dDevice; // A D3DDevice used for rendering
	LPDIRECT3DTEXTURE9      m_pTexture;   // The d3d texture for this font
	LPDIRECT3DVERTEXBUFFER9 m_pVB;        // VertexBuffer for rendering text
	DWORD m_dwTexWidth;                   // Texture dimensions
	DWORD m_dwTexHeight;
	FLOAT m_fTextScale;
	WCHAR m_Characters[128];
	FLOAT m_fTexCoords[128][4];
	DWORD m_dwSpacing;                    // Character pixel spacing per side

	// Stateblocks for setting and restoring render states
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockSaved;
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText;

public:
	// 2D text drawing function
	HRESULT Draw2DText( FLOAT sx, FLOAT sy, D3DCOLOR color,
					  const WCHAR* strText, DWORD dwFlags=0L );

	// Function to get extent of text
	HRESULT GetTextExtent( const WCHAR* strText, SIZE* pSize );

	// Initializing and destroying device-dependent objects
	HRESULT InitDeviceObjects(LPDIRECT3DDEVICE9 pd3dDevice);
	HRESULT RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();

	// Constructor / destructor
	CD3D9Font( const WCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
	~CD3D9Font();
};
