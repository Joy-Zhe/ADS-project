import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# 读取CSV文件
data = pd.read_csv('SF.csv')

# 获取矩形数据
rect_data = data[data['Rectangle'] == 'R']

# 创建图形和坐标轴
fig, ax = plt.subplots(figsize=(10, 10), dpi=600)
ax.set_aspect('auto')

# 设置坐标轴范围
ax.set_xlim(0, 1)  # 设置X轴范围
ax.set_ylim(0, 40)  # 设置Y轴范围

# 绘制矩形
for index, row in rect_data.iterrows():
    width = row['Width']
    height = row['Height']
    x = row['X']
    y = row['Y']
    rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='black', facecolor='blue')
    ax.add_patch(rect)

# 设置图形标题和轴标签
ax.set_title('SF Visualization')
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig('SF_visualization.png', dpi=600)
#NFDH
# 读取CSV文件
data = pd.read_csv('NFDH.csv')

# 获取矩形数据
rect_data = data[data['Rectangle'] == 'R']

# 创建图形和坐标轴
fig, ax = plt.subplots(figsize=(10, 10), dpi=600)
ax.set_aspect('auto')

# 设置坐标轴范围
ax.set_xlim(0, 1)  # 设置X轴范围
ax.set_ylim(0, 40)  # 设置Y轴范围

# 绘制矩形
for index, row in rect_data.iterrows():
    width = row['Width']
    height = row['Height']
    x = row['X']
    y = row['Y']
    rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='black', facecolor='blue')
    ax.add_patch(rect)

# 设置图形标题和轴标签
ax.set_title('NFDH Visualization')
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig('NFDH_visualization.png', dpi=600)

#FFDH
data = pd.read_csv('FFDH.csv')

# 获取矩形数据
rect_data = data[data['Rectangle'] == 'R']

# 创建图形和坐标轴
fig, ax = plt.subplots(figsize=(10, 10), dpi=600)
ax.set_aspect('auto')

# 设置坐标轴范围
ax.set_xlim(0, 1)  # 设置X轴范围
ax.set_ylim(0, 40)  # 设置Y轴范围

# 绘制矩形
for index, row in rect_data.iterrows():
    width = row['Width']
    height = row['Height']
    x = row['X']
    y = row['Y']
    rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='black', facecolor='blue')
    ax.add_patch(rect)

# 设置图形标题和轴标签
ax.set_title('FFDH Visualization')
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig('FFDH_visualization.png', dpi=600)


# time and height
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
plt.savefig('time_height_visualization.png', dpi=600)