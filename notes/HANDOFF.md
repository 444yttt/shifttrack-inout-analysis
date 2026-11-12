# 統合担当への引き渡し

公開解析リポジトリの再構成。元の Swift ソースではない。広告はない。製品の私有コードは含まない。時給の円は命令から再構成した。8時間・休憩60・時給1000の途中で7500円、という数字はエンジンにその入力を渡したときの計算結果であり、画面で読んだ値ではない。製品へ画面挙動として写さない。手当と控除の式は閉じていない。

## 検証済み commit

| 内容 | commit | macOS run |
| --- | --- | --- |
| 週数 × 7 日 | `febde5b6f02a26c9d13d8c164c9a100e499aaf9a` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42376695303 |
| 休憩の選択 | `0e24b5ab91b3` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377098813 |
| 編集画面の分数と秒の切り捨て | `19e5229a227f9ca73dcd551006f303393ac75b67` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377557969 |
| 丸めの適用と勤務中の休憩按分 | `cd54b571b0ae9bd95dcaf1b35f8e1862a61bfd69` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42379613656 |
| 時給の円と live の表示 | `fefc70d841ab498dedf96f964700bfa187c8770e` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42380430047 |
| 一覧タイムライン、時給履歴、交通費 | `693072de9500e5d6267e4ddef6ded46b9dc31697` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42381152178 |
| 金額表示の文言 | `02b0f271a08ef15859d1cfc960676d37c1f36ae1` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42443537367 |
| パターンを選んだ日へ置く | `1da02529ffd3df525a3f95ebe3a7ff564b401c14` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42977835967 |
| 画面型と Doto-BlackRound | `d309fae3b9dfa9ea062e13082a1fb4ae88c647e1` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42978746906 |
| カタログの色と記号名 | `5c9423cdc8475c3ff01eee3fad5106e617f75c35` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42980044157 |
| タブの記号、残りの systemName、レイアウトの即値 | `90149dd899310aa2f757d402424c420b9737da16` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42981594356 |
| 画面単位の移植仕様と網羅率 | `fc7b4b597db649f43c83f176c3e1468c24f9145f` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42984588154 |
| opaque 型から読んだ modifier 順 | `7a72cc0` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42985348451 |
| 画面関数が読む文言とフォント | `e2a2f5d938028945af7eb720b9b5d7d9e443620c` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42993936784 |

## 統合してよいもの

- `addingWeeks` / `weekSlideTag` — `0x10020499c`。`Calendar.Component.day` を週数×7。週数が正ならタグ 3、そうでなければ 1。週オフセットを ±1 する側は未回収
- `selectedBreakMinutes` — `0x1000e967c`。`overMinutes < 分数` のうち最大。同値は先の規則。無ければ 0。法定 (360,45),(480,60) では 360→0、361→45、480→45、481→60
- `editorMinuteCount` — `ShiftEntryEditor` の `_endMinute - _startMinute` を 1...1440 に正規化。同じ分は 1440。日をまたぐ負の差は 1440 を足した正の余り。編集画面用。給与明細の分数ではない

`customBreaks == 1` のとき `Workplace.breakRules`、そうでなければ法定グローバル `0x1005d0a40`。

## 呼び出しの入力としては確定、給与式としては繋がないもの

- `minutesFromEndDate` — `0x1001cee68` は同じオブジェクトの `endDate.timeIntervalSince(startDate)` を 60 で割り、0 方向へ切り捨てる。同じ時刻は 0 分。編集画面の「同じ分は 1440」とは別。時給の式ではない

## 今回、命令から再構成したもの

呼び出し順は `0x10026e844`（`TimelineView.Context.date`）→ `WorkRecord` を組む `0x10011e2e0` → `0x10011dc04` → `0x10011d530` → `0x100119384` → 金額側の `0x10011b1d0`。

- `liveAsOf` / `scaledBreakMinutes` — `0x10026e844`。`shiftEnd < now` なら asOf は終了、そうでなければ now。`end.timeIntervalSince(start) <= 0` なら休憩 0。そうでなければ `frinta(経過秒 * breakMinutes / 全体秒)` を 0 方向の整数にして `WorkRecord.breakMinutes`（metadata +0x20）へ書く。start/end はシフトの元の日付のまま。これは休憩の入力であり、円ではない
- `roundedSecondsFromStartOfDay` / `roundedDate` — `0x10011b1d0`。`PayTerms.rounding`（field 6、metadata +0x28）の `unitMinutes` と、+8 の start 方向、+9 の end 方向。`unitMinutes < 2` または `exact`(0) はその日付のまま。そうでなければその日の `startOfDay` からの秒を `unitMinutes * 60` で割り、up(1)=`frintp`、down(2)=`frintm`、それ以外（`nearest`）=`frinta`、同じ startOfDay に足す。1440 分への折り返しではない。乗算は検査付きで、溢れると `brk`。再構成はトラップしない

`PeriodicTimelineSchedule.init(from:by:)` は 3 箇所。`by` は `0x10025782c` と `0x100258254` が 30 秒、`0x100262b48` が 1 秒。どのスケジュールが `0x10026e844` の context かはポインタで結べていない。

境界（命令どおり。画面では未観察）:

- 15 分単位の 450 秒は nearest で 900 秒。449 秒は 0。1 秒の up は 900。899 秒の down は 0。unit 0/1/負、exact は不変
- 8 時間・休憩 60 分の半分は 30。開始時点は 0。終了時点は 60。240 秒は 0.5 のタイで 1。30 秒は 0。期間が 0 以下は 0。経過が負なら負のまま（-4 時間で -30、-1 時間は -7.5 が 0 から遠い側で -8）

## 画面と設定の目録

「挙動確認」は命令まで見たもの。「名前のみ」は型・フィールド・文言があるだけで、計算は見ていない。広告型（`BannerAdView`、`AdsController`、`PurchaseController`）は目録から外した。intelligence という型名はこのメタデータ一覧には無かった。

挙動確認:

- 週の移動は日数×7。タグは正の週数なら 3、そうでなければ 1。±1 ボタン自体は未確認
- 休憩規則の選択、編集画面の分（同値は 1440）、`endDate.timeIntervalSince(startDate)` の切り捨て（同値は 0）
- 法定休憩の初期値 (360,45),(480,60)。勤務先初期値は夜 22:00–05:00 の 25%、残業 480 分の 25%、休日は無効、customBreaks は 0
- 分のホイールは 1440 正規化のあと `bySettingHour`（秒 0、nextTime、first、forward）
- 上記の丸め適用と、勤務中の休憩按分
- タイムライン更新間隔の定数 30 秒が 2 箇所、1 秒が 1 箇所。どの画面の数字を動かしているかは未接続
- 時給の円、深夜・残業・休日の割増、日給の base 加算、交通の ExtraPayItem、live の表示が base + premium であること。詳細は下の「円」

名前のみ（画面型）: `InOutTab` の list / calendar / workplaces / income / settings。`WorkplaceListView`、`CalendarTabView`、`CalendarDayView`、`IncomeView`、`WallEditorView`、`SettingsView`、`ShiftCheckView`、`ShiftEntryEditor`、`PayBreakdownView`、`PayTermsEditorView`、`PayScheduleEditorView`、`PayPeriodsView`、`UnconfirmedShiftsView`、`OnboardingView`、`LateMessageView`、`WorkplaceEditorView`、`WorkplaceDirectoryView`、`GuideOverlay`（`GuideTarget` に listPay / incomeEstimate / incomeWall がある）。`RollingYen` は `value: Double` の表示型で、`0x10026e260` がアクセサを呼ぶ。金額の中身はこの型には無い。

名前のみ（設定フィールド）: `AppSettings` の shiftRemindersEnabled、startGraceMinutes、showsNativeAgenda、travelMinutes、endCheckEnabled、incomeBasis。`Workplace` の night / overtime / holiday / breakRules / closingDay / travelMode / payTerms / paySchedule / requestHourStock / 遅刻文面。`PayTerms` の method（hourly/daily）、dailyWage、bands、partWages、items。`PaySchedule` の cycle、payMonthOffset、payDay、closingWeekday、lagDays、weekendRule。`IncomeWall` の amount、alertMode、alertPercent、alertRemaining。`PayItem` の unit（perShift/perDay/perPeriod）と condition（always/nightWork）。文言「今日と今月のお給料の見込みです。シフトの時間と時給から計算します。」は `0x1004fc780`。式そのものではない。

`0x100218a18` と `0x100218ea4` は `timeIntervalSinceNow` を -300 秒と比較する。定数であり、`startGraceMinutes` を読んでいることは未確認。

## 円。0x10011b1d0 と呼び出し元

この数字は勤務先一覧（`WorkplaceListView`）の 1 秒タイムラインで、収入タブの見込み画面ではない。`0x1002616f4` は `start <= 日付 < end` のときだけ `PeriodicTimelineSchedule(from:by:)` の `by` を 1 秒にして `TimelineView` を作る。比較は `0x100262af8`（`<=`）と `0x100262b14`（`<`）。どちらも start/end を書き戻さない。クロージャ `0x100276528` が `0x10026e844` へ落ち、そこが `ShiftInstance` の start（+0x30）と end（+0x34）を `WorkRecord` にコピーする。`0x100267318` は「はじまりまで あと」「終わりまで あと」の残り時間表示で、給与の日付は変えない。

ゲートに使う日付は `0x100260e08` の戻りで、`Date()` か `Context.date` かは閉じていない。休憩の按分が読むのは、1秒タイムラインの中の `Context.date` である。

`0x10011b210` は `x0` を WorkRecord として受け取る。`0x10011b208` は `x2` を、それまでの分数を指す Double として保存する。給与関数はコピーされた start から end までを 60 秒ずつ進める。この経路に `min(now, end)` の書き込みは無い。したがって、渡されたレコードが予定の開始と終了なら、金額の区間もその予定である。7500円は「予定8時間・按分後の休憩30分・時給1000」をこの式に入れた値であり、画面の確認ではない。

時給（`PayMethod` が daily ではない）:

- BreakSpan が1つでもあると、分数の割合は 1 のまま。中点がその区間に入る分は1分ずつ落とす。`breakMinutes` の按分は使わない
- BreakSpan が無いとき、割合は `max(0, 全体分 - breakMinutes) / 全体分`。全体分が 0 以下なら 0
- 円は `支払った分 * 時給 / 60` を `PayResult.base`（+8）へ加算する
- 時給の整数は、中点の分が `WageBand` の中なら `hourlyWage`。そうでなければ `0x1000de424` の戻り（`Workplace.wageHistory`、ラベルは「時給」）
- 8時間・休憩60・時給1000・BreakSpan なしなら 7000。勤務中に休憩だけ30へ按分すると 7500 であり、予定金額の半分ではない

深夜。`NightPremium` の start/end。start と end が同じなら窓は空。start < end なら `start <= 分 < end`。そうでなければ日をまたぐ。窓の中で、enabled、バンドの `includesNightPremium` が 0、rate が 0 でないとき、`premium += その分の基本給 * rate / 100`。

残業。`prior + この分` が threshold を超えた分だけ。threshold ちょうどに着く分は 0。既に超えていればその分は全部。`premium += 残業分 * 時給 / 60 * rate / 100`。prior は引数 `x2`。

休日。`DateComponents.weekday - 1` が `ratePercentByWeekday` の範囲なら、`premium += その分の基本給 * rate / 100`。曜日が無い、または範囲外ならここでは足さない。

時給の選択。`0x1000de424` は `wageHistory` を末尾から戻る。`effectiveFrom` を年月日の日付にして、シフト日の `startOfDay` と `<=`（`0x1000de848`）で比べ、最初に当たった要素の `hourlyWage`（+0x18）を返す。履歴が空なら 0。全部がシフト日より後のときの戻りは閉じていない。配列が日付順であることは、このループは検査していない。

日給。エンジンは daily のとき時給の乗算に入らない。`0x10011a36c` の `UUID.==` が真で、かつ `PayMethod == daily` のとき `dailyWage` を base に足す。偽のときは金額を足さず、`dayItemsElsewhere` に「日給」を追加する。比べている二つの UUID のフィールド名は閉じていない。別の分岐も、二つの witness が 1 を返し method が daily なら同じ加算へ飛ぶ。

支給項目。`0x100119384` では `unit == perPeriod`（2）を飛ばす。`kind` が transport（0）以外もこの加算に来ない。`condition == nightWork`（1）のときは `ShiftPay.nightMinutes > 0` が必要。`amount >= 1` を一度だけ `PayResult.transport` に足す。perShift も perDay も、通過すれば同じ整数加算である。perDay の前には UUID と比較回数の検査があり、その規則は閉じていない。「日数倍」ではない。手当（kind 1）と控除（kind 2）を allowance / deduction に足す命令は、この呼び出し元と `0x10011b1d0` には無かった。

表示。`0x10026ecf0` が base と premium を読み、`0x10026ed14` で足す。受け取る `0x10026efb0` は、その和を `ContentTransition.numericText(value:)` に渡し、同じ関数で「終わりまで あと 」（`0x100502250`）と「円」（`0x10026f67c` の `e5 86 86`）も作る。文字の大きさは 13。これは構築順であり、画面上の配置を見た結果ではない。交通費・手当・控除はこの和に入らない。

「いま稼いだお給料」（`0x100502270`）は別関数 `0x10026b214` の accessibility 文言である。金額の `numericText` ではない。「シフトを追加」（`0x1004fb480`）は一覧ビルダー `0x1002616f4` のボタン文言。`0x100267318` は開始前なら「はじまりまで あと 」、そうでなければ「終わりまで あと 」を、残り時間の文字列に付ける。

ゲート日付はまだ `now` とは言えない。`0x100260e08` は給与側と同じ key path `0x10043a5d8` / `0x10043a600` の `Published` を読み、`ShiftInstance.end > 渡された日付` の要素を残す。その値が通る `0x1001c88b0` は `Calendar.Component.day` を読んだあと `date(byAdding:value:to:wrappingComponents:)` を value 1、wrapping false で呼ぶ。戻りが「今」かは閉じていない。

Timeline の `by`（30秒が2箇所、1秒が1箇所）は、このクロージャと結べていない。60秒は金額を刻む単位であり、画面の更新周期ではない。

## シフトパターンを選んだ日へ置く

これは元の `ShiftPart` を選んだ日へ置く経路の再構成である。元の Swift ソースではない。画面の配置は見ていない。`WeekTemplate`（`id` / `name` / `entries`、`AppData.weekTemplates`）はこのタップの命令には出てこない。曜日の繰り返しは別経路で、ここには混ぜない。

保存されるパターンは `ShiftPart`（descriptor `0x10044075c`）。フィールドは `id`, `name`, `workplaceID`, `startMinute`, `endMinute`, `breakMinutes`, `defaultTodos`, `hidden`, `color`。`AppData`（`0x10043f4b0`）とその `CodingKeys`（`0x10043f4d4`）に `shiftParts` がある。配置関数の先頭 `0x1001e5634` は、渡された配列から `UUID.==` でその `ShiftPart` を探す。

入口は二つ。どちらも衝突配列の要素数が 0 のときだけ確定処理 `0x100014370` を呼び、0 でないときは `PendingPlace` を状態へ書いて確定処理を呼ばない。

- 日チップのボタン動作 `0x10003fe54`。`0x10003ffa8` が要素数 0 で `0x1000400dc` へ飛び、`0x100040134` が `0x100014370`。衝突があるときは `PendingPlace`（`id` は新しい UUID、`partID` は metadata +0x14、`days` は +0x18、`clashes` は +0x1c）を作り、`CalendarDayView.__pendingPlace`（metadata +0x30、`0x10004006c`）へ `LazyState` の setter で書く
- カレンダーのパターン行 `0x10006e04c`。先に `CalendarTabView.__picked`（metadata +0x28、`0x10006e138`）を読む。`0x10006e2ec` が衝突 0 で `0x10006e3c8` の同じ確定処理へ飛ぶ。衝突があるときは `__pendingPlace`（metadata +0x3c、`0x10006e354`）へ書く

`PendingPlace`（`0x10043e4d0`）は `id`, `partID`, `days`, `clashes`。これはビューの状態であり、`AppData` のフィールドではない。

衝突の中身は `0x1000177dc`。選んだ日（1要素 24 バイト）ごとに、その日の `ShiftInstance` を `0x1001c88b0` から得る。`partID`（metadata +0x14）が今のパターンと `UUID.==`（`0x100017b1c`）なら、その日は重なり検査を呼ばず、衝突文字列も足さない。違う `partID` のときだけ `0x100016734` を、パターンの `workplaceID`、`startMinute`、`endMinute` で呼ぶ。戻った文字列が空でなければ、それを衝突配列に足す。`0x1001b4e08` はその重なり側が呼ぶ整形で、「のシフトがあります」（`0x1005001b0`）を読む。他の重なり文言がこの命令から読まれることは、ここでは閉じていない。

確定処理 `0x100014370` は `0x10001464c` で配置 `0x1001c75ec` を呼ぶ。配置が読むものと、読まないものは次のとおり。

- `workplaceID`（`ShiftPart` metadata +0x18、`0x1001c7b64`）で勤務先を探す。戻りが無い（タグ 1、`0x1001c7bd0` の `cmp #1`）ときは、日のループの前に `0x1001c7c18` で戻る。勤務先が無いと、どの日にも置かない
- 日のループは 24 バイト刻み。その日の既存 `ShiftInstance.partID` が同じなら `0x1001c7e28` から `0x1001c80f4` へ飛び、その日は足さない。同じパターンの二枚目は作らない
- `startMinute`（+0x1c）と `endMinute`（+0x20）を 1440 分へ折り返し、時と分に分ける。秒は 0。`bySettingHour`（`0x1003fce9c`）の追加引数に読む方針は `nextTime`、`first`、`forward`。開始は `0x1001c7fe8`、終了は `0x1001c82bc`
- `startMinute >= endMinute`（`0x1001c80a4` の比較、`0x1001c80b0` が以上で `0x1001c810c`）のとき、終了の `bySettingHour` の前に `Calendar.Component.day`（GOT `0x10056bbb8`、`0x1001c7d44`）を 1、wrapping false で足す（`0x1001c814c` が 1、`0x1001c8154` が 0、`0x1001c815c` が `byAdding`）。同じ分も翌日である
- `defaultTodos`（metadata +0x28）の各要素は新しい UUID を持つ `ShiftTodo` としてコピーし、`done` のバイトに 0 を書く（`0x1001c85bc`）
- 確定処理が配置へ渡す休憩の Optional は、ペイロード 0、タグ 1 で空である（`0x100014618` から `0x100014630`）。配置自身は `ShiftPart.breakMinutes`（metadata +0x24）を読まない。`0x1001de8dc` が書く `Meta.breakMinutes` は、この空の Optional である。休憩規則の選択 `0x1000e967c` はこのタップから呼ばれない

したがって、パターンに保存された `breakMinutes` を新しいシフトへ写す命令は、この経路では見つかっていない。製品側で法定休憩や「パターンの休憩をそのまま写す」を、この関数の代わりに置かない。

確定処理の成功側が読む文言は `inout.adsRemoved`（`0x1004fae70`、命令は `0x100014668`）。「保存しました」（`0x1004fae90`）は隣の文字列で、この命令の参照先ではない。認可が通らない側 `0x100014824` が読むアドレスは `0x1004faee0` で、cstring「保存できませんでした。もう一度お試しください。」の後半「もう一度お試しください。」に当たる。画面でその文が見えることは確認していない。

分の折り返しと、`start >= end` で終了を翌日にする比較は `tests/PatternPlace.swift` と `tools/verify_macos.py` にある。

## 画面。型と、命令が読む文言

元の Swift ソースではない。画面を見て書いた配置ではない。`Assets.car` とローカライズ資源はこの公開バイナリにも、この解析環境にも無い。色、画像、フォントファイルの中身はここから取れない。広告の `BannerAdView` は型としてはあるが、写す対象から外す。

`__swift5_types` にある画面型は次のとおり。descriptor は型名の位置で、アクセサは descriptor +12 の相対ポインタ。

| 型 | descriptor | アクセサ |
| --- | --- | --- |
| RootView | `0x1004403f8` | `0x10017876c` |
| InOutTab / InOutTabBar | `0x10043dca4` / `0x10043dcc0` | InOutTabBar は `0x10002f47c` |
| LaunchAnimationView | `0x10043f40c` | `0x1000d6708` |
| OnboardingView | `0x10043f998` | `0x10010423c` |
| WorkplaceListView | `0x100440e64` | `0x100255730` |
| WorkplaceDirectoryView | `0x100440b40` | `0x10021c788` |
| WorkplaceEditorView | `0x100440b90` | `0x10022ce3c` |
| WorkplaceImportView | `0x100440cd8` | `0x100249690` |
| WorkplaceThumbnailView | `0x100440eb4` | `0x10027a1d8` |
| LocationPickerView | `0x100440bb8` | `0x10023c87c` |
| CalendarTabView | `0x10043e520` | `0x100071b0c` |
| CalendarDayView | `0x10043e434` | `0x10003b030` |
| CalendarAccessView | `0x10043e3b4` | `0x100038674` |
| IncomeView | `0x10043f1d0` | `0x1000ba02c` |
| WallEditorView | `0x10043f1f8` | `0x1000c1994` |
| SettingsView | `0x100440448` | `0x10018d1c8` |
| AboutView | `0x10043d9ac` | `0x100009a10` |
| GuideOverlay | `0x10043edd0` | `0x1000a4f84` |
| ShiftPartEditorView | `0x1004408a0` | `0x1001f605c` |
| ShiftRepeatEditorView | `0x100440968` | `0x1001fc9bc` |
| ShiftRequestView | `0x100440a58` | `0x100213818` |
| ShiftRequestPlannerView | `0x1004409b8` | `0x1001fecf4` |
| RequestHoursStockSheet | `0x1004409e0` | `0x10020fefc` |
| ShiftCheckView | `0x1004404dc` | `0x1001a3730` |
| LateMessageView | `0x10043f300` | `0x1000cede8` |
| LateTemplateSheet | `0x10043f344` | `0x1000d5358` |
| LateTemplateEditorView | `0x10043f394` | `0x1000d59c8` |
| PayBreakdownView | `0x10043fa30` | `0x1001165c0` |
| PayPeriodsView | `0x100440050` | `0x100153adc` |
| PayPeriodDetailView | `0x100440078` | `0x100153ed8` |
| PayScheduleSettingView | `0x100440150` | `0x100158a58` |
| PayTermsEditorView | `0x100440218` | `0x10015b660` |
| PayScheduleEditorView | `0x100440240` | `0x10015b810` |
| UnconfirmedShiftsView | `0x100440028` | `0x100151334` |

body が単一の `B` で繋がっているのは、確認できた範囲では `CalendarTabView` の `0x100071b20` → `0x1000541dc` と、`IncomeView` の `0x1000ba040` → `0x1000b2154` だけである。他の画面は、アクセサの次が body そのものとは限らない。

body または、以前から結んであるビルダーが、cstring の先頭を読む文言:

- `CalendarTabView` body `0x1000541dc` は「この日に置く」
- `CalendarDayView` の `0x10003cdd8`（4608 バイト）は「確認が必要です」
- 一覧カード `0x1002616f4` は「シフトを追加」。金額側は前節のとおり「終わりまで あと 」と「円」。これは構築順であり、画面の配置ではない
- `0x10025ca2c`（8900 バイト。一覧アクセサの近く）は「今日のお給料」「今月のお給料」「支払日を設定」。この関数が一覧の body であることは未確定

画面型へは未接続のまま、関数が cstring の先頭を読む文言。製品は文言として使ってよい。どの画面のどの位置かは、この表だけでは決まらない。

- `0x1000c4b00` 遅刻の定型: 「寝坊してしまって」「寝坊してしまい」「体調が優れないため」「体調が悪くて」「電車の遅延で」「分ほど遅れます」
- `0x1000c6684` 「電車の遅延のため」「① 遅れる理由」「② 遅れる時間」「③ 言葉づかい」「文章はここで直せます。①〜③の答えを変えると作り直します。」
- `0x1000d2a5c` 「分くらい遅れます」「ごろになります」
- `0x10018dc8c` 「メッセージの文章」「シフトの重なり」「IN/OUT について」
- `0x100194a98` 「設定アプリで許可する」「リマインダー」「位置情報の許可」
- `0x100190464` 「位置情報を許可する」「シフトの前に通知」
- `0x100038a40` 「入力を続ける」「設定アプリを開く」
- `0x10022e830` 「遅刻連絡の文章の型」「住所・位置（任意）」「この勤務先を削除」
- `0x10021ec98` 「勤務先を追加」「シフトパターンを開く」
- `0x10023eff4` 「ショップカード」「Google マップのリンク」「Google マップ」
- `0x100107ec0` 「勤務先を登録」「いつものシフト」「お給料の決まり」
- `0x100067fec` と `0x10006852c` 「月の収入見込み」「シフトパターンを編集」
- `0x10010ca0c` 「深夜割増（22時〜5時）」「この日のシフトを編集」
- `0x1001bdcfc` 「追加して次へ」「シフトパターンに追加」「勤務先に戻す」「行き先の名前」
- `0x1001ba1b4` 「このまま保存」「この日のシフトを外す」
- `0x1001685ac` 「決まりの変更を追加」「締め日と支払日」「締めと支払日」「締めの曜日までの7日間が1回分です。0日は締め日に支払います。」
- `0x100115d6c` 「締め日に支給」「分単位（開始は」
- `0x1001138b4` 「勤務日に支給」「お給料（交通費の前）」
- `0x100166994` 「交通費を削除」「交通費を追加」
- `0x10014bcdc` 「未確認の勤務 」「終わった勤務を押すと、時間・休憩を確認できます。」
- `0x10014e3b4` 「明細の金額を保存」「差引支給額の差」
- `0x10008df54` 「休憩の決まりを追加」「この時間を超えたら」
- `0x1002145c8` 「ストックして入れる」「例：家の用事で」
- `0x10017c7f0` 「App Store を開く」「この日のシフトを編集」

「この日のシフトはありません」は `0x100502200` に cstring としてある。上の adrp / add / sub #0x20 の走査では、どの関数もこの先頭を読んでいない。

## フォントと記号

`Font.custom(_:size:relativeTo:)` のスタブは `0x1003fde2c`。名前は cstring ではなく、15 バイトの small string 即値である。21 箇所が両半分を即値で渡す。バイト列は `Doto-BlackRound`。`0x10026f494` からの `mov` / `movk` がそれである。金額の `0x10026efb0` は `0x10026f4b8` でこのフォントを呼び、その直前のサイズは 36。

即値でサイズまで読めた呼び出し:

| 呼び出し | 関数 | サイズ |
| --- | --- | --- |
| `0x10005e4d4` | `0x10005e184` | 64 |
| `0x10005e7cc` | `0x10005e184` | 24 |
| `0x100063208` | `0x100062150` | 18 |
| `0x100069364` | `0x100069168` | 18 |
| `0x1000b4334` | `0x1000b41c0` | 64 |
| `0x1000b50b8` | `0x1000b4ee4` | 64 |
| `0x1000bade0` | `0x1000bac3c` | 36 |
| `0x1000bb3b4` | `0x1000bb108` | 36 |
| `0x1000bc12c` | `0x1000bbcb0` | 24 |
| `0x100193a6c` | `0x100193884` | 24 |
| `0x1001abe90` | `0x1001aba88` | 44 |
| `0x1001af490` | `0x1001af2e0` | 36 |
| `0x100203d48` | `0x100203ae8` | 40 |
| `0x1002064b8` | `0x100206118` | 20 |
| `0x1002232f4` | `0x100222e8c` | 36 |
| `0x100260bac` | `0x100260714` | 64 |
| `0x100266d3c` | `0x100266998` | 36 |
| `0x10026be80` | `0x10026bc9c` | 18 |
| `0x10026e3fc` | `0x10026e260` | 36 |
| `0x10026f4b8` | `0x10026efb0` | 36 |

`0x1000697b4` も名前の即値は `Doto-BlackRound` だが、サイズは `v8` で、呼び出し直前の即値ではない。`0x1000bc508` のサイズは 24 だが、名前の前半レジスタは別の値で上書きされており、`Doto-BlackRound` とは確定できない。

`Image(systemName:)` の名前は、後ろの「Image(systemName:) の 41 呼び出し」にまとめた。

`Font.system`、`Font.Weight` の bold / heavy / medium / semibold、`UIFontWeightBold` / `Medium` / `Regular`、`RoundedRectangle`、`RoundedCornerStyle.continuous` / `circular`、`fullScreenCover` は import としてある。`RoundedRectangle` のイニシャライザ呼び出しは、この走査の import には無かった。角丸は `presentationCornerRadius` の 4 箇所だけが即値を持つ。

検証は `tests/UiFont.swift` と `tools/verify_macos.py`。フォント名の即値と、画面型の名前がバイナリにあることを見る。

## Assets.car の名前と色

`Assets.car` と `Doto-BlackRound.ttf` は公開リポジトリに置いていない。フォントは Google Fonts の Doto なので、製品側は公式の配布を使う。カタログの画像バイトも保存していない。

手順は `tools/decode_assets_car.py`。BOMStore の索引から `RENDITIONS` と `APPEARANCEKEYS` を読み、CSI ヘッダ（`ISTC`）の layout 1009 を色として読む。これは `assetutil --info` が見るのと同じ CoreUI レコードである。`assetutil` 自体は、カタログを公開ランナーへ置くことになるため実行していない。取り出した値は `notes/assets.json`。

色は sRGB（color info の下位 8 ビットが 1）。成分は R, G, B, A の 0...1。

| 名前 | appearance | sRGB8 |
| --- | --- | --- |
| AccentColor | `UIAppearanceAny`（0） | `0, 0, 0, 255` |
| AccentColor | `UIAppearanceDark`（1） | `255, 255, 255, 255` |
| LaunchBackground | `UIAppearanceAny` のみ | `195, 255, 119, 255`（成分 0.765, 1, 0.467, 1） |

ダークの AccentColor は白、それ以外は黒。LaunchBackground にダークのレコードは無い。

画像セットの facet 名: `AbukuCameraIcon`, `AccentColor`, `AppIcon`, `GraffLogo`, `LaunchBackground`, `LifeClctIcon`, `LifeCtrlIcon`, `Logo`, `PickPicIcon`, `SetupCalendar`, `SetupPay`, `SetupShift`, `SetupWorkplace`, `SourceBrowserIcon`, `TimeDay`, `TimeMorning`, `TimeNight`。

レンディションのサイズ。JPEG は SOF の画素、それ以外は CSI の幅と高さ。scale factor はいずれも 100（@1x の記録）で、Idiom フィールドは AppIcon 系だけ 1、ほかは 0。

- `SetupCalendar.jpg` / `SetupPay.jpg` / `SetupShift.jpg` / `SetupWorkplace.jpg`: 1200×800
- `TimeDay.jpg` / `TimeMorning.jpg`: 1400×583。`TimeNight.jpg`: 1400×582
- `Logo.png`: 1173×1138。`graff_logo.png` と `graff_logo_dark.png`: 1637×615。後者だけ `UIAppearanceDark`
- `icon.png`: 180×180 が 1、256×256 が 3、1024×1024 が 1。`AppIcon-1024.png`: 1024×1024。`AppIcon` は layout 1010 のマルチサイズで、画素は持たない

バイナリとの接続。`AccentColor` と `LaunchBackground` の綴りは Mach-O の cstring に無い。色名を即値で読む命令も、この走査では見つかっていない。SwiftUI がカタログの AccentColor を自動で使う可能性はあるが、命令では結べていない。

cstring としてあるのは次だけ。

- `SourceBrowserIcon` は `0x1004ff3e0`
- `LifeCtrlIcon` `0x1005b3080`、直前のラベル `LIFE/CTRL` `0x1005b3060`
- `LifeClctIcon` `0x1005b30b8`、`LIFE/CLCT` `0x1005b3098`
- `PickPicIcon` `0x1005b30f0`、`PICK/PIC` `0x1005b30d0`
- `AbukuCameraIcon` `0x1005b3128`、`ABUKU/CAMERA` `0x1005b3108`

これらは `__DATA` の名前表で、どのビューの `Image` が読むかは未接続。

## 画面ごとの関数

これは view tree の積み順ではない。その画面型のアクセサを呼び、ほかの画面型のアクセサは呼ばない関数のうち、いちばん大きいものをその画面のコードとした。コンテナ（複数の画面型を呼ぶ関数）は外してある。

| 画面 | 関数 | サイズ |
| --- | --- | --- |
| AboutView | `0x100004c68` | 952 |
| CalendarAccessView | `0x100038a40` | 4196 |
| CalendarDayView | `0x10003cdd8` | 4608 |
| CalendarTabView | `0x100062150` | 10368 |
| GuideOverlay | `0x1000a19b4` | 3348 |
| InOutTabBar | `0x100025004` | 1908 |
| IncomeView | `0x1000b7b78` | 2936 |
| LateMessageView | `0x1000c551c` | 4456 |
| LateTemplateEditorView | `0x1000cc078` | 2728 |
| LateTemplateSheet | `0x1000cda38` | 1636 |
| LaunchAnimationView | `0x1000d67ec` | 1068 |
| LocationPickerView | `0x100237b98` | 1772 |
| OnboardingView | `0x10010ea20` | 4788 |
| PayPeriodDetailView | `0x10014e3b4` | 2060 |
| PayPeriodsView | `0x1001460b8` | 1864 |
| PayScheduleEditorView | `0x10016a974` | 2144 |
| PayScheduleSettingView | `0x10014cb30` | 1824 |
| PayTermsEditorView | `0x10015e4ac` | 4512 |
| RequestHoursStockSheet | `0x10020d3d4` | 1944 |
| RootView | `0x10017fc6c` | 3620 |
| SettingsView | `0x10018dc8c` | 5164 |
| ShiftCheckView | `0x1001a6ab4` | 3276 |
| ShiftPartEditorView | `0x1001f0144` | 3040 |
| ShiftRepeatEditorView | `0x1001fa340` | 2280 |
| ShiftRequestPlannerView | `0x1002091c4` | 2976 |
| ShiftRequestView | `0x1002145c8` | 2872 |
| UnconfirmedShiftsView | `0x10014fa50` | 1744 |
| WallEditorView | `0x1000be874` | 2800 |
| WorkplaceDirectoryView | `0x10021dc9c` | 3776 |
| WorkplaceEditorView | `0x10022e830` | 8772 |
| WorkplaceImportView | `0x100243ca8` | 2388 |
| WorkplaceListView | `0x10025ca2c` | 8900 |

`PayBreakdownView` と `WorkplaceThumbnailView` は、ほかの画面と分かれた関数が無い。`CalendarTabView` の body 分岐先 `0x1000541dc` は `CalendarDayView` も呼ぶので、上の表ではタブ側の専用関数 `0x100062150` を載せている。一覧カード `0x1002616f4` は `WorkplaceListView` だけを呼ぶ 7216 バイトで、上の 8900 バイト関数の次に大きい。

積み順、余白、角丸は次の節。この表の関数の多くは、そのスタブを直接呼ばない。

## Image(systemName:) の 41 呼び出し

スタブは `0x1003fe360`。直前のレジスタが small string か、カウント付き cstring なら名前を確定した。

| 名前 | 呼び出し |
| --- | --- |
| `slider.horizontal` | `0x1000253f0`（`w21 == 0`）。カウント 17。cstring は `slider.horizontal.3` だが、末尾の `.3` はカウントの外 |
| `calendar` | `0x1000253f0`（`w21 == 1`） |
| `building.2` | `0x1000253f0`（`w21 == 2`） |
| `yensign` | `0x1000253f0`（`w21 == 3`） |
| `chevron.right` | `0x100005bec`, `0x1000b7528`, `0x10018fa54`, `0x1002263b4`, `0x10026dfc0` |
| `arrow.up.right` | `0x100006a18`, `0x100199f98` |
| `plus` | `0x10006be48`, `0x10006e650`, `0x1000b88d0`, `0x1001727b4`, `0x100193ebc`, `0x10021f8cc`, `0x100226810`, `0x10026fae8` |
| `xmark` | `0x100093d24`, `0x10020cc00` |
| `questionmark` | `0x1000a10f0` |
| `minus` | `0x100193588` |
| `minus.circle` | `0x1001ae220` |
| `ellipsis` | `0x100222cec`, `0x100269c24` |
| `checkmark` | `0x100245c3c` |
| `pencil` | `0x10026905c` |
| 「この日のシフト」 | `0x100067648`, `0x10017ca58`。カウント 0x15 の 21 バイトで、SF Symbol の名前ではない |

`0x1000253f0` は `InOutTabBar` の関数 `0x100025004` にある。`0x1000253c0` がカウント 17（`0xD000` 付き）を作り、`0x1000253d0` のポインタは `0x1004fb0e0`。`w21 == 0` の `csel` がこの組を選ぶ。`x0` がカウント、`x1` がポインタで、ほかの長い文字列と同じ順である。`w21` が 0, 1, 2, 3 のどれでもないときは、カウント 19 で `0x1004fb0c0` を渡す。そこは `income` の前のパディングで、タブの記号ではない。

### 残りの 14 呼び出し

確定。

| 呼び出し | 条件 | 渡す文字列 |
| --- | --- | --- |
| `0x10002c04c` | `[x20,#0x18]` のバイトが 0 | `questionmark` |
| `0x10002c04c` | そのバイトが 0 でない | `exclamationmark` |
| `0x100043474` | `[x28,#0x10]` のバイトが 0 | `calendar` |
| `0x100043474` | そのバイトが 0 でない | `checklist` |
| `0x10004436c`, `0x1001f4cf8`, `0x100264c30` | `ShiftTodo.done`（metadata +0x18）が 0 | `circle` |
| 上の 3 つ | `done` が 0 でない | 21 バイトの「この日のシフト」。`0x1004fb4a0`。SF Symbol の名前ではない |
| `0x1002216a4` | `0x10007ed6c` の戻り値のビット 0 が 1 | `chevron.up` |
| `0x1002216a4` | そのビットが 0 | `chevron.down` |
| `0x100208360` | `0x100208a50` への引数 | `briefcase.fill` |

バイトのフィールド名と、`chevron` のビットがどの状態かは未確定。`0x1004fb4c0` に 21 バイトの `checkmark.circle.fill` がある。上の `done != 0` が読むのはその 0x20 手前で、カウント 21 は「この日のシフト」で尽きる。

未確定。命令が渡すアドレスと、0x20 後ろの記号を分けて書く。

| 呼び出し | 命令が渡すもの | 0x20 後ろにあるもの |
| --- | --- | --- |
| `0x100066e2c` | カウント 29、`0x1004fb7c0`。UTF-8 として読めない | `exclamationmark.triangle.fill`（29 バイト） |
| `0x10008ab80` | カウント 23、`0x1004fb980`。UTF-8 として読めない | `chevron.up.chevron.down`（23 バイト） |

金額の「終わりまで あと」は、同じ `add` のあと `sub #0x20` したアドレスが本文だった。この 2 つもその形なので、後ろの記号を引数にはしない。`0x100066e2c` は `w26` のビット 0 が立っているときだけこの呼び出しへ来る。

引数が呼び出し元の文字列で、即値がこの関数に無いもの。

- `0x1001f52f0` は `0x1001f5204` の `x0`,`x1` を渡す。直接の `bl` 呼び出し元は無い
- `0x100205a04` は `0x100205984` の `x0`,`x1` を渡す。直接の `bl` 呼び出し元は無い
- `0x100208bfc` は `0x100208a50` の引数。もう一方の呼び出し元 `0x100208810` はレジスタのまま
- `0x10026d1b0` は `0x10026d128` の `x0`,`x1`。直接の `bl` 呼び出し元は無い
- `0x10027daa8` は `0x10027da1c` の `x0`,`x1`。直接の `bl` 呼び出し元は無い
- `0x1002798b8` は、オブジェクト先頭のバイトが 1 のとき、その +8 に入っている文字列を渡す。0 とそれ以外は別の分岐で、即値の記号名は無い

## ビューツリーの即値

`VStack` `0x1003fe528`、`HStack` `0x1003fe498`、`ZStack` `0x1003fe540`、`padding(CGFloat)` `0x1003fe210`、`padding(Edge.Set, CGFloat?)` `0x1003fe21c`、`presentationCornerRadius` `0x1003fe15c`、`shadow` `0x1003fe1f8`。バイナリ全体で、この順に 5、3、1、1、6、4、1 回。`View.cornerRadius` の import は無い。

間隔と余白の Optional は、`x1` が `Double` のビット、`w2` がタグ。`HStack` は 3 箇所とも `x1 = 0`、`w2 = 1`。値が入る呼び出しは `w2 = 0`。したがって `w2 = 1` は空、`w2 = 0` は値がある。`VStack` で `x1 = 0` かつ `w2 = 0` の間隔は 0。

| 呼び出し | 関数 | 内容 |
| --- | --- | --- |
| `0x10002640c` | `0x100026364` | `VStack`、間隔 8 |
| `0x100029fe8` | `0x100029f00` | `VStack`、間隔 24。直後 `0x10002a010` の `padding` は 20 |
| `0x10002cc80` | `0x10002c99c` | `VStack`、間隔 0。`0x10002ccb8` の余白 20、`0x10002cd20` の余白 16 |
| `0x10002d270` | `0x10002d03c` | `VStack`、間隔 0。`0x10002c99c` が参照するサンクの先 |
| `0x100055d64` | `0x100055c88` | `VStack`、間隔 0。`0x100055da8` の余白 24。次の関数 `0x100055ddc` が余白 20 と 12 |
| `0x10002397c` | `0x1000237bc` | `HStack`、間隔は空。`0x1000239b4` の余白 16 |
| `0x10002d90c` | `0x10002d818` | `HStack`、間隔は空 |
| `0x100089cb0` | `0x100089b00` | `HStack`、間隔は空 |
| `0x100256064` | `0x100255ab0` | `ZStack`。`WorkplaceListView` のアクセサ `0x100255730` の近く。一覧の専用関数 `0x10025ca2c` の中ではない |
| `0x100026264` | `0x100025ca8` | `shadow`。`d0 = 14`、`d1 = 0`、`d2 = 5`。色は `x21` と `x27` で、即値ではない |

`shadow` の引数順は color, radius, x, y。色が浮動小数レジスタを使わないなら、radius 14、x 0、y 5。色の中身は未確定。

`presentationCornerRadius` は 4 箇所とも `x0` が 32.0 のビット、`w1` が 0。

| 呼び出し | 関数 | 画面との関係 |
| --- | --- | --- |
| `0x10003d5ac` | `0x10003cdd8` | `CalendarDayView` の専用関数の中。確定 |
| `0x100104d30` | `0x100104588` | `OnboardingView` のアクセサの近く。画面への帰属は未確定 |
| `0x1001a5f0c` | `0x1001a5a5c` | `ShiftCheckView` のアクセサの近く。画面への帰属は未確定 |
| `0x10020b0f0` | `0x10020ad88` | `RequestHoursStockSheet` のアクセサの近く。画面への帰属は未確定 |

主要画面の専用関数が、上のスタックと余白と角丸のスタブを呼ばない。

| 画面 | 関数 | この走査で直接あったもの |
| --- | --- | --- |
| カレンダー | `0x100062150` | `Font.custom` 18（`0x100063208`）と `Text.font`。body `0x1000541dc` は 0 |
| カレンダーの日 | `0x10003cdd8` | `presentationCornerRadius` 32 |
| 勤務先一覧 | `0x10025ca2c` | `Text.font` が 4。色の即値は無い |
| 一覧カード | `0x1002616f4` | `Text.font` と `foregroundStyle` が 1。色の即値は無い |
| 勤務先の編集 | `0x10022e830` | 0 |
| 給与 | `0x1000b7b78`、body `0x1000b2154`、`0x10015e4ac` | 0 |
| 設定 | `0x10018dc8c` | 0 |
| シフト編集 | `0x1001f0144` | 0 |

`Color(UIColor)` は `0x1000ac644` 付近の短い関数が 5 つ。画面の専用関数からは直接呼ばない。Doto のサイズは前の表のまま。`0x100063208` の 18 だけが、カレンダーの専用関数 `0x100062150` の中にある。

上の表が、命令から言えるビューツリーの全部である。カレンダー、勤務先、給与、設定、シフト編集シートの中で、子ビューがどの順に積まれるかは、これらの直接呼び出しには無い。ビルダーを別関数へ渡している可能性は残る。そのポインタは画面まで辿れていない。

## 重なり判定

`0x100016734`。既存の `ShiftInstance` を走査する。

- 要素先頭の文字列が、保存してある文字列と等しい（ポインタが一致するか、`0x1003ff080` の文字列比較が真）なら次へ進む
- `start`（metadata +0x30）< スタックの日付、かつもう一つの日付 < `end`（+0x34）なら、その場で衝突にする。比較は `Date.<`（`0x1003fcd4c`）。この分岐は `w22 = 1`、`x20 = 0`
- そうでなく、`workplaceID`（+0x24）が `UUID.==`（`0x1003fcdc4`）で等しく、`Calendar.isDate(_:inSameDayAs:)`（`0x1003fcecc`）が真なら衝突。`w22 = 1`、`x20 = 1`
- そうでなく、スタック +0x280 から読んだ `x20` を 60 倍した秒が 0 以下なら、移動の経路は飛ばす。`0x1000171f0` が 60、`0x100017368` が 0 との比較
- 残る経路は `Comparable.>=`（`0x1003fe96c`）で start 側か end 側かを選び、`timeIntervalSince`（`0x1003fcd1c`）の秒を取る。その秒が `x20 * 60` 未満のとき、60.0（`0x100017234` の `0x404e000000000000`）で割って整数にする

`x20` の元はスタック +0x280 で、`Workplace` のどのフィールドかは未確定。3 つの分岐のどれが「のシフトがあります」で、どれが移動時間の文言かは、この読みでは結んでいない。その文言を足す関数は引き続き `0x1001b4e08`。

## WeekTemplate

アクセサ `0x1001ec5a4` を呼ぶのは `0x1000e4934`、`0x1001dd510`、`0x1001e4ce8`、`0x1001ea190`、`0x1001ea598`。この 5 つは、選んだ日へ置く `0x1001c75ec` を呼ばない。`0x1000e4934` は `WeekTemplate.name`（+0x14）と `entries`（+0x18）を読み、要素の +0x14、+0x18、+0x1c、+0x20、+0x24 を読む。日付へ展開する `bySettingHour` は、この 5 つの中には無い。展開の有無は未確定で、このタップの対象は引き続き `ShiftPart` である。

## 置いたシフトの保存先

配置 `0x1001c75ec` は `AppModel` のアクセサ `0x10001c974` を呼ばない。次に呼ぶ `0x1001d1b74` も呼ばない。`AppModel` の `_data`、`_notice`、`_placements`、`lastPlacedAt` への書き込みは、この 2 関数には無い。Published の配列がどれかは未確定。

## 画面単位の移植仕様

一括移植の前に、画面とシート 36 を 9 観点で分けた。仕様は `notes/screens/`。広告と Intelligence は対象外。

確定率は 58 / 324 = 17.9%。確と部を合わせた着手率は 115 / 324 = 35.5%。積み順は 36 画面とも未。数の定義と画面ごとの印は `notes/screens/COVERAGE.md`。

この区切りで命令から足したもの。

- タブの中身を組む `0x100180b74` は `SettingsView`、`IncomeView`、`WorkplaceDirectoryView`、`CalendarTabView`、`WorkplaceListView` をこの順で呼ぶ。比較で 1 つを選ばない。`w21` との対応は未確定
- カレンダー body `0x1000541dc` は `sheet(item:)` が 3、`fullScreenCover(item:)` が 1、`alert` が 3 系統。開く型は `CalendarDayView`、`ShiftPartEditorView`、`ShiftRepeatEditorView`、`ShiftRequestPlannerView`。どのシートがどの型かは未確定
- 一覧ハブ `0x100255ab0` は `sheet` が 3、`sheet(item:)` が 5。勤務先エディタ、給与期間、未確認、オンボーディング、遅刻を呼ぶ
- `DragGesture` の `d0` が 30 なのは `0x10003d320`（日ビュー）、`0x1001ff96c`（依頼）、`0x100257310`（一覧）
- `RootView` だけの関数 `0x10017ba24` は `easeOut` の duration 0.35 のあと `withAnimation`
- `easeInOut` の duration 0.15 が 4 箇所、0.3 がガイドの近くに 1 箇所。画面への所属は未確定
- spring は response / damping / blend 0 で 4 組。0.28/0.88、0.24/0.85、0.55/0.68、0.45/0.50。再生する画面は未確定
- 通知クラスとセレクタの cstring はある。呼び出しと分数は未確定

## opaque 型の復元

`__swift5_typeref` に `TupleView`、`ModifiedContent`、`_ConditionalContent` の特殊化名は無い。`__swift5_types` に opaque type は無い。`swift_getOpaqueTypeMetadata2` の 363 回は、アプリの body ではなく SwiftUI メソッドの `QOMQ` を受け取る。padding、font、foregroundStyle の `QOMQ` は import に無い。積み順は 36 画面とも未のまま。

名前が付いた modifier の順は `notes/screens/opaque.md`。日ビューの関数では `presentationBackground`、`presentationCornerRadius`、`presentationDragIndicator`、`onChange`、`sheet`、`sheet`、`alert`。遅刻画面では `navigationTitle`、`navigationBarTitleDisplayMode`、`onChange`。

`ShiftEntryEditor` は descriptor `0x100440570`、アクセサ `0x1001b8554`、専用関数 `0x1001bdcfc`。`TodoEditor` は descriptor `0x1004408c8`、アクセサ `0x1001f641c`、専用関数 `0x1001f3d30`。`PayBreakdownView` のアクセサ `0x1001165c0` は、`bl` でも `adrp` + `add` でも参照されない。

網羅率は確 64 / 324 = 19.8%。未は 206。

## 画面関数が読む文言

その画面のアクセサだけを呼ぶ関数が、cstring の先頭を読む文字列を `notes/screens/copy.md` にまとめた。画面の中の位置は未確定。元のソースではない。

これで文言が確になった画面は 25。まだ未なのは、タブバー、起動、サムネイル、概要、ガイド、シフトパターン編集、遅刻の文章編集、給与明細の内訳、給与期間の一覧、支払日の設定、Todo 編集。

記号は勤務先ディレクトリの `0x1002216a4` が `chevron.up` か `chevron.down`。ビットの意味は未確定。フォントは依頼プランナー `0x100203ae8` の Doto 40 と、一覧 `0x10026bc9c` の Doto 18 を、その画面だけの関数として結んだ。余白と角丸と積み順の未は、この走査では減っていない。

網羅率は確 82 / 324 = 25.3%。未は 194。

## 実機スクショ

46 枚は公開していない。個人の金額、勤務先名、住所はノートに書いていない。スクショで見えた配置は `観` で、命令の `確` とは別である。詳細は `notes/screens/observed.md`。

タブは左から 一覧、カレンダー、勤務先、年収、設定。設定の記号は横スライダーに見え、`slider.horizontal` と一致する。左端の一覧の記号は、`w21` の 4 つの名前には入らない。

一覧、カレンダー、勤務先、年収、設定、登録の 3 段、パターン、曜日繰り返し、シフト希望、年収の壁、ガイドは、上から下の順を `観` にした。起動、遅刻、給与明細、未確認の一覧、シフト確認、Todo 編集はスクショに無い。

網羅率は `確` 82 / 324 = 25.3% のまま。`観` は 48。`未` は 146。

## 重なり、確認、明細

重なりの文言は `0x1001b4e08` が作る。バイトが 1 なら「のシフトがあります」か、付随文字列が空なら「と時間が重なっています」。1 でないときは「分しかありません（移動に」。題「このシフトは確認が必要です」と「このまま保存」はシフト編集の関数が読む。比較は `Date.<` で、端が同じ時刻だけの接触は入らない。日をまたぐ足し算は `0x100016de8` にある。移動時間は別の文言で、設定の説明文が「違う勤務先の間が移動時間より短い」と書く。`x20` のフィールド名は未確定。スクショの「やめる」は cstring に無い。

確認画面の題「おつかれさまでした」は `ShiftCheckView` の `0x1001a6ab4` が読む。ボタン「このとおり」は単独の cstring ではなく、質問「このとおりでしたか」の中にある。確認済みにする書き込みは、その関数の中には無い。

明細 `0x10014e3b4` は base、premium、allowance、transport と同じ並びの 4 つを足し、別の値から引く。説明文は差を「明細 − 見込み」とし、見込みは交通費まで、税金と社会保険は計算しない、と書く。個人の金額は書いていない。

`観` は 58。`未` は 136。`確` は 82 のまま。

## 設計サイズ

`Font.system` の直前で `d0` に入っているのは、多くの画面で `scaledValueForValue:` の戻り値である。その呼び出しの直前の `fmov d0, #N` が設計サイズで、描画サイズそのものではない。Dynamic Type で戻り値は変わり得る。

その画面のアクセサだけを呼ぶ関数が、この順で N を渡す。

| 画面 | 設計サイズ |
| --- | --- |
| ルート | 16 |
| 登録 | 13、16 |
| カレンダーの日 | 20 |
| カレンダーの許可 | 13、16、20 |
| 年収 | 16 |
| 年収の壁 | 16 |
| 設定 | 16 |
| ガイド | 13 |
| パターン編集 | 13、16 |
| シフト希望 | 13、16 |
| 時間のストック | 13、16、20 |
| 確認 | 13、16、20 |
| 遅刻の文章 | 13、16 |
| 遅刻の定型シート | 16。サイズの命令は `0x1000ce09c` にあり、呼ぶのはこの画面だけの関数 |
| 遅刻の定型編集 | 16。サイズの命令は `0x1000ccb20` にあり、呼ぶのはこの画面だけの関数 |
| 支給期間 | 13 |
| 給与の決まり | 13 |
| 未確認 | 13 |
| シフト編集 | 13、16 |
| 勤務先の取り込み | 13、16 |
| 場所の選択 | 13、16 |
| Todo 編集 | 16 |

例はカレンダー許可の `0x100038ed0` が 20、`0x1000390c0` が 16、`0x1000393f8` が 13。セレクタは `scaledValueForValue:`。`確` は 108。`未` は 120。積み順の `確` は 0。記号の `未` は 20 のまま。起動、勤務先の編集、サムネイル、概要、支払日の設定、支払日の編集、内訳には、この形の即値が無い。

## 画面だけの関数にある即値

`確` は 86。`未` は 133。積み順の `確` は 0 のまま。`LazyVStack` と `LazyVGrid` はカレンダーだけの `0x100058000` にある。中の並びは取れていない。

- 勤務先ディレクトリだけの `0x100220ee0` は `Font.system` のサイズ 14
- 一覧だけの `0x1002570c0` は `DragGesture` の距離 30
- ガイドの専用関数は `onTapGesture` の count 1
- 繰り返し編集だけの `0x1001fbdc0` は、重なり判定を呼ぶ関数を呼ぶ
- 角丸 32 は、日ビューとシフト編集を両方呼ぶ関数と、オンボーディングと勤務先の取り込みを両方呼ぶ関数にある。どちらの画面かは未確定
- 給与エンジンを呼ぶ関数は画面アクセサを呼ばない。画面への結びつきは未確定

## 未回収。画面で見る必要があるもの

- 日給の `UUID.==` がどの二つのフィールドか。加算と「日給」ラベルの分岐自体は命令にある
- perDay の UUID と回数の検査。通過後の金額は整数の一回加算まで確認した
- 手当と控除の加算。live の数字は base + premium で、この2つは入らない
- ゲート日付が `now` そのものか。1秒タイムラインの中の休憩按分が `Context.date` を読むことは確認した
- 時給履歴が日付順に並んでいるか、全部がシフト日より後のときの戻り
- 7500円を画面で見たこと。命令と単体テストは、その入力ならその金額になる、までである
- 休憩中に金額が止まる見た目。命令上、BreakSpan が無ければ休憩は予定区間から引くだけで、経過時間で区間は切らない。終了後の asOf が end になることと、按分が予定休憩に戻ることは確認済み
- 日をまたぐ丸め。この経路は各日付の startOfDay からの秒で、1440 分では巻かない。深夜の startOfDay をまたぐ見た目は未観察
- 年収の壁の閾値比較。週オフセットを ±1 する側
- 30 秒と 1 秒のどちらが勤務中の金額表示を更新するか
- パターンの `breakMinutes` を、選んだ日へ置いたシフトの `breakMinutes` へ写す命令。上のタップは `ShiftPart` のそのフィールドを読まず、カレンダー側 `Meta.breakMinutes` には空を渡す
- 重なりの 3 分岐のどれが「のシフトがあります」で、どれが移動時間の文言か。閾値 `x20` が `Workplace` のどのフィールドか
- `WeekTemplate` の要素を日付へ展開する命令。上の 5 関数には無い
- 置いた結果が `AppModel` のどの Published へ入るか。配置と `0x1001d1b74` は `AppModel` のアクセサを呼ばない
- 36 画面すべての積み順。直接の `VStack` / `HStack` は主要画面の専用関数の中に無い。画面単位の仕様と網羅率は `notes/screens/COVERAGE.md`
- `AccentColor` と `LaunchBackground` を命令がどのビューで塗るか。名前の cstring は Mach-O に無い
- `0x1000697b4` の Doto のサイズ。`0x1000bc508` のフォント名
- `0x100066e2c` と `0x10008ab80` の記号名。命令が渡すバイトは UTF-8 ではなく、0x20 後ろの記号は引数にしていない
- `0x1001f52f0`、`0x100205a04`、`0x100208810`、`0x10026d1b0`、`0x10027daa8`、`0x1002798b8` の記号名。引数は呼び出し元の文字列で、即値がこの関数に無い

## 保存確認、移動時間、取り込み、バージョン

`確` は 109。`未` は 119。ロジックの `未` は 27 から 26。オンボーディングのロジックを `確` にした。

シフト編集だけの `0x1001b9fe4` は、重なりの戻り配列が空なら保存へ進み、空でなければアラート用の状態へ書く。「このまま保存」と即値の「やめる」は、そのアラートのボタンである。移動の分岐も同じ配列に入る。分を 60 倍した秒が 0 以下のときは間隔を見ない。見たスクショの 30 分は即値ではない。

Google マップのリンクは取り込み画面の文字列である。失敗文もその画面だけの関数が読む。バージョンの lookup URL と `URLSession.sharedSession` は `0x10001e4d0` にあり、画面アクセサは呼ばない。「App Store を開く」はルートだけの関数が読む。

写真のダイアログはオンボーディングだけの `0x100106bc0` が作る。カメラのボタンは `isSourceTypeAvailable:` の 1 が真のときだけ入る。Vision の `performRequests` は、このボタンからは届いていない。

## 起動の待ち、編集の検査、位置情報

`確` は 113。`部` は 49。`未` は 114。ロジックの `未` は 26 から 23。ジェスチャの `未` は 16 から 14。

起動だけの `0x1000d732c` は、ビットが立っていれば 0.8 秒を `Duration.seconds` と `ContinuousClock` に渡し、立っていなければ spring 0.55 / 0.68 を 0.15 秒遅らせて `withAnimation` する。シフト編集のドラッグは日ビューと共有の `0x10003cdd8` にある。カレンダー許可の `OpacityTransition` はルート、ガイド、起動と共有の `0x10017ac70` にある。

シフト希望だけの `0x100215f10` は「月」を作り、一覧を 0 と 1 の 2 回取る。勤務先編集だけの `0x100236114` は空の名前、重複する適用開始日、0 円未満の時給を読む。場所の選択だけの `0x100238b4c` は、`x8` が 0 でないとき `requestWhenInUseAuthorization` のタスクへ進む。同じタスクは画面を持たない関数からも呼ばれる。

## 記号の経路、許可、取り込みの逆ジオコード

`確` は 130。`部` は 45。`観` は 43。`未` は 106。記号の `未` は 20 から 16。ロジックの `未` は 23 から 19。ジェスチャの `未` は 14 のまま。積み順の `確` は 0 のまま。`VStack` の 5 関数は、一つの画面のアクセサまで届かない。

`Image(systemName:)` の関数から、呼び出し元が一つずつしか無い経路で画面アクセサへ届く名前を、その画面の記号にした。画面の中の位置は見ていない。

- 概要は `chevron.right` と `arrow.up.right`
- 依頼プランナーは `briefcase.fill`。もう一つの呼び出し元はレジスタのまま
- 時間のストックは `xmark`
- Todo は `done == 0` の `circle`。`done != 0` の 21 バイトは「この日のシフト」で、記号名ではない
- 設定は `chevron.right`、`minus`、`plus`、`arrow.up.right`
- 年収は `chevron.right` と `plus`
- カレンダーの日は `calendar` か `checklist`、および `circle`
- カレンダーは `plus`。29 バイトを渡す呼び出しは、UTF-8 の記号名にしていない
- 確認は `minus.circle`
- 一覧は `plus`、`pencil`、`ellipsis`、`chevron.right`、`circle`

ルート、タブ、登録、確認は、その画面のアクセサだけを参照する関数が `withAnimation` か `OpacityTransition` を呼ぶ。依頼プランナーの `0x10020499c` と `0x100200fbc` も同じである。`OpacityTransition` の持続時間は、この呼び出しには無い。

設定だけの `0x100191250` と `0x1001945ec` は `requestAuthorizationWithOptions:completionHandler:` を呼び、`w2` は 7 である。設定だけの `0x1000f44d4` は `requestFullAccessToEventsWithCompletion:` を呼ぶ。カレンダー許可とオンボーディングは、別の `0x1001cce6c` を共有する。取り込みだけの 3 箇所は `reverseGeocodeLocation:completionHandler:` を呼ぶ。座標のフィールド名は閉じていない。`requestWhenInUseAuthorization` は、場所の選択と遅刻の両方から届く。通知の追加と削除は、まだ画面へ届かない。

## 四辺同じ余白

`確` は 149。`部` は 44。`観` は 33。`未` は 98。余白の `未` は 21 から 13。余白の `確` は 1 から 20。積み順の `確` は 0 のまま。記号の `未` は 16 のまま。ジェスチャの `未` は 14 のまま。ロジックの `未` は 19 のまま。

`EdgeInsets.init(_all:)` の直前が `fmov d0, #即値` で、その関数が画面アクセサだけに届くとき、その即値をその画面の余白にした。画面の中の位置は見ていない。`_FrameLayout` の幅と高さは余白にしていない。

| 画面 | `d0` | 代表 |
| --- | --- | --- |
| ルート | 16、20 | `0x10017bfb4` |
| タブ | 4、6、9、18 | `0x100024274` |
| オンボーディング | 8、12、16、20 | `0x10010640c` |
| 一覧 | 4、6、8、12、16、20、24、および -8、-6、-4 | `0x100257258` |
| ディレクトリ | 4、8、12、16、20、24 | `0x10021dc08` |
| 場所の選択 | 16 | `0x1002371a8` |
| カレンダー | 2、3、5、8、12、16、20 | `0x10005a4a8` |
| 日 | 4、8、12、20、24 | `0x10003e428` |
| カレンダー許可 | 24 | `0x100038de8` |
| 年収 | 8、20、24 | `0x1000b359c` |
| 年収の壁 | 10、14 | `0x1000bd640` |
| 設定 | 8、12、20、24 | `0x10018dc14` |
| ガイド | 20 | `0x1000a219c` |
| パターン編集 | 4 | `0x1001f1850` |
| シフト希望 | 10 | `0x100215518` |
| 依頼プランナー | 6、8、10、12、16 | `0x100201920` |
| 確認 | 8、20 | `0x1001a7c2c` |
| 定型文シート | 10 | `0x1000ce420` |
| シフト編集 | 4 | `0x1001be250` |
| Todo | 12 | `0x1001f28d0` |

時間のストックだけの関数には、このイニシャライザは無い。共有の `0x1002005ec` が 20、8、12 を渡し、呼び出し元 `0x1001ff66c` は依頼、プランナー、時間のストックを一緒に呼ぶ。取り込みの余白は、オンボーディングと共有の `0x100104588` が 20 と 12 を渡す側のまま。繰り返しの余白は、スクショの `観` のままにした。複数画面を呼ぶ関数の余白で、`観` を置き換えない。

`padding(Edge.Set)` の 24、20、12 は、カレンダー body が複数画面を呼ぶ関数に残る。子ビューの順は、この余白からは出ていない。`presentationCornerRadius` の残る 2 箇所（`0x1001a5f0c`、`0x10020b0f0`）は、画面アクセサまで届かない。

記号の残る 8 箇所、`VStack` の 4 箇所、`HStack` の 3 箇所は、相対ポインタの先で呼び出し元が切れる。ジェスチャの `未` 14 画面には、その画面だけへ届くドラッグ、タップ、`withAnimation`、`OpacityTransition` は無かった。ロジックの `未` は、検証文の近くに比較があっても、比較の対象が金額や時刻とは閉じていない。通知の追加と削除も、画面へ届いたままではない。

## 文言と、遅刻の置換の入口

`確` は 155。`部` は 43。`観` は 32。`未` は 94。文言の `未` は 7 から 3。ロジックの `部` は 6 から 5。積み順の `確` は 0 のまま。ジェスチャの `未` は 14 のまま。

概要だけの `0x1000066b4` は「GRAFF. のアプリをすべて見る」を読む。定型文の編集の専用関数は、宛名と理由と遅れの置き換えを説明する文を読む。別の関数 `0x1000ccf18` は二つの定型文を読む。支払日の設定の専用関数は「支給の見込み」を読む。同じ cstring は他の画面の関数も読む。支給期間の専用関数は「勤務先はまだ登録されていません」を読む。Todo だけの `0x1001f2b8c` は「やることを追加」を読む。画面の中の位置は見ていない。

遅刻だけの `0x1000d2f18` は「{宛名}」「{理由}」「{遅れ}」を順に `String.contains` へ渡す。同じ関数は、その前に `replacingOccurrences` を 5 回呼ぶ。5 回の検索文字列は閉じていない。宛名が空の行を省く処理は、説明文にはある。`contains` の飛び先がそれかは未確定。

`Form` の content は、遅刻では `0x1000d1f34` が `0x1000c6684` へ無条件で飛ぶ。繰り返しは `0x1001fe33c`、取り込みは `0x10024c524` ほか 2 つ。どの関数も `Section.create` のあいだに分岐がある。一つの子の並びにはしていない。

概要、定型文の編集、支払日の編集、勤務先の編集は `Font.system` を呼ぶ。サイズはレジスタで、即値は無い。サムネイルと内訳のアクセサは、descriptor の相対ポインタ以外からは指されていない。コードの `bl` も `adrp` + `add` も無い。この 2 画面の `未` は残る。ジェスチャの `未` 14 画面には、その画面だけへ届くドラッグ、タップ、`withAnimation`、`OpacityTransition` は無かった。
