# 電影院售票管理系統

## 專案簡介

本專案是 C++17 期末專題，實作一套可在終端機操作的電影院售票管理系統。系統支援電影管理、場次管理、購票、退票、票券查詢、座位表查詢與營收統計，並使用本地文字檔保存資料。

專案已完成可展示版本，教授可直接執行：

```powershell
.\docs\executable\cinema_ticket_system.exe
```

若 PowerShell 顯示中文亂碼，可先執行：

```powershell
chcp 65001
```

建議使用 Windows Terminal 或 VS Code Terminal 操作。

## 系統功能

- 電影管理：新增電影、顯示所有電影、查詢電影、刪除電影。
- 場次管理：新增電影場次、顯示所有場次、查詢指定電影場次。
- 售票功能：選擇電影、選擇場次、顯示座位表、選擇座位、選擇票種、計算票價、完成購票。
- 退票功能：依票號退票，退票後釋放座位。
- 查詢功能：查詢單張票券、顯示所有已售出票券、查看場次座位表。
- 統計功能：統計總營收、各電影售票數量、各票種銷售數量與小計。
- 檔案儲存：使用 `data/` 內文字檔保存電影、場次、票券資料。

## 使用技術

- C++17
- CMake
- STL：`vector`、`map`、`string`、`fstream`、`algorithm`
- OOP：class、inheritance、polymorphism
- 本地文字檔讀寫
- Windows 終端機 UTF-8 中文輸出設定
- 終端機互動式 UI

## C++ 類別繼承設計

票券使用抽象基底類別與多型：

```text
Ticket
├── AdultTicket
├── StudentTicket
└── ChildTicket
```

`Ticket` 定義 pure virtual function：

- `calculatePrice()`
- `getTicketType()`

各子類別票價：

- 成人票：320
- 學生票：280
- 兒童票：220

系統使用 `vector<unique_ptr<Ticket>>` 儲存票券。讀取 `data/tickets.txt` 時，會依 `ticketType` 還原成 `AdultTicket`、`StudentTicket` 或 `ChildTicket`，並透過多型計算票價與取得票種。

使用者角色也保留繼承架構：

```text
User
├── Admin
└── Customer
```

詳細類別說明請見 [docs/class-design.md](docs/class-design.md)。

## STL 使用說明

- `vector<Movie>`：儲存電影資料。
- `vector<Showtime>`：儲存場次資料。
- `vector<unique_ptr<Ticket>>`：儲存票券並展示多型。
- `map<string, int>`：統計各電影售票數量、各票種銷售數量與票種小計。
- `string`：處理 ID、片名、日期、時間、座位與票種。
- `fstream`：讀寫 `data/` 文字檔。
- `algorithm`：查詢、比對、刪除與判斷資料。

## 檔案讀寫設計

資料檔位於 `data/`，使用 `|` 分隔欄位。

```text
data/movies.txt
data/showtimes.txt
data/tickets.txt
```

格式範例：

```text
movieId|title|genre|duration
M001|鬼滅之刃劇場版|動畫|120

showtimeId|movieId|date|time|hall|rows|cols|soldSeats
S001|M001|2026-01-10|14:00|A廳|5|6|A3,B2,C5

ticketId|showtimeId|movieTitle|seatNo|ticketType|price
T001|S001|鬼滅之刃劇場版|A3|成人票|320
```

補充：

- `soldSeats` 使用逗號分隔，例如 `A3,B2,C5`。
- 資料檔不存在時會自動建立。
- 資料檔為空時會自動填入預設展示資料。
- 格式錯誤會顯示 `[警告]` 並略過該列，程式不會崩潰。
- 主選單 `8. 儲存資料` 會寫回 `data/`。
- 離開系統前會詢問是否儲存資料。

完整格式請見 [docs/file-format.md](docs/file-format.md)。

## 終端機 UI 操作說明

主選單：

```text
========================================
        電影院售票管理系統
========================================
資料狀態：電影 4 筆｜場次 4 筆｜票券 3 筆
----------------------------------------
1. 電影管理
2. 場次管理
3. 購買電影票
4. 退票
5. 查詢票券
6. 查看座位表
7. 營收統計
8. 儲存資料
0. 離開系統
========================================
請輸入選項：
```

常用流程：

- 電影管理：主選單輸入 `1`。
- 場次管理：主選單輸入 `2`。
- 購票：主選單輸入 `3`，依序選電影、場次、座位、票種。
- 退票：主選單輸入 `4`，輸入票號並確認。
- 查詢票券：主選單輸入 `5`。
- 查看座位表：主選單輸入 `6`。
- 營收統計：主選單輸入 `7`。
- 儲存資料：主選單輸入 `8`。
- 離開系統：主選單輸入 `0`。

座位表：

```text
    1   2   3   4   5
A   X   O   O   O   O
B   O   O   O   O   O

O = 可選座位
X = 已售出座位
```

完整操作說明請見 [docs/usage-guide.md](docs/usage-guide.md)。

## 專案目錄結構

```text
cinema-ticket-system/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── CinemaSystem.h
│   ├── FileManager.h
│   ├── Movie.h
│   ├── Showtime.h
│   ├── Ticket.h
│   ├── UIManager.h
│   └── User.h
├── src/
│   ├── CinemaSystem.cpp
│   ├── FileManager.cpp
│   ├── Movie.cpp
│   ├── Showtime.cpp
│   ├── Ticket.cpp
│   ├── UIManager.cpp
│   ├── User.cpp
│   └── main.cpp
├── data/
│   ├── movies.txt
│   ├── showtimes.txt
│   └── tickets.txt
├── docs/
│   ├── class-design.md
│   ├── file-format.md
│   ├── iteration-log.md
│   ├── usage-guide.md
│   └── executable/
│       └── cinema_ticket_system.exe
└── screenshots/
    └── README.md
```

## 安裝與編譯方式

在專案根目錄執行：

```powershell
cmake -S . -B build -G Ninja
cmake --build build
```

編譯後執行：

```powershell
.\build\cinema_ticket_system.exe
```

## 執行方式

方法一：使用 CMake 編譯後執行。

```powershell
.\build\cinema_ticket_system.exe
```

方法二：直接執行專案內提供的 Windows 執行檔。

```powershell
.\docs\executable\cinema_ticket_system.exe
```

`docs/executable/cinema_ticket_system.exe` 是教授展示用執行檔。若重新編譯後要更新此檔案，可執行：

```powershell
Copy-Item .\build\cinema_ticket_system.exe .\docs\executable\cinema_ticket_system.exe -Force
```

## Git 分支與開發流程

本專案使用多分支展示開發流程：

- `main`：穩定展示版本。
- `develop`：主要整合分支。
- `feature/project-setup`：建立 CMake 與專案結構。
- `feature/oop-classes`：建立類別與繼承架構。
- `feature/menu-ui`：建立互動式終端機 UI。
- `feature/file-io`：完成資料檔讀寫。
- `feature/movie-showtime`：完成電影與場次管理。
- `feature/ticket-system`：完成購票、退票、票券查詢、座位表。
- `feature/statistics`：完成營收統計。
- `feature/documentation`：整理 README、docs 與截圖說明。
- `release/v1.0`：最後可展示版本。

建議流程：

```powershell
git checkout develop
git checkout -b feature/<name>
git add .
git commit -m "<message>"
git push -u origin feature/<name>
git checkout develop
git merge feature/<name>
git push origin develop
```

## 開發迭代紀錄

完整紀錄請見 [docs/iteration-log.md](docs/iteration-log.md)。

摘要：

- Iteration 1：專案初始化。
- Iteration 2：核心類別與 OOP 繼承。
- Iteration 3：終端機互動 UI 骨架。
- Iteration 4：檔案讀寫功能。
- Iteration 5：電影管理與場次管理。
- Iteration 6：售票、退票與座位表。
- Iteration 7：查詢與營收統計。
- Iteration 8：文件、截圖說明與最終發佈整理。

## 系統畫面截圖

截圖請放在 `screenshots/`。目前先保留路徑，之後可手動截圖補上圖片。

![主選單](screenshots/main-menu.png)
![座位表](screenshots/seat-map.png)
![營收統計](screenshots/statistics.png)

建議截圖清單請見 [screenshots/README.md](screenshots/README.md)。

## 未來可擴充功能

- 管理員登入與權限控制。
- 付款方式與付款狀態。
- 影廳管理與座位配置管理。
- 電影分級、上映期間與票價活動。
- GUI 版本。
- SQLite 或其他資料庫版本。
