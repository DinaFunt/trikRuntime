FROM ubuntu:trusty
MAINTAINER Iakov Kirilenko <Iakov.Kirilenko@trikset.com>
ENV DEBIAN_FRONTEND noninteractive
RUN apt update
RUN apt -y full-upgrade
RUN apt install software-properties-common -y
RUN add-apt-repository -y ppa:beineri/opt-qt563-trusty
RUN add-apt-repository -y ppa:jonathonf/gcc
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt update && apt -y full-upgrade
RUN apt install -y qt56-meta-minimal qt56svg qt56script qt56multimedia
#RUN add-apt-repository ppa:forkotov02/opt-qt-5.11.1-trusty -y
#RUN add-apt-repository ppa:deadsnakes/ppa -y # python3.x
#RUN apt update
#RUN apt install qt511x11extras

RUN apt install -y curl rsync build-essential g++ pkg-config libboost-system-dev libboost-wave-dev \
        tcl vera++ xvfb mesa-common-dev libgl1-mesa-dri libglu1-mesa-dev libpng-dev zlib1g-dev xbitmaps \
        xterm git-core ccache

#for TRIK Studio build
RUN apt install -y libusb-1.0-0-dev dbus
RUN [ -r /etc/machine-id ] || { dbus-uuidgen | tee /etc/machine-id ; }

#RUN apt-get install -y qdbus qmlscene qt5-qmake \
#        qtbase5-dev-tools qtchooser qtdeclarative5-dev libqt5svg5-dev \
#    qtscript5-dev qt5-default qtbase5-private-dev qtmultimedia5-dev

RUN apt install -y python-pip libpython-dev
RUN pip install --user --upgrade pip
RUN pip install --user codecov

RUN apt install -y libssl-dev realpath
ENV PYENV_VERSION 3.5.6
ENV PYENV_ROOT "/pyenv"
RUN curl -L https://raw.githubusercontent.com/trikset/trik-pythonqt/master/with_pyenv | bash

RUN apt install --no-install-recommends qt56tools

ENV QTDIR "/opt/qt56"
ENV PATH "${QTDIR}/bin:/usr/lib/ccache:${PATH}"
ENV PATH "$PYENV_ROOT/bin:$PATH"

RUN echo 'source /opt/qt56/bin/qt56-env.sh' >> /root/.bashrc
RUN echo 'eval "$(pyenv init -)"' >> /root/.bashrc
RUN echo 'eval "$(pyenv virtualenv-init -)"' >> /root/.bashrc
RUN echo 'PKG_CONFIG_PATH=$(python3-config --prefix)/lib/pkgconfig' >> /root/.bashrc
#RUN ln -svt /etc/profile.d/ /opt/qt56/bin/qt56-env.sh
#ENTRYPOINT ["/bin/bash", "-lc"]
