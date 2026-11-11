# 移植仕様の網羅率

元の Swift ソースではない。広告の `BannerAdView` と Intelligence は対象外。画像、フォントファイル、`Assets.car`、実機スクショはこのリポジトリに置いていない。スクショから読んだ配置は印 `観` で、命令の `確` とは別である。

対象は画面とシート 36。観点は 9。セルは 324。

| 印 | 意味 |
| --- | --- |
| 確 | その画面のアクセサだけを呼ぶ関数、またはその画面の body として既に結んである関数の中にある |
| 部 | その画面を他の画面と一緒に呼ぶ関数、またはアクセサの近くにある。画面の中の位置は未確定 |
| 観 | 実機スクショで見える。命令の証明ではない。個人の金額、勤務先名、住所は書いていない |
| 未 | 命令にもスクショにも、その観点が無い |

確定率は 確 ÷ 324。着手率は（確 + 部）÷ 324。半分換算は（確 + 部 × 0.5）÷ 324。積み順を推測で埋めない。

| | 画面数 36 |
| --- | --- |
| 確 | 111（34.3%） |
| 部 | 48（14.8%） |
| 観 | 55（17.0%） |
| 未 | 110（34.0%） |
| 確 + 部 + 観 | 214（66.0%） |

観点ごとの数。

| 観点 | 確 | 部 | 観 | 未 |
| --- | --- | --- | --- | --- |
| 入口（型と関数） | 35 | 1 | 0 | 0 |
| 文言 | 28 | 0 | 3 | 5 |
| SF Symbols | 2 | 1 | 21 | 12 |
| フォントとサイズ | 26 | 0 | 3 | 7 |
| 余白と角丸 | 1 | 3 | 11 | 21 |
| 積み順 | 0 | 0 | 17 | 19 |
| ジェスチャとアニメーション | 7 | 13 | 0 | 16 |
| 遷移 | 7 | 26 | 0 | 3 |
| ロジック | 5 | 4 | 0 | 27 |

積み順の `確` は 0 のままである。スクショで上から下の順が見えた画面だけ `観` にした。命令の `VStack` はバイナリ全体で 5 のまま。詳細は `observed.md`。

## 画面ごとの印

列は入口、文言、記号、フォント、余白、積み順、操作、遷移、ロジック。

| 画面 | 印 |
| --- | --- |
| RootView | 確 確 未 確 未 未 部 部 未 |
| InOutTabBar | 確 観 確 観 観 観 部 未 未 |
| LaunchAnimationView | 確 未 未 未 未 未 部 部 未 |
| OnboardingView | 確 確 観 確 部 観 部 部 未 |
| WorkplaceListView | 確 確 部 確 観 観 確 部 確 |
| WorkplaceDirectoryView | 確 確 確 確 観 観 確 部 未 |
| WorkplaceEditorView | 確 確 観 未 未 未 未 確 未 |
| WorkplaceImportView | 確 確 未 確 部 未 未 確 未 |
| WorkplaceThumbnailView | 確 未 観 未 未 未 未 未 未 |
| LocationPickerView | 確 確 観 確 未 未 確 部 未 |
| CalendarTabView | 確 確 観 確 観 観 確 確 確 |
| CalendarDayView | 確 確 観 確 確 観 確 確 確 |
| CalendarAccessView | 確 確 未 確 未 未 未 部 未 |
| IncomeView | 確 確 観 確 観 観 部 部 未 |
| WallEditorView | 確 確 観 確 観 観 未 部 未 |
| SettingsView | 確 確 観 確 観 観 部 部 未 |
| AboutView | 確 未 未 未 未 未 未 部 未 |
| GuideOverlay | 確 観 観 確 観 観 確 部 未 |
| ShiftPartEditorView | 確 観 観 確 観 観 未 部 未 |
| ShiftRepeatEditorView | 確 確 観 観 観 観 未 確 確 |
| ShiftRequestView | 確 確 観 確 観 観 部 部 未 |
| ShiftRequestPlannerView | 確 確 観 確 未 未 部 部 部 |
| RequestHoursStockSheet | 確 確 未 確 未 未 部 部 未 |
| ShiftCheckView | 確 確 観 確 未 観 部 部 未 |
| LateMessageView | 確 確 未 確 未 未 確 確 未 |
| LateTemplateSheet | 確 確 未 確 未 未 未 部 未 |
| LateTemplateEditorView | 確 確 観 確 未 未 未 部 未 |
| PayBreakdownView | 部 未 未 未 未 未 未 未 部 |
| PayPeriodsView | 確 確 観 確 未 観 未 部 未 |
| PayPeriodDetailView | 確 確 観 観 未 観 部 部 部 |
| PayScheduleSettingView | 確 未 未 未 未 未 未 確 未 |
| PayTermsEditorView | 確 確 未 確 未 未 未 部 部 |
| PayScheduleEditorView | 確 確 観 未 未 未 部 部 未 |
| UnconfirmedShiftsView | 確 確 観 確 未 観 部 部 未 |
| ShiftEntryEditor | 確 確 観 確 部 未 未 部 確 |
| TodoEditor | 確 確 未 確 未 未 未 部 未 |

`PayBreakdownView` は、アクセサ `0x1001165c0` への `bl` も `adrp` + `add` も無い。積み順は 36 画面とも未。今回 確にした文言は、その画面のアクセサだけを呼ぶ関数が cstring の先頭を読むもの。画面の中の位置は見ていない。

画面別の命令は `calendar.md`、`workplace.md`、`pay.md`、`shift.md`、`settings.md`、`root.md`。スクショとの突き合わせは `observed.md`。記号・文言・フォントの今回の突き合わせは `parallel-symbols.md`。設定下段の追加分は、文言も記号も列を動かしていない。設定の文言は元から確、記号は `観` のまま。広告の文は移植しない。残りの未は、その画面だけの関数を全部見て、`systemName` と design size とカウント一致の見出しが無かったので未のまま。件数は動かしていない。給与、重なり、`WeekTemplate`、保存先、通知は `logic.md`。opaque 型から読んだ modifier 順は `opaque.md`。
