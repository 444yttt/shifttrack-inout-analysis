# 勤務先

元の Swift ソースではない。

## WorkplaceListView

descriptor `0x100440e64`、アクセサ `0x100255730`。専用関数 `0x10025ca2c`（8900 バイト）。カード `0x1002616f4`（7216 バイト）もこのアクセサだけを呼ぶ。

確定。`0x10025ca2c` は「今日のお給料」「今月のお給料」「支払日を設定」を読む。カードは「シフトを追加」を読む。勤務中の金額は、カードが `start <= 日付 < end` のときだけ 1 秒の `TimelineView` を作り、`0x10026e844` が休憩を按分し、`0x10026efb0` が「終わりまで あと 」と金額と「円」を作る。金額の Doto はサイズ 36。これは構築順であり、画面上の配置ではない。給与式は `logic.md`。

確定。`0x1002570c0` は一覧だけを呼び、`0x100257300` の `fmov d0, #30` の直後に `DragGesture` を呼ぶ。第 1 引数は `minimumDistance` なので、この 30 はその距離である。

部分。`0x100255ab0` は一覧と一緒に `WorkplaceEditorView`、`PayPeriodsView`、`UnconfirmedShiftsView`、`OnboardingView`、`LateMessageView` を呼ぶ。`sheet(isPresented:)` が 3、`sheet(item:)` が 5、`alert` が 1、`ZStack` が `0x100256064` にある。どのシートがどの画面かは未確定。`0x10025ed50`、`0x10026acac`、`0x10026b134` は `withAnimation`。一覧の Doto サイズ 64、36、18 は、専用関数の外の関数 `0x100260714`、`0x100266998`、`0x10026bc9c`、`0x10026e260` にある。

確定。`Image(systemName:)` の `plus` は `0x10026fae8`、`pencil` は `0x10026905c`、`ellipsis` は `0x100269c24`、`chevron.right` は `0x10026dfc0`。`0x100264c30` は `ShiftTodo.done` が 0 のとき `circle`、0 でないとき 21 バイトの「この日のシフト」を渡す。後者は SF Symbol の名前ではない。これらの関数は、呼び出し元を辿ると一覧のアクセサだけに届く。画面の中の位置は未確定。

確定。このアクセサだけを参照する関数が `EdgeInsets.init(_all:)` を呼ぶ。`d0` は 4、6、8、12、16、20、24 と、負の -8、`-6`、`-4` がある。20 は `0x100257258`、`-8` は `0x1002622ec`。画面の中の位置は未確定。

未確定。カードの積み順、角丸、色。`Color(UIColor)` の 5 つの短い関数は画面へ結べていない。

## WorkplaceDirectoryView

descriptor `0x100440b40`、アクセサ `0x10021c788`。専用関数 `0x10021dc9c`。

確定。`0x10021ec98` はこのアクセサだけを呼び、「勤務先を追加」「シフトパターンを開く」を読む。`onTapGesture(count:perform:)` が 1 つある。count の即値は未確定。`0x100220ee0` もこのアクセサだけを呼び、`0x1002216d0` で `Font.system` の `d0` に 14 を渡す。

部分。`0x10021cae0` はディレクトリと一緒に `WorkplaceEditorView`、`ShiftPartEditorView`、`OnboardingView`、`LateMessageView` を呼ぶ。`sheet` が 1、`sheet(item:)` が 4。

確定。このアクセサだけを参照する関数が `EdgeInsets.init(_all:)` に 4、8、12、16、20、24 を渡す。20 は `0x10021dc08`。画面の中の位置は未確定。

未確定。積み順、記号。

## WorkplaceEditorView

descriptor `0x100440b90`、アクセサ `0x10022ce3c`。専用関数 `0x10022e830`（8772 バイト）。

確定。この関数は「遅刻連絡の文章の型」「住所・位置（任意）」「この勤務先を削除」を読む。`0x10022dc40` はこのアクセサだけを呼び、`NavigationStack` を作る。`0x100236114` もこのアクセサだけを呼ぶ。名前を空白で削り、空なら「勤務先の名前を入力してください。」へ進む。続く分岐で「時給の適用開始日が重複しています。日付を変更してください。」「お給料の決まりの適用開始日が重複しています。日付を変更してください。」「時給を0円以上で入力してください。」を読む。

部分。`0x10022e0d0` はエディタと `WorkplaceImportView` を呼び、`toolbar` がある。`0x100230fa8` はエディタと `PayTermsEditorView`、`0x100230a74` は `PayScheduleEditorView`、`0x100233194` は `LateTemplateEditorView`、`0x100235010` は `LocationPickerView` を、それぞれ `NavigationLink` で結ぶ関数から呼ぶ。リンクのラベルは未確定。

未確定。積み順、余白、角丸、フォント、記号、削除の確認、保存先。

## WorkplaceImportView

descriptor `0x100440cd8`、アクセサ `0x100249690`。専用関数 `0x100243ca8`。

確定。`0x10023eb54` はこのアクセサだけを呼び、`NavigationStack` を作る。`0x10023eff4` もこのアクセサだけを呼び、「ショップカード」「Google マップのリンク」「Google マップ」「読み取り結果」を読み、`toolbar` がある。`0x100240458` は `ToolbarItem` を 2 つ作る。`0x100242020` もこのアクセサだけを呼び、「Google マップのリンクから店舗の情報を読めませんでした。店名や住所を直接入力してください。」を読む。`0x100243ca8` は「読み取った文字」を読む。リンクの貼り付けは、この画面の二つの入口のうち写真と並ぶ側である。

「Google マップのリンクを貼り付け」は `0x100247350` が読む。この関数は画面アクセサを呼ばない。説明「ショップカードの写真か、Google マップでお店の「共有」からコピーしたリンク」は `0x1002475a8` が読む。こちらも画面アクセサを呼ばない。

部分。`0x10023dffc` と `0x10022b078` は `fullScreenCover(isPresented:)`、`onChange`、`sheet(item:)` を持ち、インポートのアクセサを呼ぶ。エディタ側の関数と重なる。

部分。`0x100104588` はオンボーディングとこの画面を呼び、`presentationCornerRadius` に 32 を渡す。同じ関数は `EdgeInsets.init(_all:)` に 20（`0x100104a74`）と 12（`0x100104ac0`）を渡す。角丸と余白がどちらの画面かは未確定。

確定。`reverseGeocodeLocation:completionHandler:` は `0x10009a79c`、`0x10009a9dc`、`0x10009ae84` の 3 箇所。それぞれの関数から呼び出し元を辿ると、`WorkplaceImportView` のアクセサだけに届く。渡している座標のフィールド名は、この 3 箇所では閉じていない。

未確定。積み順、フォント、記号、読み込む項目の対応。

## LocationPickerView

descriptor `0x100440bb8`、アクセサ `0x10023c87c`。専用関数 `0x100237b98`。

確定。`0x100237320` はこのアクセサだけを呼び、`onTapGesture(count:coordinateSpace:perform:)` がある。`0x100238b4c` もこのアクセサだけを呼ぶ。`x8` が 0 でないとき、`0x1000d8454` へ尾呼び出しする。その先の `0x1000d853c` が `requestWhenInUseAuthorization` を呼ぶ。`0x100218c0c` も同じ尾呼び出しをする。この関数自身は画面アクセサを参照しない。呼び出し元を辿ると `LateMessageView` の `0x1000cbc74` に届く。

部分。`0x100235010` は `WorkplaceEditorView` と一緒に `NavigationLink` でこの画面を出す。`0x100235d74` はエディタだけを呼び、`ScrollViewProxy.scrollTo` がある。地図側のスクロールではない。

確定。`0x100236f50` はこのアクセサだけを参照し、`0x1002371a8` の `fmov d0, #16` の直後に `EdgeInsets.init(_all:)` を呼ぶ。画面の中の位置は未確定。

未確定。文言、記号、フォント、積み順。

## WorkplaceThumbnailView

descriptor `0x100440eb4`、アクセサ `0x10027a1d8`。他の画面と分かれた関数は無い。

未確定。文言、記号、フォント、余白、積み順、操作、遷移、ロジック。カタログの `Logo` や時間帯画像を、このビューが読むことは未確定。
