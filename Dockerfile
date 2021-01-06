FROM ubuntu:20.04

WORKDIR /app

COPY . /app

RUN apt update && \
    apt upgrade && \
    apt -y install cmake && \
    apt -y install g++ && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && \

CMD ["bash"]
