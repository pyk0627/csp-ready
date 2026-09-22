#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test.py — 202606-4 石子游戏 本地检验脚本 (v2)

v2 变化：
1. 失败不再写文件，直接在终端打印详细信息（原因/用时/输入/期望/实际）。
2. PASS 默认带用时；汇总给出总用时与最慢测试点。
3. 默认即官方限制：c++14 / 1.0s / 512MB；cpp 默认 main.cpp。
   平时只需:  python test.py
   性能测试:  python test.py --full
"""

import argparse
import io
import os
import random
import shutil
import subprocess
import sys
import tempfile
import time
from array import array
from pathlib import Path

try:
    import resource
except ImportError:
    resource = None


class StopTesting(Exception):
    pass


def make_preexec(mem_mb: int):
    if os.name != "posix" or resource is None or mem_mb <= 0:
        return None

    def preexec():
        try:
            mem = mem_mb * 1024 * 1024
            resource.setrlimit(resource.RLIMIT_AS, (mem, mem))
        except Exception:
            pass

    return preexec


def brute_solve(b, queries):
    n = len(b) - 1
    px0 = [0] * (n + 1)
    px1 = [0] * (n + 1)
    for i in range(1, n + 1):
        px0[i] = px0[i - 1]
        px1[i] = px1[i - 1]
        if i & 1:
            px1[i] ^= b[i]
        else:
            px0[i] ^= b[i]

    ans = []
    for L, R in queries:
        length = R - L + 1
        dp = [0] * (length + 1)
        for e in range(length):
            i = L + e
            best = dp[e]
            for s in range(e + 1):
                l = L + s
                if l & 1:
                    ok = (px1[i] == px1[l - 1])
                else:
                    ok = (px0[i] == px0[l - 1])
                if ok:
                    cand = dp[s] + 1
                    if cand > best:
                        best = cand
            dp[e + 1] = best
        ans.append(dp[length])
    return ans


def solve_fast(b, queries):
    n = len(b) - 1
    if n == 0:
        return [0 for _ in queries]

    INF = n + 2
    size = n + 2
    typecode = "I" if array("I").itemsize >= 4 else "Q"
    if INF > 0xFFFFFFFF:
        typecode = "Q"

    best = array(typecode, [INF]) * size

    for start, m in ((1, (n + 1) // 2), (2, n // 2)):
        if m == 0:
            continue
        after = [0] * m
        x = 0
        pos = start
        for t in range(m):
            x ^= b[pos]
            after[t] = x
            pos += 2

        last = {}
        for t in range(m - 1, -1, -1):
            last[after[t]] = t
            val_before = 0 if t == 0 else after[t - 1]
            j = last.get(val_before)
            if j is not None:
                best[start + 2 * t] = start + 2 * j
        del after, last

    LOG = max(1, (n + 1).bit_length())
    up0 = array(typecode, [INF]) * size
    up0[0] = 0
    cur_min = INF
    for i in range(n, 0, -1):
        if best[i] < cur_min:
            cur_min = best[i]
        if cur_min <= n:
            up0[i] = cur_min + 1
    up0[n + 1] = INF
    del best

    up = [up0]
    limit_index = n + 1
    idx_range = range(1, size)
    for _ in range(1, LOG):
        prev = up[-1]
        curr = array(typecode, [INF]) * size
        curr[0] = 0
        for i in idx_range:
            mid = prev[i]
            if mid <= limit_index:
                curr[i] = prev[mid]
        up.append(curr)

    pows = [1 << k for k in range(LOG)]
    ans = []
    for L, R in queries:
        limit = R + 1
        cur = L
        cnt = 0
        for k in range(LOG - 1, -1, -1):
            nx = up[k][cur]
            if nx <= limit:
                cnt += pows[k]
                cur = nx
        ans.append(cnt)
    return ans


def format_input(b, queries):
    n = len(b) - 1
    q = len(queries)
    buf = io.StringIO()
    buf.write(f"{n} {q}\n")
    buf.write(" ".join(map(str, b[1:])))
    buf.write("\n")
    for L, R in queries:
        buf.write(f"{L} {R}\n")
    return buf.getvalue()


def parse_input(text: str):
    data = text.split()
    if len(data) < 2:
        raise ValueError("输入太短，无法读取 n 和 q")
    it = iter(data)
    n = int(next(it))
    q = int(next(it))
    b = [0] * (n + 1)
    for i in range(1, n + 1):
        b[i] = int(next(it))
    queries = []
    for _ in range(q):
        L = int(next(it))
        R = int(next(it))
        queries.append((L, R))
    return n, q, b, queries


def compare_output(actual: str, expected_tokens, token_only=False):
    expected_tokens = list(expected_tokens)

    if token_only:
        actual_tokens = actual.split()
        if actual_tokens == expected_tokens:
            return True, ""
        if len(actual_tokens) != len(expected_tokens):
            return False, (f"token 数不匹配：期望 {len(expected_tokens)} 个，"
                           f"实际 {len(actual_tokens)} 个")
        for i, (e, a) in enumerate(zip(expected_tokens, actual_tokens), 1):
            if e != a:
                return False, f"第 {i} 个输出（第 {i} 个询问）：期望 {e}，实际 {a}"
        return False, "输出不一致"

    if not expected_tokens:
        if actual.strip() == "":
            return True, ""
        return False, "期望无输出，但实际有输出"

    text = actual.replace("\r\n", "\n").replace("\r", "\n")
    if text.endswith("\n"):
        text = text[:-1]
    lines = text.split("\n")

    if len(lines) != len(expected_tokens):
        return False, (f"行数不匹配：期望 {len(expected_tokens)} 行，"
                       f"实际 {len(lines)} 行（多了/少了输出行）")

    for idx, (line, tok) in enumerate(zip(lines, expected_tokens), 1):
        if line.strip() != tok:
            return False, f"第 {idx} 行（第 {idx} 个询问）：期望 '{tok}'，实际 '{line.strip()}'"
    return True, ""


def run_program(cmd, input_text: str, time_limit: float, mem_mb: int):
    kwargs = {
        "stdout": subprocess.PIPE,
        "stderr": subprocess.PIPE,
        "input": input_text.encode("utf-8"),
    }
    pre = make_preexec(mem_mb)
    if pre is not None:
        kwargs["preexec_fn"] = pre

    start = time.perf_counter()
    try:
        proc = subprocess.run(cmd, timeout=time_limit + 1.0, **kwargs)
    except subprocess.TimeoutExpired:
        return False, "", f"时间超限（>{time_limit}s，被强制终止）", time_limit, None
    except Exception as e:
        return False, "", f"运行失败：{e}", time.perf_counter() - start, None
    elapsed = time.perf_counter() - start

    if elapsed > time_limit + 0.2:
        return False, "", (f"时间超限：实际 {elapsed:.3f}s > 限制 {time_limit}s"), elapsed, proc.returncode
    if proc.returncode != 0:
        err = proc.stderr.decode("utf-8", errors="replace")
        return False, "", (f"运行时错误，退出码 {proc.returncode}\n"
                           f"stderr 尾部:\n{err[-1000:]}"), elapsed, proc.returncode

    out = proc.stdout.decode("utf-8", errors="replace")
    return True, out, "", elapsed, proc.returncode


def compile_cpp(src: str, std: str, out_path: str, extra_flags):
    cmd = ["g++", "-O2", "-Wall", f"-std={std}", "-o", out_path, src]
    cmd.extend(extra_flags)
    try:
        proc = subprocess.run(cmd, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE, timeout=120)
    except FileNotFoundError:
        return False, "未找到 g++。"
    except subprocess.TimeoutExpired:
        return False, "编译超时。"
    if proc.returncode != 0:
        return False, proc.stderr.decode("utf-8", errors="replace")
    return True, ""


def random_value(rng: random.Random, mode: int):
    if mode == 0:
        return rng.randint(0, 1)
    if mode == 1:
        return rng.randint(0, 7)
    if mode == 2:
        return 0 if rng.random() < 0.5 else rng.randint(0, 7)
    return rng.getrandbits(31)


def generate_case(rng, n, q):
    mode = rng.randint(0, 3)
    b = [0] + [random_value(rng, mode) for _ in range(n)]
    queries = []
    for _ in range(q):
        L = rng.randint(1, n)
        R = rng.randint(L, n)
        queries.append((L, R))
    return b, queries


def generate_medium_case(rng, n, q):
    r = rng.random()
    if r < 0.10:
        vals = [0] * n
    elif r < 0.35:
        vals = [0 if rng.random() < 0.5 else rng.getrandbits(31) for _ in range(n)]
    else:
        vals = [rng.getrandbits(31) for _ in range(n)]
    b = [0] + vals
    queries = []
    for _ in range(q):
        L = rng.randint(1, n)
        R = rng.randint(L, n)
        queries.append((L, R))
    return b, queries


def indent_block(title, text, max_lines=60):
    if text is None:
        text = ""
    text = text.rstrip("\n")
    lines = text.split("\n") if text != "" else ["<空>"]
    if len(lines) > max_lines:
        head = lines[:max_lines - 6]
        tail = lines[-5:]
        lines = head + [f"...（省略 {len(lines) - len(head) - len(tail)} 行）..."] + tail
    out = [f"  {title}:"]
    out.extend("    | " + l for l in lines)
    return "\n".join(out)


def main():
    parser = argparse.ArgumentParser(
        description="本地检验 202606-4 石子游戏 C++ 代码",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("cpp", nargs="?", default="main.cpp")
    parser.add_argument("--exe", default=None)
    parser.add_argument("--std", default="c++14")
    parser.add_argument("--cpp-flags", default="")
    parser.add_argument("--time-limit", type=float, default=1.0)
    parser.add_argument("--mem-limit", type=int, default=512)
    parser.add_argument("--seed", type=int, default=20260604)
    parser.add_argument("--random-tests", type=int, default=50)
    parser.add_argument("--max-n", type=int, default=8)
    parser.add_argument("--max-q", type=int, default=8)
    parser.add_argument("--medium-tests", type=int, default=20)
    parser.add_argument("--medium-n", type=int, default=200)
    parser.add_argument("--medium-q", type=int, default=200)
    parser.add_argument("--test-dir", default=None)
    parser.add_argument("--max-expected-n", type=int, default=300000)
    parser.add_argument("--force-expected", action="store_true")
    parser.add_argument("--perf", action="store_true")
    parser.add_argument("--perf-n", type=int, default=200000)
    parser.add_argument("--perf-q", type=int, default=200000)
    parser.add_argument("--full", action="store_true",
                        help="等价于 --perf --perf-n 1000000 --perf-q 1000000")
    parser.add_argument("--token-compare", action="store_true")
    parser.add_argument("--quiet", action="store_true", help="只打印失败和汇总")
    parser.add_argument("--keep-going", action="store_true")
    parser.add_argument("--skip-sample", action="store_true")
    parser.add_argument("--skip-edge", action="store_true")
    parser.add_argument("--skip-random", action="store_true")
    parser.add_argument("--skip-medium", action="store_true")
    args = parser.parse_args()

    if args.full:
        args.perf = True
        args.perf_n = 1000000
        args.perf_q = 1000000

    tmpdir = None
    if args.exe:
        exe_path = args.exe
        if not Path(exe_path).exists():
            print(f"[ERROR] 可执行文件不存在: {exe_path}")
            sys.exit(1)
    else:
        if not Path(args.cpp).exists():
            print(f"[ERROR] C++ 源文件不存在: {args.cpp}")
            sys.exit(1)
        tmpdir = tempfile.mkdtemp(prefix="stone_check_")
        exe_path = os.path.join(tmpdir, "main.exe")
        ok, msg = compile_cpp(args.cpp, args.std, exe_path,
                              args.cpp_flags.split() if args.cpp_flags else [])
        if not ok:
            shutil.rmtree(tmpdir, ignore_errors=True)
            print("[COMPILE FAIL]")
            print(msg)
            sys.exit(1)
        print(f"[COMPILE] OK (g++ -O2 -Wall -std={args.std})")

    total = passed = failed = 0
    stop = False
    case_times = []

    def report(ok, name, msg="", detail="", elapsed=None):
        nonlocal total, passed, failed, stop
        total += 1
        if elapsed is not None:
            case_times.append((name, elapsed))
        if ok:
            passed += 1
            if not args.quiet:
                suffix = f" ({elapsed:.3f}s)" if elapsed is not None else ""
                print(f"[PASS] {name}{suffix}")
        else:
            failed += 1
            print(f"[FAIL] {name}")
            print(f"  reason : {msg}")
            if detail:
                print(detail)
            if not args.keep_going:
                stop = True

    def run_and_check(name, input_text, expected_tokens, token_only=False):
        expected_tokens = [str(x) for x in expected_tokens]
        expected_text = "\n".join(expected_tokens) + ("\n" if expected_tokens else "")

        ok, out, msg, elapsed, _ = run_program([exe_path], input_text,
                                               args.time_limit, args.mem_limit)
        if not ok:
            detail = "\n".join([
                indent_block("input", input_text),
                indent_block("expected", expected_text),
                indent_block("actual", out),
            ])
            report(False, name, msg, detail, elapsed)
            return False

        ok2, msg2 = compare_output(out, expected_tokens, token_only or args.token_compare)
        if ok2:
            report(True, name, "", "", elapsed)
            return True

        detail = "\n".join([
            indent_block("input", input_text),
            indent_block("expected", expected_text),
            indent_block("actual", out),
        ])
        report(False, name, msg2, detail, elapsed)
        return False

    def internal_error(tag, input_text, exp, got):
        print(f"[INTERNAL ERROR] 内置快速标程与暴力标程不一致（{tag}），脚本自身有 bug")
        print(indent_block("input", input_text))
        print(indent_block("brute", "\n".join(map(str, exp))))
        print(indent_block("fast", "\n".join(map(str, got))))
        sys.exit(2)

    rng = random.Random(args.seed)

    try:
        if not args.skip_sample:
            sample_in = "4 2\n1 2 1 0\n2 3\n1 4\n"
            run_and_check("sample/1", sample_in, ["0", "2"])
            if stop:
                raise StopTesting

        if not args.skip_edge:
            edge_cases = [
                ([0], [(1, 1)]),
                ([1], [(1, 1)]),
                ([0, 0], [(1, 1), (2, 2), (1, 2)]),
                ([1, 1], [(1, 1), (2, 2), (1, 2)]),
                ([1, 0], [(1, 2), (2, 2)]),
                ([0, 1], [(1, 2), (1, 1)]),
                ([1, 2, 1, 0], [(2, 3), (1, 4)]),
                ([1, 0, 1], [(1, 3), (2, 2), (1, 2), (2, 3)]),
                ([0, 1, 0], [(1, 3), (2, 3), (1, 2)]),
                ([0, 0, 0, 0, 0], [(1, 5), (2, 4), (3, 3), (1, 1), (2, 5)]),
                ([1, 2, 3, 4, 5], [(1, 5), (2, 5), (1, 4)]),
                ([(1 << 31) - 1, 0, (1 << 31) - 1], [(1, 3), (1, 1), (2, 2), (3, 3)]),
            ]
            for idx, (vals, qs) in enumerate(edge_cases, 1):
                b = [0] + vals
                input_text = format_input(b, qs)
                expected = brute_solve(b, qs)
                fast = solve_fast(b, qs)
                if fast != expected:
                    internal_error(f"edge/{idx}", input_text, expected, fast)
                run_and_check(f"edge/{idx}", input_text, expected)
                if stop:
                    raise StopTesting

        if not args.skip_random:
            if not args.quiet:
                print("[RANDOM SMALL] 随机小数据对拍中...")
            for t in range(1, args.random_tests + 1):
                n = rng.randint(1, args.max_n)
                q = rng.randint(1, args.max_q)
                b, queries = generate_case(rng, n, q)
                input_text = format_input(b, queries)
                expected = brute_solve(b, queries)
                fast = solve_fast(b, queries)
                if fast != expected:
                    internal_error(f"random-small/{t}", input_text, expected, fast)
                run_and_check(f"random-small/{t}", input_text, expected)
                if stop:
                    raise StopTesting

        if not args.skip_medium:
            if not args.quiet:
                print("[RANDOM MEDIUM] 随机中等数据对拍中...")
            for t in range(1, args.medium_tests + 1):
                n = rng.randint(1, args.medium_n)
                q = rng.randint(1, args.medium_q)
                b, queries = generate_medium_case(rng, n, q)
                input_text = format_input(b, queries)
                expected = solve_fast(b, queries)
                run_and_check(f"random-medium/{t}", input_text, expected)
                if stop:
                    raise StopTesting

        if args.perf:
            n, q = args.perf_n, args.perf_q
            if n <= 0 or q <= 0:
                print("[PERF] 跳过：n/q 必须为正")
            else:
                print(f"[PERF] 生成大数据 n={n}, q={q} ...")
                b = [0] * (n + 1)
                for i in range(1, n + 1):
                    b[i] = 0 if rng.random() < 0.15 else rng.getrandbits(31)
                queries = []
                for _ in range(q):
                    L = rng.randint(1, n)
                    R = rng.randint(L, n)
                    queries.append((L, R))
                if queries:
                    queries[0] = (1, n)
                print("[PERF] 内置标程计算期望答案...")
                t0 = time.perf_counter()
                expected = solve_fast(b, queries)
                print(f"[PERF] 期望答案完成，用时 {time.perf_counter() - t0:.2f}s")
                input_text = format_input(b, queries)
                run_and_check("perf/large", input_text, expected)
                if stop:
                    raise StopTesting

        if args.test_dir:
            td = Path(args.test_dir)
            if not td.is_dir():
                print(f"[ERROR] test-dir 不是目录: {args.test_dir}")
            else:
                files = sorted(td.glob("*.in"))
                if not files:
                    print(f"[WARN] {args.test_dir} 下没有 .in 文件")
                for in_file in files:
                    name = f"dir/{in_file.stem}"
                    input_text = in_file.read_text(encoding="utf-8")
                    ans_file = in_file.with_suffix(".ans")
                    if not ans_file.exists():
                        ans_file = in_file.with_suffix(".out")
                    if ans_file.exists():
                        expected_tokens = ans_file.read_text(encoding="utf-8").split()
                    else:
                        try:
                            head = input_text.split(maxsplit=2)
                            n_only = int(head[0])
                        except Exception as e:
                            report(False, name, f"无法解析输入: {e}",
                                   indent_block("input", input_text))
                            if stop:
                                raise StopTesting
                            continue
                        if n_only > args.max_expected_n and not args.force_expected:
                            print(f"[SKIP] {name}: n={n_only} 过大且无答案文件")
                            continue
                        print(f"[INFO] {name}: 内置标程计算期望答案...")
                        try:
                            n, q, b, queries = parse_input(input_text)
                            expected_tokens = [str(x) for x in solve_fast(b, queries)]
                        except Exception as e:
                            report(False, name, f"计算期望答案失败: {e}",
                                   indent_block("input", input_text))
                            if stop:
                                raise StopTesting
                            continue
                    run_and_check(name, input_text, expected_tokens)
                    if stop:
                        raise StopTesting

    except StopTesting:
        pass
    finally:
        if tmpdir:
            shutil.rmtree(tmpdir, ignore_errors=True)

    print("=" * 60)
    print(f"Total: {total}, Passed: {passed}, Failed: {failed}")
    if case_times:
        tot = sum(t for _, t in case_times)
        slow_name, slow_t = max(case_times, key=lambda x: x[1])
        print(f"程序总用时: {tot:.3f}s | 最慢测试点: {slow_name} ({slow_t:.3f}s)")
    if failed == 0:
        print("Result: ALL CHECKS PASSED")
        sys.exit(0)
    else:
        print("Result: CHECKS FAILED")
        sys.exit(1)


if __name__ == "__main__":
    main()
