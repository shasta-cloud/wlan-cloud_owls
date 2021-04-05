#Build stage 0

FROM alpine

RUN apk update && \
    apk add --no-cache openssl openssh && \
    apk add --no-cache ncurses-libs && \
    apk add --no-cache bash util-linux coreutils curl && \
    apk add --no-cache make cmake gcc g++ libstdc++ libgcc git zlib-dev yaml-cpp-dev && \
    apk add --no-cache openssl-dev boost-dev unixodbc-dev postgresql-dev mariadb-dev && \
    apk add --no-cache apache2-utils yaml-dev apr-util-dev

RUN mkdir /root/.ssh
ADD git_rsa /root/.ssh/git_rsa
RUN touch /root/.ssh/known_hosts
RUN chown -R root:root /root/.ssh
RUN chmod 600 /root/.ssh/git_rsa && \
    echo "IdentityFile /root/.ssh/git_rsa" >> /etc/ssh/ssh_config && \
    echo -e "StrictHostKeyChecking no" >> /etc/ssh/ssh_config
RUN ssh-keyscan github.com >> /root/.ssh/known_hosts
RUN git clone git@github.com:stephb9959/ucentralsim.git /ucentralsim

RUN git clone https://github.com/stephb9959/poco /poco
WORKDIR /poco
RUN mkdir cmake-build
WORKDIR cmake-build
RUN cmake ..
RUN cmake --build . --config Release -j8
RUN cmake --build . --target install
WORKDIR /ucentralsim
RUN mkdir cmake-build
WORKDIR /ucentralsim/cmake-build
RUN cmake ..
RUN cmake --build . --config Release -j8

RUN mkdir /ucentral
RUN cp /ucentralsim/cmake-build/ucentralsim /ucentral/ucentralsim
RUN chmod +x /ucentral/ucentralsim
RUN mkdir /ucentralsim-data

RUN rm -rf /poco
RUN rm -rf /ucentralsim

ENTRYPOINT /ucentral/ucentralsim


