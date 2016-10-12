FROM boinc/server_apache:1.3.4-b2d

MAINTAINER MTRNord <info@nordgedanken.de>

# install packages 
RUN echo "deb http://ftp.debian.org/debian jessie-backports main" >> /etc/apt/sources.list \ 
    && apt-get update && apt-get install -y \
        python-matplotlib \
        python-mysqldb \
        python-numpy \
        python-scipy \
        python-yaml \
        python-pip \
        vim \
        git \
    && apt-get install -y python-certbot-apache -t jessie-backports
    
RUN git clone https://github.com/facebook/zstd.git && cd zstd && git checkout master && make && make install

RUN pip install zstandard docker-py

RUN a2enmod ssl
RUN a2enmod proxy
RUN a2enmod proxy_http

# get xkcd font
RUN curl -L http://antiyawn.com/uploads/Humor-Sans-1.0.ttf > /usr/share/matplotlib/mpl-data/fonts/ttf/Humor-Sans.ttf
