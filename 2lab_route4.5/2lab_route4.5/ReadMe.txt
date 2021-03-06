﻿========================================================================
    КОНСОЛЬНОЕ ПРИЛОЖЕНИЕ. Обзор проекта 2lab_route4.5
========================================================================

4.5. Маршрут (6)

Дана матрица N x N, заполненная целыми положительными числами. Путь по матрице 

начинается в левом верхнем углу. За один ход можно пройти в соседнюю по вертикали или 

горизонтали клетку (если она существует). Нельзя ходить по диагонали, нельзя оставаться на 

месте. Требуется найти максимальную сумму чисел, стоящих в клетках по пути длиной K клеток 

(клетку можно посещать несколько раз).

Ограничения: 2 ≤ N ≤ 20, элементы матрицы имеют значения от 1 до 9999, 1 ≤ K ≤ 20.

Ввод из файла INPUT.TXT. В первой строке находятся разделенные пробелом числа N и K. 

Затем идут N строк по N чисел в каждой.

Вывод в файл OUTPUT.TXT. Вывести в первой строке максимальную сумму. В следующих K 

строках – соответствующий маршрут в виде координат клеток.

Пример 

Ввод

5 7

1 1 1 1 1

1 1 3 1 9

1 1 6 1 1

1 1 3 1 1

1 1 1 1 1

Вывод

21

1 1

1 2

1 3

2 3

3 3

4 3

3 3

Подсказка. В цикле по количеству клеток пути определить для каждой клетки, какое 

максимальное значение может быть получено в соседних с ней клетках с учетом предыдущих 

шагов.