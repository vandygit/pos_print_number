# pos_print_number

Программа для Arduino Nano, компилируется в Andruino IDE

Печатает на POS-термопринтере порядковый номер заказа большими цифрами - от 01 до 99, вначале - Логотип1, потом номер, затем Логотип2 из NVmemory приинтера.

Аппаратные TX и RX ( pin1 и pin2) не используются, т.к. при одновременно не возможно загружать прошивку и передавать данные в COM, поэтому используется библиотека SoftwareSerial (11, 10) для RX, TX.

На D3 - нажимная кнопка с аппаратным ( RC ) и программным обработчиком дребезга контактов

D5 - можно подключить контроллер замены кнопки - сенсорный, ультразвуковой, инфракрасный датчики

Схема приложена. Нарисована в easyeda.
Печатной платы нет, элементы расраяны на монтажной плате 5см*7см монтажными проводами.


Ближайшая доработка - использовать более мелкие и красивые цифры для печати номера, при включении контроллера (подаче питания) при зажатой кнопке - Random начальный номер
