# 画面にまたがるロジック

元の Swift ソースではない。給与の 7500 円は画面で読んだ値ではない。

## 選んだ日へパターンを置く

確定。保存済みの型は `ShiftPart`（`AppData.shiftParts`）。`WeekTemplate` ではない。

日チップ `0x10003fe54` とカレンダーの行 `0x10006e04c` は、衝突配列が空のときだけ `0x100014370` を呼ぶ。衝突があるときは `PendingPlace` を `__pendingPlace` へ書く。配置 `0x1001c75ec` は次のとおり。

- `workplaceID` が無いと、日のループの前に戻る。何も置かない
- 同じ `partID` が既にある日は足さない
- `startMinute` と `endMinute` を 1440 分で正規化し、時と分に分ける。秒は 0
- `start >= end`（同じ分を含む）は終了を翌日にする
- `defaultTodos` は新しい id でコピーし、`done` は 0
- `ShiftPart.breakMinutes` は読まない。渡す `Meta.breakMinutes` は空

未確定。置いた `ShiftInstance` の Published の保存先。配置は `AppModel` のアクセサ `0x10001c974` を呼ばない。次の `0x1001d1b74` も呼ばない。`_data`、`_notice`、`_placements`、`lastPlacedAt` への書き込みは、この 2 関数には無い。

## 重なり

確定。`0x100016734` は既存の `ShiftInstance` を走査する。

- 要素先頭の文字列が保存済みの文字列と等しければ次へ進む
- `start < 日付` かつ `日付 < end` なら衝突
- `workplaceID` が等しく、`Calendar.isDate(_:inSameDayAs:)` が真なら衝突
- スタック +0x280 の `x20` を 60 倍した秒が 0 以下なら、移動の経路は飛ばす
- それ以外は `timeIntervalSince` の秒が `x20 * 60` 未満のとき、60 で割って整数にする

未確定。`x20` が `Workplace` のどのフィールドか。3 つの分岐のどれが「のシフトがあります」で、どれが移動時間の文言か。

## WeekTemplate

確定。アクセサ `0x1001ec5a4` を呼ぶのは `0x1000e4934`、`0x1001dd510`、`0x1001e4ce8`、`0x1001ea190`、`0x1001ea598`。この 5 つは配置 `0x1001c75ec` を呼ばない。`0x1000e4934` は `name`（+0x14）と `entries`（+0x18）、要素の +0x14 から +0x24 を読む。

未確定。要素を日付へ展開する命令。この 5 関数に `bySettingHour` は無い。

## 給与

確定している式は `notes/HANDOFF.md` の検証済みの節。ここには画面との境界だけを繰り返す。

- 一覧カードの 1 秒タイムラインだけが、勤務中の金額を更新する経路として結んである。30 秒のスケジュール 2 箇所は別
- 表示する円は `base + premium`。手当と控除はこの和に入らない
- 休憩の按分は予定の start/end を変えず、`breakMinutes` だけを書き換える
- 丸めは startOfDay からの秒で、1440 分では巻かない
- 時給履歴は末尾から、`effectiveFrom` がシフト日以下の最初の `hourlyWage`。空なら 0
- 交通は、対象の kind で amount が 1 以上なら一度足す

未確定。日給の二つの UUID のフィールド名。perDay の回数。手当と控除の加算。ゲート日付が `now` そのものか。履歴が日付順か。全部がシフト日より後のときの戻り。年収の壁の閾値。

## 通知

確定。import にあるクラスは `UNUserNotificationCenter`、`UNMutableNotificationContent`、`UNNotificationSound`、`UNNotificationRequest`、`EKEventStore`、`EKEvent`。セレクタの cstring として `requestAuthorizationWithOptions:`、`addNotificationRequest:withCompletionHandler:`、`currentNotificationCenter`、`removePendingNotificationRequests`、`saveEvent:span:commit:error:` がある。

部分。設定の近くの関数が「シフトの前に通知」「リマインダー」「位置情報の許可」を読む。

未確定。どの関数がセレクタを呼び、何分前に通知を作り、どの画面が許可を求めるか。

## アニメーションの即値で、画面が未確定のもの

`easeInOut(duration:)` の 0.15（`0x3FC3333333333333`）は `0x10002291c`、`0x100022cdc`、`0x10002ed80`、`0x1001715f4`。画面の専用関数ではない。

`withAnimation` はバイナリ全体で 27。上の画面ファイルに書いたもの以外は、再生する画面が未確定。spring の 4 つの定数は `root.md`。
