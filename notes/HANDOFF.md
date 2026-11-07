# 統合担当への引き渡し

公開解析リポジトリの再構成。元の Swift ソースではない。広告はない。製品の私有コードは含まない。時給の円は `0x10011b1d0` の命令から再構成した。手当・控除の式は閉じていない。日給を足す条件の追加ビットの出所も未確定なので、そこを推測で埋めない。

## 検証済み commit

| 内容 | commit | macOS run |
| --- | --- | --- |
| 週数 × 7 日 | `febde5b6f02a26c9d13d8c164c9a100e499aaf9a` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42376695303 |
| 休憩の選択 | `0e24b5ab91b3` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377098813 |
| 編集画面の分数と秒の切り捨て | `19e5229a227f9ca73dcd551006f303393ac75b67` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377557969 |
| 丸めの適用と勤務中の休憩按分 | `cd54b571b0ae9bd95dcaf1b35f8e1862a61bfd69` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42379613656 |
| 時給の円と live の表示 | `fefc70d841ab498dedf96f964700bfa187c8770e` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42380430047 |

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

`0x10011b210` は `x0` を WorkRecord として受け取る。`0x10011b208` は `x2` を、それまでの分数を指す Double として保存する。給与関数はレコードの start から end までを 60 秒ずつ進める。`now` を end に書く命令はこの経路に無い。勤務中の `0x10026e844` が差し替えるのは `breakMinutes` だけなので、金額の区間は予定の開始から終了である。

時給（`PayMethod` が daily ではない）:

- BreakSpan が1つでもあると、分数の割合は 1 のまま。中点がその区間に入る分は1分ずつ落とす。`breakMinutes` の按分は使わない
- BreakSpan が無いとき、割合は `max(0, 全体分 - breakMinutes) / 全体分`。全体分が 0 以下なら 0
- 円は `支払った分 * 時給 / 60` を `PayResult.base`（+8）へ加算する
- 時給の整数は、中点の分が `WageBand` の中なら `hourlyWage`。そうでなければ `0x1000de424` の戻り（`Workplace.wageHistory`、ラベルは「時給」）
- 8時間・休憩60・時給1000・BreakSpan なしなら 7000。勤務中に休憩だけ30へ按分すると 7500 であり、予定金額の半分ではない

深夜。`NightPremium` の start/end。start と end が同じなら窓は空。start < end なら `start <= 分 < end`。そうでなければ日をまたぐ。窓の中で、enabled、バンドの `includesNightPremium` が 0、rate が 0 でないとき、`premium += その分の基本給 * rate / 100`。

残業。`prior + この分` が threshold を超えた分だけ。threshold ちょうどに着く分は 0。既に超えていればその分は全部。`premium += 残業分 * 時給 / 60 * rate / 100`。prior は引数 `x2`。

休日。`DateComponents.weekday - 1` が `ratePercentByWeekday` の範囲なら、`premium += その分の基本給 * rate / 100`。曜日が無い、または範囲外ならここでは足さない。

日給。エンジンは daily のとき上の乗算に入らない。呼び出し元 `0x100119384` が `PayMethod == daily`（バイト 1）かつ別の下位ビットが 1 のとき、`PayTerms.dailyWage` を base に足す。そのビットのフィールド名は特定していない。

支給項目。`PayItem.unit == perPeriod`（バイト 2）はこのループを飛ばす。`ExtraPayItem.kind == transport`（バイト 0）かつ `amount >= 1` の整数を `PayResult.transport`（+0x20）に足す。手当と控除の加算はこの命令ではない。

表示。`0x10026ecf0` が base と premium を読み、`0x10026ed14` で足し、`0x10026efb0` が `ContentTransition.numericText(value:)` に渡す。交通費・手当・控除はこの数字に入らない。`RollingYen` 型はこの和と結んでいない。

Timeline の `by`（30秒が2箇所、1秒が1箇所）は、このクロージャと結べていない。60秒は金額を刻む単位であり、画面の更新周期ではない。

## 未回収。画面で見る必要があるもの

- 日給を足す下位ビットのフィールド名。`PayMethod.daily` と `dailyWage` の加算自体は命令にある
- `PayItem` の perShift / perDay が金額へどう乗るか。perPeriod を飛ばすことと、交通の `ExtraPayItem` を transport に足すことだけ確認した
- 手当と控除の加算。live の数字は base + premium で、この2つは入らない
- 休憩中に金額が止まる見た目。命令上、BreakSpan が無ければ休憩は予定区間から引くだけで、経過時間で区間は切らない。終了後の asOf が end になることと、按分が予定休憩に戻ることは確認済み
- 日をまたぐ丸め。この経路は各日付の startOfDay からの秒で、1440 分では巻かない。深夜の startOfDay をまたぐ見た目は未観察
- 年収の壁の閾値比較。週オフセットを ±1 する側
- 30 秒と 1 秒のどちらが勤務中の金額表示を更新するか
