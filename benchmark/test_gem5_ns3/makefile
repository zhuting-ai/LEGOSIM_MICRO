# Project environment
# SIMULATOR_ROOT 应当由 setup_env.sh 定义
BENCHMARK_ROOT=$(SIMULATOR_ROOT)/benchmark/test_gem5

# 编译器设置
CXX=g++
# 必须包含 interchiplet 的头文件路径
CXXFLAGS=-Wall -g -I$(SIMULATOR_ROOT)/interchiplet/includes
# 静态链接库路径
INTERCHIPLET_LIB=$(SIMULATOR_ROOT)/interchiplet/lib/libinterchiplet_c.a

# 目标文件
TARGET=test_gem5
SRCS=test_gem5.cpp
OBJS=obj/test_gem5.o

# 运行工具
INTERCHIPLET=$(SIMULATOR_ROOT)/interchiplet/bin/interchiplet

all: dir $(TARGET)

# 编译可执行文件：注意使用 -static 确保 gem5 能够运行
$(TARGET): $(OBJS)
	$(CXX) -static $(OBJS) $(INTERCHIPLET_LIB) -lpthread -o $(TARGET)

# 编译对象文件
obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建必要目录
dir:
	mkdir -p obj

# 运行仿真
run:
	$(INTERCHIPLET) ./test_gem5.yml

# 清理
clean:
	rm -rf obj $(TARGET)
	rm -rf bench.txt delayInfo.txt buffer* message_record.txt
	rm -rf proc_r* *.log
	rm -rf traffic.csv
