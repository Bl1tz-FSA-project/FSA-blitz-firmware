# Frequency Spectrum Analyzer 'Blitz'
Firmware source for ESP32 based drone detector.
Lead Developer: @SamcraftSam

ЧАС (Частотний Аналізатор Спектру) - недороге, гнучке й відкрите до модифікацій рішення для виявлення й аналізу пакетів у радіоефірі. Підходить для виявлення дронів й засобів зв'язку. 
Пристрій працює на базі мікроконтролера ESP32-C3, для прослуховування ефіру використовується радіомодуль NRF95. Робочий частотний діапазон налаштовується користувачем, від 150 до 1020 МГц.
Базовий, заводський алгоритм передбачає виявлення радіо-пакетів методом обчислення Ейнтропії Шенона. 
Така методика хоч і не гарантує точність, але зате не вимагає інформації про джерело сигналу і працюватиме навіть з зашифрованим трафіком.

Варто зазначити, що наразі проєкт в розробці на стадії прототипу, тож нові алгоритми та оновлення інтерфейсу в процесі.

    Targets:
     - Whole frontend must be written from scratch
     - Handle buttons
     - Test RF detection algorithm on the FPV drone etc.
     - Firmware must be patch-friendly
     - Add extensive guide on README.md
     - Firmware protection

# FOR DEV:

init/init.h - Ініціалізація всіх бібліотек, макросів, класів, заліза(окрім радіо).

init/globals.h - Глобальні змінні для даних.

frontend/displayCtrl.h  - бібліотека, що має спростити розробку під дисплей. Основні функції забезпечують зручний вивід тексту, функцій під графічні примітиви поки що немає. Читати коментарі в файлі!

Курсор стає по верхньому пікселю, тому, наприклад, для повного відображення тексту знизу, позиція курсора по У має бути менша ніж 60 (в макросі 55). Для великого тексту ще менше - 50 пікселів. 

	|=========   Рахунок координат по Х - зліва-направо
	|0 1 2 3 4   Рахунок по У - зверху-вниз.
	|1
	|2
	|3
	|4

128х64 пікселі.

Верхні пікселі(один рядок під капс) - жовті, інші - сині.

# Друк на дисплеї:
Ширина дисплею - до 10 символів великим шрифтом. Жовту зону використовувати під капс.
Жовта зона(жовті пікселі) - під заголовок. Синя зона - під логи, до 6 рядків тексту шрифтом 1.


backend/scanner.h - радіомодуль і пов'язані з ним алгоритми. Є процедура ініціалізації радіоапаратури, є конкретні алгоритми сканування. Деталі у самому коді. НЕ робити правки без узгодження з автором!

backend/entropy.h - НЕ ЧІПАТИ!

# Для кращого ознайомлення читайте код і мануали по бібліотекам. 

# Поки працює - не чіпай. Є ідея як покращити? Роби окрему гілку!

 - поки що дивно працює радіо-частина, скоро тестуватиму цю частину
    Радіо-частина - ок, але не виводить RSSI
    Ентропія працює стабільно, детекції в логах - теж

    Проблема з виводом на дисплей, значення змінних стираються! Треба фіксити! можливо, "inline"!!!!
    Зафікси до завтра!