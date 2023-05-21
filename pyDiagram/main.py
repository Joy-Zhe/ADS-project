import pandas as pd
import matplotlib.pyplot as plt

# 读取CSV文件
data = pd.read_csv('results.csv')

# 创建两个子图：一个用于比较高度，一个用于比较时间
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)

# height ans
ax1.plot(data[data['algorithm'] == 'FFDH']['n'], data[data['algorithm'] == 'FFDH']['height'], label='FFDH')
ax1.plot(data[data['algorithm'] == 'NFDH']['n'], data[data['algorithm'] == 'NFDH']['height'], label='NFDH')
ax1.plot(data[data['algorithm'] == 'SF']['n'], data[data['algorithm'] == 'SF']['height'], label='SF')
ax1.set_ylabel('Height')
ax1.legend()

# algorithm times
ax2.plot(data[data['algorithm'] == 'FFDH']['n'], data[data['algorithm'] == 'FFDH']['time'], label='FFDH')
ax2.plot(data[data['algorithm'] == 'NFDH']['n'], data[data['algorithm'] == 'NFDH']['time'], label='NFDH')
ax2.plot(data[data['algorithm'] == 'SF']['n'], data[data['algorithm'] == 'SF']['time'], label='SF')
ax2.set_xlabel('n')
ax2.set_ylabel('Time')
ax2.legend()

# 显示图形
plt.show()
