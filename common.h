#pragma once
#include <stdint.h>
#include <string_view>
#include <iostream>

using namespace std;

struct Point {
	int x;
	int y;
};

namespace rem_math {
bool IsPointInRectangle(Point p, int width, int height);

Point RectAt0(Point p, int x, int y);

float Rad(uint16_t rotation);

Point RotateBackTo0(Point p, int pivotX, int pivotY, uint16_t rotation);
}//namespace rem_math
namespace print {
void FormAction(string_view form_name, int form_id, ostream& out);

void NothingHappened(Point p, ostream& out);

void ElementAction(string_view form_name, int form_id, string_view element_name, int element_id, ostream& out);

void EmptySpace(Point p, ostream& out);
}