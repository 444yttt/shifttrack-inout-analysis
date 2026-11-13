# カレンダー

元の Swift ソースではない。配置は画面を見て書いていない。

## CalendarTabView

descriptor `0x10043e520`、アクセサ `0x100071b0c`。専用関数 `0x100062150`（10368 バイト）。body は `0x100071b20` から `0x1000541dc`（6536 バイト）。

確定。専用関数 `0x100063208` は `Font.custom` に `Doto-BlackRound` とサイズ 18 を渡す。body は `CalendarDayView`、`ShiftPartEditorView`、`ShiftRepeatEditorView`、`ShiftRequestPlannerView` のアクセサを呼ぶ。同じ body に `sheet(item:)` が 3、`fullScreenCover(item:)` が 1、`alert` が 2、`alert` の presenting 形が 1、`onAppear` が 1、`onChange` が 2 ある。シートの中身がどのエディタかは、この回数だけでは決まらない。

確定。選んだ日へ `ShiftPart` を置く処理は、日チップ `0x10003fe54` とパターン行 `0x10006e04c` から確定処理 `0x100014370`、配置 `0x1001c75ec` へ進む。詳細は `logic.md`。

部分。`0x100067fec` と `0x10006852c` は「月の収入見込み」「シフトパターンを編集」を読む。body の範囲の外である。`0x100058000` は `CalendarTabView` だけを呼び、`DragGesture`、`LazyVGrid`、`LazyVStack`、`sensoryFeedback` がある。`0x1000587c8` の `fmov d0, #30` の直後、`0x1000587e0` が `DragGesture` の `minimumDistance` を呼ぶ。この 30 は、その距離である。

確定。`plus` の `Image(systemName:)` は `0x10006be48` と `0x10006e650`。呼び出し元を辿ると、この画面のアクセサだけに届く。`0x100066e2c` も `Image(systemName:)` だが、渡す 29 バイトは UTF-8 として読めない。0x20 後ろの `exclamationmark.triangle.fill` は引数にしていない。

確定。このアクセサだけを参照する関数が `EdgeInsets.init(_all:)` に 2、3、5、8、12、16、20 を渡す。16 は `0x10005a4a8`。画面の中の位置は未確定。

未確定。タブ画面の積み順、角丸、グリッドの列数。

## CalendarDayView

descriptor `0x10043e434`、アクセサ `0x10003b030`。専用関数 `0x10003cdd8`（4608 バイト）。

確定。この関数は「確認が必要です」を読む。`0x10003d5ac` は `presentationCornerRadius` に 32.0 を渡す。`w1` は 0。`0x10003d320` は `DragGesture` の `d0` に 30 を渡す。イニシャライザの第 1 引数は `minimumDistance` なので、この 30 はその距離の即値である。座標空間はレジスタで、未確定。同じ関数に `sheet(item:)` が 2、`alert`、`presentationDetents`、`PresentationDetent.large`、`onChange` がある。

確定。日チップのワンタップ配置はこの画面の状態 `__pendingPlace`（metadata +0x30）へ書く。衝突が空のときだけ配置する。`logic.md`。

確定。`0x100043474` の `Image(systemName:)` は、`[x28,#0x10]` のバイトが 0 なら `calendar`、0 でなければ `checklist`。`0x10004436c` は `ShiftTodo.done` が 0 なら `circle`、0 でなければ 21 バイトの「この日のシフト」を渡す。後者は SF Symbol の名前ではない。どちらも呼び出し元を辿ると、この画面のアクセサだけに届く。

確定。このアクセサだけを参照する関数が `EdgeInsets.init(_all:)` に 4、8、12、20、24 を渡す。20 は `0x10003e428`。角丸 32 とは別の呼び出しである。画面の中の位置は未確定。

未確定。シートが 2 つのうちどちらがシフト編集か。角丸 32 がシート自身か、中の図形か。積み順、フォント、色。

## CalendarAccessView

descriptor `0x10043e3b4`、アクセサ `0x100038674`。専用関数 `0x100038a40`。

確定。この関数は「入力を続ける」「設定アプリを開く」を読む。

部分。`0x10017ac70` はルート、ガイド、起動、この画面を呼び、`OpacityTransition` を 2 回使う。どの画面の遷移かは未確定。

部分。`requestFullAccessToEventsWithCompletion:` の `0x1001cce6c` は、この画面の `0x10003a3ec` と、オンボーディングの `0x100112c98` の両方から届く。どちらのボタンがカレンダーの全件アクセスを求めるかは、この共有だけでは決まらない。設定だけの別呼び出しは `settings.md`。

確定。専用関数 `0x100038a40` は、`0x100038de8` の `fmov d0, #24` の直後に `EdgeInsets.init(_all:)` を呼ぶ。もう 1 箇所も 24 である。画面の中の位置は未確定。

未確定。積み順、フォント、記号、許可が無いときの分岐。
