#pragma once
#include <list>
#include "common.h"
#include "elements.h"

class EventHandler {
public:
	Form* AddForm(int x, int y, int width, int height);

	Form* DeleteForm();

	//for testing
	int GetFrontId();

	void React(const Point click);

private:
	//порядок отрисовки
	std::list<Form*> forms_;
};