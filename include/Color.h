/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_COLOR_H)
#define __INCLUDE_PYCASSO_COLOR_H

namespace pyc
{

class Color
{
public:
	Color();
	Color(const Color &c);
	Color(unsigned int red, unsigned int green, unsigned int blue);
	Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);
	virtual ~Color();

	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;
};

}

#endif

