/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_EXCEPTION_H)
#define __INCLUDE_PYCASSO_EXCEPTION_H

#include <string>

namespace pyc
{

class PycassoException
{
public:
	PycassoException();
	PycassoException(unsigned int code);
	PycassoException(unsigned int code, std::string extraText);
	virtual ~PycassoException();

protected:
	unsigned int mCode;
	std::string mExtraText;
};

}

#endif

