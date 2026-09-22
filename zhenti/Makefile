# ===== 与 CCF CSP 认证考试一致的编译配置 =====
# 考试: g++ ,编译选项包括 -O2 和 -DONLINE_JUDGE,std 可选 c++98/11/14
CXX      := g++
STD      := -std=c++14
CXXFLAGS := $(STD) -O2 -DONLINE_JUDGE

# 收集当前目录及所有子目录下的 .cpp,但排除 ti/ 目录
# 以后想再排除别的目录,照抄一段 "-path ./xxx -prune -o" 加在前面即可
SRCS := $(shell find . -path ./ti -prune -o -type f -name '*.cpp' -print | sed 's|^\./||')
BINS := $(SRCS:.cpp=)

all: $(BINS)

$(BINS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# 一键编译并运行: make run FILE=1-42-1/1-42-1
FILE ?= $(firstword $(BINS))
run: $(FILE)
	./$(FILE)

clean:
	rm -f $(BINS)

.PHONY: all run clean
