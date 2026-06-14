# 電影院售票管理系統

## 專案簡介

本專案是 C++17 期末專題，目標是實作一套終端機版電影院售票管理系統。系統將支援電影管理、場次管理、購票、退票、票券查詢、座位表查詢與營收統計，並使用本地文字檔保存資料。

目前進度：Iteration 1 專案初始化。

## 系統功能規劃

- 電影管理：新增電影、顯示所有電影、查詢電影、刪除電影。
- 場次管理：新增電影場次、顯示所有場次、查詢指定電影場次。
- 售票功能：選擇場次、顯示座位表、選擇座位、選擇票種、計算票價、更新座位狀態。
- 退票功能：依票號退票，退票後釋放座位。
- 查詢功能：查詢票券、查詢目前已售出票券、查詢場次座位狀態。
- 統計功能：統計總營收、各電影售票數量、不同票種銷售數量。

## 使用技術

- C++17
- CMake
- STL：`vector`、`map`、`string`、`fstream`、`algorithm`
- 物件導向設計：class、inheritance、polymorphism
- 本地文字檔讀寫
- 終端機互動式 UI

## C++ 類別繼承設計

票券將使用繼承與多型展示 C++ OOP 能力：

```text
Ticket
├── AdultTicket
├── StudentTicket
└── ChildTicket
```

規劃使用 `vector<unique_ptr<Ticket>>` 儲存票券。讀取 `data/tickets.txt` 時，系統會根據 `ticketType` 欄位還原成對應的子類別物件：

- `成人票` -> `AdultTicket`
- `學生票` -> `StudentTicket`
- `兒童票` -> `ChildTicket`

各票種會覆寫 `calculatePrice()` 與 `getTicketType()`，以展示 virtual function 與 polymorphism。

使用者角色也可使用繼承輔助展示：

```text
User
├── Admin
└── Customer
```

## 檔案讀寫設計

資料檔會放在 `data/` 目錄，使用 `|` 分隔欄位。

### data/movies.txt

```text
movieId|title|genre|duration
M001|鬼滅之刃劇場版|動畫|120
M002|名偵探柯南劇場版|推理|110
```

### data/showtimes.txt

```text
showtimeId|movieId|date|time|hall|rows|cols|soldSeats
S001|M001|2026-01-10|14:00|A廳|5|6|A3,B2,B3,C5
S002|M002|2026-01-10|16:30|B廳|5|6|
```

### data/tickets.txt

```text
ticketId|showtimeId|movieTitle|seatNo|ticketType|price
T001|S001|鬼滅之刃劇場版|A3|成人票|320
T002|S001|鬼滅之刃劇場版|B2|學生票|280
```

## 終端機 UI 操作規劃

建議使用 Windows Terminal 或 VS Code Terminal 執行本系統，以獲得較好的中文字元與 ANSI 顏色顯示效果。程式可以使用 ANSI 顏色提示成功、錯誤、警告與標題，但操作流程不會依賴顏色，因此即使在不支援顏色的終端機中仍可使用。

Windows 版本將盡量加入 ANSI 支援處理，讓 Windows Terminal / CMD 都能正常顯示基本顏色。

### 主選單

```text
========================================
        電影院售票管理系統
========================================
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

### 座位表

```text
========================================
座位表
========================================
        1   2   3   4   5   6
A       O   O   X   O   O   O
B       O   X   X   O   O   O
C       O   O   O   O   X   O

O = 可選座位
X = 已售出座位
========================================
```

中文表格輸出會避免過度依賴 `setw` 對齊，因為不同終端機對中文寬度處理可能不同。系統會採用簡單分隔線、固定欄位標題、逐列顯示與清楚編號，確保教授操作時容易閱讀。

## 專案目錄結構

```text
cinema-ticket-system/
├── CMakeLists.txt
├── README.md
├── include/
├── src/
│   └── main.cpp
├── data/
├── docs/
│   └── executable/
│       └── cinema_ticket_system.exe
└── screenshots/
```

`screenshots/` 會保留給展示圖片，例如主選單、座位表、購票成功畫面。

最終 Windows 執行檔主要放置位置：

```text
docs/executable/cinema_ticket_system.exe
```

`release/` 不是主要交付位置，可不建立；若之後需要，也只作為備份或額外發佈說明使用。

## 安裝與編譯方式

### 方法一：使用 CMake 自行編譯

在專案根目錄執行：

```powershell
cmake -S . -B build
cmake --build build --config Release
```

若使用 Visual Studio generator，執行檔通常會產生在：

```text
build/Release/cinema_ticket_system.exe
```

若使用 Makefiles 或 Ninja，執行檔可能會產生在：

```text
build/cinema_ticket_system.exe
```

## 執行方式

建議使用 Windows Terminal 或 VS Code Terminal 執行。如果 PowerShell 顯示中文亂碼，可以先切換成 UTF-8 code page：

```powershell
chcp 65001
```

再執行程式。

### 方法一：執行 CMake 編譯結果

```powershell
.\build\Release\cinema_ticket_system.exe
```

或：

```powershell
.\build\cinema_ticket_system.exe
```

### 方法二：直接執行教授展示用 exe

```powershell
.\docs\executable\cinema_ticket_system.exe
```

## 複製執行檔到 docs/executable

Visual Studio generator 常見指令：

```powershell
Copy-Item .\build\Release\cinema_ticket_system.exe .\docs\executable\cinema_ticket_system.exe -Force
```

Ninja 或 Makefiles 常見指令：

```powershell
Copy-Item .\build\cinema_ticket_system.exe .\docs\executable\cinema_ticket_system.exe -Force
```

## Git 分支與開發流程

建議分支：

- `main`：穩定版本。
- `develop`：主要開發整合分支。
- `feature/project-setup`：建立 CMake 與專案結構。
- `feature/oop-classes`：建立類別與繼承架構。
- `feature/file-io`：完成讀檔與寫檔。
- `feature/menu-ui`：完成終端機 UI。
- `feature/movie-showtime`：完成電影與場次管理。
- `feature/ticket-system`：完成售票、退票、座位表。
- `feature/statistics`：完成統計功能。
- `feature/documentation`：完成 README 與 docs 文件。
- `release/v1.0`：最後可展示版本。

Iteration 1 建議 commit：

```powershell
git init
git checkout -b main
git add .
git commit -m "chore: initialize cinema ticket system project"
git checkout -b develop
git checkout -b feature/project-setup
git commit --allow-empty -m "chore: start project setup iteration"
```

若已經先在 `feature/project-setup` 建立檔案，則可以改用：

```powershell
git init
git checkout -b main
git checkout -b develop
git checkout -b feature/project-setup
git add .
git commit -m "chore: create cmake project structure"
```

## 開發迭代紀錄

### Iteration 1：專案初始化

- 建立 CMake 專案。
- 建立基本目錄結構。
- 建立 README 初版。
- 建立最小可執行 `src/main.cpp`。

### Iteration 2：核心類別與 OOP

- 建立 Movie、Showtime、Seat。
- 建立 Ticket / AdultTicket / StudentTicket / ChildTicket。
- 建立 User / Admin / Customer。

### Iteration 3：檔案讀寫

- 完成 movies、showtimes、tickets 讀檔與寫檔。
- 根據 ticketType 還原票券子類別。

### Iteration 4：終端機 UI

- 完成主選單與子選單。
- 完成輸入驗證。
- 完成表格、座位表與狀態提示。

### Iteration 5：電影與場次管理

- 完成電影 CRUD。
- 完成場次新增、顯示與查詢。

### Iteration 6：售票與退票

- 完成售票流程。
- 完成退票流程。
- 完成座位狀態更新。

### Iteration 7：查詢與統計

- 完成票券查詢。
- 完成座位狀態查詢。
- 完成營收與銷售統計。

### Iteration 8：文件與展示版本

- 完成 README。
- 補充 docs 文件。
- 放置 screenshots。
- 產生 `docs/executable/cinema_ticket_system.exe`。

## 未來可擴充功能

- 管理員登入。
- 付款方式。
- 電影分級與影廳管理。
- GUI 版本。
- SQLite 或其他資料庫版本。
