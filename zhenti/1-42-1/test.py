import random
import subprocess
import sys
import glob
import os

# ========== 配置 ==========
TEST_CASES = 200

# 源码文件名:命令行传参指定;不传则自动取当前目录下唯一的 .cpp
cpps = glob.glob("*.cpp")
if len(sys.argv) > 1:
    SRC = sys.argv[1]
elif len(cpps) == 1:
    SRC = cpps[0]
else:
    print("❌ 无法确定源码文件,请传参运行,如: python3 test.py main.cpp")
    sys.exit(1)
BIN = os.path.splitext(SRC)[0]

# ========== 1. 自动编译(使用 CCF CSP 考试编译选项) ==========
print(f"⏳ 正在编译 {SRC} ...")
compile_res = subprocess.run(
    ["g++", SRC, "-o", BIN, "-std=c++14", "-O2", "-DONLINE_JUDGE"],
    capture_output=True, text=True)
if compile_res.returncode != 0:
    print("❌ 编译失败!请检查 C++ 语法错误:")
    print(compile_res.stderr)
    sys.exit(1)
print("✅ 编译成功!\n")

# ========== 0. 先跑官方样例 ==========
SAMPLE_IN = """4
7.5
0.0
13.9
2026.5
"""
SAMPLE_OUT = """8 0 14 2027
8 0 14 2026
"""
run_res = subprocess.run(["./" + BIN], input=SAMPLE_IN,
                         capture_output=True, text=True)
if run_res.stdout.split() != SAMPLE_OUT.split():
    print("❌ 官方样例都没过!")
    print("【样例输入】\n" + SAMPLE_IN)
    print("【样例输出】\n" + SAMPLE_OUT)
    print("【你的输出】\n" + run_res.stdout)
    sys.exit(1)
print("✅ 官方样例通过!\n")

# ========== 2. 标程(绝对正确的逻辑,用来当裁判) ==========
def standard_solve(input_str):
    lines = input_str.strip().split('\n')
    n = int(lines[0])
    res1, res2 = [], []
    for i in range(1, n + 1):
        a_str, b_str = lines[i].split('.')
        a = int(a_str)
        b = int(b_str)

        # 四舍五入
        r1 = a + 1 if b >= 5 else a

        # 银行家舍入(向偶数舍入)
        if b > 5:
            r2 = a + 1
        elif b == 5:
            r2 = a + 1 if a % 2 != 0 else a
        else:
            r2 = a

        res1.append(str(r1))
        res2.append(str(r2))
    return " ".join(res1) + "\n" + " ".join(res2)

# ========== 3. 随机生成测试数据(专门挑易错点) ==========
def generate_input():
    n = random.randint(1, 10)
    lines = [str(n)]
    for _ in range(n):
        # 50% 普通随机数,50% 边界数(b=4/5/6、a 的奇偶与极值)
        if random.random() < 0.5:
            a = random.randint(0, 100000)
            b = random.randint(0, 9)
        else:
            a = random.choice([0, 1, 2, 99998, 99999, 100000])
            b = random.choice([4, 5, 6])
        lines.append(f"{a}.{b}")
    return "\n".join(lines)

# ========== 4. 开始暴力对拍 ==========
print(f"🚀 开始对拍 {TEST_CASES} 组数据(包含大量边界测试)...")
for i in range(TEST_CASES):
    data = generate_input()
    std_out = standard_solve(data)

    try:
        run_res = subprocess.run(["./" + BIN], input=data,
                                 capture_output=True, text=True, timeout=2)
        my_out = run_res.stdout
    except subprocess.TimeoutExpired:
        print(f"⏳ 超时!在第 {i+1} 组数据")
        print("【输入数据】\n" + data)
        sys.exit(1)

    # 按 token 对比(和 OJ 判法一致:忽略行末空格/换行等空白差异)
    if my_out.split() != std_out.split():
        print(f"\n❌ 发现错误(在第 {i+1} 组测试)!")
        print("【输入数据】\n" + data)
        print("【标准答案】\n" + std_out.strip())
        print("【你的输出】\n" + my_out.strip())
        sys.exit(1)

print("\n🎉 全部通过!你的代码逻辑完全正确,可以放心去 OJ 提交了!")
