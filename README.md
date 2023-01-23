# IGC-RTP

IGC-RTPのソフトウェアが含まれるリポジトリです．

# 導入方法（たぶん）

1. CubeIDEのワークスペースにこのリポジトリをクローン

（ワークスペースの場所は，Windowsのデフォルトだと`C:\Users\<ユーザー名>\STM32CubeIDE\workspace_<バージョン>`
```
cd <ワークスペースのパス>
git clone https://github.com/shimotoriharuki/IGC-RTP
```

2. CubeIDEを開いて「C/C++ Project」ウィンドウで右クリック
3. 「Import」をクリック
4. 「General」の中にある「Existing Projects int Workspace」をクリック
5. 「Browse」ボタンをクリックしてクローンしてきたディレクトリを選択

# 変更の確認手順

```shell
git remote add upstream <フォーク元のURL> # フォーク元のURLをupstreamという名前で登録 一度やればOK
git fetch upstream # upstreamの変更をローカルに持ってくる
git merge upstream/<ブランチ名> # マスターに変更を持ってくる
```

- https://leico.github.io/TechnicalNote/Git/pull-fork-origin

# LICENSE
このソフトウェアパッケージは[MITライセンス](https://github.com/shimotoriharuki/IGC-RTP/blob/master/LICENSE)の下、再頒布および使用が使用が許可されます．
