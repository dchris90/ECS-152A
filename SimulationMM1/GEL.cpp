#include "GEL.h"


GEL::GEL()
{
	start = nullptr;
}

GEL::~GEL()
{
	while (start != nullptr)
	{
		Event *temp = start;
		start = start->next;
		delete temp;
	}
}

void GEL::InsertEvent(Event *evt)
{
	if (start == nullptr)
	{
		start = evt;
	}

	else
	{
		Event *iter = start;
		bool inserted = false;

		while (true)
		{
			if (iter->event_time > evt->event_time)
			{
				// Insert event
				evt->next = iter;
				evt->prev = iter->prev;

				if (iter->prev != nullptr)
				{
					iter->prev->next = evt;
				}

				else
				{
					start = evt;
				}

				iter->prev = evt;
				inserted = true;
				break;
			}

			if (iter->next == nullptr)
			{
				break;
			}

			else
			{
				iter = iter->next;
			}
		}

		if (!inserted)
		{
			iter->next = evt;
			evt->prev = iter;
		}
	}
}

Event* GEL::GetHead()
{
	Event* head = start;
	start = start->next;

	if (start != nullptr)
	{
		start->prev = nullptr;
	}

	head->next = head->prev = nullptr;

	return head;
}

bool GEL::IsEmpty()
{
	return start == nullptr;
}
