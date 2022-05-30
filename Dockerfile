FROM gcc

COPY . /docker

WORKDIR /docker

RUN gcc -o main.cpp

CMD ["./main"]