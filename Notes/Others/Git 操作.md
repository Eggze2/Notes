# Git 操作

#### 文件移动

大多数文件可直接通过GUI操作，但某些文件（如图像）要求从命令行移动它们

1. 使用

   ```
   git status
   ```

   检查旧文件位置和新文件位置

   ```shell
   $ git status
   > # On branch YOUR-BRANCH
   > # Changes not staged for commit:
   > #   (use "git add/rm ..." to update what will be committed)
   > #   (use "git checkout -- ..." to discard changes in working directory)
   > #
   > #     deleted:    /OLD-FOLDER/IMAGE.PNG
   > #
   > # Untracked files:
   > #   (use "git add ..." to include in what will be committed)
   > #
   > #     /NEW-FOLDER/IMAGE.PNG
   > #
   > # no changes added to commit (use "git add" and/or "git commit -a")
   ```

2. 将要提交的文件暂存到本地仓库。 这将从旧位置删除（即

   ```
   git rm
   ```

   ）文件，并将文件添加（即

   ```
   git add
   ```

   ）到新位置

   ```shell
   $ git add .
   # Adds the file to your local repository and stages it for commit.
   # 若要取消暂存文件，请使用“git reset HEAD YOUR-FILE”。
   ```

3. 使用

   ```
   git status
   ```

   检查为提交而暂存的更改

   ```shell
   $ git status
   > # On branch YOUR-BRANCH
   > # Changes to be committed:
   > #   (use "git reset HEAD ..." to unstage)
   > #
   > #    renamed:    /old-folder/image.png -> /new-folder/image.png
   # Displays the changes staged for commit
   ```

4. 提交暂存在本地仓库中的文件

   ```shell
   $ git commit -m "Move file to new directory"
   # Commits the tracked changes and prepares them to be pushed to a remote repository.
   # 要删除此提交并修改文件，请使用 'git reset --soft HEAD~1' 并再次提交和添加文件。
   ```

5. 将本地存储库中的

   更改推送

   到 GitHub.com

   ```shell
   $ git push origin YOUR_BRANCH
   # Pushes the changes in your local repository up to the remote repository you specified as the origin
   ```

#### 重命名文件

1. 将当前工作目录更改为您的本地仓库

2. 重命名文件，指定旧文件名和要为文件提供的新名称。 这将暂存您的提交更改

   ```shell
   $ git mv OLD-FILENAME NEW-FILENAME
   ```

3. 使用

   ```
   git status
   ```

   检查旧文件名和新文件名

   ```shell
   $ git status
   > # On branch YOUR-BRANCH
   > # Changes to be committed:
   > #   (use "git reset HEAD ..." to unstage)
   > #
   > #     renamed: OLD-FILENAME -> NEW-FILENAME
   > #
   ```

4. 提交暂存在本地仓库中的文件

   ```shell
   $ git commit -m "Rename file"
   # Commits the tracked changes and prepares them to be pushed to a remote repository.
   # 要删除此提交并修改文件，请使用 'git reset --soft HEAD~1' 并再次提交和添加文件。
   ```

5. 将本地存储库中的

   更改推送

   到 GitHub.com

   ```shell
   $ git push origin YOUR_BRANCH
   # Pushes the changes in your local repository up to the remote repository you specified as the origin
   ```

#### 更新远程代码到本地仓库

使用Git协同开发时，除了往服务器推送本地的代码也会经常从服务器上拉取代码，在拉取代码的还是除了使用`git pull`推送，还可以使用`git fetch`和`git merge`命令。

使用`git fetch`操作的好处是，`git fetch` 并没更改本地仓库的代码，只是拉取了远程 `commit` 数据，将远程仓库的 `commit id` 更新为`latest`。

- 查看远程仓库

```bash
git remote -v
```

> 默认情况下会有一个`origin`的远程仓库名

- 从远程获取最新版本到本地新建的分支

```bash
git fetch origin master:temp
```

- 比较区别

```bash
git diff temp
```

> 比较本地`master`分支和远程`master`分支的区别

- 合并分支

```bash
git merge temp
```

> 合并`temp`分支到`master`。

- 删除临时分支

```bash
git branch -d temp
```

> 如果该分支没有合并到主分支会报错，可以用命令强制删除`git branch -D <branch_name>`

#### 解决Failed to connect to github.com port 443: Operation timed out

```bash
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy http://127.0.0.1:7890
```

