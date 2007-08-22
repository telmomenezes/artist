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

#include "pyc_types.h"
#include <string>

namespace pyc
{

class PycassoException
{
public:
	PycassoException();
	PycassoException(const PycassoException& exception);
	PycassoException(ExceptionCode code);
	PycassoException(ExceptionCode code, std::string extraText);
	virtual ~PycassoException();

	ExceptionCode getCode(){return mCode;}
	std::string getText();

protected:
	std::string getCodeText();

	ExceptionCode mCode;
	std::string mExtraText;
};

}

#endif

