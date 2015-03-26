#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -Werror
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -Werror
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.0.0\"
INCPATH=-I. \
  -I./include \
  -I./output \
  -I./output/include
DEP_INCPATH=

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=a35b34b03968fbcd722792d526cf6b78  COMAKE


.PHONY:all
all:comake2_makefile_check oreo .copy 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf oreo
	rm -rf ./output/bin/oreo
	rm -rf .copy
	rm -rf output
	rm -rf src/oreo_oreo.o
	rm -rf src/oreo_oreo_epoll.o
	rm -rf src/oreo_oreo_event.o
	rm -rf src/oreo_oreo_lock.o
	rm -rf src/oreo_oreo_queue.o
	rm -rf src/oreo_oreo_tcp_server.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

oreo:src/oreo_oreo.o \
  src/oreo_oreo_epoll.o \
  src/oreo_oreo_event.o \
  src/oreo_oreo_lock.o \
  src/oreo_oreo_queue.o \
  src/oreo_oreo_tcp_server.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40moreo[0m']"
	$(CXX) src/oreo_oreo.o \
  src/oreo_oreo_epoll.o \
  src/oreo_oreo_event.o \
  src/oreo_oreo_lock.o \
  src/oreo_oreo_queue.o \
  src/oreo_oreo_tcp_server.o -Xlinker "-("   -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lidn -Xlinker "-)" -o oreo
	mkdir -p ./output/bin
	cp -f --link oreo ./output/bin

.copy:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m.copy[0m']"
	mkdir -p output
	cp  oreo output/

src/oreo_oreo.o:src/oreo.cpp \
  include/oreo_tcp_server.h \
  include/oreo_lock.h \
  include/oreo_queue.h \
  include/oreo_event.h \
  include/oreo_epoll.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo.o src/oreo.cpp

src/oreo_oreo_epoll.o:src/oreo_epoll.cpp \
  include/oreo_epoll.h \
  include/oreo_event.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo_epoll.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo_epoll.o src/oreo_epoll.cpp

src/oreo_oreo_event.o:src/oreo_event.cpp \
  include/oreo_event.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo_event.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo_event.o src/oreo_event.cpp

src/oreo_oreo_lock.o:src/oreo_lock.cpp \
  include/oreo_lock.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo_lock.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo_lock.o src/oreo_lock.cpp

src/oreo_oreo_queue.o:src/oreo_queue.cpp \
  include/oreo_queue.h \
  include/oreo_lock.h \
  include/oreo_event.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo_queue.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo_queue.o src/oreo_queue.cpp

src/oreo_oreo_tcp_server.o:src/oreo_tcp_server.cpp \
  include/oreo_tcp_server.h \
  include/oreo_lock.h \
  include/oreo_queue.h \
  include/oreo_event.h \
  include/oreo_epoll.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/oreo_oreo_tcp_server.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/oreo_oreo_tcp_server.o src/oreo_tcp_server.cpp

endif #ifeq ($(shell uname -m),x86_64)


