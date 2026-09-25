#!/bin/bash

# Создаём тестовый файл
echo "Hello world" > /tmp/grep_test.txt
echo "Error: something" >> /tmp/grep_test.txt
echo "Warning: check" >> /tmp/grep_test.txt
echo "error: another" >> /tmp/grep_test.txt
echo "No match here" >> /tmp/grep_test.txt

echo "=== Тест 1: Простой поиск ==="
diff <(./src/grep/s21_grep "error" /tmp/grep_test.txt) <(grep "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 2: Флаг -i (игнор регистра) ==="
diff <(./src/grep/s21_grep -i "error" /tmp/grep_test.txt) <(grep -i "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 3: Флаг -v (инверсия) ==="
diff <(./src/grep/s21_grep -v "error" /tmp/grep_test.txt) <(grep -v "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 4: Флаг -c (количество) ==="
diff <(./src/grep/s21_grep -c "error" /tmp/grep_test.txt) <(grep -c "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 5: Флаг -n (номера строк) ==="
diff <(./src/grep/s21_grep -n "error" /tmp/grep_test.txt) <(grep -n "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 6: Флаг -l (имя файла) ==="
diff <(./src/grep/s21_grep -l "error" /tmp/grep_test.txt) <(grep -l "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 7: Флаги -i -v ==="
diff <(./src/grep/s21_grep -i -v "error" /tmp/grep_test.txt) <(grep -i -v "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 8: Флаги -c -i ==="
diff <(./src/grep/s21_grep -c -i "error" /tmp/grep_test.txt) <(grep -c -i "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

echo "=== Тест 9: Флаг -e (шаблон) ==="
diff <(./src/grep/s21_grep -e "error" /tmp/grep_test.txt) <(grep -e "error" /tmp/grep_test.txt) && echo "PASS" || echo "FAIL"

# Удаляем тестовый файл
rm /tmp/grep_test.txt
