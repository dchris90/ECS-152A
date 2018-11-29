#pragma once

#include "Event.h"

class GEL
{
public:
	GEL();
	~GEL();

	Event *start;

	void InsertEvent(Event *evt);
	Event* GetHead();
	bool IsEmpty();
};
