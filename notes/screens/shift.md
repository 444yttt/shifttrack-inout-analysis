# シフトの編集と依頼

配置、重なり、`WeekTemplate` は `logic.md`。

## ShiftPartEditorView

descriptor `0x1004408a0`、アクセサ `0x1001f605c`。専用関数 `0x1001f0144`。

部分。カレンダー body `0x1000541dc` と勤務先ハブ `0x10021cae0` が、他の画面と一緒にこのアクセサを呼ぶ。シートの引数と、このエディタの対応は未確定。

未確定。文言、記号、フォント、余白、積み順、ジェスチャ。パターンのフィールド（`workplaceID`、`startMinute`、`endMinute`、`breakMinutes`、`defaultTodos`、`hidden`、`color`）はモデルとして確定している。この画面のどの入力がどのフィールドへ書くかは未確定。

## ShiftRepeatEditorView

descriptor `0x100440968`、アクセサ `0x1001fc9bc`。専用関数 `0x1001fa340`。

確定。`0x1001f8f44` はこのアクセサだけを呼び、`NavigationStack` と `alert`（actions と message を取る形）を作る。`0x1001f96f4` もこのアクセサだけを呼び、`toolbar` がある。`0x1001fbdc0` はこのアクセサだけを呼び、`0x100017d04` を呼ぶ。その先が重なり `0x100016734` である。どの分岐の文言を出すかは、この呼び出しだけでは決まらない。

部分。カレンダー body が他のエディタと一緒にこのアクセサを呼ぶ。曜日の文言「選んだ曜日に、このシフトパターンを置きます。」は `0x1001f9a5c` にある。専用関数 `0x1001fa340` の範囲は 2280 バイトで、`0x1001fa340 + 2280 = 0x1001fac38`。`0x1001f9a5c` はその範囲の外である。

未確定。積み順、余白、フォント、記号。繰り返し配置 `0x1001ca710` は `breakMinutes` を読むが、選んだ日のワンタップとは別である。

## ShiftRequestView

descriptor `0x100440a58`、アクセサ `0x100213818`。専用関数 `0x1002145c8`。

確定。この関数は「ストックして入れる」「例：家の用事で」を読む。`0x100215f10` もこのアクセサだけを呼ぶ。1 文字の「月」（`0x1002161d0` の即値）を作り、`0x100216974` を `w0 = 0` と `w0 = 1` で 2 回呼ぶ。二つの戻りを、テンプレの二つの欄へ渡す側である。どちらの整数が出勤希望で、どちらが休み希望かは、この 2 回の並びだけでは閉じていない。

部分。`0x1001ff66c` は `ShiftRequestView`、`ShiftRequestPlannerView`、`RequestHoursStockSheet` を呼び、`sheet` が 2、`confirmationDialog` が 1、`DragGesture` の `d0` が 30、`onChange` がある。

未確定。積み順、余白、フォント、記号、ダイアログの文言。

## ShiftRequestPlannerView

descriptor `0x1004409b8`、アクセサ `0x1001fecf4`。専用関数 `0x1002091c4`。

部分。`0x10020499c` はこのアクセサを呼び、週数 × 7 の日付移動と `withAnimation` がある。週の ±1 ボタンは未回収。`0x100200fbc` も `withAnimation`。カレンダー body と `0x1001ff66c` がこのアクセサを他の画面と一緒に呼ぶ。

未確定。文言、積み順、余白、フォント、記号。

## RequestHoursStockSheet

descriptor `0x1004409e0`、アクセサ `0x10020fefc`。専用関数 `0x10020d3d4`。

部分。`0x1001ff66c` が他の依頼画面と一緒にこのアクセサを呼ぶ。`0x10020ad88` は `ScrollView`、`presentationDetents`、`large` と `medium` を呼ぶ。この関数は画面アクセサを呼ばない。シートの角丸 32 は `0x10020b0f0` にあり、同じ関数の中である。シート本体であることは未確定。

未確定。文言、積み順、フォント、記号。

## ShiftCheckView

descriptor `0x1004404dc`、アクセサ `0x1001a3730`。専用関数 `0x1001a6ab4`。

部分。`0x100179048` はルートと一緒にこのアクセサを呼び、`fullScreenCover` がある。`0x10014a990` は給与明細と `sheet(item:)`。`0x100151348` は未確認勤務と `NavigationStack`。`0x1001a5a5c` は `ScrollView`、`presentationDetents`、`large`、角丸 32 を呼ぶが、画面アクセサは呼ばない。

未確定。文言、積み順、余白がこの画面のものか、フォント、記号。

## ShiftEntryEditor と TodoEditor

型名の cstring は `0x100436290` と `0x100437d18`。アクセサはこの走査では結んでいない。

部分。編集分数 `0x1001b8770` は `_endMinute - _startMinute` を 1...1440 に正規化する。同じ分は 1440。これは給与明細の分数ではない。`ShiftTodo.done == 0` の 3 箇所は `circle`、`done != 0` は 21 バイトの「この日のシフト」を `Image(systemName:)` に渡す。SF Symbol の名前ではない。`0x10003cdd8` は日ビューとこのエディタを両方呼び、`DragGesture`、`onEnded`、`simultaneousGesture`、`presentationCornerRadius` 32 がある。ドラッグと角丸がどちらの画面のものであるかは、この関数だけでは決まらない。`0x1001b9fe4` はこのアクセサだけを呼び、重なり `0x100016734` を呼ぶ。

未確定。エディタの積み順、余白、フォント、遷移、`done` の表示がこの文字列のまま画面へ出るか。
