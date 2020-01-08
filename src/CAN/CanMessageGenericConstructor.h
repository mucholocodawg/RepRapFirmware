/*
 * CanMessageGenericConstructor.h
 *
 *  Created on: 23 Jul 2019
 *      Author: David
 */

#ifndef SRC_CANMESSAGEGENERICCONSTRUCTOR_H_
#define SRC_CANMESSAGEGENERICCONSTRUCTOR_H_

#include "RepRapFirmware.h"

#if SUPPORT_CAN_EXPANSION

#include <CanMessageFormats.h>
#include <GCodes/GCodeResult.h>
#include <GCodes/GCodeException.h>

class GCodeBuffer;

class CanMessageGenericConstructor
{
public:
	CanMessageGenericConstructor(const ParamDescriptor *p_param) noexcept;

	// Populate from a GCode message. Throws if an error occurs.
	void PopulateFromCommand(GCodeBuffer& gb) THROWS_GCODE_EXCEPTION;

	// Methods to add parameters
	void AddU64Param(char c, uint64_t v) THROWS_GCODE_EXCEPTION;
	void AddUParam(char c, uint32_t v) THROWS_GCODE_EXCEPTION;
	void AddIParam(char c, int32_t v) THROWS_GCODE_EXCEPTION;
	void AddFParam(char c, float v) THROWS_GCODE_EXCEPTION;
	void AddCharParam(char c, char v) THROWS_GCODE_EXCEPTION;
	void AddStringParam(char c, const char* v) THROWS_GCODE_EXCEPTION;

	GCodeResult SendAndGetResponse(CanMessageType msgType, CanAddress dest, const StringRef& reply) noexcept;

private:
	// Append a value to the data, returning true if it wouldn't fit
	void StoreValue(const void *vp, size_t sz) THROWS_GCODE_EXCEPTION;

	// Append a value to the data, returning true if it wouldn't fit
	template<class T> void StoreValue(const T& val) THROWS_GCODE_EXCEPTION { StoreValue(&val, sizeof(T)); }

	// Insert a value in the data, returning true if it wouldn't fit
	void InsertValue(const void *vp, size_t sz, size_t pos) THROWS_GCODE_EXCEPTION;

	static GCodeException ConstructParseException(const char *msg) noexcept
	{
		return GCodeException(-1, -1, msg);
	}

	static GCodeException ConstructParseException(const char *msg, uint32_t param) noexcept
	{
		return GCodeException(-1, -1, msg, param);
	}

	const ParamDescriptor * const paramTable;
	size_t dataLen;
	CanMessageGeneric msg;
};

#endif

#endif /* SRC_CANMESSAGEGENERICCONSTRUCTOR_H_ */
