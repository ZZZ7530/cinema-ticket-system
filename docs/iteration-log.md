# 開發迭代紀錄

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
