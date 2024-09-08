cpp_srcs := $(shell find src -name *.cpp)
cpp_objs := $(patsubst src/%.cpp,obj/%.o,$(cpp_srcs))

include_path := ./include
I_flag := $(include_path:%=-I%)
compile_option := -g -O3 -w $(I_flag)

obj/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_option)

workspace/exec:$(cpp_objs)
	@mkdir -p $(dir $@)
	@g++ $^ -o $@

run:workspace/exec
	@./$<

clean:
	@rm -rf obj

debug:
	@echo $(cpp_srcs)
	@echo $(cpp_objs)
	@echo $(I_flag)
	@echo $(compile_option)

.PHONY:debug run clean workspace/exec
