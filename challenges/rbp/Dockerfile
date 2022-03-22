FROM ubuntu:20.04
MAINTAINER r888800009

RUN apt-get update && \
    DEBAIN_FRONTEND=noninteractive apt-get install -qy xinetd

RUN useradd -m rbp
RUN chown -R root:root /home/rbp
RUN chmod -R 755 /home/rbp
RUN chmod -R 700 /tmp /var/tmp
RUN chmod 1700 /tmp /var/tmp /dev/shm

CMD ["/usr/sbin/xinetd", "-dontfork"]
