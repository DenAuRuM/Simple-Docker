## Привет, дорогой пир!

Представь, что ты дочитал роман о море "Моби Дик" во время морского путешествия по лазуритным водам Атлантики. Дочитав роман ты понимаешь, что почерпнул вдохновение на создание великолепного отчета по Докеру.

![simple_docker](screenshots/simple_docker.png)

## Начнем с базы.

Для начала разберемся с определениями.

### **Nginx**

**Nginx** (произносится как энджинкс) - это обратный прокси-сервер (промежуточное звено между клиентом веб-браузером и другими серверами), который испольузется как балансировщик нагрузки, а также кеширования HTTP. Обратный прокси-сервер славится тем, что обладает высокой производительностью и низким потреблением памяти.

**Nginx** обладает главным и несколькими рабочими процессами. Основная задача главного процесса — чтение и проверка конфигурации и управление рабочими процессами.Рабочие процессы выполняют фактическую обработку запросов.

Все модули определяются в конфигурационном файле *nginx.conf*.

### **Docker**

Контейнер - это новый "исполняемый файл", который включает в себя все необходимые продукты зависомсти. Главное преимущество контейнеризации - это изоляция зависимостей и единая простая точка запуска ПО.

Основные понятия:

**Docker** - это платформа, которая предназначена для разработки, развертывания и запуска приложений в контейнерах. Предшественником Docker были виртуальные машины. Они, как и контейнер, изолируют приложение и его зависимости от внешней среды. Преимущества над виртуальными машинами заключаются в:
* низком потреблении ресурсов;
* легко переносить;
* быстрее запускаются;
* быстрее приходят в работоспособное сосотояние.

Docker-образ состоит из слоёв. Каждый слой описывает какое-то изменение, которое должно быть выполнено с данными на запущенном контейнере. Структура связей между слоями - иерархическая. Существует базовый слой, на который "накладываются" остальные слои. Для создания образа используется Dockerfile. Каждая инструкция в нем создает новый слой.

### **Dockle**
**Dockle** - это инструмент для проверки безопасности образов контейнеров, который можно использовать для поиска уязвимостей.

Основные функции и преимущества Dockle:

* поиск уязвимостей в образах;
* помощь в создании правильного Dockerfile;
* простота в использовании, нужно указать только имя образа;
* поддержка CIS Benchmarks.

### **Docker Compose**
**Docker Compose** - это инструмент для развёртывания проектов. При использовании нескольких сервисов нужен для обеспечения функционировании проектов.

## **Part 1. Готовый докер**


== Задание ==

Возьми официальный докер-образ с nginx и выкачай его при помощи ```docker pull```.

![docker pull nginxs](screenshots/part%201%20pull%20nginxs.png)

Проверь наличие докер-образа через ```docker images```.

![docker images](screenshots/part%201%20docker%20images.png)

Запусти докер-образ через ```docker run -d [image_id|repository]```. Флаг ```-d``` или ```--detach``` запускает контейнер на фоне и показывает id. 

![docker run](screenshots/part%201%20docker%20run%20-d.png)

Проверь, что образ запустился через ```docker ps```.

![docker ps](screenshots/part%201%20docker%20ps.png)

Посмотри информацию о контейнере через ```docker inspect [container_id|container_name]```. 

![docker inspect](screenshots/part%201%20docker%20inspect.png)

По выводу команды определи и помести в отчёт:

**Размер контейнера**. 
```ShmSize``` использует оперативную память для хранения контейнеров в байтах. По умолчанию контейнер занимает ~ 64 МБ. 

![docker size](screenshots/part%201%20docker%20size.png)

**Список замапленных портов**.
"Замапить" - подразумевается перенаправление запросов через хосты в Docker-контейнер. Иными словами - сопоставление портов делает процессы внутри контейнера доступными извне. 

`docker inspect 7ab701406346 | grep Ports -A 3`
> -A выводит 3 строчки после совпадения слова.

![ports](screenshots/part%201%20ports.png)

**IP контейнера**. IP-адрес контейнера - это адрес, по которому контейнер доступен извне.

![networks](screenshots/part%201%20networks.png)

Останови докер образ через ```docker stop [container_id|container_name]```.

![docker stop](screenshots/part%201%20docker%20stop.png)

Проверь, что образ остановился через ```docker ps```.

![docker stop check](screenshots/part%201%20docker%20stop%20check.png)

Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду run.

```docker run -d -p 80:80 -p 443:443 e784f4560448```

![docker run -p 80:80](screenshots/part%201%20docker%20run.png)

Проверь, что в браузере по адресу localhost:80 доступна стартовая страница nginx.

![localhost:80](screenshots/part%201%20localhost%2080.png)

Перезапусти докер контейнер через ```docker restart [container_id|container_name]```. Проверь любым способом, что контейнер запустился.

Запускаем команду ```docker restart e784f4560448``` и проверяем uptime нашего контейнера.

![docker restart](screenshots/part%201%20docker%20restart.png)


## **Part 2. Операции с контейнером**

== Задание == 

Прочитай конфигурационный файл nginx.conf внутри докер контейнера через команду ```exec```.

На скрине представлены основные настройки nginx, а конкретные сервера лежат в /etc/nginx/conf.d/*.conf

```docker exec 5f6e5d6f5a01 cat /etc/nginx/nginx.conf```

![docker exec](screenshots/part%202%20exec.png)

Создай на локальной машине файл `nginx.conf`. Настрой в нем по пути /status отдачу страницы статуса сервера nginx.

Добавляем в конфиг:

```
location = /status {
    stub_status;
}
```

Смотрим конфиг:

![conf edited](screenshots/part%202%20conf%20edited.png)

Скопируй созданный файл nginx.conf внутрь докер-образа через команду `docker cp`.

![docker cp](screenshots/part%202%20docker%20cp.png)

Перезапусти nginx внутри докер-образа через команду `exec`. После внесения изменений проверяем конфигурацию nginx на наличие ошибок при помощи `nginx -t`.

![nginx -t](screenshots/part%202%20nginx%20-t.png)

Далее перезапускаем при помощи `nginx -s reload`, чтобы применить последние изменения.

![docker exec](screenshots/part%202%20docker%20exec.png)

Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

![localhost](screenshots/part%202%20localhost.png)

Экспортируй контейнер в файл `container.tar` через команду ```export```.

![container tar](screenshots/part%202%20container%20tar.png)

![ls -la](screenshots/part%202%20container%20tar%20with%20grep.png)

Останови контейнер.

![stop container](screenshots/part%202%20stop%20container.png)

Удали образ через ```docker rmi [image_id|repository]```, не удаляя перед этим контейнеры.

![docker rmi](screenshots/part%202%20docker%20rmi.png)

Удали остановленный контейнер.

![rm container](screenshots/part%202%20docker%20remove%20container.png)

Импортируй контейнер обратно через команду import.

![docker import](screenshots/part%202%20docker%20import.png)

Запусти импортированный контейнер.

![part 2 with my nginx](screenshots/part%202%20docker%20run%20with%20my%20nginx.png)

Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

![my nginx](screenshots/part%202%20localhost%20with%20my_nginx.png)

## **Part 3. Мини веб-сервер**

== Задание ==

Напиши мини-сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью Hello World!.

Сервер на Си:

![server on c](screenshots/part%203%20server.png)

Для начала удаляем образы и контейнер nginx, чтобы все отрабатывало корректно.

```
docker stop [container_id]
docker rmi [iamge_id]
docker rm [container_id]
```
Качаем заново:

```
docker pull nginx
```

Запускаем контейнер:
```
docker run -p 80:80 -p 81:81 -d nginx:latest
```

Запусти написанный мини-сервер через spawn-fcgi на порту 8080.

Для начала скопируем файл server.c в контейнер. Заходим внутрь контейнера и смотрим содержимое кода на си:

![docker cp](screenshots/part%203%20cp%20to%20docker.png)

![docker nano](screenshots/part%203%20docker%20nano.png)

Далее запускаем через `gcc` с флагом `-lfcgi` и запускаем на порту 8080

![docker exec](<screenshots/part 3 docker exec.png>)

Исходя из сообщения выше, процесс "ребенок" заспавнился и даже имеет свой собственный PID.

Напиши свой nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080. 

Копируем наш файл в контейнер и перезапускаем через exec.

```
docker cp nginx/nginx.conf [cont_name]:/etc/nginx/nginx.conf
docker exec [cont_name | cont_id] nginx -s reload
```

![docker cp n exec](screenshots/part%203%20docker%20cp%20n%20exec.png)

Проверь, что в браузере по localhost:81 отдается написанная тобой страничка.

![localhost 81](<screenshots/part 3 localhost 81.png>)

Положи файл nginx.conf по пути ./nginx/nginx.conf (это понадобится позже).

## **Part 4. Свой докер**

== Задание ==
При написании докер-образа избегай множественных вызовов команд RUN

```
Напиши свой докер-образ, который:

1) собирает исходники мини сервера на FastCgi из Части 3;

2) запускает его на 8080 порту;

3) копирует внутрь образа написанный ./nginx/nginx.conf;

4) запускает nginx.
nginx можно установить внутрь докера самостоятельно, а можно воспользоваться готовым образом с nginx'ом, как базовым.
```

> Про Docker-образ читаем перед сном [тут](https://ru.hexlet.io/courses/docker-basics/lessons/image-creation/theory_unit)

Собери написанный докер-образ через docker build при этом указав имя и тег.

![docker build](screenshots/part%204%20docker%20build.png)

Проверь через docker images, что все собралось корректно.

![docker images](screenshots/part%204%20docker%20images.png)

Запусти собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2).

![docker run](screenshots/part%204%20docker%20run.png)

Проверь, что по localhost:80 доступна страничка написанного мини сервера.

![docker curl](screenshots/part%204%20curl%20localhost.png)

Допиши в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx.

Добавляем в конфиг nginx/nginx.conf:
```
location = /status {
    stub_status;
}
```

Перезапусти докер-образ.

```
docker ps
docker restart f88174a49d8e
```

![docker ps n restart](screenshots/part%204%20docker%20ps%20n%20restart.png)

Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер-образа должен обновиться самостоятельно без лишних действий

Проверь, что теперь по localhost:80/status отдается страничка со статусом nginx

![status n localhost](screenshots/part%204%20status%20n%20localhost.png)

## Part 5. Dockle

Устанавливаем dockle при помощи homebrew:
```
brew install goodwithtech/r/dockle
```

== Задание ==

Просканируй образ из предыдущего задания через dockle [image_id|repository].

![dockle analyse](screenshots/part%205%20dockle.png)

Исправь образ так, чтобы при проверке через dockle не было ошибок и предупреждений. Пройдемся по каждой ошибке:

![part 5 fatal](screenshots/part%205%20fatal.png)

Добавляем в последнюю строчку после apt-get update:
```
rm -rf /var/lib/apt/lists/*
```

Следующее предупреждение:

![dockle warn](screenshots/part%205%20dockle%202.png)

Делаем пользователя не root:

```
USER www-data
```

Следующее предупрждение:
![part 5 dockle info](screenshots/part%205%20dockle%203.png)

В консоль перед запуском прописываем:
```
export DOCKER_CONTENT_TRUST=1
```

Также, в Dockerfile прописываем следующие права доступа:
```
    chown -R www-data /var/lib/nginx; \
    chown -R www-data:www-data /var/log/nginx; \
    chmod -R 755 /var/log/nginx; \
    touch /var/run/nginx.pid; \
    chown -R www-data:www-data /var/run/nginx.pid; \
    chown -R www-data:www-data /home/run/; \
    mkdir /var/lib/nginx/body; \
    mkdir /var/lib/nginx/fastcgi; \
    mkdir /var/lib/nginx/proxy; \
    mkdir /var/lib/nginx/uwsgi; \
    mkdir /var/lib/nginx/scgi; \
    chown -R www-data:www-data /home/
```

Далее:
![part 5 dockle 4](screenshots/part%205%20dockle%204.png)

Добавляем в наш Dockerfile:
```
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 CMD [ "curl", "--fail", "http://localhost:81" ]
```
`--interval=30s` - интервал между проверками состояния (30 сек);

`--timeout=10s` - проверка работоспособности, которая запускает период ожидания. Считается проверка работоспособности неудачной, если время превышено;

`--start-period=5s` - определяет, сколько времени потребуется контейнеру для загрузки;

`--retries=3` - количество попыток, которые после сбоев пытаются "поднять" контейнер. После достижения максимального количество (3 раза) статус контейнера считается неработоспособным.

`CMD [ "curl", "--fail", "http://localhost:81" ]` выполняет HTTP-запрос к серверу на порту 81. 
`--fail` означает, что завершится с ошибкой, если получают ошибку 404 или 500. 

Далее:
![paty 5 safety files](screenshots/part%205%20safety%20files.png)

Добавляем следующие команды:
```
chmod 755 /usr/bin/expiry;
chmod 755 /usr/bin/newgrp;
chmod 755 /usr/bin/mount;
chmod 755 /usr/bin/umount;
chmod 755 /usr/bin/chage;
chmod 755 /usr/bin/gpasswd;
chmod 755 /usr/bin/su;
chmod 755 /usr/sbin/pam_extrausers_chkpwd;
chmod 755 /usr/sbin/unix_chkpwd;
chmod 755 /usr/bin/chfn;
chmod 755 /usr/bin/passwd;
chmod 755 /usr/bin/chsh;
```
Последняя босс-ошибка:
![](screenshots/part%205%20the%20last%20boss%20error.png)

УБираем ее при помощи заменой строчки 
```
FROM nginx
``` 
на 
```
FROM ubuntu:latest
``` 
Собираем новый образ Docker:
```
docker build -t mini_server:11 .
```
Проверяем его при помощи Dockle:
```
dockle mini_server:11
```
Прогоняем Dockleй:
![Докля все оки!](screenshots/part%205%20check.png)

Если мы хотим запустить контейнер, то возможно, выдастся ошибка:
![part 5 error](screenshots/part%205%20error.png)

Для того, чтобы ее исправить, нужно написать:
```
export DOCKER_CONTENT_TRUST=0
```
P.s. Можно оставить от Докли уровень Info, так как он носит характер информации, а не предупреждения или фаталити

![info warn fatal](screenshots/part%205%20info%20warn%20n%20fatal.png)

Проверяем, что все работает:

![](screenshots/part%205%20docker%20run%20.png)

![](screenshots/part%205%20localhost.png)

## Part 6. Базовый Docker Compose

== Задание ==

Напиши файл docker-compose.yml, с помощью которого:

1) Подними докер-контейнер из Части 5 (он должен работать в локальной сети, т.е. не нужно использовать инструкцию EXPOSE и мапить порты на локальную машину).

2) Подними докер-контейнер с nginx, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.

Замапь 8080 порт второго контейнера на 80 порт локальной машины.

Останови все запущенные контейнеры.

![stopped containers](screenshots/part%206%20stopped%20container.png)

Собери и запусти проект с помощью команд `docker-compose build` и `docker-compose up`.

![docker compose](screenshots/part%206%20docker-compose%20build.png)

Проверь, что в браузере по `localhost:80` отдается написанная тобой страничка, как и ранее.

![part 6 localhost](screenshots/part%206%20localhost.png)