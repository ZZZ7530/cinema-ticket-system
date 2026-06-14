# 電影院售票管理系統

## 專案簡介

本專案是 C++17 期末專題，目標是實作一套終端機版電影院售票管理系統。系統將支援電影管理、場次管理、購票、退票、票券查詢、座位表查詢與營收統計，並使用本地文字檔保存資料。

目前進度：Iteration 7 查詢與營收統計功能。

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
- OOP：class、inheritance、polymorphism
- 本地文字檔讀寫
- 終端機互動式 UI

## STL 使用說明

- `vector<Movie>`：儲存電影資料。
- `vector<Showtime>`：儲存場次資料。
- `vector<unique_ptr<Ticket>>`：儲存票券並展示多型。
- `map<string, int>`：統計各電影售票數量、各票種銷售數量與票種小計。
- `string`：處理 ID、片名、日期、時間、座位與票種。
- `fstream`：讀寫 `data/` 文字檔。
- `algorithm`：查詢、比對、刪除與判斷資料。

## C++ 類別繼承設計

票券使用繼承與多型展示 C++ OOP 能力：

```text
Ticket
├── AdultTicket
├── StudentTicket
└── ChildTicket
```

`Ticket` 是抽象基底類別，定義：

- `virtual int calculatePrice() const = 0`
- `virtual std::string getTicketType() const = 0`

各票種票價：

- 成人票：320
- 學生票：280
- 兒童票：220

系統規劃使用 `vector<unique_ptr<Ticket>>` 儲存票券。讀取 `data/tickets.txt` 時，會根據 `ticketType` 還原成對應子類別：

- `成人票` -> `AdultTicket`
- `學生票` -> `StudentTicket`
- `兒童票` -> `ChildTicket`

使用者角色也使用繼承：

```text
User
├── Admin
└── Customer
```

`User` 定義 `virtual std::string getRole() const = 0`，由 `Admin` 與 `Customer` 覆寫。

## 類別設計文件

詳細類別設計請見：

```text
docs/class-design.md
```

目前已建立：

- `Movie`
- `Showtime`
- `Ticket`
- `AdultTicket`
- `StudentTicket`
- `ChildTicket`
- `User`
- `Admin`
- `Customer`
- `CinemaSystem`
- `UIManager`
- `FileManager`

## 檔案讀寫設計

資料檔會放在 `data/` 目錄，使用 `|` 分隔欄位。

Iteration 4 已完成檔案讀寫功能：

- 程式啟動時自動讀取 `data/movies.txt`、`data/showtimes.txt`、`data/tickets.txt`。
- 若檔案不存在，會自動建立檔案。
- 若資料檔是空檔，會自動填入預設範例資料，方便展示。
- 若資料列格式錯誤，會顯示 `[警告]` 並略過錯誤資料，程式不會崩潰。
- 主選單 `8. 儲存資料` 會將目前資料寫回三個檔案。
- 離開系統前會詢問是否儲存資料。
- 票券讀檔會依 `ticketType` 還原成 `AdultTicket`、`StudentTicket` 或 `ChildTicket`，並以 `vector<unique_ptr<Ticket>>` 保存。

完整格式說明請見：

```text
docs/file-format.md
```

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

Windows 版本會設定 console input/output code page 為 UTF-8，讓中文輸出更穩定。

Iteration 5 已完成互動式電影管理與場次管理。主選單會重複顯示，使用者可輸入選項進入子選單，並以 `0` 返回或離開。電影與場次的新增、查詢、顯示、刪除會先修改記憶體資料；使用主選單 `8. 儲存資料` 或離開系統前選擇儲存，才會寫回 `data/` 文字檔。

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

選擇 `8. 儲存資料` 時，系統會呼叫 `saveAllData()`，並顯示：

```text
[成功] 資料已儲存
```

若寫入失敗，系統會顯示 `[警告]`，但不會直接崩潰。

### 電影管理子選單

```text
========== 電影管理 ==========
1. 新增電影
2. 顯示所有電影
3. 查詢電影
4. 刪除電影
0. 返回主選單
請輸入選項：
```

電影管理已支援：

- 新增電影：系統自動產生 `M004`、`M005` 等 ID，使用者輸入片名、類型、片長。
- 顯示所有電影：用簡單表格顯示 ID、片名、類型、片長。
- 查詢電影：可輸入電影 ID 或片名關鍵字。
- 刪除電影：輸入電影 ID，若已有場次則禁止刪除；刪除前需輸入 `y/n` 確認。

操作範例：

```text
主選單輸入 1
電影管理輸入 1
請輸入片名：測試電影
請輸入類型：劇情
請輸入片長（分鐘）：100
[成功] 電影新增完成，電影 ID：M004
```

### 場次管理子選單

```text
========== 場次管理 ==========
1. 新增電影場次
2. 顯示所有場次
3. 查詢指定電影場次
0. 返回主選單
請輸入選項：
```

場次管理已支援：

- 新增電影場次：系統自動產生 `S004`、`S005` 等 ID。
- 顯示所有場次：顯示場次 ID、電影名稱、日期、時間、影廳、座位數、已售出座位數。
- 查詢指定電影場次：可輸入電影 ID 或片名關鍵字。

操作範例：

```text
主選單輸入 2
場次管理輸入 1
請輸入電影 ID：M004
請輸入日期（例如 2026-01-12）：2026-01-12
請輸入時間（例如 18:30）：18:30
請輸入影廳（例如 A廳）：D廳
請輸入座位列數 rows：4
請輸入座位行數 cols：5
[成功] 場次新增完成，場次 ID：S004
```

### 營收統計子選單

```text
========== 營收統計 ==========
1. 查看總營收
2. 查看各電影售票數量
3. 查看各票種銷售數量
0. 返回主選單
請輸入選項：
```

營收統計已支援：

- 查看總營收：根據目前所有票券計算票價總和。
- 查看各電影售票數量：使用 `map<string, int>` 統計每部電影賣出幾張票。
- 查看各票種銷售數量：使用 `map<string, int>` 統計成人票、學生票、兒童票數量，並顯示各票種小計金額。

範例：

```text
目前總營收：NT$880
成人票：1 張，小計 NT$320
學生票：2 張，小計 NT$560
兒童票：0 張，小計 NT$0
```

輸入錯誤處理：

- 輸入非數字時會提示 `[錯誤] 請輸入數字選項。`
- 輸入不存在的選項時會提示 `[錯誤] 沒有這個選項，請重新輸入。`
- 執行功能提示後，按 Enter 返回原選單。

### 購票流程

主選單輸入 `3` 可購買電影票：

```text
1. 顯示所有電影
2. 輸入電影 ID 或左側序號
3. 選擇場次 ID
4. 查看座位表並輸入座位，例如 A3
5. 選擇票種
6. 確認購買
```

票種與票價：

- 成人票：320
- 學生票：280
- 兒童票：220

購票完成後，系統會自動產生票號，例如 `T004`，並把座位加入該場次的 `soldSeats`。購票資料會先保存在記憶體，使用主選單 `8. 儲存資料` 或離開前選擇儲存才會寫回 `data/tickets.txt` 與 `data/showtimes.txt`。

### 退票流程

主選單輸入 `4` 可依票號退票：

```text
請輸入票號：T003
是否確認退票 (y/n)：y
[成功] 退票完成
```

退票後會刪除票券，並釋放該場次座位。

### 查詢票券

主選單輸入 `5` 可查詢票券：

- 依票號查詢單張票券。
- 顯示所有已售出票券。

顯示欄位包含：票號、電影名稱、場次 ID、座位、票種、票價。

### 查看座位表

主選單輸入 `6` 可查看指定場次座位表：

```text
O = 可選座位
X = 已售出座位
```

### 座位表

```text
========================================
座位表
========================================
    1   2   3   4   5   6
A   O   O   X   O   O   O
B   O   X   X   O   O   O
C   O   O   O   O   X   O

O = 可選座位
X = 已售出座位
========================================
```

中文表格輸出會避免過度依賴 `setw` 對齊，改用分隔線、固定欄位標題、逐列顯示與清楚編號。

## 專案目錄結構

```text
cinema-ticket-system/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── Movie.h
│   ├── Showtime.h
│   ├── Ticket.h
│   ├── User.h
│   ├── CinemaSystem.h
│   ├── UIManager.h
│   └── FileManager.h
├── src/
│   ├── main.cpp
│   ├── Movie.cpp
│   ├── Showtime.cpp
│   ├── Ticket.cpp
│   ├── User.cpp
│   ├── CinemaSystem.cpp
│   ├── UIManager.cpp
│   └── FileManager.cpp
├── data/
│   ├── movies.txt
│   ├── showtimes.txt
│   └── tickets.txt
├── docs/
│   ├── class-design.md
│   ├── iteration-log.md
│   ├── file-format.md
│   └── executable/
│       └── cinema_ticket_system.exe
└── screenshots/
```

`screenshots/` 會保留給展示圖片，例如主選單、座位表、購票成功畫面。

最終 Windows 執行檔主要放置位置：

```text
docs/executable/cinema_ticket_system.exe
```

## 安裝與編譯方式

在專案根目錄執行：

```powershell
cmake -S . -B build -G Ninja
cmake --build build
```

## 執行方式

建議使用 Windows Terminal 或 VS Code Terminal 執行。如果 PowerShell 顯示中文亂碼，可以先切換成 UTF-8 code page：

```powershell
chcp 65001
```

再執行程式。

### 方法一：執行 CMake 編譯結果

```powershell
.\build\cinema_ticket_system.exe
```

### 方法二：直接執行教授展示用 exe

```powershell
.\docs\executable\cinema_ticket_system.exe
```

## 複製執行檔到 docs/executable

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

## 開發迭代紀錄

### Iteration 1：專案初始化

- 建立 CMake 專案。
- 建立基本目錄結構。
- 建立 README 初版。
- 建立最小可執行 `src/main.cpp`。
- 修正 Windows 終端機中文 UTF-8 顯示。

### Iteration 2：核心類別與 OOP

- 建立 `Movie` 類別。
- 建立 `Showtime` 類別與座位狀態方法。
- 建立 `Ticket` 抽象基底類別。
- 建立 `AdultTicket`、`StudentTicket`、`ChildTicket`。
- 建立 `User`、`Admin`、`Customer`。
- 在 `main.cpp` 中暫時加入物件建立、座位操作與多型測試。

### Iteration 3：終端機互動 UI 骨架

- 建立 `CinemaSystem` 類別作為系統資料與功能整合入口。
- 建立 `UIManager` 類別負責主選單、子選單、輸入驗證與暫停返回。
- `main.cpp` 改為啟動互動式主選單。
- 主選單與電影管理、場次管理、營收統計子選單可以重複操作。
- 尚未完成的功能會顯示提示，並可按 Enter 返回。

### Iteration 4：檔案讀寫

- 完成 movies、showtimes、tickets 讀檔與寫檔。
- 根據 ticketType 還原票券子類別。
- 建立 `FileManager` 集中處理本地文字檔。
- 主選單 `8. 儲存資料` 可寫回 data 檔案。
- 離開系統前詢問是否儲存資料。
- 新增 `docs/file-format.md`。

### Iteration 5：電影與場次管理

- 完成電影新增、顯示、查詢、刪除。
- 完成場次新增、顯示、依電影查詢。
- 電影 ID 與場次 ID 由系統自動產生。
- 片長、rows、cols 會檢查正整數。
- 刪除電影時，若已有場次會禁止刪除。

### Iteration 6：售票、退票與座位表

- 完成購票流程，包含選電影、選場次、選座位、選票種、確認購買。
- 使用 `Ticket` 多型建立 `AdultTicket`、`StudentTicket`、`ChildTicket`。
- 完成退票流程，退票後會釋放座位。
- 完成票券查詢，可查單張票券或所有已售出票券。
- 完成指定場次座位表顯示，使用 `O` / `X` 顯示可選與已售出座位。
- 購票與退票會同步更新記憶體中的 `tickets` 與 `soldSeats`。

### Iteration 7：查詢與營收統計

- 完成總營收統計。
- 完成各電影售票數量統計。
- 完成各票種銷售數量與小計金額統計。
- 使用 `map<string, int>` 彙總電影與票種銷售資料。

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
