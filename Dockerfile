FROM boinc/server_makeproject

MAINTAINER MTRNord <info@nordgedanken.de>

# project files
COPY py $PROJHOME/py
COPY project.xml config.xml boincserver.httpd.conf $PROJHOME/
COPY html $PROJHOME/html
COPY bin $PROJHOME/bin

# compile markdown files
RUN cd $PROJHOME/html/user && ./compile_md.py

# finish up
ARG GITTAG
RUN echo $GITTAG > $PROJHOME/.gittag
