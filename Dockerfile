FROM  node

# Update and upgrade packages
RUN apt-get update && apt-get upgrade -y
RUN apt-get install locales-all -y
RUN apt-get install ssh -y
RUN apt-get install sudo -y
RUN apt-get install curl file -y
RUN useradd -ms /bin/bash rick
RUN su - rick
WORKDIR /home/rick

RUN export USER=rick

RUN apt-get install vim -y

RUN apt-get install git -y

RUN apt-get install build-essential -y


RUN git clone https://github.com/Homebrew/brew ~/.linuxbrew/Homebrew
RUN mkdir ~/.linuxbrew/bin
RUN ln -s ../Homebrew/bin/brew ~/.linuxbrew/bin
RUN eval $(~/.linuxbrew/bin/brew shellenv)
RUN ~/.linuxbrew/bin/brew tap watsonbox/cmu-sphinx 
RUN ~/.linuxbrew/bin/brew install sox
RUN ~/.linuxbrew/bin/brew install automake
RUN ~/.linuxbrew/bin/brew install autoconf
RUN ~/.linuxbrew/bin/brew install libtool
RUN ~/.linuxbrew/bin/brew install bison
RUN ~/.linuxbrew/bin/brew install swing
RUN ~/.linuxbrew/bin/brew install pulseaudio
RUN ~/.linuxbrew/bin/brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxbase
RUN ~/.linuxbrew/bin/brew install --HEAD watsonbox/cmu-sphinx/cmu-pocketsphinx


ENTRYPOINT [ "/bin/bash" ]
