любит('Таня', 'яблоки').

любит('Сергей', 'бананы').

любит('Андрей', 'яблоки').

любит('Света', 'карамель').

любит('Вова', 'карамель').

любит('Таня', 'халва').

любит('Света', 'апельсины').

любит('Вова', 'бананы').

a :- любит(X, 'бананы'), write(X).
b :- любит(X, 'халва'), любит(X, 'яблоки'), write(X).
c :- любит('Вова', X), write(X).
d :- любит('Света', X),любит('Вова', X), write(X).
