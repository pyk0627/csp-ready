#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CCF CSP 202606-2 机器人宿管指南 本地测试脚本（fail-fast 版）

行为:
    - 按顺序跑测试点;
    - 遇到第一个失败(WA / 超时 / 运行时错误)立即打印详情并退出, 退出码 1;
    - 全部通过才打印总结, 退出码 0。

用法:
    python3 test.py

可选环境变量:
    SRC=main.cpp python3 test.py
    SEED=123 python3 test.py
    TIMEOUT=5 python3 test.py
"""

import os
import random
import subprocess
import sys
from pathlib import Path

# 被测源代码
SRC = Path(os.environ.get("SRC", "main.cpp"))

# 可执行文件: 必须带路径(绝对路径或 ./), 否则 Linux 只搜 PATH
if os.name == "nt":
    EXE = Path(os.path.abspath("main.exe"))
else:
    EXE = Path(os.path.abspath("main.out"))

CXX = os.environ.get("CXX", "g++")
CXXFLAGS = ["-std=c++14", "-O2", "-Wall", "-Wextra", "-pedantic"]

TIMEOUT = float(os.environ.get("TIMEOUT", "5"))
SEED = int(os.environ.get("SEED", "20260602"))


def compile_program():
    if not SRC.exists():
        print(f"[错误] 找不到源文件: {SRC}")
        print("请把你的程序保存为 main.cpp，或用 SRC=xxx.cpp python3 test.py 指定文件。")
        return False

    cmd = [CXX, *CXXFLAGS, str(SRC), "-o", str(EXE)]
    print("[编译命令]", " ".join(cmd))

    proc = subprocess.run(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True
    )

    if proc.returncode != 0:
        print("[编译失败]")
        print(proc.stderr)
        return False

    if proc.stderr.strip():
        print("[编译警告]")
        print(proc.stderr)

    if not EXE.exists():
        print(f"[错误] 编译后没有生成可执行文件: {EXE}")
        return False

    print("[编译成功]", EXE)
    return True


def run_program(input_text):
    return subprocess.run(
        [str(EXE)],
        input=input_text,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,
        timeout=TIMEOUT
    )


def bad_apples(t, k):
    """坏苹果数量: ceil(t * k / 100)"""
    return (t * k + 99) // 100


def first_good(n, k):
    """第一天丢弃坏苹果后剩余的好苹果数"""
    good = n - bad_apples(n, k)
    return max(0, good)


def can_eat(x, n, k, m):
    """x 个机器人能否至少吃满 m 天"""
    apples = n
    for _ in range(m):
        bad = bad_apples(apples, k)
        apples -= bad
        if apples < x:
            return False
        apples -= x
    return True


def reference_binary(n, k, m):
    """参考程序: 二分答案, 用于对拍"""
    lo = 0
    hi = first_good(n, k) + 1
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if can_eat(mid, n, k, m):
            lo = mid
        else:
            hi = mid
    return lo


def brute_small(n, k, m):
    """小数据暴力枚举答案"""
    ans = 0
    limit = first_good(n, k)
    for x in range(limit + 1):
        if can_eat(x, n, k, m):
            ans = x
        else:
            break
    return ans


class Case:
    def __init__(self, n, k, m, expected=None, tag="", important=False):
        self.n = n
        self.k = k
        self.m = m
        self.input_text = f"{n} {k} {m}\n"
        self.tag = tag or f"n={n}, k={k}, m={m}"
        self.important = important
        if expected is None:
            expected = reference_binary(n, k, m)
        self.expected = str(expected).strip()


def build_cases():
    cases = []

    # 官方样例
    cases.append(Case(1000, 1, 5, 194, "样例1", True))
    cases.append(Case(19, 5, 3, 5, "样例2", True))

    # 手工边界
    cases.append(Case(10, 1, 1, 9, "边界: m=1", True))
    cases.append(Case(100, 5, 1, 95, "边界: m=1 整除", True))
    cases.append(Case(100, 5, 2, 46, "边界: 两天", True))
    cases.append(Case(20, 5, 1, 19, "边界: 向上取整=1", True))
    cases.append(Case(21, 5, 1, 19, "边界: 向上取整=2", True))
    cases.append(Case(1, 1, 1, 0, "边界: 无正解(官方保证答案为正时不会出现)", True))
    cases.append(Case(1000000000, 1, 1, 990000000, "边界: 1e9 规模", True))

    random.seed(SEED)

    # 小数据暴力对拍
    for i in range(150):
        n = random.randint(1, 200)
        k = random.randint(1, 5)
        m = random.randint(1, 20)
        expected = brute_small(n, k, m)
        cases.append(Case(n, k, m, expected, f"随机小样例{i + 1}", False))

    # 中等数据与参考二分对拍
    for i in range(50):
        n = random.randint(1, 1000000)
        k = random.randint(1, 5)
        m = random.randint(1, 50)
        cases.append(Case(n, k, m, None, f"随机中样例{i + 1}", False))

    # 大数据: 检查 long long / 溢出 / 复杂度
    big_cases = [
        (10 ** 12, 1, 1000, "大数: 1e12, k=1, m=1000"),
        (10 ** 18, 1, 2000, "大数: 1e18, k=1, m=2000"),
        (10 ** 18, 2, 1000, "大数: 1e18, k=2, m=1000"),
        (10 ** 18, 3, 700, "大数: 1e18, k=3, m=700"),
        (10 ** 18, 5, 500, "大数: 1e18, k=5, m=500"),
    ]
    for n, k, m, tag in big_cases:
        cases.append(Case(n, k, m, None, tag, True))

    return cases


def fail(idx, total, case, reason, extra=""):
    """打印第一个失败的详情"""
    print(f"\n[FAIL] ({idx}/{total}) {case.tag} {reason}")
    print(f"输入    : {case.input_text.strip()}")
    if extra:
        print(extra)
    return 1


def main():
    print(f"随机种子: {SEED}")

    if not compile_program():
        return 1

    print("生成测试数据...")
    cases = build_cases()

    total = len(cases)
    passed = 0

    print(f"共 {total} 个测试点 (遇到第一个失败立即停止)")

    for idx, case in enumerate(cases, 1):
        try:
            proc = run_program(case.input_text)
        except subprocess.TimeoutExpired:
            return fail(idx, total, case, f"超时(>{TIMEOUT}s)")
        except FileNotFoundError:
            print(f"[错误] 无法启动可执行文件: {EXE}")
            print("Linux 下不能用裸文件名启动程序, 路径必须含 '/' (如 ./main.out 或绝对路径)。")
            return 1

        if proc.returncode != 0:
            return fail(idx, total, case, "运行时错误/崩溃",
                        proc.stderr.strip())

        got = proc.stdout.strip()

        if got != case.expected:
            return fail(idx, total, case, "答案错误",
                        f"期望输出: {case.expected}\n实际输出: {got}")

        # 通过
        passed += 1
        if case.important:
            print(f"[PASS] {case.tag}")
        else:
            print(".", end="", flush=True)
            if idx % 80 == 0:
                print()

    print(f"\n总结: 全部通过 {passed}/{total}，本地测试未发现错误。")
    return 0


if __name__ == "__main__":
    sys.exit(main())
