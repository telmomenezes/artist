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
	mCode = EXCEPTION_UNDEFINED;
	mExtraText = "";
}

PycassoException::PycassoException(const PycassoException& exception)
{
	mCode = exception.mCode;
	mExtraText = exception.mExtraText;
}

PycassoException::PycassoException(ExceptionCode code)
{
	mCode = code;
	mExtraText = "";
}

PycassoException::PycassoException(ExceptionCode code, std::string extraText)
{
	mCode = code;
	mExtraText = extraText;
}

PycassoException::~PycassoException()
{
}

std::string PycassoException::getText()
{
	std::string text = "Pycasso " + getCodeText() + " : " + mExtraText;
	return text;
}

std::string PycassoException::getCodeText()
{
	switch (mCode)
	{
	case EXCEPTION_INITIALIZATION:
		return "Initialization Exception";
	case EXCEPTION_MISSING_OBJECT:
		return "Missing Object Exception";
	case EXCEPTION_OBJECT_EXISTS:
		return "Object Exists Exception";
	case EXCEPTION_MEMORY:
		return "Memory Exception";
	case EXCEPTION_FILE:
		return "File Exception";
	default:
		return "Undefined Exception";
	}
}

}

