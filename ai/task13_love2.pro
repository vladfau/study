любит('Таня', 'яблоки').
любит('Сергей', 'бананы').
любит('Андрей', 'яблоки').
любит('Света', 'карамель').
любит('Вова', 'карамель').
любит('Таня', 'халва').
любит('Света', 'апельсины').
любит('Вова', 'бананы').

фрукты('яблоки').
фрукты('бананы').
фрукты('апельсины').

сладкое('карамель').
сладкое('халва').

любит_фрукты :- любит(X, Y), фрукты(Y), write(X).
любит_сладкое :- любит(X, Y), сладкоe(Y), write(X).
любит_вкусное :- любит(X, Y), любит(A, B), сладкое(Y), фрукты(B), X = A,  write(X).
