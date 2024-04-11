import subprocess

# 地图文件路径
maps = ['3']
# 要分析的程序路径
projects = ['x64\Debug\project.exe']

for project in projects:
    print(project)
    for map in maps:
        map_file_path = fr"maps\map{map}.txt"
        command = [r"../windows/SemiFinalJudge.exe", "-m", map_file_path, project,'-l', 'NONE', '-s','45']

        result = subprocess.run(command, check=True)
        if result.returncode == 0:
            print("执行成功")
        else:
            print(f"执行失败，返回码：{result.returncode}")
    # 执行命令并等待它完成
