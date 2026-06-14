# 類別設計文件

## Movie

`Movie` 負責保存電影基本資料。

- 欄位：`movieId`、`title`、`genre`、`duration`
- 方法：
  - 建構子
  - getter
  - `toFileString()`
  - `fromFileString()`
  - `display()`

檔案格式：

```text
movieId|title|genre|duration
M001|鬼滅之刃劇場版|動畫|120
```

## Showtime

`Showtime` 負責保存電影場次資料與座位狀態。

- 欄位：`showtimeId`、`movieId`、`date`、`time`、`hall`、`rows`、`cols`、`soldSeats`
- 方法：
  - `isSeatSold()`
  - `sellSeat()`
  - `releaseSeat()`
  - `displaySeatMap()`
  - `toFileString()`
  - `fromFileString()`

座位以 `A1`、`A2`、`B1` 格式表示。`soldSeats` 儲存已售出的座位編號。

## Ticket 繼承與多型

`Ticket` 是抽象基底類別，提供票券共同欄位與介面。

```text
Ticket
├── AdultTicket
├── StudentTicket
└── ChildTicket
```

`Ticket` 定義以下 pure virtual function：

- `calculatePrice()`
- `getTicketType()`

各子類別票價：

- `AdultTicket`：成人票，320 元
- `StudentTicket`：學生票，280 元
- `ChildTicket`：兒童票，220 元

系統會使用 `vector<unique_ptr<Ticket>>` 保存票券，因此可以透過基底類別指標呼叫不同子類別的 `calculatePrice()` 與 `getTicketType()`，展示 polymorphism。

讀取 `tickets.txt` 時，會依照 `ticketType` 還原子類別：

- `成人票` -> `AdultTicket`
- `學生票` -> `StudentTicket`
- `兒童票` -> `ChildTicket`

## User 繼承

`User` 是使用者基底類別。

```text
User
├── Admin
└── Customer
```

`User` 定義 virtual function：

- `getRole()`

`Admin` 回傳 `管理員`，`Customer` 回傳 `顧客`。此架構用來展示角色設計，也方便後續把管理功能與一般顧客功能拆開。

## Iteration 2 驗證重點

- 可以建立 `Movie` 並轉成檔案格式。
- 可以建立 `Showtime`，售出與釋放座位，並顯示座位表。
- 可以建立 `AdultTicket`、`StudentTicket`、`ChildTicket`。
- 可以用 `vector<unique_ptr<Ticket>>` 透過多型計算票價。
- 可以建立 `Admin` 與 `Customer`，並透過 `User` 指標呼叫 `getRole()`。
