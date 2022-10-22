#define _USE_MATH_DEFINES
#include <cmath>
#include <string_view>
#include <iostream>
#include "common.h"
using namespace std;


namespace rem_math {
bool IsPointInRectangle(Point p, int width, int height) {
	return (p.x < width&& p.x >= 0 && p.y < height&& p.y >= 0);
}

Point RectAt0(Point p, int x, int y) {
	return { p.x - x, p.y - y };
}

float Rad(uint16_t rotation) {
	return rotation * M_PI / 180;
}

Point RotateBackTo0(Point p, int pivotX, int pivotY, uint16_t rotation) {
	int x = round((p.x - pivotX) * cos(-Rad(rotation)) - (-p.y + pivotY) * sin(-Rad(rotation)) + pivotX);
	int y = -round((p.x - pivotX) * sin(-Rad(rotation)) + (-p.y + pivotY) * cos(-Rad(rotation)) - pivotY);
	return { x, y };
}
}//namespace rem_math

namespace print {
void FormAction(string_view form_name, int form_id, ostream& out) {
	out << "Click "s << form_name << form_id << " is now active"s << endl;
}

void NothingHappened(Point p, ostream& out) {
	out << "Nothing happened at "s << p.x << " "s << p.y << endl;
}

void ElementAction(string_view form_name, int form_id, string_view element_name, int element_id, ostream& out) {
	out << "Click "s << form_name << form_id << "->"s << element_name << element_id << endl;
}

void EmptySpace(Point p, ostream& out) {
	out << "Nothing is there at "s << p.x << " "s << p.y << endl;
}

}