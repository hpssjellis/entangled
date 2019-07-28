FROM gitpod/workspace-full:latest

USER root

RUN apt-get update                                                  \
    && apt-get install -y default-jdk                               \
             build-essential clang libdbus-1-dev libgtk-3-dev       \
             libnotify-dev libgnome-keyring-dev libgconf2-dev       \
             libasound2-dev libcap-dev libcups2-dev libxtst-dev     \
             libxss1 libnss3-dev gcc-multilib g++-multilib curl     \
             gperf bison python-dbusmock                            \
    && apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*

RUN apt-get update                                                                                        \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends dbus gcc g++ automake    \
               libtool lsb-release make  clang-format-6.0   libdbus-1-dev libboost-dev libreadline-dev    \                                     
               autoconf autoconf-archive  software-properties-common bsdtar xsltproc                      \
                 ocl-icd-opencl-dev  opencl-headers  libssl-dev  bazel                                    \
    && apt-get update  



## NOTE: not installing libreadline and libglib2.0-dev may cause some issues

# will clean folders last   
    
    
# Get gcc-arm-embedded key
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys B4D03348F75E3362B1E1C2A1D1FAA6ECF64D33B0

# Add ggc-arm-embedded ppa
RUN echo "deb http://ppa.launchpad.net/team-gcc-arm-embedded/ppa/ubuntu bionic main" > /etc/apt/sources.list.d/team-gcc-arm-embedded-ubuntu-ppa-bionic.list

# Install gcc-arm-armbedded
RUN apt update && apt install -y --no-install-recommends \
    gcc-arm-embedded \
 && rm -rf /var/lib/apt/lists/*  
    
    
    
    
    
    
 


USER gitpod
  
RUN mkdir -p /home/gitpod/rocksetta                                                                            \ 
    && mkdir -p /home/gitpod/rocksetta/logs                                                                    \ 
    && touch /home/gitpod/rocksetta/logs/mylogs.txt                                                            \
    && echo "Installation start, made some folders in /home/gitpod" >> /home/gitpod/rocksetta/logs/mylogs.txt  \
    && echo "Back to root to install the Android sdk" >> /home/gitpod/rocksetta/logs/mylogs.txt                
    








# Give back control
USER root


# Cleaning
RUN apt-get clean


















#install prerequisits
RUN apt-get update && \
    apt-get -y install sudo

RUN sudo apt update && sudo apt -y install ocl-icd-opencl-dev 

RUN sudo apt -y install opencl-headers && sudo apt-get -y install libssl-dev
