родитель('Михаил', 'Алексей').
родитель('Евдокия', 'Алексей').

родитель('Алексей', 'Феодор').
родитель('Мария', 'Феодор').

родитель('Алексей', 'Софья').
родитель('Мария', 'Софья').

родитель('Алексей', 'Иоанн').
родитель('Мария', 'Иоанн').

родитель('Алексей', 'Петр').
родитель('Наталья', 'Петр').

родитель('Петр', 'Анна').
родитель('Екатерина', 'Анна').

родитель('Петр', 'Елизавета').
родитель('Екатерина', 'Елизавета').

женщина('Евдокия').
женщина('Мария').
женщина('Наталья').
женщина('Елизавета').
женщина('Екатерина').
женщина('Анна').
женщина('Софья').

мужчина('Михаил').
мужчина('Алексей').
мужчина('Петр').
мужчина('Феодор').
мужчина('Иоанн').

бабушка(X, Y) :- родитель(X, Z), родитель(Z, Y), женщина(X).
внук(X, Y) :- родитель(Z, X), родитель(Y, Z), мужчина(X).
брат(X, Y) :- родитель(Z, X), родитель(Z, Y), мужчина(X).
сестра(X, Y) :- родитель(Z, X), родитель(Z, Y), женщина(X).

t1 :- findall(X, бабушка(X, _), L), write(L).

t2 :- findall(X, внук(X, 'Евдокия'), L), write(L).

t3 :- findall(X, (брат('Иоанн', X), брат(X, 'Иоанн')), L), write(L).

t4 :- findall(X, сестра(X, 'Феодор'), L), write(L).
