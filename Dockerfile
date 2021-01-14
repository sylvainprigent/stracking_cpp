#======= Stage 1: build the app from sources =======#
FROM ubuntu:20.04 AS builder

WORKDIR /app
COPY . /app
RUN apt -y update && \
    apt -y upgrade && \
    apt -y install cmake && \
    apt -y install g++ && \
	apt -y install git && \
	apt -y install libtiff-dev && \
	chmod u+x build.sh && \
	./build.sh

#======= Stage 2: final image ================#
FROM ubuntu:20.04
COPY --from=builder  /app/build/bin/AssociationTracker /bin/AssociationTracker
COPY --from=builder  /lib/x86_64-linux-gnu/libtiff.so.5 /lib/x86_64-linux-gnu/libtiff.so.5
COPY --from=builder  /lib/x86_64-linux-gnu/libjpeg.so.8 /lib/x86_64-linux-gnu/libjpeg.so.8
COPY --from=builder  /lib/x86_64-linux-gnu/libwebp.so.6 /lib/x86_64-linux-gnu/libwebp.so.6
COPY --from=builder  /lib/x86_64-linux-gnu/libjbig.so.0 /lib/x86_64-linux-gnu/libjbig.so.0
CMD ["bash"]
