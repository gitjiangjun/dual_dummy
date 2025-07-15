#!/bin/bash

# 自动化构建脚本 for Ubuntu 22.04 and ROS 2
# 功能：
# 1. 先单独构建 dummy2_description 包
# 2. 然后并行构建其他包（4个worker）
# 3. 最后自动 source 安装文件

set -e  # 遇到错误立即退出


# 第一步：单独构建 dummy2_description
echo -e "\n\033[1;36m第一步：构建 dummy2_description 包...\033[0m"
colcon build --packages-select dummy2_description
if [ $? -ne 0 ]; then
    echo -e "\033[1;31m构建 dummy2_description 失败！\033[0m"
    exit 1
fi

# 第二步：并行构建其他包（4个worker）
echo -e "\n\033[1;36m第二步：并行构建其他包（4 workers）...\033[0m"
colcon build --parallel-workers 4 --event-handlers console_direct+
if [ $? -ne 0 ]; then
    echo -e "\033[1;31m并行构建失败！\033[0m"
    exit 1
fi

# 第三步：自动source安装文件
echo -e "\n\033[1;36m第三步：设置环境变量...\033[0m"
source install/setup.bash
if [ $? -ne 0 ]; then
    echo -e "\033[1;31mSource 失败！\033[0m"
    exit 1
fi

echo -e "\n\033[1;32m所有步骤完成！环境已准备好使用。\033[0m"
