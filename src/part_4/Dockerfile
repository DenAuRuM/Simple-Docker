FROM nginx
USER root
WORKDIR /src/

COPY ./nginx/nginx.conf /etc/nginx/nginx.conf 
COPY ./server.c /home/server.c
COPY ./script.sh /home/script.sh

RUN apt-get update; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev

WORKDIR /home/

ENTRYPOINT ["sh", "./script.sh"]