﻿Контрабандисты(10)

В некоторой местности имеется сеть автомобильных дорог. Каждая дорога соединяет два разных 
населенных пункта. Пункты пронумерованы от 1 до N. Известно, какой максимальный груз можно 
провезти по каждой из дорог. Движение по дорогам возможно в обоих направлениях.
Контрабандисты мечтают доставить как можно больше своего нелегального товара из пу
нкта A в пункт B. 
Им стало известно, что полиция готовит засаду для конфискации товара. Засада может быть организована на какой-
либо дороге или в некотором населенном пункте, исключая пункты A и B.
Контрабандисты решили отправить товар двумя партиями по двум разным путям, которые не 
имеют  общих  населенных  пунктов  и  дорог.  Какой  наибольший  груз  можно  гарантированно 
доставить из пункта A в пункт B?

Ввод.
В  первой  строке  содержатся  через  пробел  значения N, M, A и B,  где N–количество 
населенных  пунктов  (3  ≤ N ≤  30), M – число  дорог, A и B – номера  начального  и  конечного 
населенных пунктов (A ≠ B). В каждой из следующих M строк находятся через пробел три значения 
Ui, Vi, Hi, задающие параметры очередной дороги. Значения Ui и Vi(1 ≤ Ui < Vi ≤ 30) определяют 
номера населенных пунктов на концах дороги, а  Hi(1 ≤ Hi ≤ 10^5) указывает максимальный груз, 
который можно провезти по этой дороге. Все значения целые и положительные.

Вывод.
Единственная строка должна содержать величину наибольшего гарантированного груза, 
который  можно  доставить  из  пункта A в  пункт B с  учетом  пропускной  способности  дорог  и 
возможности перехвата полицией одной из партий. Если двух различных путей из пункта 
A в пункт B не существует, вывести в выходной файл No.

Пример
Ввод 1      Ввод 2     Ввод 3
3 3 3 1     4 2 3 4    3 2 1 2
1 3 5       1 2 5      1 2 5
1 2 7       1 3 3      1 3 3
3 2 4                      
Вывод 1     Вывод 2    Вывод 3
4			No		   No