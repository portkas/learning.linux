lib_srcs := $(filter-out src/main.cpp,$(shell find src -name *.cpp))
lib_objs := $(patsubst src/%.cpp,obj/%.o,$(lib_srcs))

include_path := ./include
library_path := ./lib
linking_path := xxx

I_option := $(include_path:%=-I%)
l_option := $(linking_path:%=-l%)
L_option := $(library_path:%=-L%)

compile_option := -g -O3 -w $(I_option)
linking_option := $(l_option) $(L_option)

# =============编译静态库=============
obj/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_option)

lib/libxxx.a:$(lib_objs)
	@mkdir -p $(dir $@)
	@ar -r $@ $^

static_lib:lib/libxxx.a

# =============链接静态库=============
obj/main.o:src/main.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_option)

workspace/exec:obj/main.o
	@mkdir -p $(dir $@)
	@g++ $^ -o $@ $(linking_option)

run: workspace/exec
	@./$<

clean:
	@rm -rf obj workspace

debug:
	@echo $(lib_srcs)
	@echo $(lib_objs)
	@echo $(I_option)
	@echo $(l_option)
	@echo $(L_option)
	@echo $(compile_option)

.PHONY: debug clean run
