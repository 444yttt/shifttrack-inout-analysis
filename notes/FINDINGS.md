# IN/OUT 1.0 (3) から回収できたものと、できていないもの

対象は許諾済みの `com.graff.inout` IN/OUT 1.0 build 3 の実行ファイルだけ。公開物は `bin/IN-OUT`（署名領域を外し、広告ユニット ID・mailto の宛先・`embedded.mobileprovision` というファイル名文字列を同長で潰したもの）。元 IPA、`_CodeSignature`、プロビジョニングプロファイル、広告 SDK、フォントは置いていない。

sha256 `11b0cf24cb5beabcc440ab1b54ba8886aee25b9e6caf686009397289d8b3b4a5`、サイズ 6379760。`tools/verify_macos.py` がこの値と命令バイトを見る。

この文書の区分:

- **命令**: `bin/IN-OUT` の機械語を直接読んだ結果
- **疑似コード**: Ghidra 11.4 の出力。`notes/ghidra/`。元の Swift ではない
- **再構成**: その証拠から書き直した Swift。`recovered/InOutRecovered.swift`。元ソースの復元ではない
- **未回収**: 型名や画面の文言だけでは埋めていない

## バイナリの事実

- Mach-O 64-bit、ARM64、`MH_EXECUTE`、優先ロードアドレス `0x100000000`
- `LC_FUNCTION_STARTS` は 15672。値はファイル先頭からのオフセット（先頭 `0x4000`、末尾 `0x3fc950`）
- `n_type == 0x0f` の定義シンボルは `__mh_execute_header` だけ。ほかは未定義のインポート
- chained fixups のセグメント pointer format は 6（`DYLD_CHAINED_PTR_64_OFFSET`）。Ghidra の Mach-O loader も 36904 個の format 6 ポインタを報告した
- コード署名の load command は dataoff/datasize を 0 にし、署名バイトはファイルから切り落とした

## SwiftUI.View の witness

次のアドレスは単一の `B` で、計算した分岐先が body と一致する。シンボルテーブルにこれらの名前はない。型名は `__swift5_types` のフィールド記述と、以前の witness 追跡を命令で再確認したもの。

| thunk | 命令先 | body の関数サイズ |
| --- | --- | --- |
| `0x100071b20` | `0x1000541dc` CalendarTabView.body | 6536 |
| `0x100028500` | `0x100027b88` SlotTimePicker.body | 892 |
| `0x100048f9c` | `0x10003cdd8` CalendarDayView.body | 4608 |
| `0x1000ba040` | `0x1000b2154` IncomeView.body | 2316 |
| `0x1000c0280` | `0x1000bc9b8` WallEditorView.body | 1536 |

`SlotTimePicker.body` の疑似コードは SwiftUI の `DatePickerComponents` を組む view body で、時刻の正規化ではない。正規化は直後の関数。

## メタデータから分かったモデル

`__swift5_types` / field descriptor / `__swift5_reflstr` から読んだ。これはリフレクションであり、元のソースファイルではない。計算式はここにはない。

給与まわりの入れ物:

- `PayRounding`: `unitMinutes: Int`, `start`, `end`。`RoundingDirection` は `exact` / `up` / `down` / `nearest`
- `PayTerms`: `method`（`hourly` / `daily`）, `dailyWage`, `bands`, `partWages`, `rounding`, `items`, `effectiveFrom`
- `NightPremium`: `enabled`, `startMinute`, `endMinute`, `ratePercent`
- `OvertimePremium`: `enabled`, `thresholdMinutes`, `ratePercent`
- `HolidayPremium`: `enabled`, `ratePercentByWeekday: [Int]`
- `BreakRule`: `id`, `overMinutes`, `breakMinutes`
- `Workplace.customBreaks: Bool`, `breakRules`
- `PayResult`: `workedMinutes`, `base`, `premium`, `allowance`, `transport`, `deduction`
- `IncomeWall`: `amount`, `alertMode`, `alertPercent`, `alertRemaining`, `notifiedYear`

`PayRounding` の witness が Codable/hash だった、という以前の観察は今回も崩していない。丸めの式そのものの関数は特定していない。

## 命令と疑似コードで対応が付いた処理

### 法定休憩の初期値 — 回収済み

`0x1000da43c`（312 bytes）。`BreakRule` を 2 つ作り、フィールドオフセットはメタデータの `+0x14` と `+0x18`（`overMinutes` と `breakMinutes`）。即値は次の順。

- `overMinutes = 0x168`（360）、`breakMinutes = 0x2d`（45）
- `overMinutes = 0x1e0`（480）、`breakMinutes = 0x3c`（60）

配列オブジェクトをグローバル `0x1005d0a40` へ書く。Ghidra の疑似コードも同じ即値と `lRam00000001005d0a40` を出している。オブジェクトポインタのレジスタ割り当ては疑似コード側が崩れているので、ストア先の特定は命令列を優先する。

どの規則を勤務分数に対して選ぶ比較ループは、この初期化関数の中にはない。未回収。

### 勤務先初期値の深夜・残業・休日・休憩 — 回収済み

`0x1000defb8`。疑似コードは `notes/ghidra/workplace_defaults.c`。定数プール `0x10042d680` は int64 で `(1320, 300, 480, 25)`。

- あるフィールド（メタデータ `+0x1c`）: enabled byte `1`、`+8` に 1320、`+16` に 300、`+0x18` に 25。`NightPremium` の並び（enabled, startMinute, endMinute, ratePercent）と一致。1320 分は 22:00、300 分は 05:00
- 次のフィールド（`+0x20`）: enabled `1`、`+8` に 480、`+16` に 25。`OvertimePremium`（enabled, thresholdMinutes, ratePercent）と一致。480 分は 8 時間
- 次（`+0x24`）: `[Int]` を count 7 で確保してゼロ埋め、enabled byte は `0`。`HolidayPremium`
- その次の byte は `0`（`customBreaks == false` の並びに一致）
- `swift_once(legal_break_defaults)` のあと、グローバル `0x1005d0a40` を次のフィールドへコピー（`breakRules`）

デコード失敗時に定数プール `0x10042d6a0` の `(2000, 1)` を別の入れ物へ書く経路がある。フィールド名まではシンボルで結んでいないので、時給 2000 円だとは断定しない。

ここまでが初期値。時給 × 分 / 60 や割増の加算式は、この関数からは出ていない。

### 分の正規化と時刻ホイール — 回収済み

`0x1000968c4`: 引数を 1440（`0x5a0`）で割った余りにし、負なら 1440 を足す。時は `/ 60`、分は余り。コロン（`0x3a`）と `"%02d"`（レジスタ即値 `0x64323025`）で文字列にする。

`0x100027f04`: SwiftUI `Binding` の wrapped value に同じ 1440/60 分割をかけ、`Calendar.current` で `date(bySettingHour:minute:second:of:matchingPolicy:repeatedTimePolicy:direction:)` を呼ぶ。秒は 0、matchingPolicy は `.nextTime`、repeatedTimePolicy は `.first`、direction は `.forward`。

ドラッグ量から分を増減する式は、body（`0x100027b88`）の疑似コードが view 構築のままで、独立した式としては取り出していない。

### 日付の移動 — 一部回収

`Calendar.date(byAdding:value:to:wrappingComponents:)` の value と component が疑似コード上で読めたもの。wrappingComponents は 0（false）。`weekOfYear` のケースシンボルは got `0x10056bbb0` にあるが、下の週送り関数はそれを読まない。`__weekOffset` というフィールド名はある。オフセットを ±1 する呼び出し元の式は、唯一の caller `0x100210b7c` が引数 `x0` をそのまま渡すだけで、増減そのものは未回収。

- `0x1001b4a94`: `startOfDay(for:)` のあと `Component.day` で -1 と +2
- `0x1000837d8`: `Component.day` で +14 と -1
- `0x10006028c`: `dateInterval(of: .month, for:)` と、`Component.day` の -1 および +1

## 週送り — 日数への変換は回収済み

`0x10020499c`（1356 bytes）。唯一の直接呼び出しは `0x100210b7c` で、受け取った `x0` を変えずに渡す。

命令:

- `0x1002049c0` `mov x25, x0`。週数は第1引数
- `0x100204b40` が got `0x10056bbb8` を読む。これは `Calendar.Component.day`。隣の `0x10056bbb0` は `weekOfYear` だが、この関数は読まない
- `0x100204b68` から `lsl x8, x25, #3` / `sub x24, x8, x25` / `mov w8, #7` / `smulh`。`x24 = x25 * 7`。上位半分が符号と合わなければ `0x100204ecc` の `brk #1`
- `0x100204be4` でその積を `x1` に置き、`w3 = 0` で `0x100204bf0` から `Calendar.date(byAdding:value:to:wrappingComponents:)` を呼ぶ
- 呼ぶ直前の疑似コードは SwiftUI `State.wrappedValue` を `to:` に渡している。`startOfDay` はこの関数の中では呼ばない
- 加算に成功したあと `0x100204c68` は保存してある週数を 0 と比較し、`mov w8, #3` / `csinc ..., gt`。週数が正なら 1 byte のタグは 3、0 以下なら 1。そのバイトは `LazyState` の setter に渡る。タグの型名はこの関数内に無い

再構成は `InOutRecovered.addingWeeks` と `weekSlideTag`。`tests/WeekShift.swift` はタグと、Foundation の「7日加える」が同じ日付になることを見る。オーバーフローでトラップする点は Swift の `*` と同じで、境界値の実行はしていない。

## 未回収のまま残しているもの

- 休憩規則の選択（勤務分数と `overMinutes` の比較）
- `PayRounding` の unitMinutes / start / end を時刻へ適用する式
- 時給・日給・時間帯・割増から金額を出す式
- 年収の壁の閾値判定。画面文字列と `IncomeWall` のフィールドはある。比較関数は特定していない
- 週送りの「オフセットを ±1 するボタン」自体。日数への変換は `0x10020499c` で回収済み（下の節）

画面文言（「6時間を超えたら45分」など）は上記の初期値と矛盾しないが、それ自体は計算の回収ではない。

## 統合するとき

`recovered/InOutRecovered.swift` は上の回収分だけ。広告は入れていない。製品側の独自機能を置き換えるコードはここには無い。private の ShiftTrack はこの token から 404 で、開いていない。
