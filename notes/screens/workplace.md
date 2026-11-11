# 勤務先

元の Swift ソースではない。

## WorkplaceListView

descriptor `0x100440e64`、アクセサ `0x100255730`。専用関数 `0x10025ca2c`（8900 バイト）。カード `0x1002616f4`（7216 バイト）もこのアクセサだけを呼ぶ。

確定。`0x10025ca2c` は「今日のお給料」「今月のお給料」「支払日を設定」を読む。カードは「シフトを追加」を読む。勤務中の金額は、カードが `start <= 日付 < end` のときだけ 1 秒の `TimelineView` を作り、`0x10026e844` が休憩を按分し、`0x10026efb0` が「終わりまで あと 」と金額と「円」を作る。金額の Doto はサイズ 36。これは構築順であり、画面上の配置ではない。給与式は `logic.md`。

部分。`0x100255ab0` は一覧と一緒に `WorkplaceEditorView`、`PayPeriodsView`、`UnconfirmedShiftsView`、`OnboardingView`、`LateMessageView` を呼ぶ。`sheet(isPresented:)` が 3、`sheet(item:)` が 5、`alert` が 1、`ZStack` が `0x100256064` にある。どのシートがどの画面かは未確定。`0x1002570c0` は一覧だけを呼び、`DragGesture` の `d0` が 30。`0x10025ed50`、`0x10026acac`、`0x10026b134` は `withAnimation`。一覧の Doto サイズ 64、36、18 は、専用関数の外の関数 `0x100260714`、`0x100266998`、`0x10026bc9c`、`0x10026e260` にある。

未確定。カードの積み順、余白、角丸、記号の位置、色。`Color(UIColor)` の 5 つの短い関数は画面へ結べていない。

## WorkplaceDirectoryView

descriptor `0x100440b40`、アクセサ `0x10021c788`。専用関数 `0x10021dc9c`。

確定。`0x10021ec98` はこのアクセサだけを呼び、「勤務先を追加」「シフトパターンを開く」を読む。`onTapGesture(count:perform:)` が 1 つある。count の即値は未確定。

部分。`0x10021cae0` はディレクトリと一緒に `WorkplaceEditorView`、`ShiftPartEditorView`、`OnboardingView`、`LateMessageView` を呼ぶ。`sheet` が 1、`sheet(item:)` が 4。

未確定。積み順、余白、フォント、記号。

## WorkplaceEditorView

descriptor `0x100440b90`、アクセサ `0x10022ce3c`。専用関数 `0x10022e830`（8772 バイト）。

確定。この関数は「遅刻連絡の文章の型」「住所・位置（任意）」「この勤務先を削除」を読む。`0x10022dc40` はこのアクセサだけを呼び、`NavigationStack` を作る。

部分。`0x10022e0d0` はエディタと `WorkplaceImportView` を呼び、`toolbar` がある。`0x100230fa8` はエディタと `PayTermsEditorView`、`0x100230a74` は `PayScheduleEditorView`、`0x100233194` は `LateTemplateEditorView`、`0x100235010` は `LocationPickerView` を、それぞれ `NavigationLink` で結ぶ関数から呼ぶ。リンクのラベルは未確定。

未確定。積み順、余白、角丸、フォント、記号、削除の確認、保存先。

## WorkplaceImportView

descriptor `0x100440cd8`、アクセサ `0x100249690`。専用関数 `0x100243ca8`。

確定。`0x10023eb54` はこのアクセサだけを呼び、`NavigationStack` を作る。`0x10023eff4` もこのアクセサだけを呼び、「ショップカード」「Google マップのリンク」「Google マップ」を読み、`toolbar` がある。`0x100240458` は `ToolbarItem` を 2 つ作る。

部分。`0x10023dffc` と `0x10022b078` は `fullScreenCover(isPresented:)`、`onChange`、`sheet(item:)` を持ち、インポートのアクセサを呼ぶ。エディタ側の関数と重なる。

未確定。積み順、余白、フォント、記号、読み込む項目の対応。

## LocationPickerView

descriptor `0x100440bb8`、アクセサ `0x10023c87c`。専用関数 `0x100237b98`。

確定。`0x100237320` はこのアクセサだけを呼び、`onTapGesture(count:coordinateSpace:perform:)` がある。

部分。`0x100235010` は `WorkplaceEditorView` と一緒に `NavigationLink` でこの画面を出す。`0x100235d74` はエディタだけを呼び、`ScrollViewProxy.scrollTo` がある。地図側のスクロールではない。

未確定。文言、記号、フォント、余白、積み順。

## WorkplaceThumbnailView

descriptor `0x100440eb4`、アクセサ `0x10027a1d8`。他の画面と分かれた関数は無い。

未確定。文言、記号、フォント、余白、積み順、操作、遷移、ロジック。カタログの `Logo` や時間帯画像を、このビューが読むことは未確定。
