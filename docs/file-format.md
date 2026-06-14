# 資料檔格式說明

本系統使用本地文字檔保存資料，所有資料檔皆放在 `data/` 目錄，欄位使用 `|` 分隔。程式啟動時會自動讀取資料，使用主選單 `8. 儲存資料` 可寫回檔案。

若資料檔不存在，系統會自動建立檔案。若資料檔是空檔，系統會自動填入預設範例資料，方便展示。若資料列格式錯誤，系統會顯示 `[警告]`，略過該列並繼續執行。

## data/movies.txt

格式：

```text
movieId|title|genre|duration
```

範例：

```text
M001|鬼滅之刃劇場版|動畫|120
M002|名偵探柯南劇場版|推理|110
```

欄位說明：

- `movieId`：電影編號，例如 `M001`
- `title`：電影名稱
- `genre`：電影類型
- `duration`：片長，單位為分鐘

## data/showtimes.txt

格式：

```text
showtimeId|movieId|date|time|hall|rows|cols|soldSeats
```

範例：

```text
S001|M001|2026-01-10|14:00|A廳|5|6|A3,B2,C5
S003|M003|2026-01-11|19:00|C廳|6|8|
```

欄位說明：

- `showtimeId`：場次編號，例如 `S001`
- `movieId`：對應電影編號
- `date`：放映日期
- `time`：放映時間
- `hall`：影廳
- `rows`：座位列數
- `cols`：座位欄數
- `soldSeats`：已售出座位，使用逗號分隔，例如 `A3,B2,C5`

若沒有已售出座位，`soldSeats` 可留空，但仍保留最後一個欄位分隔符號。

## data/tickets.txt

格式：

```text
ticketId|showtimeId|movieTitle|seatNo|ticketType|price
```

範例：

```text
T001|S001|鬼滅之刃劇場版|A3|成人票|320
T002|S001|鬼滅之刃劇場版|B2|學生票|280
T003|S002|名偵探柯南劇場版|A1|兒童票|220
```

欄位說明：

- `ticketId`：票券編號，例如 `T001`
- `showtimeId`：對應場次編號
- `movieTitle`：電影名稱
- `seatNo`：座位編號，例如 `A3`
- `ticketType`：票種
- `price`：票價

讀取 `tickets.txt` 時，系統會依 `ticketType` 還原成對應子類別物件，並使用 `vector<unique_ptr<Ticket>>` 儲存：

- `成人票` -> `AdultTicket`
- `學生票` -> `StudentTicket`
- `兒童票` -> `ChildTicket`

目前票價由子類別的 `calculatePrice()` 決定：

- 成人票：320
- 學生票：280
- 兒童票：220
