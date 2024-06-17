FROM ubuntu:latest

WORKDIR /home/

COPY --chown=www-data ./nginx/nginx.conf /etc/nginx/nginx.conf 
COPY --chown=www-data ./server.c /home/server.c
COPY --chown=www-data ./script.sh /home/script.sh

RUN apt-get update; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev nginx curl gnupg1 ca-certificates; \ 
    rm -rf /var/lib/apt/lists/*; \
    chown -R www-data /var/lib/nginx; \
    chown -R www-data:www-data /var/log/nginx; \
    chmod -R 755 /var/log/nginx; \
    chmod 755 /usr/bin/expiry; \
    chmod 755 /usr/bin/newgrp; \
    chmod 755 /usr/bin/mount; \
    chmod 755 /usr/bin/umount; \
    chmod 755 /usr/bin/chage; \
    chmod 755 /usr/bin/gpasswd; \
    chmod 755 /usr/bin/su; \
    chmod 755 /usr/sbin/pam_extrausers_chkpwd; \
    chmod 755 /usr/sbin/unix_chkpwd; \
    chmod 755 /usr/bin/chfn; \
    chmod 755 /usr/bin/passwd; \
    chmod 755 /usr/bin/chsh; \
    touch /var/run/nginx.pid; \
    chown -R www-data:www-data /var/run/nginx.pid; \
    chown -R www-data:www-data /home/run/; \
    mkdir /var/lib/nginx/body; \
    mkdir /var/lib/nginx/fastcgi; \
    mkdir /var/lib/nginx/proxy; \
    mkdir /var/lib/nginx/uwsgi; \
    mkdir /var/lib/nginx/scgi; \
    chown -R www-data:www-data /home/; \
    chmod +x /home/script.sh 
    
USER www-data

WORKDIR /home/

HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 CMD [ "curl", "--fail", "http://localhost:81" ]

ENTRYPOINT ["sh", "./script.sh"]