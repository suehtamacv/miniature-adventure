
# Copyright 2009-2013 Yi-Qing WANG 
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
# author Yi-Qing WANG <yiqing.wang@polytechnique.edu>



CC=cc
CXX=g++ 

COMMON_CSRC=io_png.c 
COMMON_CXXSRC=commonUtil.cpp Detector.cpp 
TRAIN_CXXSRC=train.cpp boostUtil.cpp detectUtil.cpp TrainExamples.cpp
DETECT_CXXSRC=detect.cpp detectUtil.cpp 

COMMON_COBJ=$(COMMON_CSRC:.c=.o)
COMMON_CXXOBJ=$(COMMON_CXXSRC:.cpp=.o)
COMMON_OBJ=$(COMMON_COBJ) $(COMMON_CXXOBJ)
TRAIN_CXXOBJ=$(TRAIN_CXXSRC:.cpp=.o)
DETECT_CXXOBJ=$(DETECT_CXXSRC:.cpp=.o)

VERSION=RELEASE

DEBUG_CFLAGS=-ansi -Wno-write-strings -Wall -Wextra -Werror -Wno-unknown-pragmas -g
DEBUG_CXXFLAGS=$(DEBUG_CFLAGS) -I./eigen 
RELEASE_CFLAGS=-O2
RELEASE_CXXFLAGS=$(RELEASE_CFLAGS) -I./eigen -DNDEBUG 
 
CFLAGS=$($(VERSION)_CFLAGS) 
CXXFLAGS=$($(VERSION)_CXXFLAGS) 
LDLIB=-lpng

ifdef OMP
CFLAGS+=-fopenmp
CXXFLAGS+=-fopenmp
LDLIB+=-lgomp
endif

default: eigen 
	@make all

all: train detect 

train: $(TRAIN_CXXOBJ) $(COMMON_OBJ) 
	$(CXX) $^ $(LDLIB) -o $@

detect: $(DETECT_CXXOBJ) $(COMMON_OBJ) 
	$(CXX) $^ $(LDLIB) -o $@

%.o: %.cpp %.h 
	$(CXX) -o $@ -c $< $(CXXFLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(TRAIN_CXXOBJ) $(COMMON_OBJ) $(DETECT_CXXOBJ) detect train

eigen:
	@if [ ! -d eigen ]; then \
	wget -q -O eigen.tar.gz http://bitbucket.org/eigen/eigen/get/3.2.1.tar.gz; \
	tar xfz eigen.tar.gz ; \
	mv eigen-* eigen; \
	rm -rf eigen-* eigen.tar.gz; fi 	

srcdoc:
	rm -rf doc
	doxygen doxygen.conf
	mv doxygen_docs/html doc
	rm -rf doxygen_docs 
	firefox doc/annotated.html
