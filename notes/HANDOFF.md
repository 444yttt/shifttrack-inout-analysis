# 統合担当への引き渡し

公開解析リポジトリの再構成。元の Swift ソースではない。広告はない。製品の私有コードは含まない。給与の金額式と `PayRounding` の適用は未確定なので、ここにある関数を給与明細へそのまま繋がない。

## 検証済み commit

| 内容 | commit | macOS run |
| --- | --- | --- |
| 週数 × 7 日 | `febde5b6f02a26c9d13d8c164c9a100e499aaf9a` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42376695303 |
| 休憩の選択 | `0e24b5ab91b3` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377098813 |
| 編集画面の分数と秒の切り捨て | `19e5229a227f9ca73dcd551006f303393ac75b67` | https://github.com/444yttt/shifttrack-inout-analysis/actions/runs/42377557969 |

## 統合してよいもの

- `addingWeeks` / `weekSlideTag` — `0x10020499c`。`Calendar.Component.day` を週数×7。週数が正ならタグ 3、そうでなければ 1。週オフセットを ±1 する側は未回収
- `selectedBreakMinutes` — `0x1000e967c`。`overMinutes < 分数` のうち最大。同値は先の規則。無ければ 0。法定 (360,45),(480,60) では 360→0、361→45、480→45、481→60
- `editorMinuteCount` — `ShiftEntryEditor` の `_endMinute - _startMinute` を 1...1440 に正規化。同じ分は 1440。日をまたぐ負の差は 1440 を足した正の余り。編集画面用。給与明細の分数ではない

`customBreaks == 1` のとき `Workplace.breakRules`、そうでなければ法定グローバル `0x1005d0a40`。

## 渡すが給与へ繋がないもの

- `truncatedMinutes` — すでに得ている秒を 60 で割り 0 方向へ切り捨てる。`0x1001cee68` が選択関数へ渡す直前の変換。どちらの日付が `timeIntervalSince` の受信側かは未確定

## 未回収

丸め（`PayRounding` の unitMinutes / start / end の適用）、時給から金額、年収の壁の閾値、週オフセットの ±1。画面文言や Codable からは補っていない。
