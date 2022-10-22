#include <string>
#include <string_view>
#include <iostream>
#include <optional>
#include <vector>
#include <cassert>
#include "elements.h"
#include "common.h"
#include "event_handler.h"

using namespace std;


void TestClickForms() {
	cout << "Test1"s << endl;
	EventHandler eh;
	const int W = 10;
	const int H = 20;
	int x = 0;
	int y = 0;
	vector<Form*> forms(10);
	for (int i = 0; i < 10; ++i) {
		forms[i] = eh.AddForm(x, y, W, H);
		x += 5;
		y += 10;
	}
	x = 46;
	y = 109;
	assert(forms[9]->IsActive());
	assert(eh.GetFrontId() == forms.size()- 1 + forms[0]->GetId());
	for (int i = 9; i != -1; --i) {
		Point click = { x,y };
		cout << x <<" "s<< y << endl;
		eh.React(click);
		assert(forms[i]->IsActive());
		assert(eh.GetFrontId() == forms[i]->GetId());
		x -= 5;
		y -= 10;
	}

}

void TestElementsOnForm() {
	EventHandler eh;
	const int W = 25;
	const int H = 50;
	int x = 0;
	int y = 0;
	Form* form1 = eh.AddForm(x, y, W, H);
	form1->AddButton(x, y, W, H, true, 0, 0, 0);
	form1->AddButton(x, y, W, H, true, 0, 0, 0);
	form1->AddImage(x, y, W, H, false, 0, 0, 0);
	assert(form1->IsActive());
	Point click = { W - 10,H - 10 };
	assert(form1->CheckInside(click) == true);
	assert(form1->GetTopElementType() == "Image"sv);
	optional<Element*> check_elements = form1->CheckInsideElements(click);
	assert(check_elements);
	assert(form1->GetTopElementType() == "Image"sv);
	assert(check_elements.value()->GetName() == "Button"sv);
	assert(check_elements.value()->GetId() == 1);
}


void SmallDemoEventHadler() {
	cout << "Demonstration"s << endl;
	EventHandler eh;
	Form* form1 = eh.AddForm(0, 0, 20, 20);
	form1->AddButton(5, 5, 10, 5, true, 0, 0, 0);
	form1->AddImage(10, 2, 10, 15, false, 0, 0, 0);
	Form* form2 = eh.AddForm(15, 15, 40, 50);
	form2->AddEdit(15, 15, 10, 10, true, 0, 0, 0);
	form2->AddButton(25, 55, 14, 14, true, 45, 0, 0);
	Form* form3 = eh.AddForm(30, 0, 60, 20);
	form3->AddImage(50, 15, 15, 10, true, 0, 0, 0);
	form3->AddButton(70, 12, 12, 4, true, 30, 72, 15);
	Form* form4 = eh.AddForm(40, 0, 20, 10);
	form4->AddButton(50, 5, 20, 20, true, 10, 50, 50);
	form4->AddButton(50, 5, 20, 20, false, 10, 50, 50);

	//could've created vector<Point> = {{..., ...}, ....}; right away, but doing this instead just for comments
	Point click1 = { 90, 70 }; //nothing is there
	Point click2 = { 40, 5 }; //form4 is there, but it is active, so nothing happens
	Point click20 = { 55, 5 }; //form4 button0 is supposed to be there
	Point click21 = { 50, 5 }; //form4 button0 is supposed to be there still
	Point click3 = { 60, 15 }; //form 3 is active now
	Point click4 = { 60, 15 }; //form3 image0
	Point click5 = { 45, 5 }; // form4 is inactive now, form 3 is already active, so nothing happens
	Point click50 = { 72, 12 }; //form4 button0
	Point click6 = { 25, 10 }; //nothing is there
	Point click7 = { -10, -10 }; //nothing is there
	Point click8 = { 20, 20 }; //form 2 is active now
	Point click9 = { 20, 20 }; //form 2 edit0
	Point click10 = { 35, 55 }; //not even close to form 2 button1, so nothing
	Point click11 = { 12, 15 }; //form 1
	Point click12 = { 12, 15 }; //form 1 image0 is invisible so nothing happens
	Point click13 = { 12, 8 }; // form1 button0
	Point click14 = { 50, 10 }; // form3 is active

	vector<Point> vec = { click1, click2, click20, click21, click3, click4, click5, click50, click6, click7, click8, click9, click10,
	click11, click12, click13, click14 };
	for (const Point p : vec) {
		eh.React(p);
	}
}

void TestRotation() {

	Point corn = { 50, 5 };
	int pivotX = 50;
	int pivotY = 50;
	uint16_t rotation = 10;
	Point p = rem_math::RotateBackTo0(corn, pivotX, pivotY, rotation);
	assert(p.x == 58 && p.y == 6);

}

int main() {
	TestClickForms();
	TestElementsOnForm();
	TestRotation();
	SmallDemoEventHadler();
}

