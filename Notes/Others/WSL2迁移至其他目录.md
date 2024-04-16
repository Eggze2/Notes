WSL2迁移至其他目录
(1) 管理员身份运行PowerShell，执行：
wsl -l -v
(2) 停止正在运行的wsl

wsl --shutdown

(3) 将需要迁移的Linux，进行导出

wsl --export Ubuntu D:/ubuntu.tar

(4) 导出完成之后，将原有的Linux卸载

wsl --unregister Ubuntu

(5) 将导出的文件放到需要保存的地方，进行导入即可

wsl --import Ubuntu D:\ubuntu\ D:\ubuntu.tar --version 2

(6) 设置默认用户
ubuntu.exe config --default-user <username>  
如果是ubuntu20.04 就是ubuntu2004.exe