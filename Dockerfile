FROM boinc/server_makeproject:latest-b2d

MAINTAINER MTRNord <info@nordgedanken.de>

#install extra packages
RUN apt-get update && apt-get install -y ruby-kramdown

# project files
COPY config.xml boincserver.httpd.conf $PROJHOME/
COPY html $PROJHOME/html
COPY bin $PROJHOME/bin
COPY boinc2docker/plan_class_spec.xml $PROJHOME/plan_class_spec.xml
COPY boinc2docker/add_cuda.py $PROJHOME/bin/add_cuda.py

# compile markdown files
RUN cd $PROJHOME/html/user && ./compile_md.py

#add Cuda
RUN cd $PROJHOME/ && chmod +x ./bin/add_cuda.py && ./bin/add_cuda.py

# finish up
ARG GITTAG
RUN echo $GITTAG > $PROJHOME/.gittag
