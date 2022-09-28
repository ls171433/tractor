MODULE_NAME:=tractor-test
BUILD_DIR=build-$(MODULE_NAME)

ifeq ("x$(shell uname -o 2>/dev/null)","xMsys")
    OS_NAME:=windows
else
    OS_NAME:=unix
endif

CXX:=c++
LD:=$(CXX)
AR:=ar

CXXFLAGS:=-std=c++11 -Wall -Iinclude -Itest
LDFLAGS:=-lgtest -lgtest_main

SRCS:=$(shell find test -name "*.cpp" -or -name "*.cc" -or -name "*.cxx")
TEMP:=$(SRCS)
TEMP:=$(TEMP:%.cpp=%.temp)
TEMP:=$(TEMP:%.cc=%.temp)
TEMP:=$(TEMP:%.cxx=%.temp)
OBJS:=$(TEMP:%.temp=$(BUILD_DIR)/%.o)
DEPS:=$(TEMP:%.temp=$(BUILD_DIR)/%.d)

ifeq ("x$(OS_NAME)","xwindows")
    EXEC_NAME:=$(MODULE_NAME).exe
    SHARED_NAME:=lib$(MODULE_NAME).dll
    STATIC_NAME:=lib$(MODULE_NAME).lib
else
    EXEC_NAME:=$(MODULE_NAME)
    SHARED_NAME:=lib$(MODULE_NAME).so
    STATIC_NAME:=lib$(MODULE_NAME).a
endif



default: all

all: exec

exec: $(EXEC_NAME)

shared: $(SHARED_NAME)

static: $(STATIC_NAME)

echo:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(OS_NAME)
	@echo $(EXEC_NAME)
	@echo $(SHARED_NAME)
	@echo $(STATIC_NAME)

clean:
	rm -fr $(BUILD_DIR) $(EXEC_NAME) $(SHARED_NAME) $(STATIC_NAME)

-include $(DEPS)



$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@

$(BUILD_DIR)/%.o: %.cxx
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@



$(EXEC_NAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(SHARED_NAME): $(OBJS)
	$(LD) -shared $^ $(LDFLAGS) -o $@

$(STATIC_NAME): $(OBJS)
	$(AR) rcs $@ $^
