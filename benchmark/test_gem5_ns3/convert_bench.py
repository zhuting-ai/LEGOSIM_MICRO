import sys

def convert(input_file, output_file):
    header = "taskId,sourceNode,destNode,dataSize(Byte),opType,priority,delay,phaseId,dependOnPhases\n"
    
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        f_out.write(header)
        
        for i, line in enumerate(f_in):
            parts = line.split()
            if len(parts) < 5:
                continue
            
            # 提取字段 (注意: 根据你提供的 bench.txt 样例)
            # 71132500 71134500 0 1 2 0
            # [0]创建时间 [1]注入时间 [2]源 [3]目的 [4]大小 [5]类型
            src = parts[2]
            dst = parts[3]
            size = int(parts[4]) * 64  # 如果是 flit，通常转为 64 字节
            # 假设 bench.txt 的单位是 ps (10^-12)，ns3 需要 ns
            injection_time_ns = int(int(parts[0]) / 100)
		            
            # 组装为 traffic.csv 格式
            new_line = f"{i},{src},{dst},{size},URMA_WRITE,7,{injection_time_ns}ns,0,\n"
            f_out.write(new_line)

    print(f"Successfully converted {input_file} to {output_file}")

if __name__ == "__main__":
    import os
    import sys

    # 1. 获取脚本文件所在的绝对路径（即 test_gem5 目录）
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 2. 拼接出文件的绝对路径
    input_path = os.path.join(script_dir, 'bench.txt')
    output_path = os.path.join(script_dir, 'traffic.csv')

    # 3. 打印一下，方便在 log 里调试
    print(f"Reading from: {input_path}")
    
    if not os.path.exists(input_path):
        print(f"Error: {input_path} not found!")
        sys.exit(1)

    convert(input_path, output_path)
