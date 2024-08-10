#!/bin/bash

# Скрипт для центрирования текста с разделителями "=" и символом "#" в начале
text="$*"
total_width=79  # Учитываем, что первый символ будет "#"
text_length=${#text}
padding=$(( (total_width - text_length - 2) / 2 ))

# Вывод строки с символом "#", центрированным текстом и разделителями "="
printf "#"
printf "%0.s=" $(seq 1 $padding)
printf " %s " "$text"
printf "%0.s=" $(seq 1 $((total_width - padding - text_length - 2)))
echo
