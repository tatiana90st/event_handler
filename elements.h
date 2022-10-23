#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <list>
#include <optional>
#include "common.h"

using namespace std;

class Element {
public:
	Element(int x, int y, int width, int height, int id,
		bool visibility = true, uint16_t rotation = 0, int pivotX = 0, int pivotY = 0);

	virtual void OnClick() = 0;

	virtual string_view GetName() const = 0;

	int GetId() const;

	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;

	bool CheckInside(const Point click) const;

	bool IsVisible() const;

private:
	int x_;
	int y_;
	int width_;
	int height_;
	int id_;
	bool visibility_ = true;
	uint16_t rotation_ = 0;
	int pivotX_ = 0;
	int pivotY_ = 0;
};

class Form : public Element {
public:
	Form(int x, int y, int width, int height);

	string_view GetName() const override;

	void OnClick() override;

	//можно добавить проверку за выход за границы формы
	void AddButton(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY);

	void AddImage(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY);

	void AddEdit(int x, int y, int width, int height, bool visibility, uint16_t rotation, int pivotX, int pivotY);

	void MakeUnactive();
	void MakeActive();
	bool IsActive();

	optional<Element*> CheckInsideElements(const Point click);
	string_view GetTopElementType();

	static int form_id_;
private:
	bool is_active_;
	//list для порядка отрисовки
	list<Element*> elements_on_form_;

	int buttons_count_ = 0;
	int images_count_ = 0;
	int edits_count_ = 0;
};

class Button : public Element {
public:
	Button(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
		const Form& form);

	string_view GetName() const override;

	void OnClick() override;

private:
	const Form& belongs_to_;
};


class Image : public Element {
public:
	Image(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
		const Form& form);

	string_view GetName() const override;

	void OnClick() override;
private:
	const Form& belongs_to_;
};

class Edit : public Element {
public:
	Edit(int x, int y, int width, int height, int id, bool visibility, uint16_t rotation, int pivotX, int pivotY,
		const Form& form);

	string_view GetName() const override;

	void OnClick() override;

private:
	const Form& belongs_to_;
};
