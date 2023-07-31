# Linux-monitor
## 项目介绍
本项目旨在开发一个实时监控Linux服务器性能的分布式应用。将该应用部署在本地客户端和多台远程Linux服务器上，以实现对服务器性能的实时监控和图形化界面展示。
<br />
**目前已实现的监控模块有：**
1. CPU使用率
2. 负载
3. 软中断
4. 内存使用率和网络流量的监控。
<br />
**本项目架构图如下：**
![image]()

## 安装
### Linux环境（ubuntu） <br />
需要~3GB磁盘空间
* 安装docker
    ```shell
    sudo apt install docker
* 下载QT安装包，解压并移入`docker/build/qt/`目录下
* 构建docker镜像
    ```shell
    cd docker/build
    docker build --network host -f base.dockerfile .
* 进入docker容器
     ```shell
     # 启动容器
     ./monitor_docker_run.sh
     # 进入容器
     ./monitor_docker_into.sh
 * 编译代码
      ```shell
      cd /work/cmake
      cmake ..
      make -j4
## 测试
提供对本机性能监控的测试程序
1. 运行grpc服务端和monitor进程
   ```shell
   cd /work/cmake/rpc_manager
   ./server
   cd /work/cmake/test_monitor
   ./monitor
2. 打开客户端监控界面
   ``` shell
   cd /work/cmake/display_monitor
   ./display
## 效果
<br />
![image](https://github.com/moyiro/Linux-monitor/blob/master/IMG/CPU%20monitor.png)
