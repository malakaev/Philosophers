# Philosophers
Implementation of the thread deadlock protection algorithm.

Стек: C, Make. Для MacOS и Linux.

Классическая задача про обедающих философов.
Реализация алгоритма управления потоками и мьютексами. Потоки - философы, мьютексы - вилки.

• Один или несколько философов сидят за круглым столом и занимаются одним из трех дел: едят, думают или спят.
• Во время еды они не думают и не спят, во время сна они не едят и не думают и, конечно, во время размышлений они не едят и не спят.
• Философы сидят за круглым столом с большой миской спагетти в центре.
• На столе есть несколько вилок.
• Поскольку спагетти трудно подавать и есть одной вилкой, предполагается, что философ должен есть двумя вилками, по одной на каждую руку.
• Философы никогда не должны голодать.
• Каждый философ нуждается в еде.
• Философы не разговаривают друг с другом.
• Философы не знают, когда другой философ вот-вот умрет.
• Каждый раз, когда философ заканчивает есть, он роняет вилки и начинает спать.
• Когда философ закончит спать, он начнет думать.
• Симуляция прекращается, когда философ умирает.

Каждая программа должна иметь одинаковые параметры: количество времени для 
number_of_philosophers 
time_to_die 
time_to_eat 
time_to_sleep 
[number_of_times_each_philosopher_must_eat]

◦ number_of_philosophers: это число философов, а также количество вилок
◦ time_to_die: измеряется в миллисекундах, если философ не начнет есть "time_to_die" через миллисекунды после начала своего последнего приема пищи или начала симуляции, он умрет
◦ time_to_eat: измеряется в миллисекундах и представляет собой время, необходимое философу для еды. В течение этого времени ему нужно будет держать две вилки.
◦ time_to_sleep: измеряется в миллисекундах и является временем, которое философ проведет во сне.
◦ number_of_times_each_philosopher_must_eat: аргумент необязателен, если все философы съедят хотя бы number_of_times_each_philosopher_must_eat’ симуляция остановится. Если не указано иное, симуляция прекратится только после смерти философа.

Каждому философу должно быть присвоено число от 1 до "number_of_философов".

• Философ номер 1 находится рядом с номером философа "number_of_философов".
Любой другой философ с номером N сидит между философом N - 1 и
философом N + 1

• Любое изменение статуса философа должно быть записано следующим образом 
(X заменяется номером философа, а timestamp_in_ms - текущей меткой времени в миллисекундах)

◦ timestamp_in_ms X has taken a fork	◦ отметка времени в мс X взял вилку
◦ timestamp_in_ms X is eating		◦ отметка времени в мс X ест
◦ timestamp_in_ms X is sleeping		◦ отметка времени в мс X спит
◦ timestamp_in_ms X is thinking		◦ отметка времени в мс X думает
◦ timestamp_in_ms X died			◦ отметка времени в мс X умер

• Напечатанный статус не должен быть зашифрован или переплетен со статусом другого философа.

• У вас не может быть более 10 мс между смертью философа и тем, когда он напечатает свою смерть.

• Опять же, философы должны избегать смерти!


Для запуска выполнить команду Make в терминале.
Пример запуска ./philo 5 800 200 200
