FROM boinc/server_apache

MAINTAINER MTRNord <info@nordgedanken.de>

# install packages 
RUN echo "deb http://ftp.debian.org/debian jessie-backports main" >> /etc/apt/sources.list \ 
    && apt-get update && apt-get install -y \
        python-matplotlib \
        python-mysqldb \
        python-numpy \
        python-scipy \
        python-yaml \
        vim \
    && apt-get install -y python-certbot-apache -t jessie-backports

RUN a2enmod ssl
RUN a2enmod proxy

# get xkcd font
RUN curl -L http://antiyawn.com/uploads/Humor-Sans-1.0.ttf > /usr/share/matplotlib/mpl-data/fonts/ttf/Humor-Sans.ttf
