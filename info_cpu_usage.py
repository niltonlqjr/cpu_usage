import argparse

def mean(lst):
    return sum(lst)/len(lst)
    

myparser = argparse.ArgumentParser("Program to read output of cpu usage")
myparser.add_argument('-c', '--cpu-column', type=int, default=0, dest='cpu_usage_col', 
                      help='column that stores the objective')
myparser.add_argument('-i', '--id-column', type=int, default=1, dest='pid_col',
                      help='column of PID')
myparser.add_argument('input_file', type=str,
                      help='input filename')
args = myparser.parse_args()
print(args)

pid_col = args.pid_col
cpu_col = args.cpu_usage_col

tmp_logs = {}


with open(args.input_file) as f:
    line = '\n'
    while line != '':
        line = f.readline()
        spl = line.split()
        ult=max(pid_col,cpu_col)
        if len(spl) > ult:
            str_pid = spl[pid_col]
            str_usage = spl[cpu_col]
            try:
                pid = int(str_pid)
            except:
                raise ValueError("PID is not an integer value")
            
            try:
                cpu_usage = float(str_usage)
            except:
                raise ValueError("CPU usage is not a float value")
            
            cmd_lst = [spl[i] for i in range(len(spl)) if ((i != pid_col) and (i != cpu_col))]
            cmdline = ' '.join(cmd_lst)
            
            if pid in tmp_logs:
                tmp_logs[pid]['target'].append(cpu_usage)
                tmp_logs[pid]['line'].append(cmdline)
            else:
                tmp_logs[pid] = {}
                tmp_logs[pid]['target']=[cpu_usage]
                tmp_logs[pid]['line']=[cmdline]
        else:
            print(f"skipping line:{line} because it has not enought columns")


logs={}

for pid in tmp_logs:
    if len(tmp_logs[pid]['target']) > 1:
       logs[pid]=tmp_logs[pid]

for pid in logs:
    print('process:',pid,'\nmean_usage:',mean(logs[pid]['target']),'\ncommand:',logs[pid]['line'][0])
    print('===========')

