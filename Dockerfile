FROM boinc/server_makeproject:latest-b2d

MAINTAINER MTRNord <info@nordgedanken.de>

#install extra packages
RUN apt-get update && apt-get install -y ruby-kramdown

# project files
COPY config.xml boincserver.httpd.conf $PROJHOME/
COPY html $PROJHOME/html
COPY bin $PROJHOME/bin

# compile markdown files
RUN cd $PROJHOME/html/user && ./compile_md.py

# finish up
ARG GITTAG
RUN echo $GITTAG > $PROJHOME/.gittag
