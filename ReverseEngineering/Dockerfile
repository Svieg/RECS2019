FROM ubuntu:latest

ENV TZ=America/Montreal
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update Ubuntu
RUN apt-get update
RUN apt-get upgrade -y

# Install RE and basic tools
RUN apt-get install -y gdb radare2 python python3 python3-pip python-pip qemu-system-arm binwalk qemu-user-static gdb-multiarch

#Install sasquatch deps
RUN apt-get install -y git build-essential liblzma-dev liblzo2-dev zlib1g-dev squashfs-tools wget

# Install sasquatch
RUN git clone https://github.com/Svieg/sasquatch
RUN cd sasquatch && ./build.sh

# Add cs_games:cs_games user
RUN useradd --create-home --shell /bin/bash cs_games
RUN echo "cs_games:cs_games" | chpasswd

# start ssh
EXPOSE 22
CMD ["/bin/bash"]
