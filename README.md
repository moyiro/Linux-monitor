# Linux-monitor
## 项目背景
本项目旨在开发一个监控Linux服务器性能的分布式应用，通过RPC实时获取远程服务器的运行状态，并通过QT界面对服务器性能进行分析和展示。目前已实现CPU使用率、负载、软中断、内存使用率和网络流量的监控。


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
