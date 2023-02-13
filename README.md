# IGC-RTP

IGC-RTPのソフトウェアが含まれるリポジトリです．

# 導入方法（たぶん）
1. このリポジトリをフォーク 
2. フォークしたリポジトリをCubeIDEのワークスペースにクローン

（ワークスペースの場所は，Windowsのデフォルトだと `C:\Users\<ユーザー名>\STM32CubeIDE\workspace_<バージョン>`

```
cd <ワークスペースのパス>
git clone https://github.com/shimotoriharuki/IGC-RTP
```

3. CubeIDEを開いて「C/C++ Project」ウィンドウで右クリック
4. 「Import」をクリック
5. 「General」の中にある「Existing Projects int Workspace」をクリック
6. 「Browse」ボタンをクリックしてクローンしてきたディレクトリを選択
# 運用方法
* 基本的にフォークしたリポジトリで開発してください
* コミットは頻繁にして，コミットメッセージは意味のあるものにしてください
* なにか機能を追加したらGitHubからプルリクを送ってください
* `UserSelection.h`で自分の名前のマクロを有効にしてゲインなどのパラメータを切り替えてください．自分の名前以外のマクロはコメントアウトしてください
# 変更の確認手順

```shell
git fetch origin <テストしたいブランチ名>
```

## before

```shell
git remote add upstream <フォーク元のURL> # フォーク元のURLをupstreamという名前で登録 一度やればOK
git fetch upstream # upstreamの変更をローカルに持ってくる
git merge upstream/<ブランチ名> # マスターに変更を持ってくる
```

* https://leico.github.io/TechnicalNote/Git/pull-fork-origin
# LICENSE

このソフトウェアパッケージは[3条項BSDのライセンス](https://github.com/shimotoriharuki/IGC-RTP/blob/master/LICENSE)の下、再頒布および使用が使用が許可されます．
