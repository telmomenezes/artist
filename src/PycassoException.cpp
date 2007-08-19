/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "PycassoException.h"

namespace pyc
{

PycassoException::PycassoException()
{
	mCode = 0;
	mExtraText = "";
}

PycassoException::PycassoException(unsigned int code)
{
	mCode = code;
	mExtraText = "";
}

PycassoException::PycassoException(unsigned int code, std::string extraText)
{
	mCode = code;
	mExtraText = extraText;
}

PycassoException::~PycassoException()
{
}

}

