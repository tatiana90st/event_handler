# Обработчик событий
Реализация класса обработчика событий оконных форм  
### class EventHandler 
Хранит указатели на формы графического интерфейса в порядке отрисовки. Принимает события мыши (клик с указанием координат)  
[event_handler.h](https://github.com/tatiana90st/event_handler/blob/main/event_handler.h)  
[event_handler.cpp](https://github.com/tatiana90st/event_handler/blob/main/event_handler.cpp)  
#### Реализованные методы  
- AddForm(int x, int y, int width, int height) - добавление формы; возвращает указатель на добаленную форму  
- DeleteForm() - удаление активной формы; возвращает указатель на форму, которая стала активной после удаления  
- React(const Point click) - обработка события:  
  - Если клик не попадает ни на одну форму, ничего не произойдет
  - Если клик попадает по неактивной форме, она становится активной
  - Если клик по активной форме не попадает ни на один элемент, ничего не произойдет
  - Если клик по активной форме попадает на невидимый элемент, ничего не произойдет
  - Если клик по активной форме попадает на видимый элемент, в std::cout будет выведено сообщение "Click FormN->EementM"  
### Вспомогательные методы  
Методы для определения вхождения точки в прямоугольник, методы вывода сообщений на экран  
[common.h](https://github.com/tatiana90st/event_handler/blob/main/common.h)  
[common.cpp](https://github.com/tatiana90st/event_handler/blob/main/common.cpp)  
### class Elements и потомки
[elements.h](https://github.com/tatiana90st/event_handler/blob/main/elements.h)  
[elements.cpp](https://github.com/tatiana90st/event_handler/blob/main/elements.cpp)  
#### class Elements  
Основные методы:
- CheckInside(const Point click) - проверяет попадение клика на элементы, возвращает значение типа bool
- IsVisible() - проверяет воидимость элемента, возвращает значение типа bool  
- OnClick() - реакция на попадание клика на элемент  
#### class Form  
Класс формы графического интерфейса, хранит список указателей на элементы, расположенные на ней, в порядке отрисовки.
Основные методы:
- AddButton - добавление кнопки на форму  
- AddImage - добавление изображения на форму 
- AddEdit - добавлениетекстового поля ввода
- CheckInsideElements(const Point click) - проверка элеметов формы на попадание клика, возвращает значение типа std::optional<Element*>  
#### class Button, Image, Edit

### Тесты  
[main.cpp](https://github.com/tatiana90st/event_handler/blob/main/main.cpp) 

#### Задачи на будущее:
- [ ] реализовать возможность для формы менять свойства элементов
- [ ] реализовать возможность удаления элемента на форме
- [ ] реализовать конструкторы и деструкторы всего
- [ ] тесты, больше тестов
