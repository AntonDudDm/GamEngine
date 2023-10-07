# GamEngine

Это проект по написанию 2D движка для видеоигр полностью на C++.

## Поддерживаемые классы ##

### VECTORS
В данном проекте используются классы необходимые для векторного анализа, такие как 'Vector' для работы с векторами и 'Line' для работы с линиями.

### Primitives
Добавлены классы примтивов, реализующие 3 вида преметов: окружность 'Circle', Коробку 'AABB' и Коробку способную к вращению в пространстве 'BOX2D'.

### Math
Класс отвечающий за работу с вектрорами, линиями и примитивами при их вращении и любом другом взаимодействии

### Itersection and RayCast
Набор классов отвечающий за проверку пересечений точек и линий с примтивами, в том числе поддерживающий технологию RayCast.
