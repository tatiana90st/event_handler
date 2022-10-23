#include <string>
#include <string_view>
#include <iostream>
#include <optional>
#include <vector>
#include <cassert>
#include <random>
#include "elements.h"
#include "common.h"
#include "event_handler.h"
#include "log_duration.h"

using namespace std;

void TestClickForms() {
	Form::form_id_ = 1;
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
	assert(eh.GetFrontId() == forms.size() - 1 + forms[0]->GetId());
	for (int i = 9; i != -1; --i) {
		Point click = { x,y };
		eh.React(click);
		assert(forms[i]->IsActive());
		assert(eh.GetFrontId() == forms[i]->GetId());
		x -= 5;
		y -= 10;
	}
}

void TestFormsMult() {
	LOG_DURATION("10 forms 1000 clicks"s); //7ms
	Form::form_id_ = 1;
	EventHandler eh;
	const int W = 30;
	const int H = 40;
	int x_max = 100;
	int y_max = 60;
	mt19937 generator;
	for (int i = 0; i < 10; ++i) {//10
		int x = uniform_int_distribution(0, x_max)(generator);
		int y = uniform_int_distribution(0, y_max)(generator);
		eh.AddForm(x, y, W, H);
	}
	x_max += W;
	y_max += H;
	for (int i = 0; i != 1000; ++i) {
		int x = uniform_int_distribution(0, x_max)(generator);
		int y = uniform_int_distribution(0, y_max)(generator);
		Point click = { x,y };
		eh.React(click);
	}
}

void TestElementsOnForm() {
	Form::form_id_ = 1;
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
	Form::form_id_ = 1;
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

	Point click = { 90, 70 }; //nothing is there
	eh.React(click);
	assert(form4->IsActive());
	click = { 40, 5 }; //form4 is there, but it is active, so nothing happens
	eh.React(click);
	assert(form4->IsActive());
	click = { 55, 5 }; //form4 button0 is supposed to be there
	eh.React(click);
	click = { 50, 5 }; //form4 button0 is supposed to be there still
	eh.React(click);
	click = { 60, 15 }; //form 3 is active now
	eh.React(click);
	assert(form3->IsActive());
	click = { 60, 15 }; //form3 image0
	eh.React(click);
	click = { 45, 5 }; // form4 is inactive now, form 3 is already active, so nothing happens
	eh.React(click);
	assert(!form4->IsActive());
	assert(form3->IsActive());
	click = { 72, 12 }; //form3 button0
	eh.React(click);
	click = { 25, 10 }; //nothing is there
	eh.React(click);
	assert(form3->IsActive());
	click = { -10, -10 }; //nothing is there
	eh.React(click);
	assert(form3->IsActive());
	click = { 20, 20 }; //form 2 is active now
	eh.React(click);
	assert(!form3->IsActive());
	assert(form2->IsActive());
	click = { 20, 20 }; //form 2 edit0
	eh.React(click);
	click = { 35, 55 }; //not even close to form 2 button1, so nothing
	eh.React(click);
	assert(form2->IsActive());
	click = { 12, 15 }; //form 1
	eh.React(click);
	assert(!form2->IsActive());
	assert(form1->IsActive());
	click = { 12, 15 }; //form 1 image0 is invisible so nothing happens
	eh.React(click);
	assert(form1->IsActive());
	click = { 12, 8 }; // form1 button0
	eh.React(click);
	click = { 50, 10 }; // form3 is active
	eh.React(click);
	assert(!form1->IsActive());
	assert(form3->IsActive());
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
	TestFormsMult();
	TestElementsOnForm();
	TestRotation();
	SmallDemoEventHadler();
}

