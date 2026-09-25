#!/bin/bash

# Создаём тестовый файл
echo "Строка 1" > /tmp/test.txt
echo "Строка 2" >> /tmp/test.txt
echo "" >> /tmp/test.txt
echo "Строка 4" >> /tmp/test.txt

echo "=== Тест 1: Без флагов ==="
diff <(./src/cat/s21_cat /tmp/test.txt) <(cat /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 2: Флаг -n (нумерация) ==="
diff <(./src/cat/s21_cat -n /tmp/test.txt) <(cat -n /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 3: Флаг -b (нумерация непустых) ==="
diff <(./src/cat/s21_cat -b /tmp/test.txt) <(cat -b /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 4: Флаг -e (показывать $) ==="
diff <(./src/cat/s21_cat -e /tmp/test.txt) <(cat -e /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 5: Флаг -E (показывать $) ==="
diff <(./src/cat/s21_cat -E /tmp/test.txt) <(cat -E /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 6: Флаг -s (сжатие пустых) ==="
diff <(./src/cat/s21_cat -s /tmp/test.txt) <(cat -s /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 7: Флаг -v (непечатаемые) ==="
diff <(./src/cat/s21_cat -v /tmp/test.txt) <(cat -v /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 8: Флаги -n -e ==="
diff <(./src/cat/s21_cat -n -e /tmp/test.txt) <(cat -n -e /tmp/test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 9: Флаги -b -s ==="
diff <(./src/cat/s21_cat -b -s /tmp/test.txt) <(cat -b -s /tmp/test.txt) && echo "PASS" || echo "FAIL"

# Удаляем тестовый файл
rm /tmp/test.txt
