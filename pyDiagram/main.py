import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# 读取CSV文件
data = pd.read_csv('results.csv')

# 获取矩形数据
rect_data = data[data['Rectangle'] == 'R']

# 创建图形和坐标轴
fig, ax = plt.subplots(figsize=(10, 10), dpi=600)
ax.set_aspect('auto')

# 设置坐标轴范围
ax.set_xlim(0, 1)  # 设置X轴范围
ax.set_ylim(0, 1000)  # 设置Y轴范围

# 绘制矩形
for index, row in rect_data.iterrows():
    width = row['Width']
    height = row['Height']
    x = row['X']
    y = row['Y']
    rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='black', facecolor='blue')
    ax.add_patch(rect)

# 设置图形标题和轴标签
ax.set_title('Rectangle Visualization')
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig('rectangle_visualization.png', dpi=600)
# 显示图形
# plt.show()
