FROM ubuntu:20.04
MAINTAINER r888800009

RUN apt-get update && \
    DEBAIN_FRONTEND=noninteractive apt-get install -qy xinetd

RUN useradd -m babybof
RUN chown -R root:root /home/babybof
RUN chmod -R 755 /home/babybof

CMD ["/usr/sbin/xinetd", "-dontfork"]

