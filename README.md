# Based Proc Monitor

## 說明

- 監測一個PID的system call

## 操作說明

#### 安裝

```bash
sudo ./monitor_load
```

#### 卸載

```bash
sudo ./monitor_unload
```

#### 監測

```bash
sudo ./monitor_write "PID"     # 選擇PID
sudo ./monitor_write "start"   # 開始監測
sudo ./monitor_write "pause"   # 暫停監測
sudo ./monitor_write "recover" # 恢復監測，不需重新選擇PID
sudo ./monitor_write "stop"    # 結束監測，需要重新選擇PID
sudo cat /proc/monitor         # 查看監測結果
```
