#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
test.py

用于本地检验 main.cpp 是否能通过本题（死锁优化）。
默认会编译 main.cpp，并运行：
  1. 内置样例；
  2. 当前目录 / tests 目录下的 *.in 与 *.ans；
  3. 内置参考模拟器生成的随机对拍测试。

遇到第一个失败用例即停止后续测试，避免刷屏。

用法：
    python test.py
可选参数：
    --num       随机测试数量，默认 80
    --seed      随机种子
    --timeout   单次运行超时秒数，默认 10
    --no-random 不跑随机测试
"""

import argparse
import difflib
import glob
import os
import random
import subprocess
import sys

# ---------------------------------------------------------------------------
# 参考模拟器常量
# ---------------------------------------------------------------------------

INACTIVE = 0
APPLYING = 1
RUNNING = 2
FINISHED = 3


# ---------------------------------------------------------------------------
# 内置参考实现：严格按照题面模拟
# ---------------------------------------------------------------------------

def solve_reference(text: str):
    tokens = text.split()
    if not tokens:
        return ""

    it = iter(tokens)
    try:
        n = int(next(it))
        m = int(next(it))
    except StopIteration:
        return ""

    typ = [''] * (n + 1)
    st = [0] * (n + 1)
    w = [0] * (n + 1)
    k = [0] * (n + 1)
    a = [None] * (n + 1)
    t = [None] * (n + 1)

    max_st = 0

    for i in range(1, n + 1):
        typ[i] = next(it)
        if typ[i] == 'X':
            st[i] = int(next(it))
            k[i] = int(next(it))
            w[i] = 0
        else:
            st[i] = int(next(it))
            w[i] = int(next(it))
            k[i] = int(next(it))

        max_st = max(max_st, st[i])

        a[i] = [0] * k[i]
        t[i] = [0] * k[i]

        for j in range(k[i]):
            a[i][j] = int(next(it))
            t[i][j] = int(next(it))

    state = [INACTIVE] * (n + 1)
    task = [0] * (n + 1)
    run_rem = [0] * (n + 1)

    # app_fail:
    #   -1 表示 X 类，或者 A 类已经触发过释放、之后按普通申请处理
    #   对 A/B: 0..w-1 表示当前申请周期内已经失败次数
    #   对 C:   0..w   表示当前申请周期内已经失败次数；等于 w 时下一段首抢夺
    app_fail = [-1] * (n + 1)

    revenue = [0] * (n + 1)
    finish_seg = [-1] * (n + 1)

    owner = [0] * (m + 1)      # owner[r] = 0 表示空闲，否则为进程编号
    held = [0] * (n + 1)       # held[i] = 进程 i 当前占有的资源数

    def release_all(pid: int):
        for r in range(1, m + 1):
            if owner[r] == pid:
                owner[r] = 0
                held[pid] -= 1

    seg = 1
    seen = set()

    # 防止参考模拟器在极端本地输入上无限跑下去。
    # 若超过限制，返回 None，测试框架会跳过该用例而不是判错。
    step_limit = int(os.environ.get("TEST_REF_LIMIT", "1000000"))
    seen_limit = int(os.environ.get("TEST_REF_SEEN_LIMIT", "300000"))

    while True:
        done = True
        for i in range(1, n + 1):
            if state[i] != FINISHED:
                done = False
                break
        if done:
            break

        # 所有进程都已经开始活动后，绝对段号不再影响未来事件。
        # 此时若状态重复，则之后必然循环，不会结束，输出 -1。
        if seg > max_st:
            key = (
                tuple(state[1:]),
                tuple(task[1:]),
                tuple(run_rem[1:]),
                tuple(app_fail[1:]),
                tuple(owner[1:]),
            )
            if key in seen:
                break
            seen.add(key)
            if len(seen) > seen_limit:
                return None

        if seg > step_limit:
            return None

        # -------------------------------------------------------------------
        # 段首：新进程开始活动
        # -------------------------------------------------------------------
        for i in range(1, n + 1):
            if state[i] == INACTIVE and st[i] == seg:
                state[i] = APPLYING
                task[i] = 0
                app_fail[i] = 0 if typ[i] != 'X' else -1

        # -------------------------------------------------------------------
        # 段首：收集申请
        # -------------------------------------------------------------------
        applicants = {}
        for i in range(1, n + 1):
            if state[i] == APPLYING:
                x = a[i][task[i]]
                applicants.setdefault(x, []).append(i)

        success = set()
        force_lose = set()
        normal_fail = set()

        # -------------------------------------------------------------------
        # 段首：按资源解决冲突
        # -------------------------------------------------------------------
        for x, pids in applicants.items():
            force = []
            for p in pids:
                if typ[p] == 'C' and app_fail[p] == w[p]:
                    force.append(p)

            if force:
                # C 类抢夺：编号最大者成功，其余 C 类抢夺失败但也进入运行状态。
                # 其他任何申请均失败。
                win = max(force)

                old = owner[x]
                if old != win:
                    if old != 0:
                        held[old] -= 1
                    owner[x] = win
                    held[win] += 1

                success.add(win)

                for p in pids:
                    if p == win:
                        continue
                    if typ[p] == 'C' and app_fail[p] == w[p]:
                        force_lose.add(p)
                    else:
                        normal_fail.add(p)
            else:
                if owner[x] != 0:
                    # 资源已被占有，所有申请失败
                    for p in pids:
                        normal_fail.add(p)
                else:
                    # 资源空闲，编号最小者成功
                    win = min(pids)
                    owner[x] = win
                    held[win] += 1
                    success.add(win)

                    for p in pids:
                        if p != win:
                            normal_fail.add(p)

        # -------------------------------------------------------------------
        # 段首：处理申请成功 / C 类抢夺失败
        # -------------------------------------------------------------------
        for p in success:
            state[p] = RUNNING
            run_rem[p] = t[p][task[p]]
            app_fail[p] = -1

        for p in force_lose:
            state[p] = RUNNING
            run_rem[p] = t[p][task[p]]
            app_fail[p] = -1

        # -------------------------------------------------------------------
        # 段首：处理普通申请失败，以及 A/B/C 的特殊失败行为
        # -------------------------------------------------------------------
        pending_release = []

        for p in normal_fail:
            tp = typ[p]
            if tp == 'X':
                continue

            af = app_fail[p]

            if tp == 'A':
                if af >= 0:
                    if af == w[p] - 1:
                        # 第 w 次失败：段末释放全部资源，之后继续普通申请
                        pending_release.append(p)
                        app_fail[p] = -1
                    else:
                        app_fail[p] = af + 1

            elif tp == 'B':
                if af >= 0:
                    if af == w[p] - 1:
                        # 第 w 次失败：放弃当前资源申请，直接进入该任务运行
                        state[p] = RUNNING
                        run_rem[p] = t[p][task[p]]
                        app_fail[p] = -1
                    else:
                        app_fail[p] = af + 1

            elif tp == 'C':
                if af >= 0:
                    # 普通失败累计；到 w 次后下一段首抢夺
                    app_fail[p] = af + 1

        # -------------------------------------------------------------------
        # 段中：运行中的进程获得收益
        # -------------------------------------------------------------------
        for i in range(1, n + 1):
            if state[i] == RUNNING:
                revenue[i] += held[i]

        # -------------------------------------------------------------------
        # 段末：运行任务推进 / 任务结束 / 进程结束
        # -------------------------------------------------------------------
        for i in range(1, n + 1):
            if state[i] == RUNNING:
                run_rem[i] -= 1
                if run_rem[i] == 0:
                    if task[i] == k[i] - 1:
                        state[i] = FINISHED
                        finish_seg[i] = seg
                        release_all(i)
                    else:
                        task[i] += 1
                        state[i] = APPLYING
                        app_fail[i] = 0 if typ[i] != 'X' else -1
                        run_rem[i] = 0

        # A 类在第 w 次失败后的段末释放
        for p in pending_release:
            release_all(p)

        seg += 1

    out = []
    for i in range(1, n + 1):
        if finish_seg[i] != -1:
            dur = finish_seg[i] - st[i] + 1
        else:
            dur = -1
        out.append(f"{revenue[i]} {dur}")

    return "\n".join(out)


# ---------------------------------------------------------------------------
# 测试框架
# ---------------------------------------------------------------------------

def normalize_tokens(s: str):
    return s.split()


def compare_output(expected: str, actual: str) -> bool:
    return normalize_tokens(expected) == normalize_tokens(actual)


def short_text(s: str, limit: int = 8000) -> str:
    if s is None:
        return "(空)"
    if len(s) <= limit:
        return s
    return s[:limit] + f"\n... （还有 {len(s) - limit} 个字符未显示） ..."


def make_diff(expected: str, actual: str) -> str:
    exp_lines = expected.splitlines()
    act_lines = actual.splitlines()
    return "\n".join(
        difflib.unified_diff(
            exp_lines,
            act_lines,
            fromfile="expected",
            tofile="actual",
            lineterm="",
        )
    )


def compile_main() -> str:
    cpp_file = "main.cpp"
    if not os.path.exists(cpp_file):
        print("错误：当前目录未找到 main.cpp")
        sys.exit(1)

    exe_name = "main_test.exe" if os.name == "nt" else "main_test.out"
    exe_path = os.path.abspath(exe_name)

    if os.path.exists(exe_path):
        try:
            os.remove(exe_path)
        except Exception:
            pass

    cxx = os.environ.get("CXX", "g++")
    base_flags = ["-O2"]

    # 优先按较接近 CCF 常见标准的 C++14 编译；
    # 若失败，再尝试 C++17 / C++20，方便本地排查。
    standards = ["-std=c++14", "-std=c++17", "-std=c++20"]
    last_error = ""

    for std in standards:
        cmd = [cxx, cpp_file, "-o", exe_path] + base_flags + [std]
        try:
            proc = subprocess.run(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
        except FileNotFoundError:
            print(f"错误：找不到编译器 {cxx}，请确认已安装 g++ 并加入 PATH")
            sys.exit(1)

        if proc.returncode == 0:
            if std != "-std=c++14":
                print(f"注意：使用 {std} 编译成功；若官方环境为 C++14，请确认代码在 C++14 下也可编译。")
            return exe_path

        last_error = proc.stderr.decode("utf-8", "replace")

    print("编译失败：")
    print(last_error)
    sys.exit(1)


def run_program(exe_path: str, input_text: str, timeout: float):
    try:
        proc = subprocess.run(
            [exe_path],
            input=input_text.encode("utf-8"),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout,
        )
        return (
            proc.returncode,
            proc.stdout.decode("utf-8", "replace"),
            proc.stderr.decode("utf-8", "replace"),
        )
    except subprocess.TimeoutExpired:
        return "timeout", "", f"超时（超过 {timeout} 秒）"


def safe_name(s: str) -> str:
    return "".join(ch if (ch.isalnum() or ch in "-_") else "_" for ch in s)


def check_case(
    exe_path: str,
    name: str,
    input_text: str,
    expected: str,
    timeout: float,
    save_prefix: str,
):
    rc, actual, err = run_program(exe_path, input_text, timeout)
    has_stderr = bool(err and err.strip())

    # ---------------- 超时 ----------------
    if rc == "timeout":
        detail = []
        detail.append("=" * 70)
        detail.append(f"测试用例：{name}")
        detail.append("-" * 70)
        detail.append("【输入】")
        detail.append(short_text(input_text))
        detail.append("-" * 70)
        detail.append("【期望输出（正确）】")
        detail.append(short_text(expected))
        detail.append("-" * 70)
        detail.append(f"【实际结果（错误）】程序超时：{err}")
        if has_stderr:
            detail.append("【程序 stderr】")
            detail.append(short_text(err))
        detail.append("=" * 70)
        return False, "\n".join(detail)

    # ---------------- 运行时错误 ----------------
    if rc != 0:
        detail = []
        detail.append("=" * 70)
        detail.append(f"测试用例：{name}")
        detail.append("-" * 70)
        detail.append("【输入】")
        detail.append(short_text(input_text))
        detail.append("-" * 70)
        detail.append("【期望输出（正确）】")
        detail.append(short_text(expected))
        detail.append("-" * 70)
        detail.append(f"【实际结果（错误）】程序运行时错误，返回码 {rc}")
        if has_stderr:
            detail.append("【程序 stderr】")
            detail.append(short_text(err))
        detail.append("=" * 70)
        return False, "\n".join(detail)

    # ---------------- 输出正确 ----------------
    if compare_output(expected, actual):
        if has_stderr:
            warn = []
            warn.append("-" * 70)
            warn.append(f"[注意] 用例 {name} 输出正确，但程序产生了 stderr 输出：")
            warn.append(short_text(err))
            warn.append("-" * 70)
            return True, "\n".join(warn)
        return True, ""

    # ---------------- 输出不一致 ----------------
    detail = []
    detail.append("=" * 70)
    detail.append(f"测试用例：{name}")
    detail.append("-" * 70)
    detail.append("【输入】")
    detail.append(short_text(input_text))
    detail.append("-" * 70)
    detail.append("【期望输出（正确）】")
    detail.append(short_text(expected))

    # 保存失败用例，方便复现
    try:
        with open(save_prefix + ".in", "w", encoding="utf-8") as f:
            f.write(input_text)
        with open(save_prefix + ".ans", "w", encoding="utf-8") as f:
            f.write(expected)
        with open(save_prefix + ".out", "w", encoding="utf-8") as f:
            f.write(actual)
        detail.append(
            f"（已保存失败用例：{save_prefix}.in / "
            f"{save_prefix}.ans / {save_prefix}.out）"
        )
    except Exception:
        pass

    detail.append("-" * 70)
    detail.append("【实际输出（错误）】")
    detail.append(short_text(actual))

    if has_stderr:
        detail.append("-" * 70)
        detail.append("【程序 stderr】")
        detail.append(short_text(stderr))

    detail.append("-" * 70)
    detail.append("【差异（expected vs actual）】")
    detail.append(short_text(make_diff(expected, actual)))
    detail.append("=" * 70)

    return False, "\n".join(detail)


# ---------------------------------------------------------------------------
# 内置测试
# ---------------------------------------------------------------------------

SAMPLE1_IN = """3 5
X 1 3 1 3 3 4 4 3
B 2 2 4 2 1 1 2 5 3 3 2
C 3 3 2 1 2 4 2
"""

SAMPLE1_OUT = """15 10
13 10
6 10
"""

SIMPLE_IN = """1 1
X 1 1 1 5
"""

# 修正：X 类，1 个资源，运行 5 段，每段收益 1 -> 总收益 5
SIMPLE_OUT = """5 5
"""

DEADLOCK_IN = """2 2
X 1 2 1 1 2 1
X 1 2 2 1 1 1
"""

DEADLOCK_OUT = """1 -1
1 -1
"""

C_FORCE_IN = """2 1
X 1 1 1 10
C 1 1 1 1 1
"""

C_FORCE_OUT = """1 10
1 2
"""

A_WAIT_IN = """2 1
X 1 1 1 10
A 1 1 1 1 1
"""

A_WAIT_OUT = """10 10
1 11
"""

MULTI_C_FORCE_IN = """3 1
X 1 1 1 10
C 1 2 1 1 1
C 1 2 1 1 1
"""

# 修正：p1 在段 1、段 2 各得 1 收益（共 2），段 3 起资源被 p3 抢走后收益为 0
MULTI_C_FORCE_OUT = """2 10
0 3
1 3
"""

BUILTIN_TESTS = [
    ("sample1", SAMPLE1_IN, SAMPLE1_OUT),
    ("simple_single_x", SIMPLE_IN, SIMPLE_OUT),
    ("deadlock_x", DEADLOCK_IN, DEADLOCK_OUT),
    ("c_force", C_FORCE_IN, C_FORCE_OUT),
    ("a_wait", A_WAIT_IN, A_WAIT_OUT),
    ("multi_c_force", MULTI_C_FORCE_IN, MULTI_C_FORCE_OUT),
]


# ---------------------------------------------------------------------------
# 随机输入生成
# ---------------------------------------------------------------------------

def random_input(rng: random.Random, profile: str, size: str) -> str:
    if size == "small":
        n = rng.randint(1, 4)
        m = rng.randint(1, 4)
        max_k = 2
        max_t = 3
        max_st = 3
        max_w = 3
    else:
        n = rng.randint(2, 6)
        m = rng.randint(2, 6)
        max_k = 4
        max_t = 5
        max_st = 6
        max_w = 5

    m = max(1, m)

    lines = [f"{n} {m}"]

    for _ in range(n):
        if profile == "xonly":
            tp = "X"
        elif profile == "noC":
            tp = rng.choice(["X", "A", "B"])
        elif profile == "C-heavy":
            tp = rng.choice(["C", "C", "X", "B"])
        else:
            tp = rng.choice(["X", "A", "B", "C"])

        k = rng.randint(1, min(max_k, m))
        st = rng.randint(1, max_st)

        resources = rng.sample(range(1, m + 1), k)
        parts = []

        if tp == "X":
            parts.append(tp)
            parts.append(str(st))
            parts.append(str(k))
        else:
            parts.append(tp)
            parts.append(str(st))
            parts.append(str(rng.randint(1, max_w)))
            parts.append(str(k))

        for res in resources:
            parts.append(str(res))
            parts.append(str(rng.randint(1, max_t)))

        lines.append(" ".join(parts))

    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------
# 主函数
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="Local checker for main.cpp")
    parser.add_argument("--num", type=int, default=80, help="随机测试数量")
    parser.add_argument("--seed", type=int, default=20260531, help="随机种子")
    parser.add_argument("--timeout", type=float, default=10.0, help="单次运行超时秒数")
    parser.add_argument("--no-random", action="store_true", help="不运行随机测试")
    args = parser.parse_args()

    exe_path = compile_main()
    print(f"编译成功：{exe_path}")
    print("-" * 70)

    passed = 0
    failed = 0
    skipped = 0
    stop = False  # 遇到第一个失败即停止后续测试

    # 1. 内置测试
    for name, inp, expected in BUILTIN_TESTS:
        if stop:
            break

        # 用参考模拟器交叉校验硬编码的期望值，若不一致则以参考模拟器为准
        try:
            ref_expected = solve_reference(inp)
            if ref_expected is not None and not compare_output(expected, ref_expected):
                print(
                    f"[WARN] builtin/{name} 硬编码期望输出与参考模拟器不一致，"
                    f"以参考模拟器为准\n"
                    f"  硬编码：{expected!r}\n"
                    f"  参考器：{ref_expected!r}"
                )
                expected = ref_expected
        except Exception as e:
            print(f"[WARN] builtin/{name} 参考模拟器异常：{e}，使用硬编码期望输出")

        ok, msg = check_case(
            exe_path,
            name,
            inp,
            expected,
            args.timeout,
            f"fail_{safe_name(name)}",
        )
        if ok:
            print(f"[PASS] builtin/{name}")
            if msg:
                print(msg)
            passed += 1
        else:
            print(f"[FAIL] builtin/{name}")
            print(msg)
            failed += 1
            stop = True

    # 2. 本地 *.in / *.ans
    if not stop:
        local_inputs = []
        local_inputs.extend(sorted(glob.glob("*.in")))
        local_inputs.extend(sorted(glob.glob(os.path.join("tests", "*.in"))))

        for in_path in local_inputs:
            if stop:
                break

            base = os.path.basename(in_path)
            ans_path = os.path.splitext(in_path)[0] + ".ans"

            try:
                with open(in_path, "r", encoding="utf-8") as f:
                    inp = f.read()
            except Exception as e:
                print(f"[FAIL] local/{base}")
                print(f"读入输入失败：{e}")
                failed += 1
                stop = True
                break

            expected = None
            source = ""

            if os.path.exists(ans_path):
                try:
                    with open(ans_path, "r", encoding="utf-8") as f:
                        expected = f.read()
                    source = "ans"
                except Exception as e:
                    print(f"[FAIL] local/{base}")
                    print(f"读入答案失败：{e}")
                    failed += 1
                    stop = True
                    break
            else:
                try:
                    expected = solve_reference(inp)
                    source = "reference"
                except Exception as e:
                    print(f"[FAIL] local/{base}")
                    print(f"参考模拟器异常：{e}")
                    failed += 1
                    stop = True
                    break

            if expected is None:
                print(f"[SKIP] local/{base}：参考模拟器无法在限制内完成")
                skipped += 1
                continue

            ok, msg = check_case(
                exe_path,
                base,
                inp,
                expected,
                args.timeout,
                f"fail_{safe_name(base)}",
            )

            if ok:
                print(f"[PASS] local/{base} ({source})")
                if msg:
                    print(msg)
                passed += 1
            else:
                print(f"[FAIL] local/{base} ({source})")
                print(msg)
                failed += 1
                stop = True
                break

    # 3. 随机对拍
    if not stop and not args.no_random and args.num > 0:
        rng = random.Random(args.seed)
        profiles = ["mixed", "xonly", "noC", "C-heavy"]

        for idx in range(args.num):
            if stop:
                break

            profile = profiles[idx % len(profiles)]
            size = "small" if idx % 3 == 0 else "medium"

            inp = random_input(rng, profile, size)

            try:
                expected = solve_reference(inp)
            except Exception as e:
                print(f"[FAIL] random_{idx:03d} ({profile}/{size})")
                print(f"参考模拟器异常：{e}")
                print(short_text(inp))
                failed += 1
                stop = True
                break

            if expected is None:
                print(f"[SKIP] random_{idx:03d} ({profile}/{size})：参考模拟器无法在限制内完成")
                skipped += 1
                continue

            ok, msg = check_case(
                exe_path,
                f"random_{idx:03d}",
                inp,
                expected,
                args.timeout,
                f"fail_random_{idx:03d}_{safe_name(profile)}_{size}",
            )

            if ok:
                print(f"[PASS] random_{idx:03d} ({profile}/{size})")
                if msg:
                    print(msg)
                passed += 1
            else:
                print(f"[FAIL] random_{idx:03d} ({profile}/{size})")
                print(msg)
                failed += 1
                stop = True
                break

    print("-" * 70)
    print(f"通过：{passed}")
    print(f"失败：{failed}")
    print(f"跳过：{skipped}")

    if failed:
        print("（遇到第一个失败即停止后续测试）")
        sys.exit(1)
    else:
        print("ALL TESTS PASSED")
        sys.exit(0)


if __name__ == "__main__":
    main()