# HSE_cpp_hw3

Было произведено изменение без использования потоков:
(закомментирована изначальная реализация)
![image](https://github.com/user-attachments/assets/85657108-abd4-4360-bfa8-7a8df27100fb)

Замеры проводились на 300 тиках по 4 до и после изменения:

Замеры до изменения:

![image](https://github.com/user-attachments/assets/7a241783-0a50-47cc-b492-9d932029877d)

![image](https://github.com/user-attachments/assets/148b1b53-9dea-45af-b3ee-5345f63e5bfd)

![image](https://github.com/user-attachments/assets/d3444f08-2dc9-43c2-a343-ebeac4ad053d)

![image](https://github.com/user-attachments/assets/c0d7adb1-c769-4b49-bc6b-42512d94bef6)

Среднее время: 91,1785 секунд



После изменения:

![image](https://github.com/user-attachments/assets/ae442e9e-cc40-49a8-8134-45f2121888b6)

![image](https://github.com/user-attachments/assets/53c36b64-c3b2-43ef-a4a3-20e856973d71)

![image](https://github.com/user-attachments/assets/f7f33135-c21e-4597-a3d9-7ca61df8e7f0)

![image](https://github.com/user-attachments/assets/7d404746-add7-4b42-b855-ebb7a17179fc)

Среднее время: 42,3345 секунд
т.е. быстрее более чем в два раза.

---

Распараллелены вычисления влияния давления и внешних сил (external forces) в fluid.cpp.
Для компактности изменния тут не приводятся, однако в самом коде аналогично закомменирована старая реализация и рядом находится новая.
