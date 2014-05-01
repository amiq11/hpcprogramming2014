################################
# Makefile for Benkyokai2014
# by Makoto Shimazu <shimazu@eidos.ic.i.u-tokyo.ac.jp>
################################

# 自分のつくったものに合うように変更すること
YOURSRCS  := mymulmat.cpp
YOURCLASS := MyMulMat
YOURCLASSHEADER := mymulmat.h

# 適宜変更しても大丈夫
CXX       = g++
LD        = g++
CXXFLAGS += -std=c++11
LDFLAGS  +=

# 測定用
MAIN      := main.bin
SRCDIR	  := src
OBJDIR	  := obj
# LIBS      += 
MDIR	  := measure
MSRCS	  := main.cpp tester.cpp dataset.cpp
MOBJS	  := $(MSRCS:.cpp=.o)
MOBJS_FULL = $(addprefix $(OBJDIR)/$(MDIR)/, $(MOBJS))
MDEPS     := $(MSRCS:.cpp=.d)
MDEPS_FULL = $(addprefix $(OBJDIR)/$(MDIR)/, $(MDEPS))
# Path to your codes
YOUROBJS      := $(YOURSRCS:.cpp=.o)
YOUROBJS_FULL  = $(addprefix $(OBJDIR)/, $(YOUROBJS))
YOURDEPS      := $(YOURSRCS:.cpp=.d)
YOURDEPS_FULL  = $(addprefix $(OBJDIR)/, $(YOURDEPS))
# Append flags
CXXFLAGS  += -MMD -W -Wall

.PHONY: all
all: build

.PHONY: build
build: dirs $(MAIN)

$(MAIN): $(MOBJS_FULL) $(YOUROBJS_FULL)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -DMMCLASS=$(YOURCLASS) -include $(SRCDIR)/$(YOURCLASSHEADER) -c -o $@ $< $(LIBS)


.PHONY: dirs
dirs:
	mkdir -pv $(OBJDIR) $(OBJDIR)/$(MDIR)

.PHONY: clean
clean:
	rm -rf $(MAIN) $(OBJDIR)


-include $(YOURDEPS_FULL) $(MDEPS_FULL)
