cpp_srcs:=$(shell find src -name *.cpp)
cpp_objs:=$(patsubst src/%.cpp,obj/%.o,$(cpp_srcs))
so_objs:=$(filter-out obj/main.o,$(cpp_objs))

include_path:=./include
library_path:=./lib
linking_path:=xxx

I_option:=$(include_path:%=-I%)
l_option:=$(linking_path:%=-l%)
L_option:=$(library_path:%=-L%)
r_option:=$(library_path:%=-Wl,-rpath=%)

compile_option:=-g -O3 -w -fPIC $(I_option)
linking_option:=$(l_option) $(L_option) $(r_option)

# =================编译过程===============
obj/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_option)

compile:$(cpp_objs)

lib/libxxx.so:$(so_objs)
	@mkdir -p $(dir $@)
	@g++ -shared $^ -o $@

dynamic:lib/libxxx.so

# =================链接过程================
workspace/exec:obj/main.o
	@mkdir -p $(dir $@)
	@g++ $^ -o $@ $(linking_option)

run:workspace/exec
	@./$<

clean:
	rm -rf obj

debug:
	@echo $(cpp_srcs)
	@echo $(cpp_objs)
	@echo $(so_objs)

.PHONY: debug dynamic run clean
