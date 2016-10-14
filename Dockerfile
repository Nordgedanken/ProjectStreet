FROM boinc/server_makeproject:latest-b2d

MAINTAINER MTRNord <info@nordgedanken.de>

#install extra packages
RUN apt-get update && apt-get install -y ruby-kramdown

# project files
COPY config.xml boincserver.httpd.conf $PROJHOME/
COPY html $PROJHOME/html
COPY bin $PROJHOME/bin
#COPY boinc2docker/plan_class_spec.xml $PROJHOME/plan_class_spec.xml
COPY apps/stage1_1-boinc2docker/ $PROJHOME/stage1_1-boinc2docker/
RUN boinc2docker_create_app $PROJHOME/stage1_1-boinc2docker/boinc2docker.yml

COPY apps/stage1_2-boinc2docker/ $PROJHOME/stage1_2-boinc2docker/
RUN boinc2docker_create_app $PROJHOME/stage1_2-boinc2docker/boinc2docker.yml

COPY apps/stage1_3-boinc2docker/ $PROJHOME/stage1_3-boinc2docker/
RUN boinc2docker_create_app $PROJHOME/stage1_3-boinc2docker/boinc2docker.yml

COPY apps/stage1_4-boinc2docker/ $PROJHOME/stage1_4-boinc2docker/
RUN boinc2docker_create_app $PROJHOME/stage1_4-boinc2docker/boinc2docker.yml


# compile markdown files
RUN cd $PROJHOME/html/user && ./compile_md.py

# finish up
ARG GITTAG
RUN echo $GITTAG > $PROJHOME/.gittag
