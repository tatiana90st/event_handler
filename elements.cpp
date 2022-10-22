#include <string>
#include <string_view>
#include <iostream>
#include <list>
#include <optional>
#include "elements.h"
#include "common.h"

using namespace std;

Element::Element(int x, int y, int width, int height, int id,
	bool visibility, uint16_t rotation, int pivotX, int pivotY)
	: x_(x), y_(y), width_(width), height_(height), id_(id)
	, visibility_(visibility), rotation_(rotation), pivotX_(pivotX), pivotY_(pivotY) {

}

int Element::GetId() const {
	return id_;
}

bool Element::CheckInside(const Point click) const {
	if (!IsVisible()) {
		return false;
	}
	if (rotation_ == 0 || rotation_ == 360) {
		Point d_click = rem_math::RectAt0(click, x_, y_);
		return rem_math::IsPointInRectangle(d_click, width_, height_);
	}
	else {
		Point modified = rem_math::RotateBackTo0(click, pivotX_, pivotY_, rotation_);
		modified = rem_math::RectAt0(modified, x_, y_);
		return rem_math::IsPointInRectangle(modified, width_, height_);
	}
}

bool Element::IsVisible() const {
	return visibility_;
}


Form::Form(int x, int y, int width, int height)
	: Element(x, y, width, height, form_id_)
	, is_active_(true) {
	++form_id_;
}

string_view Form::GetName() const {
	return "Form"sv;
}

void Form::OnClick() {
	if (!is_active_) {
		MakeActive();
		print::FormAction(GetName(), GetId(), cerr);
	}
}

//можно добавить проверку за выход за границы формы
void  Form::AddButton(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY) {
	Button* button = new Button(x, y, width, height, buttons_count_, visibility, rotation, pivotX, pivotY, *this);
	elements_on_form_.push_front(button);
	++buttons_count_;
}

void  Form::AddImage(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY) {
	Image* image = new Image(x, y, width, height, images_count_, visibility, rotation, pivotX, pivotY, *this);
	elements_on_form_.push_front(image);
	++images_count_;
}

void  Form::AddEdit(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY) {
	Edit* edit = new Edit(x, y, width, height, images_count_, visibility, rotation, pivotX, pivotY, *this);
	elements_on_form_.push_front(edit);
	++edits_count_;
}

void  Form::MakeUnactive() {
	is_active_ = false;
}
void  Form::MakeActive() {
	is_active_ = true;
}

bool  Form::IsActive() {
	return is_active_;
}

optional<Element*>  Form::CheckInsideElements(const Point click) {
	//обратный порядок проверки!!!
	for (Element* element : elements_on_form_) {
		if (element->CheckInside(click)) {
			return element;
		}
	}
	return nullopt;
}

string_view Form::GetTopElementType() {
	return elements_on_form_.front()->GetName();
}

int Form::form_id_ = 1;

Button::Button(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
	const Form& form)
	: Element(x, y, width, height, id, visibility, rotation, pivotX, pivotY)
	, belongs_to_(form) {
}

string_view Button::GetName() const {
	return "Button"sv;
}

void Button::OnClick() {
	print::ElementAction(belongs_to_.GetName(), belongs_to_.GetId(), GetName(), GetId(), cout);
}


Image::Image(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
	const Form& form)
	: Element(x, y, width, height, id, visibility, rotation, pivotX, pivotY)
	, belongs_to_(form) {
}

string_view Image::GetName() const {
	return "Image"sv;
}

void Image::OnClick() {
	print::ElementAction(belongs_to_.GetName(), belongs_to_.GetId(), GetName(), GetId(), cout);
}


Edit::Edit(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
	const Form& form)
	: Element(x, y, width, height, id, visibility, rotation, pivotX, pivotY)
	, belongs_to_(form) {
}

string_view Edit::GetName() const {
	return "Edit"sv;
}

void Edit::OnClick() {
	print::ElementAction(belongs_to_.GetName(), belongs_to_.GetId(), GetName(), GetId(), cout);
}

