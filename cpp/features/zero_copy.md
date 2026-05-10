在高性能计算（HPC）、多媒体处理和分布式存储中，传统的内存拷贝（CPU Copy）往往是性能瓶颈。你提到的这三项技术本质上都是为了实现 **Zero-copy（零拷贝）** 或 **Direct Data Access（直接数据访问）**。

简单来说，它们的关系就像是：`mmap` 是基础搬运工，`dmabuf` 是跨设备的搬运桥梁，而 `ibverbs` 是跨网络的瞬移阵法。

---

## 1. mmap (Memory Map)
`mmap` 是最基础的技术，它将文件或设备直接映射到进程的虚拟地址空间。

* **原理**：它让你可以像操作内存数组一样操作文件，跳过了用户态和内核态之间的 `read/write` 缓冲区拷贝。
* **应用场景**：大文件处理、进程间通信（Shared Memory）。

### 代码示例
```cpp
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void mmap_example() {
    int fd = open("data.bin", O_RDWR);
    size_t size = 4096;
    
    // 将文件映射到内存
    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    // 像操作内存一样读写文件
    static_cast<char*>(addr)[0] = 'H';
    
    munmap(addr, size);
    close(fd);
}
```

---

## 2. dmabuf (DMA Buffer)
`dmabuf` 是 Linux 内核中用于 **跨设备共享内存** 的机制。

* **原理**：它引入了一个文件描述符（fd）来代表一块物理内存。比如，摄像头驱动采集到的图像数据，可以通过 `dmabuf` 直接传给 GPU 进行渲染，而不需要 CPU 把数据在内存里搬来搬去。
* **核心关键词**：**Sharing（共享）**。它定义了谁是 Buffer 的生产者，谁是消费者。



---

## 3. ibverbs (InfiniBand Verbs)
`ibverbs` 是 **RDMA（远程直接内存访问）** 的编程接口。

* **原理**：它最硬核的地方在于 **内存注册（Memory Registration, MR）**。在数据传输前，必须先调用 `ibv_reg_mr` 锁定一片内存。
    * **锁定物理页**：防止操作系统把这块内存交换到磁盘（Swap）。
    * **权限授权**：给网卡（HCA）权限，让网卡直接绕过 CPU 去读写这块内存。
* **应用场景**：高性能计算集群、分布式数据库。

### 代码示例（内存注册片段）
```cpp
#include <infiniband/verbs.h>

void ibv_example(void* ptr, size_t size, ibv_pd* pd) {
    // 注册内存：MR（Memory Region）
    // 只有注册过的内存，RDMA 网卡才能直接访问
    struct ibv_mr* mr = ibv_reg_mr(pd, ptr, size, 
                                   IBV_ACCESS_LOCAL_WRITE | 
                                   IBV_ACCESS_REMOTE_READ);
    
    if (mr) {
        printf("Memory registered with key: %u\n", mr->rkey);
    }
}
```

---

## 三者对比总结

| 技术 | 核心解决的问题 | 操作主体 | 关键点 |
| :--- | :--- | :--- | :--- |
| **mmap** | 减少磁盘 IO 拷贝 | CPU / 内存 | 建立虚拟地址到物理地址/文件的映射 |
| **dmabuf** | 跨硬件设备共享数据 | GPU / VPU / NIC | 使用 `fd` 作为内存的“通行证” |
| **ibverbs** | 跨网络零拷贝 (RDMA) | 网卡 (HCA) | **内存注册**，绕过内核协议栈 |

### 它们如何结合？
在现代高性能系统中，这三者经常协同工作。
**典型流程**：
1. 使用 `mmap` 分配一片大内存。
2. 通过 `dmabuf` 将这片内存导出给 GPU 进行计算。
3. 计算完成后，使用 `ibverbs` 将这片内存注册，通过 RDMA 直接发送到另一台服务器。

整个过程 **CPU 几乎不参与搬运数据**，只负责发号施令。
