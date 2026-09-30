import subprocess
import sys
import os
import random
import time

def compile_cpp():
    if not os.path.exists("main.cpp"):
        print("❌ 错误：未找到 main.cpp 文件！请确保当前目录下有该文件。")
        sys.exit(1)
        
    exe_name = "main"
    if sys.platform == "win32":
        exe_name = "main.exe"
    
    # 使用 C++14 标准，O2 优化，严格对齐 CCF CSP 官方环境
    compile_cmd = ["g++", "main.cpp", "-o", exe_name, "-O2", "-std=c++14"]
    print(f"⏳ 正在编译 main.cpp ...")
    result = subprocess.run(compile_cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("❌ 编译失败！请检查你的 C++ 语法：")
        print(result.stderr)
        sys.exit(1)
    print("✅ 编译成功！\n")
    return exe_name

def std_solve(input_data):
    """Python 标程，用于生成标准答案"""
    lines = input_data.strip().split('\n')
    n = int(lines[0].strip())
    a = []
    for line in lines[1:]:
        if line.strip():
            a.extend(list(map(int, line.split())))
            
    ans = 0
    for x in a:
        b = bin(x)[2:]
        if b.count('1') == b.count('0'):
            ans += 1
    return str(ans)

def generate_tests():
    """生成覆盖各种情况的测试用例"""
    tests = []
    
    # Test 1: 官方样例
    tests.append("3\n2 5 9\n")
    
    # Test 2: 边界情况 - 1 (二进制为1，1个1，0个0，非平衡)
    tests.append("1\n1\n") 
    
    # Test 3: 边界情况 - 2的幂次方
    tests.append("5\n2 4 8 16 32\n") 
    
    # Test 4: 小规模随机 (测试 50% 子任务: a_i <= 256)
    n = 10
    a = [random.randint(1, 256) for _ in range(n)]
    tests.append(f"{n}\n{' '.join(map(str, a))}\n")
    
    # Test 5: 全平衡数测试
    balanced_nums = []
    for i in range(1, 100000):
        b = bin(i)[2:]
        if b.count('1') == b.count('0'):
            balanced_nums.append(i)
    n = 50
    a = random.sample(balanced_nums, min(n, len(balanced_nums)))
    tests.append(f"{n}\n{' '.join(map(str, a))}\n")
    
    # Test 6: 全非平衡数测试
    not_balanced_nums = []
    for i in range(1, 100000):
        b = bin(i)[2:]
        if b.count('1') != b.count('0'):
            not_balanced_nums.append(i)
    n = 50
    a = random.sample(not_balanced_nums, min(n, len(not_balanced_nums)))
    tests.append(f"{n}\n{' '.join(map(str, a))}\n")
    
    # Test 7-16: 大规模随机测试 (测试 100% 子任务: n <= 100, a_i <= 10^9)
    for _ in range(10):
        n = random.randint(50, 100)
        a = [random.randint(1, 10**9) for _ in range(n)]
        tests.append(f"{n}\n{' '.join(map(str, a))}\n")
        
    # Test 17: 极限数据 N=100, 所有 a_i = 10^9
    n = 100
    a = [10**9] * n
    tests.append(f"{n}\n{' '.join(map(str, a))}\n")
    
    # Test 18: 大数平衡数测试
    large_balanced = []
    for i in range(100000, 200000):
        b = bin(i)[2:]
        if b.count('1') == b.count('0'):
            large_balanced.append(i)
    a = random.sample(large_balanced, min(100, len(large_balanced)))
    tests.append(f"{len(a)}\n{' '.join(map(str, a))}\n")

    return tests

def run_test(exe_name, input_data, test_id):
    start_time = time.time()
    try:
        if sys.platform == "win32":
            cmd = [f".\\{exe_name}"]
        else:
            cmd = [f"./{exe_name}"]
            
        # CSP 第一题通常为 1.0s 时间限制
        result = subprocess.run(
            cmd,
            input=input_data,
            capture_output=True,
            text=True,
            timeout=1.0 
        )
        elapsed = time.time() - start_time
        
        if result.returncode != 0:
            print(f"❌ Test {test_id}: RE (Runtime Error) | Time: {elapsed:.3f}s")
            print(f"   错误信息: {result.stderr.strip()}")
            return False
            
        actual_out = result.stdout.strip()
        expected_out = std_solve(input_data)
        
        # CSP 评测机会忽略行末空格和末尾换行，这里使用 strip() 模拟
        if actual_out == expected_out:
            print(f"✅ Test {test_id}: PASSED | Time: {elapsed:.3f}s")
            return True
        else:
            print(f"❌ Test {test_id}: WA (Wrong Answer) | Time: {elapsed:.3f}s")
            print(f"   输入数据:\n{input_data.strip()}")
            print(f"   期望输出: {expected_out}")
            print(f"   你的输出: {actual_out}")
            return False
            
    except subprocess.TimeoutExpired:
        print(f"❌ Test {test_id}: TLE (Time Limit Exceeded) | Time > 1.0s")
        return False
    except Exception as e:
        print(f"❌ Test {test_id}: ERROR | {e}")
        return False

def cleanup(exe_name):
    if os.path.exists("in.txt"): os.remove("in.txt")
    if os.path.exists(exe_name): os.remove(exe_name)
    if os.path.exists("main.exe"): os.remove("main.exe")

def main():
    print("="*60)
    print("      CCF CSP 202604-1 平衡数 本地黑盒评测脚本")
    print("="*60)
    exe_name = compile_cpp()
    tests = generate_tests()
    
    passed = 0
    total = len(tests)
    
    for i, test in enumerate(tests):
        if run_test(exe_name, test, i + 1):
            passed += 1
            
    cleanup(exe_name)
    
    print("\n" + "="*60)
    print(f" 📊 最终结果: {passed}/{total} 测试点通过。")
    if passed == total:
        print(" 🎉 恭喜！在本地模拟测试中表现完美，大概率可以AC！")
    else:
        print(" ⚠️ 很遗憾，仍有测试点未通过，请结合上方报错检查代码。")
    print("="*60)

if __name__ == "__main__":
    main()
