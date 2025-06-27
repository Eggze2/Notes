# Git 操作

[TOC]

### 用户设置

`git config` 命令用于配置Git的设置，包括用户信息、仓库设置等。Git支持多个配置级别，每个级别对应了不同的范围，以便在不同的上下文中使用。以下是 `git config` 的各个配置级别：

1. **系统级别（System-Level）**:
   这是Git配置的最高级别，通常位于Git安装目录下的全局配置文件。它适用于整个系统中的所有用户，对所有仓库生效。

   设置系统级别的用户名和邮箱：

     ```bash
   git config --system user.name "Your Name"
   git config --system user.email "your.email@example.com"
     ```

   请注意，设置系统级别配置需要管理员权限。

2. **全局级别（Global-Level）**:
   全局级别配置存储在用户的主目录下的 `.gitconfig` 文件中。这些设置适用于当前用户的所有Git仓库。

   设置全局级别的用户名和邮箱：

     ```bash
   git config --global user.name "Your Name"
   git config --global user.email "your.email@example.com"
     ```

3. **仓库级别（Repository-Level）**:
   仓库级别配置存储在特定Git仓库的 `.git/config` 文件中。这些设置仅适用于当前仓库。

   设置仓库级别的用户名和邮箱：

     ```bash
   git config user.name "Your Name"
   git config user.email "your.email@example.com"
     ```

4. **命令行级别（Command-Line-Level）**:
   有时，你可以在命令行中直接使用`--global`或`--system`选项，来设置全局或系统级别的配置。这将覆盖之前的配置。

   例如，设置全局级别的用户名和邮箱：

     ```bash
   git config --global user.name "Your New Name"
   git config --global user.email "new.email@example.com"
     ```

请注意，配置级别具有优先级，高级别的配置会覆盖低级别的配置。如果在仓库级别设置了某个配置项，它将覆盖全局级别或系统级别的相同配置项。

可以使用 `git config --list` 命令来查看当前配置的详细信息，包括所有级别的配置项

___



### 更新远程代码到本地仓库（针对PR）

#### 步骤 1: 配置 `upstream` 远程仓库 (只需要做一次)

当你在本地克隆你自己的 Fork 时，Git 默认只知道一个远程地址，即 `origin`，它指向你在 GitHub/Gitee 上的 Fork。现在你需要添加第二个远程地址，指向你 Fork 来的那个原始项目，我们通常将其命名为 `upstream`。

1. **打开终端或 Git Bash**，并 `cd`到你本地的项目目录中。

2. **查看当前的远程仓库配置**。你会看到只有 `origin`。

   ```Bash
   git remote -v
   # 输出会像这样:
   # origin  git@github.com:YourUsername/TheProject.git (fetch)
   # origin  git@github.com:YourUsername/TheProject.git (push)
   ```

3. **添加 `upstream` 远程仓库**。你需要到原始项目的 GitHub/Gitee 页面上复制它的 URL。

   ```Bash
   # 将 <URL_OF_THE_ORIGINAL_PROJECT> 替换成原始项目的URL
   git remote add upstream <URL_OF_THE_ORIGINAL_PROJECT>
   ```

   例如: `git remote add upstream https://github.com/OriginalOwner/TheProject.git`

4. **再次验证配置**。现在你应该能同时看到 `origin` 和 `upstream`。

   ```Bash
   git remote -v
   # 输出会像这样:
   # origin    git@github.com:YourUsername/TheProject.git (fetch)
   # origin    git@github.com:YourUsername/TheProject.git (push)
   # upstream  https://github.com/OriginalOwner/TheProject.git (fetch)
   # upstream  https://github.com/OriginalOwner/TheProject.git (push)
   ```

   一次性设置已经完成。



#### 步骤 2: 获取 `upstream` 的更新并同步 (每次开始新工作前都应执行)

在你准备开始新的修改之前，这是一个**必须执行的黄金准则**，以确保你的工作是基于最新代码的。

1. 从 upstream 拉取最新的分支和提交记录。

   fetch 命令会将数据下载到你本地，但不会自动合并或修改你当前的工作。

   ```Bash
   git fetch upstream
   ```

2. **切换到你本地的主分支** (通常是 `main` 或 `master`)。

   ```Bash
   git checkout main
   ```

3. 将 upstream 的主分支合并到你本地的主分支。

   这一步将你本地的 main 分支更新到和原始项目一模一样的最新状态。

   ```Bash
   git merge upstream/main
   ```

4. 将更新后的本地主分支推送到你的 Fork (origin)。

   现在，你本地的 main 分支是新的了，你需要把它推送到 GitHub/Gitee 上你自己的 Fork，使其也保持最新。

   ```Bash
   git push origin main
   ```

   做完这一步，你 GitHub 上的 Fork 就和原始项目完全同步了！

___



#### 继续提交新修改的完整流程

下一次贡献的完整、规范的流程应该是这样的：

1. **同步 Fork**：完整执行上面**“步骤 2”**的所有操作，确保你的 `main` 分支是最新的。

2. **创建新分支**：从你刚刚更新过的 `main` 分支上，创建一个新的、有描述性的分支来存放你的新修改。

   ```Bash
   # 确保你当前在 main 分支上
   git checkout main
   
   # 创建并切换到新分支
   git checkout -b fix-some-bug-or-add-feature
   ```

3. **进行修改和提交**：在这个新分支上，修改代码、添加文件，然后进行提交。

   ```Bash
   # ... 进行你的代码修改 ...
   git add .
   git commit -m "feat: Add an amazing new feature"
   ```

4. **推送到你的 Fork**：将你的新分支推送到 `origin`（你的 Fork）。

   ```Bash
   git push origin fix-some-bug-or-add-feature
   ```

5. **创建新的 Pull Request**：去你 GitHub/Gitee 的 Fork 页面，你将看到一个黄色的提示条，引导你从 `fix-some-bug-or-add-feature` 分支向 `upstream` 项目的 `main` 分支发起一个新的 PR。

___



### 解决Failed to connect to github.com port 443: Operation timed out

```bash
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy https://127.0.0.1:7890
```

___

