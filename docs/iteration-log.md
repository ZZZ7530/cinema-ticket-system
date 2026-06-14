# 開發迭代紀錄

本文件記錄本專案各 feature 分支與 Iteration 完成內容，用於呈現 GitHub 開發流程。

## Iteration 1：專案初始化

完成日期：2026-06-14

完成內容：

- 建立 CMake 專案。
- 建立 `include/`、`src/`、`data/`、`docs/`、`docs/executable/`、`screenshots/`。
- 建立 `src/main.cpp` 最小可執行版本。
- 建立 README 初版。
- 設定 Windows console UTF-8 輸出，改善中文亂碼問題。
- 產生並複製展示用執行檔到 `docs/executable/cinema_ticket_system.exe`。

## Iteration 2：核心類別與 OOP 繼承

完成日期：2026-06-14

完成內容：

- 建立 `Movie` 類別，包含電影 ID、片名、類型、片長與檔案格式轉換方法。
- 建立 `Showtime` 類別，包含場次資料、座位判斷、售出座位、釋放座位與座位表顯示。
- 建立 `Ticket` 抽象基底類別。
- 建立 `AdultTicket`、`StudentTicket`、`ChildTicket`，展示 virtual function 與 polymorphism。
- 建立 `User`、`Admin`、`Customer`，展示使用者角色繼承。
- 建立 `docs/class-design.md` 說明類別設計。

## Iteration 3：終端機互動 UI 骨架

完成日期：2026-06-14

完成內容：

- 建立 `CinemaSystem` 類別，作為系統資料與後續功能整合入口。
- 建立 `UIManager` 類別，集中處理終端機選單、輸入驗證與操作提示。
- `main.cpp` 改為啟動互動式主選單。
- 主選單可重複操作，輸入 `0` 才離開系統。
- 完成電影管理、場次管理、營收統計子選單骨架。
- 尚未實作的功能會顯示提示，並等待使用者按 Enter 返回。
- 處理非數字輸入與不存在的選項，避免程式崩潰。

## Iteration 4：檔案讀寫功能

完成日期：2026-06-14

完成內容：

- 建立 `FileManager` 類別，集中處理 `data/` 內文字檔讀寫。
- 完成 `data/movies.txt` 讀取與寫入，格式為 `movieId|title|genre|duration`。
- 完成 `data/showtimes.txt` 讀取與寫入，格式為 `showtimeId|movieId|date|time|hall|rows|cols|soldSeats`。
- 完成 `data/tickets.txt` 讀取與寫入，格式為 `ticketId|showtimeId|movieTitle|seatNo|ticketType|price`。
- 讀取票券時會依 `ticketType` 還原為 `AdultTicket`、`StudentTicket` 或 `ChildTicket`，並使用 `vector<unique_ptr<Ticket>>` 儲存。
- 若資料檔不存在，系統會自動建立檔案。
- 若資料檔是空檔，系統會自動填入預設範例資料，方便展示。
- `CinemaSystem` 啟動時會載入三個資料檔，儲存時會寫回三個資料檔。
- `UIManager` 會顯示載入資料筆數、讀取警告、儲存成功訊息，並在離開前詢問是否儲存。
- 建立 `docs/file-format.md` 說明資料格式。

## Iteration 5：電影管理與場次管理功能

完成日期：2026-06-14

完成內容：

- 完成電影管理功能：新增電影、顯示所有電影、查詢電影、刪除電影。
- 新增電影時由系統自動產生 `M004`、`M005` 等 ID。
- 新增電影會檢查片長必須為正整數。
- 查詢電影可使用電影 ID 或片名關鍵字。
- 刪除電影前會要求 `y/n` 確認；若電影已有場次，會禁止刪除並顯示原因。
- 完成場次管理功能：新增電影場次、顯示所有場次、查詢指定電影場次。
- 新增場次時由系統自動產生 `S004`、`S005` 等 ID。
- 新增場次會檢查 rows 與 cols 必須為正整數，已售出座位預設為空。
- 顯示場次時會列出場次 ID、電影名稱、日期、時間、影廳、座位數、已售出座位數。
- 所有新增與刪除先修改記憶體資料，使用主選單 `8. 儲存資料` 或離開前選擇儲存才寫回 `data/` 檔案。

## Iteration 6：售票、退票與座位表功能

完成日期：2026-06-14

完成內容：

- 完成主選單 `3. 購買電影票`。
- 購票流程支援選擇電影、選擇場次、查看座位表、輸入座位、選擇票種、確認購買。
- 座位會檢查格式、範圍與是否已售出。
- 使用 `Ticket` 多型建立 `AdultTicket`、`StudentTicket`、`ChildTicket`。
- 購票成功後自動產生票號，例如 `T004`，並把座位加入該場次 `soldSeats`。
- 完成主選單 `4. 退票`，可依票號退票並釋放座位。
- 完成主選單 `5. 查詢票券`，可查單張票券或顯示所有已售出票券。
- 完成主選單 `6. 查看座位表`，以 `O` / `X` 顯示可選與已售出座位。
- 購票與退票只先修改記憶體資料，使用主選單 `8. 儲存資料` 或離開前選擇儲存才寫回 `data/tickets.txt` 與 `data/showtimes.txt`。

## Iteration 7：查詢與營收統計功能

完成日期：2026-06-14

完成內容：

- 完成主選單 `7. 營收統計` 的三個功能選項。
- 查看總營收時，使用目前 `tickets` 資料與 `Ticket::calculatePrice()` 多型計算總票價。
- 使用 `map<string, int>` 統計各電影售票數量。
- 使用 `map<string, int>` 統計成人票、學生票、兒童票銷售數量。
- 使用 `map<string, int>` 統計各票種小計金額。
- 若目前沒有票券資料，電影售票統計與票種統計會顯示 `[提示] 目前尚無售票資料`。

## Iteration 8：文件、截圖說明與最終發佈整理

完成日期：2026-06-14

完成內容：

- 整理 README.md，使 GitHub 首頁能完整呈現專案介紹、功能、技術、編譯、執行與開發流程。
- 整理 `docs/class-design.md`、`docs/file-format.md`、`docs/iteration-log.md`。
- 新增 `docs/usage-guide.md`，提供完整操作指南。
- 新增 `screenshots/README.md`，說明展示截圖命名與放置位置。
- 確認並更新 `docs/executable/cinema_ticket_system.exe`。
