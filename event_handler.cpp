#include <cassert>
#include "common.h"
#include "elements.h"
#include "event_handler.h"


Form* EventHandler::AddForm(int x, int y, int width, int height) {
	Form* form = new Form(x, y, width, height);
	if (!forms_.empty()) {
		forms_.front()->MakeUnactive();
	}
	forms_.push_front(form);	
	return form;
}

Form* EventHandler::DeleteForm() {
	assert(!forms_.empty());
	
	forms_.pop_front();
	if (!forms_.empty()) {
		forms_.front()->MakeActive();
	}
	return forms_.front();
}

int EventHandler::GetFrontId() {
	return forms_.front()->GetId();
}

void EventHandler::React(const Point click) {
	for (auto it = forms_.begin(); it != forms_.end();) {
		if ((*it)->CheckInside(click)) {
			if ((*it)->IsActive()) {
				optional<Element*> check_elements = (*it)->CheckInsideElements(click);
				if (check_elements) {
					check_elements.value()->OnClick();
				}
				else {
					//demo purposes
					//print::NothingHappened(click, cerr);
				}
			}
			else {
				(*it)->OnClick(); 
				forms_.front()->MakeUnactive();
				forms_.push_front(*it);
				it = forms_.erase(it);
			}
			break;
		}
		++it;
		/*
		if (it == forms_.end()) {
			//demo purposes
			print::EmptySpace(click, cerr);
		}
		*/
	}

}
